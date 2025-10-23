/*
   Created by wkx 2025.8.20
*/
#include "config_parameters.h"
#include "eskf_flow.h"
#include "common_tool.h"

#include <iomanip>
#include <fstream>
#include <utility>
#include <yaml-cpp/yaml.h>

// #include <g2o/core/base_vertex.h>
// #include <g2o/core/base_unary_edge.h>
// #include <g2o/core/block_solver.h>
// #include <g2o/core/optimization_algorithm_levenberg.h>
// #include <g2o/core/optimization_algorithm_gauss_newton.h>
// #include <g2o/solvers/dense/linear_solver_dense.h>
ESKFFlow::ESKFFlow() {}
void ESKFFlow::transformPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Matrix4d& transform) {
    for (auto& point : cloud->points) {
        Eigen::Vector4d p(point.x, point.y, point.z, 1.0); // 将点转换为齐次坐标
        Eigen::Vector4d p_transformed = transform * p; // 应用变换
        point.x = p_transformed(0);
        point.y = p_transformed(1);
        point.z = p_transformed(2);
    }
}
void ESKFFlow::transformPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Affine3d& transform) {
    for (auto& point : cloud->points) {
        Eigen::Vector3d p(point.x, point.y, point.z); // 将点转换为 3D 向量
        Eigen::Vector3d p_transformed = transform * p; // 应用变换
        point.x = p_transformed(0);
        point.y = p_transformed(1);
        point.z = p_transformed(2);
    }
}
void ESKFFlow::WritePcdFile(const std::shared_ptr<apollo::drivers::PointCloud>&msg,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
  cloud->width = msg->width();
  cloud->height = msg->height();
  cloud->is_dense = false;
  cloud->points.resize(cloud->width * cloud->height);
  if (cloud->width == 0 || cloud->height == 0) {
    cloud->width = 1;
    cloud->height = msg->point_size();
    cloud->points.resize(msg->point_size());
  }
  for (unsigned int i = 0; i < static_cast<unsigned int>(cloud->points.size());++i) {
    cloud->points[i].x = msg->point(i).x();
    cloud->points[i].y = msg->point(i).y();
    cloud->points[i].z = msg->point(i).z();
    // cloud.points[i].intensity =
    //     static_cast<unsigned char>(msg.point(i).intensity());
  }
//   pcl::io::savePCDFileBinaryCompressed(filename, cloud);
}

// eskf 初始化
bool ESKFFlow::EskfInitEskf(const IMUData imu_data) {
   
   double time_ = gnss_odometry_last_->header().timestamp_sec() - imu_data.time;
   if(time_ < 0.1 && time_ > -1*0.1){
        GPSData curr_gps_data_;
        std::cout << "使用了gnss进行init" << std::endl;
        std::mutex mutex_;                          // 互斥量
        std::unique_lock<std::mutex> lock(mutex_);  // 加锁
        curr_gps_data_.time = gnss_odometry_last_->header().timestamp_sec();
        curr_gps_data_.position_lla.x() = gnss_odometry_last_->localization().position().x(),
        curr_gps_data_.position_lla.y() = gnss_odometry_last_->localization().position().y(),
        curr_gps_data_.position_lla.z() = gnss_odometry_last_->localization().position().z();

        curr_gps_data_.local_position_ned.x() = gnss_odometry_last_->localization().position().x(),
        curr_gps_data_.local_position_ned.y() = gnss_odometry_last_->localization().position().y(),
        curr_gps_data_.local_position_ned.z() = gnss_odometry_last_->localization().position().z();

        curr_gps_data_.velocity.x() = gnss_odometry_last_->localization().linear_velocity().x();
        curr_gps_data_.velocity.y() = gnss_odometry_last_->localization().linear_velocity().y();
        curr_gps_data_.velocity.z() = gnss_odometry_last_->localization().linear_velocity().z();

        curr_gps_data_.true_velocity.x() = gnss_odometry_last_->localization().linear_velocity().x();
        curr_gps_data_.true_velocity.y() = gnss_odometry_last_->localization().linear_velocity().y();
        curr_gps_data_.true_velocity.z() = gnss_odometry_last_->localization().linear_velocity().z();
        Eigen::Quaterniond quat(gnss_odometry_last_->localization().orientation().qw(), 
                                gnss_odometry_last_->localization().orientation().qx(), 
                                gnss_odometry_last_->localization().orientation().qy(),
                                gnss_odometry_last_->localization().orientation().qz());
        std::cout << "eskf init imu time:" << imu_data.time<<" gnss time :"<<curr_gps_data_.time
                  << " dev:" << curr_gps_data_.time - imu_data.time << std::endl;
        eskf_ptr_->Init(curr_gps_data_,imu_data,quat);
        is_init = true;
        init_gps_data_ = curr_gps_data_;
        std::cout << "完成gnss 初始化！" << std::endl;
        last_imu_time_ = imu_data.time;
        return true;
    }else {
        std::cout << "需要等待初始化数据！" << std::endl;
        return false;
    }
}

