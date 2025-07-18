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
#include <iomanip>
#include <sys/statvfs.h>
#include <sstream>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
// #include "nlohmann/json.hpp"
#include <fstream>
#include <sys/wait.h>
#ifndef ENABLE_USE_GRPC
#include "MultiMedia.h"
#include "rtc_publisher_brtc.h"
#else
#include "rtc_publisher_client.h"
#endif

namespace apollo {
namespace external_command {
// using apollo::drivers::RtcPublisherClient;
using apollo::external_command::CommandStatus;

// ExternalDriver::ExternalDriver() : command_id_(0), module_name_("demo") {}

bool ExternalDriver::Init() {
    cloud_control_cmd_writer_ = node_->CreateWriter<apollo::control::ControlCommand>(FLAGS_cloud_control_command_topic);
    ACHECK(cloud_control_cmd_writer_ != nullptr);

    apollo::cyber::common::GetProtoFromFile(
            "/apollo/modules/external_command/external_driver/conf/"
            "external_driver_config.pb.txt",
            &config_);
    MultiMedia::sys_init();
    CreateRtcPublisher(config_);

    // rtc_client_.CreateClient(config_, "all");
    // cyber::SleepFor(std::chrono::seconds(1));
    // rtc_client_1_.CreateClient(config_, "front");
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

void ExternalDriver::CreateRtcPublisher(const ExternalDriverConfig& config) {
    uint32_t color_fmt = RK_FMT_YUV422_YUYV;

    std::string app_id = config.app_id();
    std::string cer_path = config.cer_path();
    std::string car_id(getenv("CARID"));
    int32_t video_maxkbps = config.video_maxkbps();
    int32_t image_width = config.image_width();
    int32_t image_height = config.image_height();
    uint32_t pixel_fmt = RK_FMT_YUV422_YUYV;
    uint32_t encode_codec = static_cast<uint32_t>(RK_VIDEO_ID_AVC);
    uint32_t origin_width = config.image_width();
    uint32_t origin_height = config.image_height();

    for (auto stream_name : stream_name_map_) {
#ifndef ENABLE_USE_GRPC
        RtcPublisherBrtc::CreateParam param;
        param.camera_name = stream_name;
        param.video_maxkbps = video_maxkbps;
        param.image_width = image_width;
        param.image_height = image_height;
        param.cer_path = cer_path;
        param.app_id = app_id;
        param.car_id = car_id;
        param.pixel_fmt = pixel_fmt;
        param.encode_codec = encode_codec;
        param.origin_width = origin_width;
        param.origin_height = origin_height;
        RtcPublisherBrtc::GetInstance().CreateClient(param);
        if (stream_name == "all") {
            std::vector<RtcPublisherBrtc::StitchParam> stitch_param;
            for (auto config_stitch_param : config.stitch_param()) {
                RtcPublisherBrtc::StitchParam stitch_param_tmp;
                stitch_param_tmp.camera_name = config_stitch_param.camera_name();
                stitch_param_tmp.dst_rect.x = config_stitch_param.x();
                stitch_param_tmp.dst_rect.y = config_stitch_param.y();
                stitch_param_tmp.dst_rect.width = config_stitch_param.width();
                stitch_param_tmp.dst_rect.height = config_stitch_param.height();
                stitch_param_tmp.display_order = config_stitch_param.display_order();
                stitch_param_tmp.bg_color = config_stitch_param.bg_color();
                stitch_param.push_back(stitch_param_tmp);
            }
            RtcPublisherBrtc::GetInstance().SetStitchParam(stitch_param);
        }
#else

        RtcPublisherClient::GetInst().Create(
                stream_name,
                app_id,
                cer_path,
                car_id,
                video_maxkbps,
                image_width,
                image_height,
                pixel_fmt,
                encode_codec,
                origin_width,
                origin_height);
#endif
        cyber::SleepFor(std::chrono::seconds(1));
    }
}

bool ExternalDriver::InitListener(const ExternalDriverConfig& config) {
    for (const auto& channel : config.channel()) {
        std::string input_camera_channel_name = channel.input_camera_channel_name();
        std::shared_ptr<cyber::Reader<apollo::drivers::Image>> reader_;
        if (input_camera_channel_name == "/apollo/sensor/camera/front_fisheye/image") {
            reader_ = node_->CreateReader<apollo::drivers::Image>(
                    input_camera_channel_name,
                    [&](const std::shared_ptr<apollo::drivers::Image>& image) { ProcessImage(image); });
        } else {
            reader_ = node_->CreateReader<apollo::drivers::Image>(input_camera_channel_name);
        }
        // readers_.emplace_back(reader_);
        readers_[channel.channel_name()] = reader_;
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
            // CreateRtcClient(config_);
        }
        cyber::SleepFor(std::chrono::seconds(2));
    }
}
std::vector<std::string> ExternalDriver::get_system_metrics() {
    float temp = -1.0;
    long mem_avail = -1;
    float load_1min = -1.0;
    double disk_free = -1.0;

    std::ifstream temp_file("/sys/class/thermal/thermal_zone0/temp");
    if (temp_file) {
        temp_file >> temp;
        temp /= 1000;  // 转换为摄氏度
    }

    std::ifstream mem_file("/proc/meminfo");
    std::string line;
    while (std::getline(mem_file, line)) {
        if (line.find("MemAvailable:") == 0) {
            sscanf(line.c_str(), "MemAvailable: %ld kB", &mem_avail);
            mem_avail /= 1024;  // 转换为MB
            break;
        }
    }

    std::ifstream load_file("/proc/loadavg");
    if (load_file) {
        load_file >> load_1min;
    }

    struct statvfs vfs;
    if (statvfs("/", &vfs) == 0) {
        double available_bytes = static_cast<double>(vfs.f_frsize) * vfs.f_bavail;
        disk_free = available_bytes / (1024 * 1024 * 1024);  // 转换为GB
    }

    // 创建字符串向量
    std::vector<std::string> metrics;

    // 转换温度
    if (temp < 0) {
        metrics.push_back("N/A");
    } else {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << temp << "°C";
        metrics.push_back(oss.str());
    }

    // 转换内存
    if (mem_avail < 0) {
        metrics.push_back("N/A");
    } else {
        metrics.push_back(std::to_string(mem_avail) + "MB");
    }

    // 转换负载
    if (load_1min < 0) {
        metrics.push_back("N/A");
    } else {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << load_1min / 20 * 100 << "%";
        metrics.push_back(oss.str());
    }

    // 转换硬盘空间
    if (disk_free < 0) {
        metrics.push_back("N/A");
    } else {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << disk_free << "GB";
        metrics.push_back(oss.str());
    }

    return metrics;
}
void ExternalDriver::SendDataToCloud() {
    std::string car_id(getenv("CARID"));

    while (!cyber::IsShutdown()) {
        if (is_start_send_cloud) {
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

            std::string epb = std::to_string(chassis_.parking_brake());
            std::string left_turn = std::to_string(chassis_.left_turn_signal());
            std::string right_turn = std::to_string(chassis_.right_turn_signal());
            std::string low_beam = std::to_string(chassis_.low_beam_signal());
            std::string soc = std::to_string(chassis_.battery_soc_percentage());
            auto sys_info = get_system_metrics();
            // AERROR << "soc-------" << throttle << "-"<<brake<< "-"<<steer;
            if(soc.empty()){
                soc =  "0";
            }
            if (throttle == "nan"){
                throttle = "0";
            }
            if (brake == "nan"){
                brake = "0";
            }
            if (steer == "nan"){
                steer = "0";
            }

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
                       {"soc",soc},
                       {"cpu_temp", sys_info[2]},
                       {"cpu_load", sys_info[0]},

                       {"lidar", "未在线"},
                       {"memory", sys_info[1]},
                       {"disk", sys_info[3]},
                       {"vehicle_status", "正常"},
                       {"weather", "多云"}

                    };
            AINFO << "vehicle data: " << vehicle_data.dump();
#ifndef ENABLE_USE_GRPC
            RtcPublisherBrtc::GetInstance().SendUserMessage(vehicle_data.dump());
#else
            RtcPublisherClient::GetInst().SendUserMessage(vehicle_data.dump());
#endif
            cyber::SleepFor(std::chrono::milliseconds(100));
        }
        cyber::SleepFor(std::chrono::milliseconds(100));
    }
}

// bool ExternalDriver::is_all_user_leaving() const {
//     return rtc_client_.g_mylistener.user_leaving_mark && id_list.empty();
// }
bool ExternalDriver::ProcessImage(const std::shared_ptr<apollo::drivers::Image>& image) {
    if (image == nullptr) {
        AERROR << "image is null!";
        return false;
    }

    if (is_start_publish == false) {
        AERROR << "not recieve start publish request!";
        return true;
    }

    std::map<std::string, std::shared_ptr<apollo::drivers::Image>> imgs;

    uint32_t color_fmt = RK_FMT_YUV422_YUYV;

    for (auto reader : readers_) {
        reader.second->Observe();
        const auto camera_msg = reader.second->GetLatestObserved();
        if (camera_msg == nullptr) {
            AERROR << "camera message is nullptr, " << reader.first;
            // return false;
        }
        imgs.insert(std::make_pair(reader.first, camera_msg));
    }
#ifndef ENABLE_USE_GRPC
    // AERROR << "current publish_camera_name_:" << publish_camera_name_;
    if (publish_camera_name_ == "all") {
        RtcPublisherBrtc::GetInstance().SendFrame(imgs);
    } else {
        AERROR << " send signal camera:" << publish_camera_name_ << " image";
        std::shared_ptr<apollo::drivers::Image> image_ptr = nullptr;
        if (imgs.find(publish_camera_name_) != imgs.end()) {
            image_ptr = imgs[publish_camera_name_];
        }
        RtcPublisherBrtc::GetInstance().SendFrame(std::string("all"), image_ptr);
    }

#else
    RtcPublisherClient::GetInst().SendFrame(imgs, request_camera);
#endif

    // AERROR << "start send image successfully!";
    // AERROR << "send image cost time :" << time2 - time1;

    return true;
}

bool ExternalDriver::Proc() {
    std::string data;
    bool is_new_msg = false;
#ifndef ENABLE_USE_GRPC
    RtcPublisherBrtc::GetInstance().RecvUserMessage(data, is_new_msg);
#else
    RtcPublisherClient::GetInst().RecvUserMessage(data, is_new_msg);
#endif
    // int msgtype = rtc_client_.g_mylistener.msg_type;
    // int64_t id = rtc_client_.g_mylistener.feed_id;
    std::string input_command_string;
    nlohmann::json command;

    if (!data.empty() && is_new_msg) {
        try {
            command = nlohmann::json::parse(data);

            if (command.contains("action") && !command["action"].is_null()) {
                input_command_string = command["action"];
            }
        } catch (const std::exception& e) {
            AERROR << "json parse error" << e.what();
        }
        if (command.contains("is_start_publish")) {
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
        if (command.contains("camera")) {
            std::string publish_camera_name = publish_camera_name_;
            if (command["camera"] == "all") {
                publish_camera_name = "all";
            } else {
                AERROR << "change camera :" << command["camera"];
                if (readers_.find(command["camera"]) != readers_.end()) {
                    publish_camera_name = command["camera"];
                }
            }
            publish_camera_name_ = publish_camera_name;
        }

        if (command.contains("cameras")) {
            request_camera = command["cameras"].get<std::vector<std::string>>();

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
    command->set_emergency_stop(emergency_stop);
    // command->set_driving_mode(apollo::canbus::Chassis::REMOTE_CLOUD_DRIVE);
    // AERROR<< "Sending cloud control command: " << command->DebugString();
    cloud_control_cmd_writer_->Write(command);
}

}  // namespace external_command
}  // namespace apollo
