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

#include "opencv2/opencv.hpp"
// #include "nlohmann/json.hpp"
#include <fstream>

namespace apollo {
namespace external_command {
using apollo::external_command::CommandStatus;

// ExternalDriver::ExternalDriver() : command_id_(0), module_name_("demo") {}

bool ExternalDriver::Init() {
    action_command_client_ = node_->CreateClient<apollo::external_command::ActionCommand, CommandStatus>(
            "/apollo/external_command/action");
    chassis_command_client_ = node_->CreateClient<apollo::external_command::ChassisCommand, CommandStatus>(
            "/apollo/external_command/chassis");
    free_space_command_client_ = node_->CreateClient<apollo::external_command::FreeSpaceCommand, CommandStatus>(
            "/apollo/external_command/free_space");
    lane_follow_command_client_ = node_->CreateClient<apollo::external_command::LaneFollowCommand, CommandStatus>(
            "/apollo/external_command/lane_follow");
    path_follow_command_client_ = node_->CreateClient<apollo::external_command::PathFollowCommand, CommandStatus>(
            "/apollo/external_command/path_follow");
    speed_command_client_ = node_->CreateClient<apollo::external_command::SpeedCommand, CommandStatus>(
            "/apollo/external_command/speed");
    valet_parking_command_client_ = node_->CreateClient<apollo::external_command::ValetParkingCommand, CommandStatus>(
            "/apollo/external_command/valet_parking");
    status_client_ = node_->CreateClient<apollo::external_command::CommandStatusRequest, CommandStatus>(
            "/apollo/external_command/command_status");
    cloud_control_cmd_writer_ = node_->CreateWriter<apollo::control::ControlCommand>(FLAGS_cloud_control_command_topic);
    ACHECK(cloud_control_cmd_writer_ != nullptr);

    apollo::cyber::common::GetProtoFromFile(
            "/apollo/modules/external_command/external_driver/conf/"
            "external_driver_config.pb.txt",
            &config_);

    rtc_client_.CreateClient(config_, "all");
    cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_1_.CreateClient(config_, "front");
    cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_2_.CreateClient(config_, "right");
    cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_3_.CreateClient(config_, "rear");
    cyber::SleepFor(std::chrono::seconds(1));
    rtc_client_4_.CreateClient(config_, "left");

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

    return true;
}
bool ExternalDriver::InitListener(const ExternalDriverConfig& config) {
    for (const auto& channel : config.channel().input_camera_channel_name()) {
        std::shared_ptr<cyber::Reader<apollo::drivers::Image>> reader_;
        if (channel == "/apollo/sensor/camera/left_fisheye/image") {
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
    while (true) {
        cyber::SleepFor(std::chrono::milliseconds(100));
        std::string x = std::to_string(localization_.pose().position().x());
        std::string y = std::to_string(localization_.pose().position().y());
        std::string z = std::to_string(localization_.pose().position().z());
        std::string gear = std::to_string(chassis_.gear_location());
        std::string steer = std::to_string(chassis_.steering_percentage());
        std::string throttle = std::to_string(chassis_.throttle_percentage());
        std::string brake = std::to_string(chassis_.brake_percentage());
        std::string driving_mode = std::to_string(chassis_.driving_mode());
        // std::string speed = std::to_string(chassis_.speed_mps());
        std::string speed = std::to_string(20);
        std::string epb = std::to_string(chassis_.parking_brake());

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
                   {"epb", epb}};
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
    std::vector<cv::Mat> img_;
    auto t1 = cyber::Time::Now().ToSecond();
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

    if (is_start_publish && !id_list.empty()) {
        // AERROR << "is_start_publish :" << is_start_publish;

        cv::Mat img_front = img_[0];
        cv::Mat img_right;
        cv::Mat img_back;
        cv::Mat img_left;
        cv::Mat img_left_front;
        cv::Mat img_right_front;

        cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 1920, 0, 960, 0, 1920, 540, 0, 0, 1);
        cv::Mat distCoeffs = (cv::Mat_<double>(5, 1) << -0.326, 0.147, 0, 0, 0);
        const float width = 3.0;

        const float length = 20.0;
        const float height = 2.0;
        std::vector<cv::Point3f> obj_points
                = {cv::Point3f(-width / 2, 0, height),
                   cv::Point3f(-width / 2, length, height),
                   cv::Point3f(width / 2, length, height),
                   cv::Point3f(width / 2, 0, height)};

        cv::Mat rvec = (cv::Mat_<double>(3, 1) << 0.1, 0, 0);
        cv::Mat tvec = (cv::Mat_<double>(3, 1) << 0, 0.5, 5.0);
        std::vector<cv::Point2f> img_points;
        cv::projectPoints(obj_points, rvec, tvec, cameraMatrix, distCoeffs, img_points);
        const int thickness = 2;
        const cv::Scalar color = cv::Scalar(0, 0, 255);
        for (int i = 0; i < 4; ++i) {
            cv::line(img_front, img_points[i], img_points[(i + 1) % 4], color, thickness);
        }

        cv::resize(img_[0], img_front, cv::Size(), 0.5, 0.6, cv::INTER_LINEAR);
        cv::resize(img_[1], img_right, cv::Size(), 0.25, 0.3, cv::INTER_LINEAR);
        cv::resize(img_[3], img_left, cv::Size(), 0.25, 0.3, cv::INTER_LINEAR);
        cv::resize(img_[2], img_back, cv::Size(), 0.18, 0.1, cv::INTER_LINEAR);
        cv::resize(img_[3], img_left_front, cv::Size(), 0.25, 0.3, cv::INTER_LINEAR);
        cv::resize(img_[1], img_right_front, cv::Size(), 0.25, 0.3, cv::INTER_LINEAR);

        std::vector<unsigned char> buf_front;
        std::vector<unsigned char> buf_left;
        std::vector<unsigned char> buf_right;
        std::vector<unsigned char> buf_back;
        std::vector<unsigned char> buf_stitch;

        // std::vector<unsigned char> buf_stitch;
        cv::imencode(".jpg", img_front, buf_front);
        cv::imencode(".jpg", img_left, buf_left);
        cv::imencode(".jpg", img_right, buf_right);
        cv::imencode(".jpg", img_back, buf_back);

        // 定义矩形区域的左上角坐标（x, y）和矩形的宽度（width）与高度（height）
        cv::Rect roi_back((img_front.cols - img_back.cols) / 2, 0, img_back.cols, img_back.rows);
        cv::Mat roi_back_rect = img_front(roi_back);
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

        for (std::string cam : request_camera) {
            // AERROR << "camera name :" << cam;
            if (cam == "front") {
                rtc_client_1_.g_BrtcClient->sendImage(
                        reinterpret_cast<const char*>(buf_front.data()), buf_front.size());
                // AERROR<<"start send front image successfully!";
            } else if (cam == "back") {
                rtc_client_3_.g_BrtcClient->sendImage(reinterpret_cast<const char*>(buf_back.data()), buf_back.size());
                // AERROR<<"start send back image successfully!";
            } else if (cam == "left") {
                rtc_client_4_.g_BrtcClient->sendImage(reinterpret_cast<const char*>(buf_left.data()), buf_left.size());
                // AERROR<<"start send left image successfully!";
            } else if (cam == "right") {
                rtc_client_2_.g_BrtcClient->sendImage(
                        reinterpret_cast<const char*>(buf_right.data()), buf_right.size());
                // AERROR<<"start send right image successfully!";
            } else {
                continue;
            }
        }

        rtc_client_.g_BrtcClient->sendImage(reinterpret_cast<const char*>(buf_stitch.data()), buf_stitch.size());
        AINFO << "start send image successfully!";
        auto t2 = cyber::Time::Now().ToSecond();
        AERROR << "time cost : " << (t2 - t1);

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
            }
            if (command["is_start_publish"] == "false") {
                is_start_publish = false;
            }
        }
        if (command.contains("active_cameras")) {
            request_camera = command["active_cameras"].get<std::vector<std::string>>();

            // for (auto& cam : request_camera_.items()){
            //     request_camera.push_back(cam.value());
            // }
        }

        if (input_command_string == "cloud") {
            cloud_takeover = command["takeover"];
            cloud_gear = command["gear"];
            cloud_throttle = command["throttle"];
            cloud_brake = command["brake"];
            cloud_steer = command["steer"];
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
                    -std::stof(cloud_steer));
        }
    }
    rtc_client_.g_mylistener.re_mark = false;
    return true;
}

