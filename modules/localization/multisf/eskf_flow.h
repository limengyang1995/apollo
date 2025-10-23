
/*
   Created by wkx 2025.8.20
*/
#ifndef GPS_IMU_FUSION_ESKF_FLOW_H
#define GPS_IMU_FUSION_ESKF_FLOW_H
#pragma once
#include "eskf.h"
#include "imu_tool.h"
#include "config_parameters.h"
#include "observability_analysis.h"
#include "imu_data.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/filters/statistical_outlier_removal.h>

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

#include "modules/localization/multisf/fastgicp/fast_gicp.h"
#include "modules/localization/multisf/fastgicp/fast_vgicp.h"
#include "modules/localization/msf/cereal/include/cereal/types/unordered_map.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/memory.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/vector.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/binary.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/json.hpp"
#include <fstream>
#include "modules/localization/msf/cereal/eigen_cereal.hpp"

#include <memory>
#include <deque>
#include <iostream>

struct PoseVelocityStamped {
    PoseVelocityStamped() = default;
    PoseVelocityStamped(const double time_, const Eigen::Isometry3d &pose_, const Eigen::Vector3d &velocity_) :
            time_us(time_), pose(pose_), velocity(velocity_) {}
    friend std::ostream &operator<<(std::ostream &os, const PoseVelocityStamped &pose);

    double time_us{0};
    Eigen::Isometry3d pose;
    Eigen::Vector3d velocity;
};

class ESKFFlow {
public:
    ESKFFlow();

    /*!
     * 从本地文件中读取IMU和GPS的数据
     * @return
     */
    // void ReadData();

    /*!
     * 对IMU和GPS数据进行时间戳对齐，该函数只在ESKF初始化时使用
     * @return
     */
    // bool ValidGPSAndIMUData();
    bool EskfInitEskf(const IMUData imu_data);
    bool Run(const IMUData imu_data);
    void WritePcdFile(const std::shared_ptr<apollo::drivers::PointCloud>&msg,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud); 
    void transformPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Matrix4d& transform); 
    void transformPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Affine3d& transform);
    bool RunLidarFusion(const std::shared_ptr<apollo::drivers::PointCloud>& lidar_msg);
    bool LidarHDMapPoseCompute(const pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,const double lidar_pose_time,Eigen::Affine3d &fusion_result);
    // bool LidarHDMapPoseCompute(const pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,
    //                                 const pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,
    //                                 const double lidar_pose_time,
    //                                 Eigen::Affine3d&fusion_result);

public:
    Eigen::Quaterniond lio_q_;
    Eigen::Vector3d lio_pose_glob_;
    
    Eigen::Vector3d gnss_init_pose_;       //gnss 初始化时的pose
    Eigen::Quaterniond gnss_init_q_;       // gnss 初始化时的 旋转
    bool save_key_ = false;
    
    double lio_time_ = 0;
    double lio_time_last_ = 0;
    GPSData init_gps_data_;
    std::mutex mtx_map_; // 互斥锁
    std::mutex mtxgetpose; // 互斥锁
    std::fstream eskf_pose_file;
    std::fstream lidar_pose_file;
    fast_gicp::FastVGICP<pcl::PointXYZ, pcl::PointXYZ> vgicp;                               // vgicp 
    // 体素滤波，创建体素滤波器
    pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
    // 创建统计离群点移除滤波器
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    IMUData last_imu_;
    double last_imu_time_;
    bool is_init = false;
    std::deque<std::shared_ptr<apollo::localization::LocalizationEstimate>>
            ndt_lidar_pose_queue_;                                                           // 保存ndt 激光里程计的队列
    std::deque<IMUData> imu_pose_queue_;                                                     // 保存 imu的 队列
    std::deque<std::shared_ptr<apollo::drivers::gnss::GnssBestPose>> best_gnss_pose_queue_;  // 保存gnss best pose的队列
    std::deque<std::shared_ptr<apollo::localization::Gps>> gnss_odometry_queue_;             // 存储gnss odom的队列
    std::deque<std::shared_ptr<apollo::localization::Gps>> gnss_lidar_queue_;  // 保存gnss 的队列，用于激光点云计算
    std::deque<std::shared_ptr<apollo::drivers::gnss::InsStat>> gnss_status_pose_queue_;  // 保存gnss status的队列
    std::shared_ptr<ErrorStateKalmanFilter> eskf_ptr_;
    std::vector<ErrorStateKalmanFilter>vector_eskf_;
    ConfigParameters config_parameters_;
    int n = 0;
    double time_threshold = 0.03;
    std::unordered_map<int,std::vector<double>> umap_config_;        //地图配置文件，包含起始点，grid bound
    int grid_id = -9;                                                // 表示当前地图匹配的grid_id;
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud;                                               //表示地图对应的gridcloud
    std::vector<Eigen::Matrix4d, Eigen::aligned_allocator<Eigen::Matrix4d>>covariances;              //表示地图对应的gridcloud的cov
    std::unordered_map<int,pcl::PointCloud<pcl::PointXYZ>::Ptr> umap_cloud_;                         //预加载的地图点云
    std::unordered_map<int,std::vector<Eigen::Matrix4d, Eigen::aligned_allocator<Eigen::Matrix4d>>> umap_covariances_; // 预加载的协方差

    // 激光点云与地图匹配的pose
    Eigen::Affine3d lidar_poses_;
    Eigen::Affine3d lidar_poses_by_eskf_pose_;        // 该雷达pose下的eskfpose        
    double lidar_poses_time_;

    double gnss_time_;
    double lidar_time_;

    std::shared_ptr<apollo::localization::Gps>gnss_odometry_last_;       //最新的gnss odometry

    std::deque<int>umap_index_id_;
    Eigen::Affine3d lidar_extrinsic;          // 雷达外参

private:
    std::shared_ptr<IMUTool> imu_flow_ptr_;

    ObservabilityAnalysis observability_analysis;  // 可观测度分析工具

    std::deque<IMUData> imu_data_buff_;
    std::deque<GPSData> gps_data_buff_;

    IMUData curr_imu_data_;

    bool use_observability_analysis_ = false;  // 是否进行可观测度分析

    const std::string config_file_path_;
    const std::string data_file_path_;
};

#endif  // GPS_IMU_FUSION_ESKF_FLOW_H
