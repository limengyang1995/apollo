/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "cyber/common/log.h"
#include "rtc_publisher.grpc.pb.h"
#include "rtc_publisher_client.h"

namespace apollo {
namespace drivers {
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using rtc_publisher::CreateRequest;
using rtc_publisher::CreateResponse;
using rtc_publisher::DestroyRequest;
using rtc_publisher::DestroyResponse;
using rtc_publisher::RecvUserMessageRequest;
using rtc_publisher::RecvUserMessageResponse;
using rtc_publisher::RtcPublisher;
using rtc_publisher::SendFrameRequest;
using rtc_publisher::SendFrameResponse;
using rtc_publisher::SendUserMessageRequest;
using rtc_publisher::SendUserMessageResponse;

bool RtcPublisherClient::Create(
        std::string camera_name,
        std::string app_id,
        std::string cer_path,
        std::string car_id,
        int32_t video_maxkbps,
        int32_t image_width,
        int32_t image_height,
        uint32_t pixel_fmt,
        uint32_t encode_codec,
        uint32_t origin_width,
        uint32_t origin_height) {
    // Data we are sending to the server.
    CreateRequest request;
    request.set_camera_name(camera_name);
    request.set_app_id(app_id);
    request.set_cer_path(cer_path);
    request.set_car_id(car_id);
    request.set_video_maxkbps(video_maxkbps);
    request.set_image_width(image_width);
    request.set_image_height(image_height);
    request.set_pixel_fmt(pixel_fmt);
    request.set_encode_codec(encode_codec);
    request.set_origin_width(origin_width);
    request.set_origin_height(origin_height);
    // Container for the data we expect from the server.
    CreateResponse reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Create(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        AERROR << "CLIENT: excuted create success";
        return reply.success();
    }
    AERROR << status.error_code() << ": " << status.error_message();
    return false;
}

bool RtcPublisherClient::Destroy(std::string camera_name) {
    DestroyRequest request;
    request.set_camera_name(camera_name);
    DestroyResponse reply;
    ClientContext context;
    Status status = stub_->Destroy(&context, request, &reply);
    if (status.ok()) {
        AERROR << "CLIENT: excuted destroy success";
        return reply.success();
    }
    AERROR << status.error_code() << ": " << status.error_message();
    return false;
}

bool RtcPublisherClient::SendFrame(
        const std::map<std::string, std::shared_ptr<apollo::drivers::Image>>& imgs,
        const std::vector<std::string>& request_stream_name) {
    AERROR << "CLIENT: excute push image start";
    SendFrameRequest request;
    for (auto img : imgs) {
        auto image_pb = request.add_frame_info();
        image_pb->set_camera_name(img.first);
        if (img.second != nullptr) {
            image_pb->set_frame_data(img.second->data().data(), img.second->data().size());
            image_pb->set_frame_width(img.second->width());
            image_pb->set_frame_height(img.second->height());
        }
    }
    AERROR << "CLIENT: excuted push image end";
    for (auto stream_name : request_stream_name) {
        request.add_request_stream_name(stream_name);
    }
    SendFrameResponse reply;
    ClientContext context;
    Status status = stub_->SendFrame(&context, request, &reply);
    if (status.ok()) {
        AERROR << "CLIENT: excuted send frame success";
        return reply.success();
    }
    AERROR << status.error_code() << ": " << status.error_message();
    return false;
}

bool RtcPublisherClient::SendUserMessage(std::string message) {
    SendUserMessageRequest request;
    request.set_message(message);
    SendUserMessageResponse reply;
    ClientContext context;
    Status status = stub_->SendUserMessage(&context, request, &reply);
    if (status.ok()) {
        AERROR << "CLIENT: excuted send user message success";
        return reply.success();
    }
    AERROR << status.error_code() << ": " << status.error_message();
    return false;
}

bool RtcPublisherClient::RecvUserMessage(std::string& message, bool& is_new_msg) {
    RecvUserMessageRequest request;
    RecvUserMessageResponse reply;
    ClientContext context;
    Status status = stub_->RecvUserMessage(&context, request, &reply);
    if (status.ok()) {
        message = reply.message();
        is_new_msg = true;
        AERROR << "CLIENT: excuted recv user message success";
        return reply.success();
    }
    AERROR << status.error_code() << ": " << status.error_message();
    is_new_msg = false;
    return false;
}

}  // namespace drivers
}  // namespace apollo