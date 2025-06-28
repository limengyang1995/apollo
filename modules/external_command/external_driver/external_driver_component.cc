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

#include "modules/external_command/external_driver/external_driver_component.h"

#include <poll.h>

#include <cctype>

#include "modules/external_command/external_driver/proto/sweeper_custom_command.pb.h"
#include "modules/common/adapters/adapter_gflags.h"
#include "cyber/common/file.h"
#include "cyber/record/record_reader.h"
#include "cyber/common/log.h"
#include <string>
#include "thread"

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
// #include "nlohmann/json.hpp"
#include <fstream>
#include <sys/wait.h>

namespace apollo {
namespace external_command {
using apollo::external_command::CommandStatus;

// ExternalDriver::ExternalDriver() : command_id_(0), module_name_("demo") {}

bool ExternalDriver::Init() {
    cloud_control_cmd_writer_ = node_->CreateWriter<apollo::control::ControlCommand>(FLAGS_cloud_control_command_topic);
    ACHECK(cloud_control_cmd_writer_ != nullptr);

    apollo::cyber::common::GetProtoFromFile(
            "/apollo/modules/external_command/external_driver/conf/"
            "external_driver_config.pb.txt",
            &config_);
    //CreateRtcClient(config_);
    rtc_client_.CreateClient(config_, "all");
    // cyber::SleepFor(std::chrono::seconds(1));
    //rtc_client_1_.CreateClient(config_, "front");
    // cyber::SleepFor(std::chrono::seconds(1));
    // rtc_client_2_.CreateClient(config_, "right");
    // cyber::SleepFor(std::chrono::seconds(1));
    // rtc_client_3_.CreateClient(config_, "rear");
    // cyber::SleepFor(std::chrono::seconds(1));
    // rtc_client_4_.CreateClient(config_, "left");

    // std::ifstream f(config_.destination_path());
    // if (f.fail()) {
    //     AERROR << "failed to load destination file";
    // }
    // point = nlohmann::json::parse(f);
    data_to_cloud_future = cyber::Async(&ExternalDriver::SendDataToCloud, this);
    is_network_down_future = cyber::Async(&ExternalDriver::IsNetworkDown, this);
    InitListener(config_);
    localization_reader_pose = node_->CreateReader<apollo::localization::LocalizationEstimate>(
            FLAGS_localization_topic,
            [this](const std::shared_ptr<apollo::localization::LocalizationEstimate>& localization) {
                std::lock_guard<std::mutex> lock(mutex_);
                localization_.CopyFrom(*localization);
                // std::this_thread::sleep_for(std::chrono::seconds(1));
            });
    canbus_reader_ = node_->CreateReader<apollo::canbus::Chassis>(
            FLAGS_chassis_topic, [this](const std::shared_ptr<apollo::canbus::Chassis>& chassis) {
                std::lock_guard<std::mutex> lock(mutex_);
                chassis_.CopyFrom(*chassis);
                // std::this_thread::sleep_for(std::chrono::seconds(1));
            });
    // AERROR << "nenon suppot" << cv::checkHardwareSupport(100);
    return true;
}

void ExternalDriver::CreateRtcClient(const ExternalDriverConfig& config) {
    // rtc_client_.CreateClient(config_, "all");
    // cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_.CreateClient(config_, "front");
    // cyber::SleepFor(std::chrono::seconds(1));
    // rtc_client_2_.CreateClient(config_, "right");
    // cyber::SleepFor(std::chrono::seconds(1));
    // rtc_client_3_.CreateClient(config_, "rear");
    // cyber::SleepFor(std::chrono::seconds(1));
    // rtc_client_4_.CreateClient(config_, "left");
}
bool ExternalDriver::InitListener(const ExternalDriverConfig& config) {
    for (const auto& channel : config.channel().input_camera_channel_name()) {
        std::shared_ptr<cyber::Reader<apollo::drivers::Image>> reader_;
        if (channel == "/apollo/sensor/camera/camera_a3_ir/image") {
            reader_ = node_->CreateReader<apollo::drivers::Image>(
                    channel, [&](const std::shared_ptr<apollo::drivers::Image>& image) { ProcessImage(image); });
        } else {
            reader_ = node_->CreateReader<apollo::drivers::Image>(channel);
        }
        readers_.emplace_back(reader_);
    }

    return true;
}

void ExternalDriver::IsNetworkDown() {
    int fail_count = 0;
    while (!cyber::IsShutdown()) {
        int result = WEXITSTATUS(system("ping -c 5 -W 1 8.8.8.8 > /dev/null 2>&1"));
        AERROR << "result :" << result;
        if (result != 0) {
            fail_count++;
            AERROR << "fail count : " << fail_count;
            if (fail_count > 2) {
                network_down = true;
            }
        } else if (network_down) {
            AERROR << "restart all process!";
            fail_count = 0;
            network_down = false;
            CreateRtcClient(config_);
        }
        cyber::SleepFor(std::chrono::seconds(2));
    }
}
void ExternalDriver::SendDataToCloud() {
    std::string car_id(getenv("CARID"));
    AERROR << "carid is : "<< car_id;
    while (!cyber::IsShutdown()) {
        AERROR << "is_start_send_cloud: " << is_start_send_cloud;
        //if (is_start_send_cloud) {
        if (is_start_send_cloud) {
            AERROR << "enter start publish";
            cyber::SleepFor(std::chrono::milliseconds(150));
            std::string x = std::to_string(localization_.pose().position().x());
            std::string y = std::to_string(localization_.pose().position().y());
            std::string z = std::to_string(localization_.pose().position().z());
            std::string gear = std::to_string(chassis_.gear_location());
            std::string steer = std::to_string(std::round(chassis_.steering_percentage()));
            std::string throttle = std::to_string(std::round(chassis_.throttle_percentage()));
            std::string brake = std::to_string(std::round(chassis_.brake_percentage()));
            std::string driving_mode = std::to_string(chassis_.driving_mode());
            std::string speed = std::to_string(std::round(chassis_.speed_mps()));
            // std::string speed = std::to_string(10);
            std::string epb = std::to_string(chassis_.parking_brake());
            std::string left_turn = std::to_string(chassis_.left_turn_signal());
            std::string right_turn = std::to_string(chassis_.right_turn_signal());
            std::string low_beam = std::to_string(chassis_.low_beam_signal());
            std::string soc = std::to_string(chassis_.battery_soc_percentage());
           

            nlohmann::json vehicle_data
                    = {{"car_id", car_id},
                       {"x", x},
                       {"y", y},
                       {"z", z},
                       {"gear", gear},
                       {"steer", steer},
                       {"throttle", throttle},
                       {"brake", brake},
                       {"driving_mode", driving_mode},
                       {"speed", speed},
                       {"epb", epb},
                       {"left_turn", left_turn},
                       {"right_turn", right_turn},
                       {"low_beam", low_beam},
                       {"soc", soc}};
            std::string id = std::to_string(rtc_client_.g_mylistener.feed_id);
            AERROR << "feed id : " << id;
            AERROR << "vehicle data: " << vehicle_data.dump();
            if (id != "0") {
                if (std::find(id_list.begin(), id_list.end(), id) == id_list.end()) {
                    id_list.push_back(id);
                }
                if (id_list.size() > 3) {
                    id_list.erase(id_list.begin());
                }

                for (const auto& id : id_list) {
                    // AINFO << "id : " << id << "id size: " << id_list.size();
                    rtc_client_.g_BrtcClient->sendMessageToUser(vehicle_data.dump().c_str(), id.c_str());
                }

            } else {
                cyber::SleepFor(std::chrono::milliseconds(100));
            }

            // AINFO<<vehicle_data;
        }

        cyber::SleepFor(std::chrono::milliseconds(100));
    }
}

bool ExternalDriver::is_all_user_leaving() const {
    return rtc_client_.g_mylistener.user_leaving_mark && id_list.empty();
}
bool ExternalDriver::ProcessImage(const std::shared_ptr<apollo::drivers::Image>& image) {
    if (image == nullptr) {
        return false;
    }

    static std::vector<cv::Mat> img_;
    img_.reserve(4);
    img_.clear();

    for (u_int16_t i = 0; i < readers_.size(); ++i) {
        readers_[i]->Observe();
        const auto camera_msg = readers_[i]->GetLatestObserved();
        if (camera_msg == nullptr) {
            AERROR << "camera message is nullptr";
            return false;
        }
        cv::Mat img(image->height(), image->width(), CV_8UC3, const_cast<char*>(camera_msg->data().data()));
        img_.emplace_back(img);
    }
    // AERROR << "is start publish : " << is_start_publish;
    if (is_start_publish && !id_list.empty()) {
        // auto time1 = cyber::Time::Now().ToSecond();

        cv::Mat img_front = img_[0];

        std::vector<unsigned char> buf_front;


        cv::imencode(".jpg", img_front, buf_front);
        rtc_client_.g_BrtcClient->sendImage(
                        reinterpret_cast<const char*>(buf_front.data()), buf_front.size());
        // auto time2 = cyber::Time::Now().ToSecond();

        return true;
    } else {
        AINFO << "not recieve start publish request!";
        // return false;
    }
    return true;
}

bool ExternalDriver::Proc() {
    std::string data = rtc_client_.g_mylistener.recieve_msg;
    // int msgtype = rtc_client_.g_mylistener.msg_type;
    // int64_t id = rtc_client_.g_mylistener.feed_id;
    std::string input_command_string;
    nlohmann::json command;
    AERROR << " data empty: " << !data.empty() << " rtc: " << rtc_client_.g_mylistener.re_mark;
    if (!data.empty() && rtc_client_.g_mylistener.re_mark) {
        try {
            command = nlohmann::json::parse(data);

            if (command.contains("action") && !command["action"].is_null()) {
                input_command_string = command["action"];
            }
        } catch (const std::exception& e) {
            AERROR << "json parse error" << e.what();
        }
        if (command.contains("is_start_publish")) {
            AERROR << "start publish image request!" << command.dump();
            if (command["is_start_publish"] == "true") {
                AINFO << "start publish image request!" << command.dump();

                is_start_publish = true;
                is_start_send_cloud = true;
            }
            if (command["is_start_publish"] == "false") {
                is_start_publish = false;
                is_start_send_cloud = false;
                cloud_gear_position = apollo::canbus::Chassis::GEAR_NEUTRAL;
                SendCloudControlCommand(0, cloud_gear_position, 0.0, 0.0, 0.0, 0, 0, 0, 0);
            }
        }
        AERROR << "is_start_publish : " << is_start_publish << " is_start_send_cloud: " << is_start_send_cloud;
        if (command.contains("active_cameras")) {
            request_camera = command["active_cameras"].get<std::vector<std::string>>();

            // for (auto& cam : request_camera_.items()){
            //     request_camera.push_back(cam.value());
            // }
        }

        if (input_command_string == "cloud") {
            try {
                cloud_takeover = command["takeover"];
                if (command.contains("gear") && !command["gear"].is_null()) {
                    cloud_gear = command["gear"];
                    cloud_throttle = command["throttle"];
                    cloud_brake = command["brake"];
                    cloud_steer = command["steer"];
                    cloud_turn_light = command["turn_light"];
                    cloud_low_light = command["low_light"];
                    cloud_epb = command["epb"];
                    cloud_emergency_stop = command["emergency_stop"];
                }
            } catch (const std::exception& e) {
                AERROR << "json parse error" << e.what();
            }
            AERROR << "cloud takeover: " << cloud_takeover;

            switch (std::stoi(cloud_gear)) {
            case 0:
                cloud_gear_position = apollo::canbus::Chassis::GEAR_NEUTRAL;
                break;
            case 1:
                cloud_gear_position = apollo::canbus::Chassis::GEAR_DRIVE;
                break;
            case 2:
                cloud_gear_position = apollo::canbus::Chassis::GEAR_REVERSE;
                break;
            case 3:
                cloud_gear_position = apollo::canbus::Chassis::GEAR_PARKING;
                break;
            default:
                cloud_gear_position = apollo::canbus::Chassis::GEAR_INVALID;
            }

            SendCloudControlCommand(
                    std::stoi(cloud_takeover),
                    cloud_gear_position,
                    std::stof(cloud_throttle),
                    std::stof(cloud_brake),
                    -std::stof(cloud_steer),
                    std::stoi(cloud_turn_light),
                    std::stoi(cloud_low_light),
                    std::stoi(cloud_epb),
                    std::stoi(cloud_emergency_stop));
        }
    }
    rtc_client_.g_mylistener.re_mark = false;
    return true;
}

void ExternalDriver::SendCloudControlCommand(
        const bool& cloud_takeover_request,
        const apollo::canbus::Chassis::GearPosition& gear_position,
        const float& throttle,
        const float& brake,
        const float& steering_target,
        const int& turn_light,
        const int& low_light,
        const int& epb,
        const int& emergency_stop) {
    AERROR << "get cloud control command: " << cloud_takeover_request;
    auto command = std::make_shared<apollo::control::ControlCommand>();
    command->set_cloud_takeover_request(cloud_takeover_request);
    command->set_gear_location(gear_position);
    command->set_throttle(throttle * 100);
    command->set_brake(brake * 100);
    command->set_steering_target(steering_target * 100);
    command->set_low_beam(low_light);
    if (turn_light == 1) {
        command->set_left_turn(1);
        command->set_right_turn(0);
    } else if (turn_light == 2) {
        command->set_right_turn(1);
        command->set_left_turn(0);
    } else {
        command->set_left_turn(0);
        command->set_right_turn(0);
    }
    command->set_parking_brake(epb);
    // command->set_emergency_stop(emergency_stop);
    // command->set_driving_mode(apollo::canbus::Chassis::REMOTE_CLOUD_DRIVE);
    // AERROR<< "Sending cloud control command: " << command->DebugString();
    cloud_control_cmd_writer_->Write(command);
}

}  // namespace external_command
}  // namespace apollo