//通过定时方式的融合
bool ESKFFlow::Run(const IMUData imu_data){
    // 判断是否进行了初始化
    std::cout<<"is_init : "<<is_init<<std::endl;
    if (!is_init) {
        is_init = EskfInitEskf(imu_data);
        return false;
    }
    if(last_imu_time_ >= imu_data.time){
       return false;
    }
    last_imu_time_ = imu_data.time;
    // IMU进行预测
    // auto t3 = std::chrono::high_resolution_clock::now();
    std::cout<<"start eskf ,eskf_ptr_->Predict"<<std::endl;
    eskf_ptr_->Predict(imu_data);
    std::cout<<"done eskf ,eskf_ptr_->Predict"<<std::endl;
    //判断激光雷达的里程计是否需要融合
    std::cout<<"imu time:"<<imu_data.time<<"  gnss time : "<<gnss_odometry_last_->header().timestamp_sec()<<" lio time : "<<lio_time_<<std::endl;
    double time_ = gnss_odometry_last_->header().timestamp_sec() - imu_data.time;
    if(time_ > 0.1 || time_ < -1*0.1){
        return false;
    }
    if(gnss_time_ >= gnss_odometry_last_->header().timestamp_sec())
    {
        return false;
    }

    if(abs(lio_time_ - imu_data.time) < 0.05 && lio_time_last_ < lio_time_){
        double devx = eskf_ptr_->GetPose()(0,3) - lio_pose_glob_[0];
        double devy = eskf_ptr_->GetPose()(1,3) - lio_pose_glob_[1];
        double devz = eskf_ptr_->GetPose()(2,3) - lio_pose_glob_[2];
        double dev_distance = std::sqrt(devx*devx + devy*devy + devz*devz);
        std::cout<<"eskf_ptr_->GetPose-lio_pose_glob_ : "<<devx<<" "<<devy<<" "<<devz<<std::endl;
        if(dev_distance < 0.15){
            GPSData lio_data;
            lio_data.time = gnss_odometry_last_->header().timestamp_sec();

            lio_data.local_position_ned.x() = lio_pose_glob_[0];
            lio_data.local_position_ned.y() = lio_pose_glob_[1];
            lio_data.local_position_ned.z() = lio_pose_glob_[2];
            eskf_ptr_->Correct(lio_data,lio_q_);
            lio_time_last_ = lio_time_;
        }
    }
    std::cout<<"start lidar fusion !"<<std::endl;
    std::lock_guard<std::mutex> lock(mtxgetpose); // 锁定互斥锁
    // auto t0 = std::chrono::high_resolution_clock::now();
    GPSData curr_gps_data_;
    curr_gps_data_.time = gnss_odometry_last_->header().timestamp_sec();
    // curr_gps_data_.position_lla.x() = gnss_odometry_queue_.front()->localization().position().x(),
    // curr_gps_data_.position_lla.y() = gnss_odometry_queue_.front()->localization().position().y(),
    // curr_gps_data_.position_lla.z() = gnss_odometry_queue_.front()->localization().position().z();

    curr_gps_data_.local_position_ned.x() = gnss_odometry_last_->localization().position().x(),
    curr_gps_data_.local_position_ned.y() = gnss_odometry_last_->localization().position().y(),
    curr_gps_data_.local_position_ned.z() = gnss_odometry_last_->localization().position().z();

    curr_gps_data_.velocity.x() = gnss_odometry_last_->localization().linear_velocity().x();
    curr_gps_data_.velocity.y() = gnss_odometry_last_->localization().linear_velocity().y();
    curr_gps_data_.velocity.z() = gnss_odometry_last_->localization().linear_velocity().z();

    curr_gps_data_.true_velocity.x() = gnss_odometry_last_->localization().linear_velocity().x();
    curr_gps_data_.true_velocity.y() = gnss_odometry_last_->localization().linear_velocity().y();
    curr_gps_data_.true_velocity.z() = gnss_odometry_last_->localization().linear_velocity().z();
    Eigen::Quaterniond quat(gnss_odometry_last_->localization().orientation().qw(), 
                            gnss_odometry_last_->localization().orientation().qx(), 
                            gnss_odometry_last_->localization().orientation().qy(),
                            gnss_odometry_last_->localization().orientation().qz());
    std::cout<<"start eskf ,eskf_ptr_->Correct"<<std::endl;
    eskf_ptr_->CorrectPoseQVel(curr_gps_data_,quat);
    gnss_init_q_ = quat;
    gnss_init_pose_ = curr_gps_data_.local_position_ned;
    std::cout<<"done eskf ,eskf_ptr_->Correct"<<std::endl;
    if(save_key_){
        eskf_pose_file<<std::setprecision(18)<<eskf_ptr_->GetPose()(0,3)
                        <<" "<<eskf_ptr_->GetPose()(1,3)
                        <<" "<<eskf_ptr_->GetPose()(2,3)
                        <<" "<<eskf_ptr_->GetVelocity()[0]
                        <<" "<<eskf_ptr_->GetVelocity()[1]
                        <<" "<<eskf_ptr_->GetVelocity()[2]
                        <<" "<<curr_gps_data_.time<<" gnss"<<std::endl;
    }
    gnss_time_ = gnss_odometry_last_->header().timestamp_sec();
    double devx = eskf_ptr_->GetPose()(0,3) - curr_gps_data_.local_position_ned.x();
    double devy = eskf_ptr_->GetPose()(1,3) - curr_gps_data_.local_position_ned.y();
    double devz = eskf_ptr_->GetPose()(2,3) - curr_gps_data_.local_position_ned.z();
    std::cout<<std::setprecision(19)<<"eskf - gnss : "<<devx<<" "<<devy<<" "<<devz<<std::endl;
    return true;
}

