/******************************************************************************
 * Copyright 2023 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/******************************************************************************
 * @file multisf_component.cc
 *****************************************************************************/

#include "modules/localization/multisf/multisf_component.h"
#include "modules/localization/common/localization_gflags.h"
#include "modules/common/math/quaternion.h"
#include "modules/common/adapters/adapter_gflags.h"
#include "modules/localization/msf/common/util/frame_transform.h"
#include "modules/localization/FAST_LIO/src/laserMapping.h"
#include "cyber/common/file.h"

namespace apollo {
namespace multimsflocalization {

void Multisf::listFilesWithExtension(const std::string& path, const std::string& extension) {
    struct dirent* entry;
    DIR* dir = opendir(path.c_str());

    if (dir == nullptr) {
        std::cerr << "Could not open directory: " << path << std::endl;
        return;
    }

    while ((entry = readdir(dir)) != nullptr) {
        // 忽略 "." 和 ".."
        if (entry->d_name[0] != '.') {
            std::string filename(entry->d_name);
            if (filename.size() >= extension.size() && 
                filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0) {
                std::cout << filename << std::endl;
            }
        }
    }
    closedir(dir);
}
bool Multisf::Init() {
    ACHECK(ComponentBase::GetProtoConfig(&config_))
            << "failed to load multisf config file " << ComponentBase::ConfigFilePath();

    AINFO << "Load config succedded.\n" << config_.DebugString();
    //lidar config path
    std::string path1="modules/localization/msf/params/velodyne_params/velodyne64_novatel_extrinsics_example.yaml";
    std::string config_file_lidar;
    if(!apollo::cyber::common::GetFilePathWithEnv(path1,
        "APOLLO_CONF_PATH", &config_file_lidar)){
        AERROR << path1 << " No such yaml";
        return false;
    }
    // // 加载雷达外参
    // std::string path_lidar_config = "/apollo_workspace/modules/localization/msf/params/velodyne_params/velodyne64_novatel_extrinsics_example.yaml";
    std::cout<<"config_file_lidar :" <<config_file_lidar<<std::endl;
    LoadLidarExtrinsic(config_file_lidar,&lidar_extrinsic);
    // 激光里程计参数初始化
    LidarInit();
    eskf_flow.lidar_extrinsic = lidar_extrinsic;
    std::cout << "eskf_flow.lidar_extrinsic Transformation Matrix:\n" << eskf_flow.lidar_extrinsic.matrix() << std::endl;

    // 初始化vgicp参数
    eskf_flow.vgicp.setResolution(1.0);
    eskf_flow.vgicp.setNumThreads(6);
    // 设置体素大小（边长）
    float voxel_size = 0.5f;
    eskf_flow.voxel_filter.setLeafSize(voxel_size, voxel_size, voxel_size);
    eskf_flow.sor.setMeanK(10); // 用于统计的邻域点数量
    eskf_flow.sor.setStddevMulThresh(1.0); // 标准差阈值
    InitIo();

    std::string path_eskf="modules/localization/multisf/conf/config.yaml";
    std::string config_file_eskf;
    if(!apollo::cyber::common::GetFilePathWithEnv(path_eskf,
        "APOLLO_CONF_PATH", &config_file_eskf)){
        AERROR << config_file_eskf << " No such yaml";
        return false;
    }
    eskf_flow.config_parameters_.LoadParameters(config_file_eskf);
    eskf_flow.eskf_ptr_ = std::make_shared<ErrorStateKalmanFilter>(eskf_flow.config_parameters_);
    
    if(eskf_flow.save_key_){
        eskf_flow.eskf_pose_file.open("/apollo_workspace/data/apollo_data/frames/eskf_pose.txt", std::ios::out);
        gnss_pose_file.open("/apollo_workspace/data/apollo_data/frames/gnss_pose.txt", std::ios::out);
        eskf_flow.lidar_pose_file.open("/apollo_workspace/data/apollo_data/frames/lidar_pose.txt", std::ios::out);
    // imu_pose_file.open("/apollo_workspace/data/testpose/imu_pose.txt", std::ios::out | std::ios::trunc);
    // gnss_status_file.open("/apollo_workspace/data/testpose/gnss_status.txt", std::ios::out | std::ios::trunc);
    // ndt_pose_file.open("/apollo_workspace/data/testpose/ndt_pose.txt", std::ios::out | std::ios::trunc);
    }
    eskf_flow.last_imu_.time = 0.0;
   //定时循环
    localization_timer_.reset(new cyber::Timer(10, [this]() { this->OnLocalizationTimer(); }, false));
    localization_timer_->Start();

    localization_timer1_.reset(new cyber::Timer(10, [this]() { this->OnLocalizationTimerLidar(); }, false));
    localization_timer1_->Start();


    std::cout << "Init Multisf succedded."<<std::endl;
    return true;
}
void Multisf::OnLocalizationTimerLidar(){
    LidarOdometryCM(eskf_flow.lio_q_,eskf_flow.lio_pose_glob_,eskf_flow.lio_time_);
    std::cout<<"eskf_flow.lio_q_ :"<<eskf_flow.lio_q_.x()<<" "<<eskf_flow.lio_q_.y()<<" "<<eskf_flow.lio_q_.z()<<" "<<eskf_flow.lio_q_.w()
              <<" eskf_flow.lio_pose_glob_:"<<eskf_flow.lio_pose_glob_[0]<<" "<<eskf_flow.lio_pose_glob_[1]<<" "<<eskf_flow.lio_pose_glob_[2]
              <<" time :"<<eskf_flow.lio_time_<<std::endl;
             
}
void Multisf::OnLocalizationTimer(){
    std::mutex mtxgetpose; // 互斥锁
    std::lock_guard<std::mutex> lock(mtxgetpose); // 锁定互斥锁
    if(imutime < imu_data_.time){
       if(eskf_flow.Run(imu_data_)){
          std::cout<<number_++<<"done run eskf!"<<std::endl;
       }
    }  
    if(eskf_flow.is_init){
        Eigen::Affine3d eskf_pose(eskf_flow.eskf_ptr_->GetPose());
        // 拿当前gnss的速度当当前位置的速度
        PublishPoseBroadcastTopic(eskf_pose,imu_data_.time);
        // std::cout<<number_++<<"done PublishPoseBroadcastTopic!"<<std::endl;
    }
    imutime = imu_data_.time;
} 

void Multisf::MsgtoPclCloud(const std::shared_ptr<apollo::drivers::PointCloud>&msg,pcl::PointCloud<pcl::PointXYZINormal>::Ptr cloud) {
  // 分别对每个点云进行处理
  // std::cout<<"start cloud msg to PointXYZINormal cloud !"<<std::endl;
  cloud->width = int(msg->width() / 3) - 2;
  cloud->height = msg->height();
  cloud->is_dense = false;
  cloud->points.resize(cloud->width * cloud->height);
  #pragma omp parallel for num_threads(4) schedule(guided, 8)
  for (uint i = 1; i < cloud->width;i++)
  {
      cloud->points[i].x = msg->point(3 * i).x();                                    // 点云x轴坐标
      cloud->points[i].y = msg->point(3 * i).y();                                    // 点云y轴坐标
      cloud->points[i].z = msg->point(3 * i).z();                                    // 点云z轴坐标
      cloud->points[i].intensity = msg->point(i).intensity();                 // 点云强度
      float pointtime = msg->point(i).timestamp()/1000000000.0 - msg->header().timestamp_sec();
      cloud->points[i].curvature = pointtime; // use curvature as time of each laser points
      // std::cout<<"pointtime : "<<pointtime<<" cloud->points[i].curvature: "<<cloud->points[i].curvature<<std::endl;
  }
//   std::cout<<"end cloud msg to PointXYZINormal cloud !"<<std::endl;
//   std::string path = "/apollo_workspace/data/zhongche/PCD/source/" + std::to_string(msg->header().timestamp_sec()) + ".pcd";
//   pcl::io::savePCDFileBinary(path,*cloud);
}

bool Multisf::Proc(const std::shared_ptr<drivers::gnss::Imu>& Imu_msg) {

    std::mutex mtx_imu_msg; // 创建一个互斥锁
    std::lock_guard<std::mutex> lock(mtx_imu_msg); // 加锁
    if (!Imu_msg) {
        return false;
    } else {
        std::cout<<"callback imu"<<std::endl;
        imu_data_.time = Imu_msg->header().timestamp_sec();
        imu_data_.linear_accel.x() = -Imu_msg->linear_acceleration().y();
        imu_data_.linear_accel.y() = Imu_msg->linear_acceleration().x();
        imu_data_.linear_accel.z() = 0;

        imu_data_.true_linear_accel.x() = -Imu_msg->linear_acceleration().y();
        imu_data_.true_linear_accel.y() = Imu_msg->linear_acceleration().x();
        imu_data_.true_linear_accel.z() = 0;
        imu_data_.angle_velocity.x() = -Imu_msg->angular_velocity().y();
        imu_data_.angle_velocity.y() = Imu_msg->angular_velocity().x();
        imu_data_.angle_velocity.z() = 0;

        imu_data_.angle_velocity.x() = -Imu_msg->angular_velocity().y();
        imu_data_.angle_velocity.y() = Imu_msg->angular_velocity().x();
        imu_data_.angle_velocity.z() = 0;
        // 获得imu数据
        imu_cbk(Imu_msg);
        // eskf_flow.imu_pose_queue_.push_back(imu_data);
        // if(eskf_flow.Run(imu_data)){
            // auto t4 = std::chrono::high_resolution_clock::now();
            // double reg = std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() / 1e6;
            // std::cout << "eskf time : " << reg << "[msec] " << std::flush<<std::endl;
            // if(eskf_flow.is_init){
            //     Eigen::Affine3d eskf_pose(eskf_flow.eskf_ptr_->GetPose());
            //     // 拿当前gnss的速度当当前位置的速度
            //     PublishPoseBroadcastTopic(eskf_pose,imu_data.time);
            // }
            // auto t5 = std::chrono::high_resolution_clock::now();
            // double reg1 = std::chrono::duration_cast<std::chrono::nanoseconds>(t5 - t3).count() / 1e6;
            // std::cout << "pub time : " << reg1 << "[msec] " << std::flush<<std::endl;
        // }
    }

    // // 创建一个单位矩阵
    // Eigen::Affine3d transform = Eigen::Affine3d::Identity();
    // PublishPoseBroadcastTopic(transform,123456678.983657);
    return true;
}
void Multisf::InitIo() {
    LidarPoseSuber();
    LidarPub();

}
void Multisf::PublishPoseBroadcastTopic(const Eigen::Affine3d& pose,const double& time) {
    // std::cout<<"publish /apollo/localization/pose"<<std::endl;
    localization::LocalizationEstimate localization;

    double timestamp = apollo::cyber::Clock::NowInSeconds();
    std::string name = "multisf";
    localization.mutable_header()->set_module_name(name);
    localization.mutable_header()->set_timestamp_sec(timestamp);
    localization.mutable_header()->set_sequence_num(++localization_seq_num_);

    localization.set_measurement_time(time);
    // std::cout<<"pub time :"<<time<<std::endl;
    auto mutable_pose = localization.mutable_pose();
    mutable_pose->mutable_position()->set_x(pose.translation().x());
    mutable_pose->mutable_position()->set_y(pose.translation().y());
    mutable_pose->mutable_position()->set_z(pose.translation().z());

    Eigen::Quaterniond quat(pose.linear());
    mutable_pose->mutable_orientation()->set_qw(quat.w());
    mutable_pose->mutable_orientation()->set_qx(quat.x());
    mutable_pose->mutable_orientation()->set_qy(quat.y());
    mutable_pose->mutable_orientation()->set_qz(quat.z());
    double heading =
        common::math::QuaternionToHeading(quat.w(), quat.x(), quat.y(), quat.z());
    mutable_pose->set_heading(heading);

    common::math::EulerAnglesZXYd euler(quat.w(), quat.x(), quat.y(), quat.z());
    mutable_pose->mutable_euler_angles()->set_x(euler.pitch());
    mutable_pose->mutable_euler_angles()->set_y(euler.roll());
    mutable_pose->mutable_euler_angles()->set_z(euler.yaw());

    // const auto& odometry_pose = gnss_odometry_->localization();
    // mutable_pose->mutable_linear_velocity()->CopyFrom(odometry_pose.linear_velocity());
    // mutable_pose->mutable_linear_acceleration()->CopyFrom(odometry_pose.linear_acceleration());
    // mutable_pose->mutable_angular_velocity()->CopyFrom(odometry_pose.angular_velocity());
    // mutable_pose->mutable_linear_acceleration_vrf()->CopyFrom(odometry_pose.linear_acceleration_vrf());
    // mutable_pose->mutable_angular_velocity_vrf()->CopyFrom(odometry_pose.angular_velocity_vrf());
    localization_talker_->Write(localization);
}
bool Multisf::LoadLidarExtrinsic(const std::string& file_path,Eigen::Affine3d* lidar_extrinsic) {
  CHECK_NOTNULL(lidar_extrinsic);
  YAML::Node config = YAML::LoadFile(file_path);
  if (config["transform"]) {
    if (config["transform"]["translation"]) {
      lidar_extrinsic->translation()(0) =
          config["transform"]["translation"]["x"].as<double>();
      lidar_extrinsic->translation()(1) =
          config["transform"]["translation"]["y"].as<double>();
      lidar_extrinsic->translation()(2) =
          config["transform"]["translation"]["z"].as<double>();
      if (config["transform"]["rotation"]) {
        double qx = config["transform"]["rotation"]["x"].as<double>();
        double qy = config["transform"]["rotation"]["y"].as<double>();
        double qz = config["transform"]["rotation"]["z"].as<double>();
        double qw = config["transform"]["rotation"]["w"].as<double>();
        lidar_extrinsic->linear() =
            Eigen::Quaterniond(qw, qx, qy, qz).toRotationMatrix();
        return true;
      }
    }
  }
  return false;
}
void Multisf::OdometryCallback(const std::shared_ptr<localization::Gps>& gnss_odometry_msg) {
        std::cout<<"callback gnss"<<std::endl;
        std::unique_lock<std::mutex> lock(mutex_gnss_odometry_queue_);  // 加锁
        eskf_flow.gnss_odometry_queue_.push_back(gnss_odometry_msg);
        eskf_flow.gnss_lidar_queue_.push_back(gnss_odometry_msg);
        std::shared_ptr<GnssData> gnss_data(new GnssData);
        gnss_data->gnsstime = gnss_odometry_msg->header().timestamp_sec();
        gnss_data->position[0] = gnss_odometry_msg->localization().position().x(),
        gnss_data->position[1] = gnss_odometry_msg->localization().position().y(),
        gnss_data->position[2] = gnss_odometry_msg->localization().position().z();
        gnss_data->linear_velocity[0] = gnss_odometry_msg->localization().linear_velocity().x();
        gnss_data->linear_velocity[1] = gnss_odometry_msg->localization().linear_velocity().y();
        gnss_data->linear_velocity[2] = gnss_odometry_msg->localization().linear_velocity().z();
        gnss_data->q.x() = gnss_odometry_msg->localization().orientation().qx();
        gnss_data->q.y() = gnss_odometry_msg->localization().orientation().qy();
        gnss_data->q.z() = gnss_odometry_msg->localization().orientation().qz();
        gnss_data->q.w() = gnss_odometry_msg->localization().orientation().qw();
        gnss_data->key = false;
        Gnss_cbk(gnss_data);
        eskf_flow.gnss_odometry_last_ = gnss_odometry_msg;
        if(eskf_flow.save_key_){
            gnss_pose_file<<std::setprecision(18)<<gnss_odometry_msg->localization().position().x()
            <<" "<<gnss_odometry_msg->localization().position().y()
            <<" "<<gnss_odometry_msg->localization().position().z()
            <<" "<<gnss_odometry_msg->header().timestamp_sec()<<std::endl;
        }
    gnssframedown_++;

}
// void Multisf::OdometryGNssStatusCallback(const std::shared_ptr<drivers::gnss::InsStat>& odometry_status_msg) {
//     int status = int(odometry_status_msg->ins_status());
//     if(status == 2){
//         if(LoadMapInAdvance(gnss_odometry_)){
//             std::cout<<"加载地图成功！"<<std::endl;
//         }
//     }
// }
void Multisf::LidarCallback(const std::shared_ptr<drivers::PointCloud>& lidar_msg) {
    // std::cout << "lidar message recieved !" << std::endl;
    std::unique_lock<std::mutex> lock(mutex_gnss_lidar_queue_);  // 加锁
    pcl::PointCloud<pcl::PointXYZINormal>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZINormal>);
    MsgtoPclCloud(lidar_msg,cloud);
    standard_pcl_cbk(cloud,lidar_msg->header().timestamp_sec());
}

void Multisf::LidarPub(){
    localization_talker_ =
      node_->CreateWriter<localization::LocalizationEstimate>("/apollo/localization/pose");
}
void Multisf::LidarPoseSuber() {
    auto LidarPoseListener_node = apollo::cyber::CreateNode("listener");
    reader_config.channel_name = "/apollo/sensor/rslidar/PointCloud2";
    std::cout << "lidar_topic:" << reader_config.channel_name << std::endl;
    reader_config.pending_queue_size = 1;

    reader_odometry_config.channel_name = "/apollo/sensor/gnss/odometry";
    bestgnsspos_config.channel_name = "/apollo/sensor/gnss/best_pose";
    ndtpos_config.channel_name = "/apollo/localization/ndt_lidar";
    vechileheading_config.channel_name = "/apollo/sensor/gnss/heading";

    // 创建lidar cloud 监听响应进行消息读取
    std::function<void(const std::shared_ptr<drivers::PointCloud>&)> lidar_register_call
            = std::bind(&Multisf::LidarCallback, this, std::placeholders::_1);
    lidar_listener_ = this->node_->CreateReader<drivers::PointCloud>(reader_config, lidar_register_call);

    // // 创建odometry 监听响应进行消息读取
    std::function<void(const std::shared_ptr<localization::Gps>&)> odometry_call
            = std::bind(&Multisf::OdometryCallback, this, std::placeholders::_1);
    odometry_listener_ = this->node_->CreateReader<localization::Gps>("/apollo/sensor/gnss/odometry", odometry_call);

    // // 创建  gnss pose status监听响应进行消息读取
    // std::function<void(const std::shared_ptr<drivers::gnss::InsStat>&)> odometry_status_call
    //         = std::bind(&Multisf::OdometryGNssStatusCallback, this, std::placeholders::_1);
    // odometry_status_listener_
    //         = this->node_->CreateReader<drivers::gnss::InsStat>("/apollo/sensor/gnss/ins_stat", odometry_status_call);

    // corrected_imu_listener_ = node_->CreateReader<localization::CorrectedImu>(
    //         "/apollo/sensor/gnss/corrected_imu", std::bind(&Multisf::ImuCallback, this, std::placeholders::_1));

    // // 创建best gnss pos 监听响应进行消息读取
    // std::function<void(const std::shared_ptr<drivers::gnss::GnssBestPose>&)> bestgnsspos_register_call
    //         = std::bind(&Multisf::OnGnssBestPoseCallback, this, std::placeholders::_1);
    // bestgnsspos_listener_
    //         = this->node_->CreateReader<drivers::gnss::GnssBestPose>(bestgnsspos_config,
    //         bestgnsspos_register_call);

    // // Vechicle heading监听响应进行消息读取
    // std::function<void(const std::shared_ptr<drivers::gnss::Heading>&)> vechicle_heading_call
    //         = std::bind(&Multisf::VechicleHeadingCallback, this, std::placeholders::_1);
    // vehicle_heading_listener_
    //         = this->node_->CreateReader<drivers::gnss::Heading>(vechileheading_config, vechicle_heading_call);
}
}  // namespace multimsflocalization
}  // namespace apollo