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
 * @file remote_drive_component.cc
 *****************************************************************************/

#include "modules/remote_drive/remote_drive_component.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <inttypes.h>
#include <unistd.h>
#include "opencv2/opencv.hpp"

namespace apollo {
namespace remote {

bool RemoteDrive::Init() {
    RemoteDriveMsg video_param;
    if (!GetProtoConfig(&video_param)) {
        AERROR << "Failed to load remote_drive config file ";
        return false;
    }

    AINFO << "Init RemoteDrive succedded.";
    InitMainVideoroom(video_param);
    InitSetListener(g_BrtcClient, g_mylistener);
    cloud_control_cmd_writer_ = node_->CreateWriter<ControlCommand>(cloud_topic);
    return true;
}

// RTC_MESSAGE_ROOM_EVENT_LOGIN_OK                    = 100,
// RTC_MESSAGE_ROOM_EVENT_LOGIN_TIMEOUT               = 101,
// RTC_MESSAGE_ROOM_EVENT_LOGIN_ERROR                 = 102,
// RTC_MESSAGE_ROOM_EVENT_CONNECTION_LOST             = 103,
// RTC_MESSAGE_ROOM_EVENT_REMOTE_COMING               = 104,
// RTC_MESSAGE_ROOM_EVENT_REMOTE_LEAVING              = 105,
// RTC_MESSAGE_ROOM_EVENT_REMOTE_RENDERING            = 106,
// RTC_MESSAGE_ROOM_EVENT_REMOTE_GONE                 = 107,
// RTC_MESSAGE_ROOM_EVENT_SERVER_ERROR                = 108,

// RTC_ROOM_EVENT_AVAILABLE_SEND_BITRATE      		   = 200,
// RTC_ROOM_EVENT_FORCE_KEY_FRAME          		   = 201,

// RTC_ROOM_EVENT_ON_USER_JOINED_ROOM                 = 300,
// RTC_ROOM_EVENT_ON_USER_LEAVING_ROOM                = 301,
// RTC_ROOM_EVENT_ON_USER_MESSAGE             		   = 302,
// RTC_ROOM_EVENT_ON_USER_ATTRIBUTE                   = 303,

// RTC_MESSAGE_STATE_STREAM_UP                        = 2000,
// RTC_MESSAGE_STATE_SENDING_MEDIA_OK                 = 2001,
// RTC_MESSAGE_STATE_SENDING_MEDIA_FAILED             = 2002,
// RTC_MESSAGE_STATE_STREAM_DOWN                      = 2003,
// RTC_STATE_STREAM_SLOW_LINK_NACKS                   = 2100,
bool RemoteDrive::Proc(
        const std::shared_ptr<apollo::drivers::Image>& fr_msg,
        const std::shared_ptr<apollo::drivers::Image>& rr_msg,
        const std::shared_ptr<apollo::drivers::Image>& lf_msg,
        const std::shared_ptr<apollo::drivers::Image>& rh_msg) {
    if (g_mylistener.message_type == RtcMessageType::RTC_ROOM_EVENT_ON_USER_JOINED_ROOM
        || g_mylistener.message_type == RtcMessageType::RTC_MESSAGE_STATE_STREAM_UP
        || g_mylistener.message_type == RtcMessageType::RTC_ROOM_EVENT_ON_USER_MESSAGE
        || g_mylistener.message_type == RtcMessageType::RTC_MESSAGE_ROOM_EVENT_REMOTE_COMING
        || g_mylistener.message_type == RtcMessageType::RTC_STATE_STREAM_SLOW_LINK_NACKS) {
        SendMsg(fr_msg, rr_msg, lf_msg, rh_msg);
        AINFO << "message sent successfully.";
    }

    ControlCommand control_command;

    CloudControlCommand(&control_command);
    cloud_control_cmd_writer_->Write(control_command);
    return true;
}
bool RemoteDrive::SendMsg(
        const std::shared_ptr<apollo::drivers::Image>& fr_msg,
        const std::shared_ptr<apollo::drivers::Image>& rr_msg,
        const std::shared_ptr<apollo::drivers::Image>& lf_msg,
        const std::shared_ptr<apollo::drivers::Image>& rh_msg) {
    cv::Mat img_front(fr_msg->height(), fr_msg->width(), CV_8UC3, const_cast<char*>(fr_msg->data().data()));
    cv::Mat img_rear(rr_msg->height(), rr_msg->width(), CV_8UC3, const_cast<char*>(rr_msg->data().data()));
    cv::Mat img_left(lf_msg->height(), lf_msg->width(), CV_8UC3, const_cast<char*>(lf_msg->data().data()));
    cv::Mat img_right(rh_msg->height(), rh_msg->width(), CV_8UC3, const_cast<char*>(rh_msg->data().data()));

    // cv::resize(img_rear,img_rear,cv::Size(),0.25,0.25);
    cv::resize(img_left, img_left, cv::Size(), 0.35, 0.35);
    cv::resize(img_right, img_right, cv::Size(), 0.35, 0.35);

    std::string rear_image_text = "Rear Image";
    std::string left_image_text = "Left Image";
    std::string right_image_text = "Right Image";
    cv::Scalar color(0, 0, 255);

    cv::putText(img_rear, rear_image_text, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 1, cv::LINE_AA);
    cv::putText(img_left, left_image_text, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 1, cv::LINE_AA);
    cv::putText(img_right, right_image_text, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 1, cv::LINE_AA);

    cv::Rect roi_left(0, 0, img_left.cols, img_left.rows);
    cv::Rect roi_right(img_front.cols - img_right.cols, 0, img_right.cols, img_right.rows);

    cv::Mat roi_left_rect = img_front(roi_left);
    cv::Mat roi_right_rect = img_front(roi_right);

    img_left.copyTo(roi_left_rect);
    img_right.copyTo(roi_right_rect);
    
    double fx = 1800.66, fy = 1800.66, cx = 800.0, cy = 453.0, k1 = -0.54, k2 = 0.276, p1 = -0.0015, p2 = 0.0055, k3 = 0.0;
    cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
    cv::Mat dist_coeffs = (cv::Mat_<double>(1, 5) << k1, k2, p1, p2, k3);
    std::vector<cv::Point3f> objectPoints;
    std::vector<cv::Point2f> imagePoints;
    imagePoints.resize(1);
    cv::Mat tvec = (cv::Mat_<double>(3, 1) << 0, 0, 0);
    objectPoints.push_back(cv::Point3f(-2, 2.4, 6));
    objectPoints.push_back(cv::Point3f(2, 2.4, 6));
    objectPoints.push_back(cv::Point3f(2, 2.6, 16));
    objectPoints.push_back(cv::Point3f(-2, 2.6, 16));

    cv::projectPoints(objectPoints, cv::Mat::zeros(3, 1, CV_64F), tvec, camera_matrix, dist_coeffs, imagePoints);
    AERROR << "imagePoints_: " << imagePoints[0];

    cv::line(img_front, imagePoints[0], imagePoints[1], cv::Scalar(255, 0, 0), 2);
    cv::line(img_front, imagePoints[1], imagePoints[2], cv::Scalar(255, 0, 0), 2);
    cv::line(img_front, imagePoints[2], imagePoints[3], cv::Scalar(255, 0, 0), 2);
    cv::line(img_front, imagePoints[3], imagePoints[0], cv::Scalar(255, 0, 0), 2);

    std::vector<unsigned char> buf;
    cv::imencode(".jpg", img_front, buf);
    // cv::imwrite("/apollo_workspace/data/test.jpg", img_front);
    // AERROR << "buf size: " << buf.size()*sizeof(char);

    g_BrtcClient->sendImage(reinterpret_cast<const char*>(buf.data()), buf.size());
    // cv::imshow("RemoteDrive", img_front);
    // cv::waitKey(1);
    return true;
}

void RemoteDrive::InitSetListener(baidurtc::BaiduRtcRoomClient* c, MyListener& l) {
    c->registerRtcMessageListener(&l);
};

void MyListener::OnRtcMessage(RtcMessage& msg) {
    message_type = msg.msgType;
    AINFO << "message type: " << message_type;
    switch (msg.msgType) {
    case RtcMessageType::RTC_ROOM_EVENT_ON_USER_MESSAGE:
        recieve_msg = msg.extra_info;
        AINFO << "recieved cloud message: -----" << msg.extra_info;
        // g_BrtcClient->sendMessageToUser("remote drive demo!!!!!!!!", "0");
        break;
    case RtcMessageType::RTC_ROOM_EVENT_ON_USER_LEAVING_ROOM:
        recieve_msg = "";
        AINFO << "user leaving room";
        break;
    default:
        break;
    }
}

bool RemoteDrive::InitMainVideoroom(const RemoteDriveMsg& video_param) {
    void* handle = dlopen("modules/remote_drive/lib/libbaidurtc.so", RTLD_LAZY | RTLD_DEEPBIND);
    if (handle == NULL) {
        fprintf(stderr, "Could not open sdk: %s\n", dlerror());
        return false;
    }

    f_createBaiduRtcRoomClient* createClient
            = (f_createBaiduRtcRoomClient*)dlsym(handle, "_ZN8baidurtc24createBaiduRtcRoomClientEv");
    f_enableLog* enableLog = (f_enableLog*)dlsym(handle, "enableBaiduRtcLog");
    if (enableLog) {
        enableLog(0);
    }
    g_BrtcClient = createClient();

    s.HasData = true;
    s.HasVideo = true;
    s.HasAudio = true;
    s.AudioINChannel = 1;
    s.AudioINFrequency = 16000;
    s.ImageINType = RTC_IMAGE_TYPE_JPEG;

    s.AsPublisher = true;
    s.AsListener = false;
    s.AutoPublish = true;
    s.VideoFps = video_param.fps();
    s.VideoMaxkbps = video_param.videomaxkbps();
    s.VideoWidth = video_param.imagewidth();
    s.VideoHeight = video_param.imageheight();
    // s.AutoSubscribe = true;

    // g_BrtcClient->setFeedId("999999");
    g_BrtcClient->setParamSettings(&s, s.RTC_PARAM_SETTINGS_ALL);
    g_BrtcClient->setAppID("appqemmzy5zk1im");
    g_BrtcClient->setMediaServerURL("wss://rtc.exp.bcelive.com/janus");
    g_BrtcClient->setCER("/apollo/modules/remote_drive/lib/a.cer");

    std::string uid;
    std::ostringstream os;
    os << 1234500000 + rand() / 100000;
    uid = os.str();

    g_BrtcClient->loginRoom("2131", uid.c_str(), "XMT018", "token");
    return true;
}

bool RemoteDrive::CloudControlCommand(ControlCommand* control_command) {
    auto header_time = cyber::Time::Now().ToSecond();
    control_command->mutable_header()->set_timestamp_sec(header_time);
    control_command->mutable_header()->set_module_name("remote_drive");
    seq_num = seq_num + 1;
    control_command->mutable_header()->set_sequence_num(seq_num);
    if (!g_mylistener.recieve_msg.empty()) {
        std::istringstream iss(g_mylistener.recieve_msg);
        std::string pair, key, value;

        while (std::getline(iss, pair, ',')) {
            std::size_t pos = pair.find(':');
            if (pos != std::string::npos) {
                key = pair.substr(0, pos);
                value = pair.substr(pos + 1);

                if (key == "throttle") {
                    control_command->set_throttle(std::stod(value));
                } else if (key == "brake") {
                    control_command->set_brake(std::stod(value));
                } else if (key == "cloud_takeover_request") {
                    bool status = false;
                    if (value == "true") {
                        status = true;
                    }
                    control_command->set_cloud_takeover_request(status);
                } else {
                    AERROR << "no cloud control message----";
                }
            }
        }
    } else {
        control_command->set_throttle(0);
        control_command->set_brake(0.5);
        control_command->set_cloud_takeover_request(false);
    }
    return true;
}
}  // namespace remote
}  // namespace apollo