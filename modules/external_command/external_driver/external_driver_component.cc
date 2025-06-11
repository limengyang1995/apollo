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
    CreateRtcClient(config_);
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
    rtc_client_.CreateClient(config_, "all");
    cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_1_.CreateClient(config_, "front");
    cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_2_.CreateClient(config_, "right");
    cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_3_.CreateClient(config_, "rear");
    cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_4_.CreateClient(config_, "left");
}
bool ExternalDriver::InitListener(const ExternalDriverConfig& config) {
    for (const auto& channel : config.channel().input_camera_channel_name()) {
        std::shared_ptr<cyber::Reader<apollo::drivers::Image>> reader_;
        if (channel == "/apollo/sensor/camera/left_front_fisheye/image") {
            reader_ = node_->CreateReader<apollo::drivers::Image>(
                    channel, [&](const std::shared_ptr<apollo::drivers::Image>& image) { ProcessImage(image); });
        } else {
            reader_ = node_->CreateReader<apollo::drivers::Image>(channel);
        }
        readers_.emplace_back(reader_);
    }

    return true;
}

void ExternalDriver::SendDataToCloud() {
    std::string car_id(getenv("CARID"));
    bool network_down = false;
    int fail_count = 0;

    while (true) {
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
            /* nlohmann::json vehicle_data
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
                       {"left_turn", "1"},
                       {"right_turn", "1"},
                       {"low_beam", "1"},
                       {"soc", "78"}}; */
            // rtc_client_.g_BrtcClient->sendData(vehicle_data.c_str(), vehicle_data.size());
            std::string id = std::to_string(rtc_client_.g_mylistener.feed_id);
            // AERROR << "id : " << id;
            if (id != "0") {
                if (std::find(id_list.begin(), id_list.end(), id) == id_list.end()) {
                    id_list.push_back(id);
                }
                if (id_list.size() > 3) {
                    id_list.erase(id_list.begin());
                }
                // auto it = std::find(id_list.begin(), id_list.end(), rtc_client_.g_mylistener.leaving_user_id);
                // if (it != id_list.end()) {
                //     id_list.erase(it);
                // }

                for (const auto& id : id_list) {
                    // AINFO << "id : " << id << "id size: " << id_list.size();
                    rtc_client_.g_BrtcClient->sendMessageToUser(vehicle_data.dump().c_str(), id.c_str());
                }
            }
        } else {
            cyber::SleepFor(std::chrono::milliseconds(1000));
        }

        // AINFO<<vehicle_data;
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

        cv::Mat img_front;
        cv::Mat img_right;
        cv::Mat img_back;
        cv::Mat img_left;
        cv::Mat img_left_front;
        cv::Mat img_right_front;

        // const static cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 1920, 0, 960, 0, 1920, 540, 0, 0, 1);
        // const static cv::Mat distCoeffs = (cv::Mat_<double>(5, 1) << -0.326, 0.147, 0, 0, 0);
        // constexpr float width = 3.0;

        // constexpr float length = 20.0;
        // constexpr float height = 2.0;
        // const static std::vector<cv::Point3f> obj_points
        //         = {cv::Point3f(-width / 2, 0, height),
        //            cv::Point3f(-width / 2, length, height),
        //            cv::Point3f(width / 2, length, height),
        //            cv::Point3f(width / 2, 0, height)};

        // const static cv::Mat rvec = (cv::Mat_<double>(3, 1) << 0.1, 0, 0);
        // const static cv::Mat tvec = (cv::Mat_<double>(3, 1) << 0, 0.5, 5.0);

        // static std::vector<cv::Point2f> img_points;
        // img_points.clear();
        // cv::projectPoints(obj_points, rvec, tvec, cameraMatrix, distCoeffs, img_points);

        // constexpr int thickness = 2;
        // //        const static cv::Scalar color = cv::Scalar(0, 0, 255);
        // // for (int i = 0; i < 4; ++i) {
        // //     cv::line(img_front, img_points[i], img_points[(i + 1) % 4], color, thickness);
        // // }

        cv::Size front_size(img_[0].cols * 0.5, img_[0].rows * 0.6);
        cv::Size back_size(img_[3].cols * 0.18, img_[3].rows * 0.1);
        cv::Size right_size(img_[2].cols * 0.25, img_[2].rows * 0.3);
        cv::Size left_size(img_[4].cols * 0.25, img_[4].rows * 0.3);
        cv::Size left_front_size(img_[5].cols * 0.25, img_[5].rows * 0.3);
        cv::Size right_front_size(img_[1].cols * 0.25, img_[1].rows * 0.3);

        std::thread t1([&]() { resize(img_[0], img_front, front_size, 0, 0, cv::INTER_NEAREST); });
        std::thread t2([&]() { resize(img_[3], img_back, back_size, 0, 0, cv::INTER_NEAREST); });
        std::thread t3([&]() { resize(img_[2], img_right, right_size, 0, 0, cv::INTER_NEAREST); });
        std::thread t4([&]() { resize(img_[4], img_left, left_size, 0, 0, cv::INTER_NEAREST); });
        std::thread t5([&]() { resize(img_[5], img_left_front, left_front_size, 0, 0, cv::INTER_NEAREST); });
        std::thread t6([&]() { resize(img_[1], img_right_front, right_front_size, 0, 0, cv::INTER_NEAREST); });
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();

        std::vector<unsigned char> buf_front;
        std::vector<unsigned char> buf_left;
        std::vector<unsigned char> buf_right;
        std::vector<unsigned char> buf_back;
        std::vector<unsigned char> buf_stitch;

        // 定义矩形区域的左上角坐标（x, y）和矩形的宽度（width）与高度（height）

        cv::Rect roi_back((img_front.cols - img_back.cols) / 2, 0, img_back.cols, img_back.rows);
        cv::Mat&& roi_back_rect = img_front(roi_back);
        img_back.copyTo(roi_back_rect);

        cv::Mat img_left_stitch;
        cv::Mat img_right_stitch;
        cv::Mat img_stitch;
        cv::vconcat(img_left_front, img_left, img_left_stitch);
        cv::vconcat(img_right_front, img_right, img_right_stitch);

        std::vector<cv::Mat> images_to_concat = {img_left_stitch, img_front, img_right_stitch};
        cv::hconcat(images_to_concat, img_stitch);

        // cv::resize(images_stitch, images_stitch, cv::Size(1600,300), 0, 0,cv::INTER_LINEAR);
        cv::imencode(".jpg", img_stitch, buf_stitch);
        // auto time2 = cyber::Time::Now().ToSecond();

        for (const auto& cam : request_camera) {
            // AERROR << "camera name :" << cam;
            if (cam == "front") {
                cv::imencode(".jpg", img_front, buf_front);
                rtc_client_1_.g_BrtcClient->sendImage(
                        reinterpret_cast<const char*>(buf_front.data()), buf_front.size());
                // AERROR<<"start send front image successfully!";
            } else if (cam == "back") {
                cv::imencode(".jpg", img_back, buf_back);
                rtc_client_3_.g_BrtcClient->sendImage(reinterpret_cast<const char*>(buf_back.data()), buf_back.size());
                // AERROR<<"start send back image successfully!";
            } else if (cam == "left") {
                cv::imencode(".jpg", img_left, buf_left);
                rtc_client_4_.g_BrtcClient->sendImage(reinterpret_cast<const char*>(buf_left.data()), buf_left.size());
                // AERROR<<"start send left image successfully!";
            } else if (cam == "right") {
                cv::imencode(".jpg", img_right, buf_right);
                rtc_client_2_.g_BrtcClient->sendImage(
                        reinterpret_cast<const char*>(buf_right.data()), buf_right.size());
                // AERROR<<"start send right image successfully!";
            } else {
                continue;
            }
        }

        rtc_client_.g_BrtcClient->sendImage(reinterpret_cast<const char*>(buf_stitch.data()), buf_stitch.size());
        AINFO << "start send image successfully!";
        // AERROR << "send image cost time :" << time2 - time1;

        // rtc_client_.g_BrtcClient->sendImage(reinterpret_cast<const char*>(buf_stitch.data()), buf_stitch.size());
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
            if (command["is_start_publish"] == "true") {
                AINFO << "start publish image request!" << command.dump();

                is_start_publish = true;
                is_start_send_cloud = true;
            }
            if (command["is_start_publish"] == "false") {
                is_start_publish = false;
                is_start_send_cloud = false;
                cloud_gear_position = apollo::canbus::Chassis::GEAR_NEUTRAL;
                SendCloudControlCommand(0, cloud_gear_position, 0.0, 0.0, 0.0, 0, 0, 0);
            }
        }
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
                    std::stoi(cloud_epb));
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
        const int& epb) {
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
    // command->set_driving_mode(apollo::canbus::Chassis::REMOTE_CLOUD_DRIVE);
    // AERROR<< "Sending cloud control command: " << command->DebugString();
    cloud_control_cmd_writer_->Write(command);
}

}  // namespace external_command
}  // namespace apollo