// 做激光里程计的融合
bool ESKFFlow::RunLidarFusion(const std::shared_ptr<apollo::drivers::PointCloud>& lidar_msg){
    double lidar_pose_time = lidar_msg->header().timestamp_sec();
    if (!is_init) {
        return false;
    }
    if (lidar_pose_time == 0) {
        return false;
    }
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    WritePcdFile(lidar_msg,cloud);
    Eigen::Affine3d odometry_gnss_lidar;
    Eigen::Affine3d odometry_lidar_init_pose;
    Eigen::Affine3d odometry_eskf;
    std::lock_guard<std::mutex> lock(mtxgetpose); // 锁定互斥锁
    Eigen::Matrix4d cloud_odometry_result = eskf_ptr_->GetPose();
    odometry_lidar_init_pose = Eigen::Affine3d(cloud_odometry_result);
    odometry_eskf = Eigen::Affine3d(cloud_odometry_result);
    // 进行点云帧与地图匹配
    bool lidar_pose_key = LidarHDMapPoseCompute(cloud,lidar_pose_time,odometry_lidar_init_pose);
    if(lidar_pose_key){
        // lidar_poses_ = odometry_lidar_init_pose;                    //将计算的激光里程计保存进缓存
        lidar_poses_time_ = lidar_pose_time;             //保存对应的激光里程计时间
        lidar_poses_by_eskf_pose_ = odometry_lidar_init_pose * odometry_eskf.inverse();
        std::cout<<"lidar_poses_by_eskf_pose_.translation: "
        <<lidar_poses_by_eskf_pose_.translation().x()<<" "
        <<lidar_poses_by_eskf_pose_.translation().y()<<" "
        <<lidar_poses_by_eskf_pose_.translation().z()
        <<" odometry_lidar_init_pose.translation: "
        <<odometry_lidar_init_pose.translation().x()<<" "
        <<odometry_lidar_init_pose.translation().y()<<" "
        <<odometry_lidar_init_pose.translation().z()
        <<" odometry_eskf.translation: "
        <<odometry_eskf.translation().x()<<" "
        <<odometry_eskf.translation().y()<<" "
        <<odometry_eskf.translation().z()<<" "
        <<std::endl;
        return true;
    }

    return false;
}

