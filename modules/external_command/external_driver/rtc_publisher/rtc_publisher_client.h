#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "modules/common_msgs/sensor_msgs/sensor_image.pb.h"
#include "rtc_publisher.grpc.pb.h"

using grpc::Channel;
using rtc_publisher::RtcPublisher;

namespace apollo {
namespace drivers {
class RtcPublisherClient {
public:
    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    bool Create(
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
            uint32_t origin_height);
    bool Destroy(std::string camera_name);

    bool SendFrame(
            const std::map<std::string, std::shared_ptr<apollo::drivers::Image>>& imgs,
            const std::vector<std::string>& request_stream_name);

    bool SendUserMessage(std::string message);

    bool RecvUserMessage(std::string& message, bool& is_new_msg);

    static RtcPublisherClient& GetInst() {
        const std::string target_str{"localhost:58051"};
        grpc::ChannelArguments args;
        args.SetInt(GRPC_ARG_MAX_MESSAGE_LENGTH, 64 * 1024 * 1024);
        static RtcPublisherClient inst(grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(), args));
        return inst;
    }

private:
    std::unique_ptr<RtcPublisher::Stub> stub_;

    RtcPublisherClient(std::shared_ptr<Channel> channel) : stub_(RtcPublisher::NewStub(channel)) {}
};

}  // namespace drivers
}  // namespace apollo