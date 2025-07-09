#pragma once

#include <stdio.h>
#include "rtc_client.h"
#include "VideoEncoder.h"
#include "ImageUtil.hpp"
#include "MultiMedia.h"
#include <grpcpp/grpcpp.h>
#include "rtc_publisher.grpc.pb.h"

namespace apollo {
namespace external_command {

class RtcPublisherBrtc {
public:
    struct RtcPublisherHandle {
        std::string name;
        std::shared_ptr<RtcClient> p_rtc_client;
        std::shared_ptr<VideoEncoder> p_video_encoder;
    };
    ~RtcPublisherBrtc() {
        if (rtc_publisher_handle_map_.size() > 0)
            for (auto it = rtc_publisher_handle_map_.begin(); it != rtc_publisher_handle_map_.end(); ++it) {
                if (it->second != nullptr) {
                    rtc_publisher::DestroyRequest request;
                    request.set_camera_name(it->first);
                    DestroyClient(request);
                }
            }
        rtc_publisher_handle_map_.clear();
    }

    RtcPublisherBrtc(RtcPublisherBrtc const&) = delete;
    RtcPublisherBrtc& operator=(RtcPublisherBrtc const&) = delete;
    static RtcPublisherBrtc& GetInstance() {
        static RtcPublisherBrtc rtc_publisher_brtc;
        return rtc_publisher_brtc;
    }

    bool CreateClient(const rtc_publisher::CreateRequest& request);
    bool DestroyClient(const rtc_publisher::DestroyRequest& request);
    bool SendFrame(const rtc_publisher::SendFrameRequest& request);
    bool SendUserMessage(const rtc_publisher::SendUserMessageRequest& request);
    bool RecvUserMessage(std::string& message, bool& is_new_msg);

    void FrameReady(std::string name, uint8_t* data, int size, VideoEncoder::FrameType frame_type, uint64_t timestamp);

private:
    RtcPublisherBrtc() = default;
    std::map<std::string, std::shared_ptr<RtcPublisherBrtc::RtcPublisherHandle>> rtc_publisher_handle_map_;

    ImageUtil::Rect stitch_rect_[6]
            = {{480, 360, 960, 720},
               {1440, 90, 480, 360},
               {1440, 630, 480, 360},
               {720, 0, 480, 360},
               {0, 630, 480, 360},
               {0, 90, 480, 360}};

    std::map<std::string, int> cam_idx_map_
            = {{"front", 0}, {"right_front", 1}, {"right", 2}, {"back", 3}, {"left", 4}, {"left_front", 5}};
    std::vector<std::string> rtc_id_list_;

    void write_data_to_file(const std::string& filename, const void* data, size_t size) {
        FILE* file = fopen(filename.c_str(), "wb");
        if (file == nullptr) {
            std::cout << "write_data_to_file: open file failed. filename = " << filename << std::endl;
            return;
        }
        fwrite(data, size, 1, file);
        fclose(file);
    }
    bool src_write_done = false;
    bool stitch_write_done = false;
};

}  // namespace external_command
}  // namespace apollo