bool ESKFFlow::LidarHDMapPoseCompute(const pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,const double lidar_pose_time,
                                                Eigen::Affine3d&fusion_result){
    pcl::PointCloud<pcl::PointXYZ>::Ptr aligned(new pcl::PointCloud<pcl::PointXYZ>);
    //根据当前预测的pose，计算该帧点云属于grid的哪个索引
    Eigen::Vector3d translation = fusion_result.translation();
    double px = translation.x() - umap_config_[-1][0];
    double py = translation.y() - umap_config_[-1][1];
    translation.x() -= umap_config_[-1][0];
    translation.y() -= umap_config_[-1][1];
    translation.z() -= umap_config_[-1][2];
    fusion_result.translation() = translation;
    std::cout<<"fusion_result.translation: "<<fusion_result.translation()<<std::endl;
    int div_x = umap_config_[-2][0];
    int div_y = umap_config_[-2][1];
    int idx = static_cast<int>(floor((px - static_cast<float>(umap_config_[-3][0])) / 90));
    int idy = static_cast<int>(floor((py - static_cast<float>(umap_config_[-3][2])) / 90));
    int id = idy * div_x + idx;
    std::cout<<"id :"<<id<<std::endl;
    std::lock_guard<std::mutex> lock(mtx_map_); // 锁定互斥锁
    if(umap_covariances_.find(id) != umap_covariances_.end()){
        if(umap_cloud_[id]->size() < 10000){
            std::cout<<"id : "<<id<<"  地图点云数量太少"<<umap_cloud_[id]->size()<<std::endl;
            return false;
        }
        // 根据激光雷达外参对点云进行旋转平移
        transformPointCloud(source_cloud,lidar_extrinsic);
        std::string path_save = "/apollo_workspace/data/apollo_data/frames/" + std::to_string(id) + "_" + std::to_string(lidar_pose_time) + ".pcd";
        //通过gnss的位姿对点云进行转换
        transformPointCloud(source_cloud,fusion_result);
        voxel_filter.setInputCloud(source_cloud); // 设置输入点云
        // 创建输出点云
        pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
        // 执行体素滤波
        voxel_filter.filter(*filtered_cloud);
        sor.setInputCloud(filtered_cloud);
        // 创建最终输出点云
        pcl::PointCloud<pcl::PointXYZ>::Ptr final_filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
        // 执行条件过滤
        sor.filter(*final_filtered_cloud);
        pcl::io::savePCDFileBinary(path_save,*final_filtered_cloud);
        std::cout<<"path_save:"<<path_save<<std::endl;
        auto t3 = std::chrono::high_resolution_clock::now();
        vgicp.clearTarget();
        vgicp.clearSource();
        vgicp.setInputTarget(umap_cloud_[id]);
        vgicp.setInputSource(final_filtered_cloud);
        vgicp.InPutCovariances(umap_covariances_[id]);
        std::cout<<"InPutCovariances done : covariances"<<std::endl;
        vgicp.align(*aligned);
        Eigen::Matrix4f final_transformation;
        vgicp.getFinal_transformation(final_transformation);
        Eigen::Affine3d Tvgic_result = Eigen::Affine3d(final_transformation.cast<double>());
        auto t4 = std::chrono::high_resolution_clock::now();
        double reg = std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() / 1e6;
        std::cout << "vgicp time : " << reg << "[msec] " << std::flush<<std::endl;
        //保存匹配后的结果
        transformPointCloud(final_filtered_cloud,Tvgic_result);
        //转换成有强度的点云
        // 创建一个有强度的点云
        pcl::PointCloud<pcl::PointXYZI>::Ptr cloudI(new pcl::PointCloud<pcl::PointXYZI>());
        // 转换点云
        for (const auto& point : final_filtered_cloud->points) {
            pcl::PointXYZI newPoint;
            newPoint.x = point.x;
            newPoint.y = point.y;
            newPoint.z = point.z;
            newPoint.intensity = 30.0f; // 设置强度值，可以根据需要修改
            cloudI->points.push_back(newPoint);
        }
        path_save = "/apollo_workspace/data/apollo_data/frames/" + std::to_string(id) + "_" + std::to_string(lidar_pose_time) + "_save.pcd";
        pcl::io::savePCDFileBinary(path_save,*cloudI);
        std::cout<<"path_save:"<<path_save<<std::endl;
        //合并转换矩阵
        fusion_result = Tvgic_result * fusion_result;

        Eigen::Vector3d translation_reg = fusion_result.translation();
        std::cout<<"aft result.translation: "<<fusion_result.translation()<<std::endl;
        translation_reg.x() += umap_config_[-1][0];
        translation_reg.y() += umap_config_[-1][1];
        translation_reg.z() += umap_config_[-1][2];
        fusion_result.translation() = translation_reg;
        std::cout<<std::setprecision(19)<<"aft result.translation: "<<fusion_result.translation()<<std::endl;
        return true;
    }
    std::cout<<"地图没有id索引的地图!"<<std::endl;
    return false;
}

