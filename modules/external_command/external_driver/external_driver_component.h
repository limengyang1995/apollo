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
#pragma once

#include <memory>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

#include "modules/common_msgs/external_command_msgs/action_command.pb.h"
#include "modules/common_msgs/external_command_msgs/chassis_command.pb.h"
#include "modules/common_msgs/external_command_msgs/command_status.pb.h"
#include "modules/common_msgs/external_command_msgs/free_space_command.pb.h"
#include "modules/common_msgs/external_command_msgs/lane_follow_command.pb.h"
#include "modules/common_msgs/external_command_msgs/path_follow_command.pb.h"
#include "modules/common_msgs/external_command_msgs/speed_command.pb.h"
#include "modules/common_msgs/external_command_msgs/valet_parking_command.pb.h"
#include "modules/common_msgs/planning_msgs/planning.pb.h"
#include "modules/common_msgs/control_msgs/control_cmd.pb.h"
#include "modules/common_msgs/localization_msgs/localization.pb.h"
#include "modules/common_msgs/chassis_msgs/chassis.pb.h"
#include "modules/external_command/external_driver/proto/external_driver_config.pb.h"

#include "cyber/component/timer_component.h"
#include "cyber/cyber.h"
#include "modules/common/util/message_util.h"

#include "modules/common_msgs/sensor_msgs/sensor_image.pb.h"
#define DUMP_YUYV 1
namespace apollo {
namespace external_command {

// #ifndef RT_FMT_YUV422_YUYV
// #define RK_FMT_YUV422_YUYV (0x00000009)
// #endif

// #ifndef RK_VIDEO_ID_AVC
// #define RK_VIDEO_ID_AVC (0x00000008)
// #endif

class ExternalDriver final : public apollo::cyber::TimerComponent {
public:
    ExternalDriver() = default;
    ~ExternalDriver() = default;

    bool Init() override;

    bool Proc() override;

private:
    // std::string stream_name_map_[5] = {"all", "front", "right", "back", "left"};
    std::string stream_name_map_[1] = {"all"};

    std::string publish_camera_name_ = "all";

    // std::map<std::string, int> cam_idx_map_;
    // std::vector<std::string> idx_cam_map_;
    // // = {{"front", 0}, {"right_front", 1}, {"right", 2}, {"rear", 3}, {"left", 4}, {"left_front", 5}};
    // // std::string idx_cam_map_[6] = {"front", "right_front", "right", "rear", "left", "left_front"};

    void CreateRtcPublisher(const ExternalDriverConfig& config);

    bool is_write_ = false;

private:
    std::shared_ptr<cyber::Writer<apollo::drivers::Image>> writer_;
    std::string destination;
    std::string id;
    apollo::external_command::ExternalDriverConfig config_;
    // std::vector<std::shared_ptr<cyber::Reader<apollo::drivers::Image>>> readers_;
    std::map<std::string, std::shared_ptr<cyber::Reader<apollo::drivers::Image>>> readers_;

    nlohmann::json point;

    std::shared_ptr<cyber::Reader<localization::LocalizationEstimate>> localization_reader_pose;
    std::shared_ptr<cyber::Reader<apollo::canbus::Chassis>> canbus_reader_;
    std::mutex mutex_;
    const nlohmann::json data_to_cloud;
    std::future<void> data_to_cloud_future;
    std::future<void> is_network_down_future;
    int connect_detect_num = 0;
    std::vector<std::string> request_camera;
    std::vector<std::string> offline_camera_name;
    // std::vector<std::string> id_list;

private:
    // bool is_all_user_leaving() const;
    bool is_stop = false;
    bool is_start_publish = false;
    bool is_start_send_cloud = false;
    bool network_down = false;
    uint32_t num = 0;

private:
    bool ProcessImage(const std::shared_ptr<apollo::drivers::Image>& image);
    //     bool InternalProc();
    bool InitListener(const ExternalDriverConfig& config);
    apollo::localization::LocalizationEstimate localization_;
    apollo::canbus::Chassis chassis_;
    void SendDataToCloud();
    // void CreateRtcClient(const ExternalDriverConfig& config);
    void IsNetworkDown();
    std::vector<std::string> get_system_metrics();

    // void LoadConfig(const std::string& config_file_path);

private:
    // template <typename T>
    void SendCloudControlCommand(
            const bool& cloud_takeover_request,
            const apollo::canbus::Chassis::GearPosition& gear_position,
            const float& throttle,
            const float& brake,
            const float& steering_target,
            const int& turn_light,
            const int& low_light,
            const int& epb,
            const int& emergency_stop);
    std::shared_ptr<apollo::cyber::Writer<apollo::control::ControlCommand>> cloud_control_cmd_writer_;
    uint64_t command_id_;
    const std::string module_name_;
    //     std::string input_command_string = "";
    std::string cloud_takeover{"0"}, cloud_gear{"0"}, cloud_throttle{"0"}, cloud_brake{"0"}, cloud_turn_light{"0"},
            cloud_low_light{"0"}, cloud_epb{"0"}, cloud_steer{"0"}, cloud_emergency_stop{"0"};
    apollo::canbus::Chassis::GearPosition cloud_gear_position;
};

CYBER_REGISTER_COMPONENT(ExternalDriver);
}  // namespace external_command
}  // namespace apollo
