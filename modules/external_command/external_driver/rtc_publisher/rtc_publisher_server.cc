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
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "rtc_publisher.grpc.pb.h"
#include "rtc_publisher_brtc.h"
#include "MultiMedia.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
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

namespace apollo {
namespace external_command {

// Logic and data behind the server's behavior.
class RtcPublisherServiceImpl final : public RtcPublisher::Service {
public:
    Status Create(ServerContext* context, const CreateRequest* request, CreateResponse* reply) override {
        bool is_success = true;
        is_success = RtcPublisherBrtc::GetInstance().CreateClient(*request);
        reply->set_success(is_success);
        std::cout << "SERVER: CreateClient " << request->camera_name() << " , is_success:" << is_success << std::endl;
        return Status::OK;
    }

    Status Destroy(ServerContext* context, const DestroyRequest* request, DestroyResponse* reply) override {
        bool is_success = RtcPublisherBrtc::GetInstance().DestroyClient(*request);
        reply->set_success(is_success);
        std::cout << "SERVER: DestroyClient " << request->camera_name() << " , is_success:" << is_success << std::endl;
        return Status::OK;
    }

    Status SendFrame(ServerContext* context, const SendFrameRequest* request, SendFrameResponse* reply) override {
        bool is_success = RtcPublisherBrtc::GetInstance().SendFrame(*request);
        reply->set_success(is_success);
        // std::cout << "SERVER: SendFrame , is_success:" << is_success << std::endl;
        return Status::OK;
    }

    Status SendUserMessage(
            ServerContext* context,
            const SendUserMessageRequest* request,
            SendUserMessageResponse* reply) override {
        bool is_success = RtcPublisherBrtc::GetInstance().SendUserMessage(*request);
        reply->set_success(is_success);
        // std::cout << "SERVER: SendUserMessage , is_success:" << is_success << std::endl;
        return Status::OK;
    }

    Status RecvUserMessage(
            ServerContext* context,
            const RecvUserMessageRequest* request,
            RecvUserMessageResponse* reply) override {
        std::string message;
        bool is_new_msg = false;
        RtcPublisherBrtc::GetInstance().RecvUserMessage(message, is_new_msg);
        reply->set_message(message);
        reply->set_is_new(is_new_msg);
        // std::cout << "SERVER: RecvUserMessage , is_new:" << is_new_msg << std::endl;

        return Status::OK;
    }
};

}  // namespace external_command
}  // namespace apollo

void RunServer() {
    std::string server_address("localhost:58051");
    apollo::external_command::RtcPublisherServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    builder.SetMaxReceiveMessageSize(64 * 1024 * 1024);
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    apollo::external_command::MultiMedia::sys_init();
    std::cout << "RtcPublisherServer is running..." << std::endl;
    RunServer();
    apollo::external_command::MultiMedia::sys_exit();
    return 0;
}