// bool ESKFFlow::RunLidarFusion(const PointCloudXYZI::Ptr& ptr){
//     pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
//     cloud = ptr;
//     Eigen::Affine3d odometry_gnss_lidar;
//     Eigen::Affine3d odometry_lidar_init_pose;
//     Eigen::Affine3d odometry_eskf;
//     std::lock_guard<std::mutex> lock(mtxgetpose); // 锁定互斥锁
//     Eigen::Matrix4d cloud_odometry_result = eskf_ptr_->GetPose();
//     odometry_lidar_init_pose = Eigen::Affine3d(cloud_odometry_result);
//     odometry_eskf = Eigen::Affine3d(cloud_odometry_result);
//     // 进行点云帧与地图匹配
//     bool lidar_pose_key = LidarHDMapPoseCompute(cloud,lidar_pose_time,odometry_lidar_init_pose);
//     if(lidar_pose_key){
//         // lidar_poses_ = odometry_lidar_init_pose;                    //将计算的激光里程计保存进缓存
//         lidar_poses_time_ = lidar_pose_time;             //保存对应的激光里程计时间
//         lidar_poses_by_eskf_pose_ = odometry_lidar_init_pose * odometry_eskf.inverse();
//         std::cout<<"lidar_poses_by_eskf_pose_.translation: "
//         <<lidar_poses_by_eskf_pose_.translation().x()<<" "
//         <<lidar_poses_by_eskf_pose_.translation().y()<<" "
//         <<lidar_poses_by_eskf_pose_.translation().z()
//         <<" odometry_lidar_init_pose.translation: "
//         <<odometry_lidar_init_pose.translation().x()<<" "
//         <<odometry_lidar_init_pose.translation().y()<<" "
//         <<odometry_lidar_init_pose.translation().z()
//         <<" odometry_eskf.translation: "
//         <<odometry_eskf.translation().x()<<" "
//         <<odometry_eskf.translation().y()<<" "
//         <<odometry_eskf.translation().z()<<" "
//         <<std::endl;
//         return true;
//     }

//     return false;
// }

