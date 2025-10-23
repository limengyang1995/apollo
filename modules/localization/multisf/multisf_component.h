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
 * @file multisf_component.h
 *****************************************************************************/

#pragma once
#include <memory>
#include <deque>
#include <mutex>
#include <fstream>
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "cyber/cyber.h"
#include "cyber/component/component.h"
#include "modules/localization/multisf/proto/multisf.pb.h"
#include "modules/common_msgs/sensor_msgs/gnss_best_pose.pb.h"
#include "modules/common_msgs/sensor_msgs/gnss_raw_observation.pb.h"
#include "modules/common_msgs/sensor_msgs/pointcloud.pb.h"
#include "modules/common_msgs/localization_msgs/gps.pb.h"
#include "modules/common_msgs/localization_msgs/localization.pb.h"
#include "modules/transform/transform_broadcaster.h"
#include "cyber/class_loader/class_loader.h"
#include "cyber/message/raw_message.h"
#include "modules/localization/common/gnss_compensator.h"
#include "modules/common_msgs/sensor_msgs/ins.pb.h"
#include "modules/localization/ndt/ndt_localization.h"
#include "modules/common_msgs/sensor_msgs/imu.pb.h"
#include "eskf_flow.h"
#include "modules/localization/ndt/ndt_locator/ndt_solver.h"
#include "modules/localization/msf/cereal/include/cereal/types/unordered_map.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/memory.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/vector.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/binary.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/json.hpp"
#include <fstream>
#include <chrono>
#include "modules/localization/msf/cereal/eigen_cereal.hpp"
#include <memory>
#include <chrono>

#define RAD_TO_DEG_k 57.295779513082321
#define DEG_TO_RAD_k .017453292519943296

namespace apollo {
namespace multimsflocalization {

class Multisf final : public cyber::Component<drivers::gnss::Imu> {
    // class Multisf final : public cyber::Component<localization::CorrectedImu> {
public:
    bool Init() override;
    bool LoadLidarExtrinsic(const std::string& file_path,Eigen::Affine3d* lidar_extrinsic);
    void listFilesWithExtension(const std::string& path, const std::string& extension);
    // bool Proc(const std::shared_ptr<drivers::gnss::Imu>& gps_msg) override;
    bool Proc(const std::shared_ptr<drivers::gnss::Imu>& gps_msg) override;
    void InitIo();
    // void SetConfig(KITTIFiltering::KittiConfig& config);
    void LidarPoseCallback(const std::shared_ptr<apollo::localization::LocalizationEstimate>& msg);
    void WritePcdFile(const std::shared_ptr<drivers::PointCloud> &msg,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    void LidarPoseSuber();
    void LidarPub();
    void LidarCallback(const std::shared_ptr<drivers::PointCloud>& lidar_msg);
    void OdometryCallback(const std::shared_ptr<localization::Gps>& odometry_msg);
    void OnGnssBestPoseCallback(const std::shared_ptr<drivers::gnss::GnssBestPose>& gnssbestpose);
    void NDTPoseCallback(const std::shared_ptr<localization::LocalizationEstimate>& ndt_pose);
    void OdometryGNssStatusCallback(const std::shared_ptr<drivers::gnss::InsStat>& odometry_status_msg);
    // void ImuCallback(const std::shared_ptr<localization::CorrectedImu>& CorrectedImu_msg);
    // void VechicleHeadingCallback(const std::shared_ptr<drivers::gnss::Heading>& heading_msg);
    bool LoadMapInAdvance(const std::shared_ptr<localization::Gps>& gnss_odometry_msg);
    void PublishPoseBroadcastTopic(const Eigen::Affine3d& pose,const double& time); 
    void OnLocalizationTimer();
    void OnLocalizationTimerLidar();
    void MsgtoPclCloud(const std::shared_ptr<apollo::drivers::PointCloud>&msg,pcl::PointCloud<pcl::PointXYZINormal>::Ptr cloud); 

private:
    apollo::multimsflocalization::MultisfConfig config_;
    std::shared_ptr<cyber::Reader<drivers::PointCloud>> lidar_listener_ = nullptr;   // 点云  订阅者
    std::shared_ptr<cyber::Reader<localization::Gps>> odometry_listener_ = nullptr;  // gps  订阅者
    std::shared_ptr<cyber::Reader<drivers::gnss::GnssBestPose>> bestgnsspos_listener_
            = nullptr;  // gnss best pose订阅者
    std::shared_ptr<cyber::Reader<localization::LocalizationEstimate>> ndtpos_listener_
            = nullptr;  // ndt 激光里程计订阅者

    std::shared_ptr<cyber::Reader<drivers::gnss::InsStat>> odometry_status_listener_ = nullptr;

    std::shared_ptr<cyber::Writer<localization::LocalizationEstimate>> localization_talker_ = nullptr;
    // std::shared_ptr<cyber::Reader<drivers::gnss::Heading>> vehicle_heading_listener_ = nullptr;
    // std::shared_ptr<cyber::Reader<localization::CorrectedImu>> corrected_imu_listener_ = nullptr;

    cyber::ReaderConfig reader_config;
    cyber::ReaderConfig reader_odometry_config;
    cyber::ReaderConfig bestgnsspos_config;
    cyber::ReaderConfig ndtpos_config;
    cyber::ReaderConfig vechileheading_config;

public:
    int number_ = 0;
    ESKFFlow eskf_flow;
    ESKFFlow eskf_flow_lidar_;
    ESKFFlow eskf_imu_gnss;
    std::fstream gnss_pose_file;               // 保存gnss 的pose
    std::fstream imu_pose_file;                // 保存gnss 的pose
    std::fstream gnss_status_file;             // 保存gnss 的pose
    std::fstream ndt_pose_file;                // 保存ndt pose
    std::mutex mutex_ndt_lidar_pose_queue_;    // 互斥量
    std::mutex mutex_gnss_odometry_queue_;     // 互斥量
    std::mutex mutex_gnss_status_pose_queue_;  // 互斥量
    std::mutex mutex_gnss_lidar_queue_;
    Eigen::Affine3d lidar_extrinsic;          // 雷达外参

    std::deque<std::shared_ptr<apollo::localization::LocalizationEstimate>>ndt_lidar_pose_queue_;                                                   // 保存ndt 激光里程计的队列
    std::deque<std::shared_ptr<drivers::gnss::GnssBestPose>> best_gnss_pose_queue_;  // 保存gnss best pose的队列
    std::deque<std::shared_ptr<localization::Gps>> gnss_odometry_queue_;             // 存储gnss odom的队列

    std::deque<std::shared_ptr<drivers::gnss::InsStat>> gnss_status_pose_queue_;  // 保存gnss 的队列
    std::shared_ptr<localization::Gps> gnss_odometry_;

    apollo::localization::ndt::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt_;

    std::unique_ptr<cyber::Timer> localization_timer_ = nullptr;
    std::unique_ptr<cyber::Timer> localization_timer1_ = nullptr;
    double imutime = 0;                                                //记录上一时刻imu的时间

    int localization_seq_num_ = 0;
    IMUData imu_data_;                                // eskf imu data
    int gnssframedown_ = 1;

};

CYBER_REGISTER_COMPONENT(Multisf)

}  // namespace multimsflocalization
}  // namespace apollo