void ExternalDriver::SendActionCommand(apollo::external_command::ActionCommandType action_command_type) {
    auto command = std::make_shared<apollo::external_command::ActionCommand>();
    FillCommandHeader(command);
    command->set_command(action_command_type);
    AINFO << "Sending action command: " << command->DebugString();
    auto response = action_command_client_->SendRequest(command);
    if (nullptr == response) {
        AERROR << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::SendVehicleSignalCommand() {
    // Send left turn signal.
    auto command = std::make_shared<apollo::external_command::ChassisCommand>();
    FillCommandHeader(command);
    command->mutable_basic_signal()->set_turn_signal(apollo::common::VehicleSignal::TURN_LEFT);
    AINFO << "Sending chassis command: " << command->DebugString();
    auto response = chassis_command_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}
void ExternalDriver::SendCloudControlCommand(
        const bool& cloud_takeover_request,
        const apollo::canbus::Chassis::GearPosition& gear_position,
        const float& throttle,
        const float& brake,
        const float& steering_target) {
    AINFO << "get cloud control command: " << cloud_takeover_request;
    auto command = std::make_shared<apollo::control::ControlCommand>();
    command->set_cloud_takeover_request(cloud_takeover_request);
    command->set_gear_location(gear_position);
    command->set_throttle(throttle * 100);
    command->set_brake(brake * 100);
    command->set_steering_target(steering_target * 100);
    // command->set_driving_mode(apollo::canbus::Chassis::REMOTE_CLOUD_DRIVE);
    // AERROR<< "Sending cloud control command: " << command->DebugString();
    cloud_control_cmd_writer_->Write(command);
}

void ExternalDriver::SendCustomChassisCommand() {
    // Send left turn signal.
    auto command = std::make_shared<apollo::external_command::ChassisCommand>();
    FillCommandHeader(command);
    // Set custom command.
    auto custom_operation = command->mutable_custom_operation();
    // Set custom command values.
    apollo::external_command::SweeperCustomCommand sweeper_command;
    sweeper_command.set_is_turn_on_brush(true);
    sweeper_command.set_sweeping_speed(2.0);
    custom_operation->PackFrom(sweeper_command);
    AINFO << "Sending custom chassis command: " << command->DebugString();
    auto response = chassis_command_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::SendPathFollowCommandWithPathRecord(const std::string& record_path) {
    // Read planning data from record file and use the planning path points
    // as the path of PathFollowCommand.
    apollo::planning::ADCTrajectory record_planning_data;
    // Get the path points from record planning data.
    std::shared_ptr<apollo::external_command::PathFollowCommand> path_follow_command
            = std::make_shared<apollo::external_command::PathFollowCommand>();
    ReadPathFromPathRecord(record_path, path_follow_command->mutable_way_point());
    // Set header and command id of PathFollowCommand.
    FillCommandHeader(path_follow_command);
    // Set path boundary of path.
    auto path_boundary = path_follow_command->mutable_boundary_with_width();
    path_boundary->set_left_path_width(config_.left_path_width());
    path_boundary->set_right_path_width(config_.right_path_width());
    // Set target speed.
    path_follow_command->set_target_speed(config_.target_speed());
    auto response = path_follow_command_client_->SendRequest(path_follow_command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::SendPathFollowCommandWithLocationRecord(const std::string& record_dir) {
    // Read planning data from record file and use the planning path points
    // as the path of PathFollowCommand.
    std::shared_ptr<apollo::external_command::PathFollowCommand> path_follow_command
            = std::make_shared<apollo::external_command::PathFollowCommand>();
    std::vector<std::string> record_files = apollo::cyber::common::ListSubPaths(record_dir, DT_REG);
    std::string dir_prefix = record_dir + '/';
    for (const auto file_name : record_files) {
        ReadPathFromLocationRecord(dir_prefix + file_name, path_follow_command->mutable_way_point());
    }

    // Set header and command id of PathFollowCommand.
    FillCommandHeader(path_follow_command);
    // Set path boundary of path.
    auto path_boundary = path_follow_command->mutable_boundary_with_width();
    path_boundary->set_left_path_width(config_.left_path_width());
    path_boundary->set_right_path_width(config_.right_path_width());
    // Set target speed.
    path_follow_command->set_target_speed(config_.target_speed());
    auto response = path_follow_command_client_->SendRequest(path_follow_command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::SendSpeedCommand(double speed) {
    auto command = std::make_shared<apollo::external_command::SpeedCommand>();
    FillCommandHeader(command);
    command->set_target_speed(speed);
    AINFO << "Sending speed command: " << command->DebugString();
    auto response = speed_command_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::SendSpeedFactorCommand(double speed_factor) {
    auto command = std::make_shared<apollo::external_command::SpeedCommand>();
    FillCommandHeader(command);
    command->set_target_speed_factor(speed_factor);
    AINFO << "Sending speed factor command: " << command->DebugString();
    auto response = speed_command_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::RestoreSpeed() {
    auto command = std::make_shared<apollo::external_command::SpeedCommand>();
    FillCommandHeader(command);
    command->set_is_restore_target_speed(true);
    AINFO << "Restore speed: " << command->DebugString();
    auto response = speed_command_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::SendLaneFollowCommand(
        const std::vector<apollo::external_command::Pose>& way_points,
        const apollo::external_command::Pose& end,
        double target_speed) {
    auto command = std::make_shared<apollo::external_command::LaneFollowCommand>();
    FillCommandHeader(command);
    // Copy way_points
    // for (const auto& point : way_points) {
    //     auto way_point = command->add_way_point();
    //     way_point->CopyFrom(point);
    // }
    // Copy end point
    command->mutable_end_pose()->CopyFrom(end);
    if (target_speed > 0.0) {
        command->set_target_speed(target_speed);
    }
    // command->set_is_start_pose_set(true);
    AINFO << "Sending lane follow command: " << command->DebugString();
    auto response = lane_follow_command_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::SendFreespaceCommand(
        const std::vector<apollo::external_command::Point>& way_points,
        const apollo::external_command::Pose& end) {
    auto command = std::make_shared<apollo::external_command::FreeSpaceCommand>();
    FillCommandHeader(command);
    // Copy way_points
    auto roi_point = command->mutable_drivable_roi();
    for (const auto& point : way_points) {
        roi_point->add_point()->CopyFrom(point);
    }
    // Copy end point
    command->mutable_parking_spot_pose()->CopyFrom(end);
    AINFO << "Sending lane follow command: " << command->DebugString();
    auto response = free_space_command_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}
void ExternalDriver::SendValetParkingCommand(const std::string& parking_spot_id, double target_speed) {
    auto command = std::make_shared<apollo::external_command::ValetParkingCommand>();
    FillCommandHeader(command);
    command->set_parking_spot_id(parking_spot_id);
    if (target_speed > 0.0) {
        command->set_target_speed(target_speed);
    }
    AINFO << "Sending valet parking command: " << command->DebugString();
    auto response = valet_parking_command_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Command sending failed, please check the service is on!\n";
    } else {
        AINFO << "******Finish sending command.******\n";
    }
}

void ExternalDriver::ReadPathFromPathRecord(
        const std::string& record_file,
        google::protobuf::RepeatedPtrField<apollo::external_command::Point>* waypoints) {
    AINFO << "ReadPathFromPathRecord: " << record_file;
    apollo::cyber::record::RecordReader reader(record_file);
    if (!reader.IsValid()) {
        AINFO << "Fail to open " << record_file;
        return;
    }

    apollo::planning::ADCTrajectory planning_trajectory;
    apollo::cyber::record::RecordMessage message;
    while (reader.ReadMessage(&message)) {
        if (message.channel_name == "/apollo/planning") {
            if (planning_trajectory.ParseFromString(message.content)) {
                break;
            }
        }
    }
    waypoints->Clear();
    const auto& trajectory_points = planning_trajectory.trajectory_point();
    for (const auto input_point : trajectory_points) {
        auto output_point = waypoints->Add();
        output_point->set_x(input_point.path_point().x());
        output_point->set_y(input_point.path_point().y());
    }
}

void ExternalDriver::CheckCommandStatus(const uint64_t command_id) {
    auto command = std::make_shared<apollo::external_command::CommandStatusRequest>();
    FillCommandHeader(command);
    command->set_command_id(command_id);
    AINFO << "Sending check command: " << command->DebugString();
    auto response = status_client_->SendRequest(command);
    if (nullptr == response) {
        AINFO << "Check status failed!\n";
    } else {
        AINFO << response->DebugString();
        AINFO << "******Finish checking command.******\n";
    }
}

void ExternalDriver::ReadPathFromLocationRecord(
        const std::string& record_file,
        google::protobuf::RepeatedPtrField<apollo::external_command::Point>* waypoints) const {
    // AINFO << "ReadPathFromLocationRecord: " << record_file ;
    apollo::cyber::record::RecordReader reader(record_file);
    if (!reader.IsValid()) {
        AINFO << "Fail to open " << record_file;
        return;
    }
    apollo::localization::LocalizationEstimate localization;
    apollo::cyber::record::RecordMessage message;
    double last_x = 0.0;
    double last_y = 0.0;
    bool is_last_poistion_set = false;
    while (reader.ReadMessage(&message)) {
        if (message.channel_name == "/apollo/localization/pose") {
            if (localization.ParseFromString(message.content)) {
                const auto& position = localization.pose().position();
                if (!is_last_poistion_set) {
                    last_x = position.x();
                    last_y = position.y();
                    is_last_poistion_set = true;
                    continue;
                }
                // Save the location to path with min_distance.
                if (abs(last_x - position.x()) > config_.min_distance_error()
                    || abs(last_y - position.y()) > config_.min_distance_error()) {
                    auto output_point = waypoints->Add();
                    output_point->set_x(position.x());
                    output_point->set_y(position.y());
                    last_x = position.x();
                    last_y = position.y();
                }
            }
        }
    }
}
}  // namespace external_command
}  // namespace apollo