// 采用vgicp点云匹配的方式计算
// bool ESKFFlow::LidarHDMapPoseCompute(const pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,
//                                     const pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud,
//                                     const double lidar_pose_time,
//                                     Eigen::Affine3d&fusion_result){
//     pcl::PointCloud<pcl::PointXYZ>::Ptr aligned(new pcl::PointCloud<pcl::PointXYZ>);
//     //根据当前预测的pose，计算该帧点云属于grid的哪个索引
//     auto t3 = std::chrono::high_resolution_clock::now();
//     Eigen::Vector3d translation = fusion_result.translation();
//     std::lock_guard<std::mutex> lock(mtx_map_); // 锁定互斥锁
//     // 根据激光雷达外参对点云进行旋转平移
//     transformPointCloud(source_cloud,lidar_extrinsic);
//     std::string path_save = "/apollo_workspace/data/apollo_data/frames/" + std::to_string(id) + "_" + std::to_string(lidar_pose_time) + ".pcd";
//     //通过gnss的位姿对点云进行转换
//     transformPointCloud(source_cloud,fusion_result);
//     voxel_filter.setInputCloud(source_cloud); // 设置输入点云
//     // 创建输出点云
//     pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
//     // 执行体素滤波
//     voxel_filter.filter(*filtered_cloud);
//     sor.setInputCloud(filtered_cloud);
//     // 创建最终输出点云
//     pcl::PointCloud<pcl::PointXYZ>::Ptr final_filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
//     // 执行条件过滤
//     sor.filter(*final_filtered_cloud);
//     // pcl::io::savePCDFileBinary(path_save,*final_filtered_cloud);
//     // std::cout<<"path_save:"<<path_save<<std::endl;
    
//     vgicp.clearTarget();
//     vgicp.clearSource();
//     vgicp.setInputTarget(target_cloud);
//     vgicp.setInputSource(final_filtered_cloud);
//     vgicp.align(*aligned);
//     Eigen::Matrix4f final_transformation;
//     vgicp.getFinal_transformation(final_transformation);
//     Eigen::Affine3d Tvgic_result = Eigen::Affine3d(final_transformation.cast<double>());
//     auto t4 = std::chrono::high_resolution_clock::now();
//     double reg = std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() / 1e6;
//     std::cout << "vgicp time : " << reg << "[msec] " << std::flush<<std::endl;
//     //保存匹配后的结果
//     transformPointCloud(final_filtered_cloud,Tvgic_result);
//     //转换成有强度的点云
//     // 创建一个有强度的点云
//     // pcl::PointCloud<pcl::PointXYZI>::Ptr cloudI(new pcl::PointCloud<pcl::PointXYZI>());
//     // 转换点云
//     // for (const auto& point : final_filtered_cloud->points) {
//     //     pcl::PointXYZI newPoint;
//     //     newPoint.x = point.x;
//     //     newPoint.y = point.y;
//     //     newPoint.z = point.z;
//     //     newPoint.intensity = 30.0f; // 设置强度值，可以根据需要修改
//     //     cloudI->points.push_back(newPoint);
//     // }
//     path_save = "/apollo_workspace/data/apollo_data/frames/" + std::to_string(id) + "_" + std::to_string(lidar_pose_time) + "_save.pcd";
//     pcl::io::savePCDFileBinary(path_save,*final_filtered_cloud);
//     std::cout<<"path_save:"<<path_save<<std::endl;
//     //合并转换矩阵
//     fusion_result = Tvgic_result * fusion_result;

//     Eigen::Vector3d translation_reg = fusion_result.translation();
//     std::cout<<"aft result.translation: "<<fusion_result.translation()<<std::endl;
//     translation_reg.x() += umap_config_[-1][0];
//     translation_reg.y() += umap_config_[-1][1];
//     translation_reg.z() += umap_config_[-1][2];
//     fusion_result.translation() = translation_reg;
//     std::cout<<std::setprecision(19)<<"aft result.translation: "<<fusion_result.translation()<<std::endl;
//     return true;
// }



