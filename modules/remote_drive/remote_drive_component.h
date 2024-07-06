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
 * @file remote_drive_component.h
 *****************************************************************************/

#pragma once
#include <memory>
#include <string>
#include "cyber/cyber.h"
#include "cyber/component/component.h"
#include "modules/remote_drive/proto/remote_drive.pb.h"
#include "modules/common_msgs/sensor_msgs/sensor_image.pb.h"
#include "modules/remote_drive/include/BaiduRtcInterface.h"
#include "modules/common_msgs/control_msgs/control_cmd.pb.h"
#include "cyber/time/time.h"


namespace apollo {
namespace remote {
using namespace apollo::control;

class MyListener : public IRtcMessageListener {
public:
    int message_type = 0;
    void OnRtcMessage(RtcMessage& msg) override;
    std::string recieve_msg;
};

class RemoteDrive final : public cyber::Component<
                                  apollo::drivers::Image,
                                  apollo::drivers::Image,
                                  apollo::drivers::Image,
                                  apollo::drivers::Image> {
public:
    RemoteDrive() = default;
    ~RemoteDrive() = default;
    bool Init() override;
    bool Proc(
            const std::shared_ptr<apollo::drivers::Image>& fr_msg,
            const std::shared_ptr<apollo::drivers::Image>& rr_msg,
            const std::shared_ptr<apollo::drivers::Image>& lf_msg,
            const std::shared_ptr<apollo::drivers::Image>& rh_msg) override;

private:
    // apollo::remote::RemoteDriveConfig config_;
    baidurtc::BaiduRtcRoomClient* g_BrtcClient = nullptr;
    typedef baidurtc::BaiduRtcRoomClient* f_createBaiduRtcRoomClient();
    RtcParameterSettings s;
    typedef void f_enableLog(int e);
    MyListener g_mylistener;
    IDataFrameObserver* iDfo[2];
    std::shared_ptr<cyber::Writer<ControlCommand>> cloud_control_cmd_writer_;
    std::string cloud_topic = "/apollo/cloud_control";
    int seq_num = 0;
    
    // std::shared_ptr<ControlCommand> control_command;

private:
    void InitSetListener(baidurtc::BaiduRtcRoomClient* c, MyListener& l);
    bool InitMainVideoroom(const RemoteDriveMsg& video_param);
    bool SendMsg(
            const std::shared_ptr<apollo::drivers::Image>& fr_msg,
            const std::shared_ptr<apollo::drivers::Image>& rr_msg,
            const std::shared_ptr<apollo::drivers::Image>& lf_msg,
            const std::shared_ptr<apollo::drivers::Image>& rh_msg);
    bool CloudControlCommand(ControlCommand *control_command);

};



CYBER_REGISTER_COMPONENT(RemoteDrive);

}  // namespace remote
}  // namespace apollo
