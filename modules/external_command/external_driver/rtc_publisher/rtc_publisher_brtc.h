#pragma once

#include <stdio.h>
#include "rtc_client.h"
#include "VideoEncoder.h"
#include "ImageUtil.hpp"
#include "MultiMedia.h"
#include "modules/common_msgs/sensor_msgs/sensor_image.pb.h"
// #include <grpcpp/grpcpp.h>
// #include "rtc_publisher.grpc.pb.h"

namespace apollo {
namespace external_command {

class RtcPublisherBrtc {
public:
    struct RtcPublisherHandle {
        std::string name;
        std::shared_ptr<RtcClient> p_rtc_client{nullptr};
        std::shared_ptr<VideoEncoder> p_video_encoder{nullptr};
    };

    struct CreateParam {
        std::string camera_name;
        int32_t video_maxkbps;
        int32_t image_width;
        int32_t image_height;
        std::string cer_path;
        std::string app_id;
        std::string car_id;

        uint32_t pixel_fmt;
        uint32_t encode_codec;
        uint32_t origin_width;
        uint32_t origin_height;
    };
    // struct FrameInfo {
    //     std::string camera_name;
    //     char* frame_data;
    //     int32_t frame_data_size;
    //     int32_t frame_width;
    //     int32_t frame_height;
    // };

    ~RtcPublisherBrtc() {
        if (rtc_publisher_handle_map_.size() > 0)
            for (auto it = rtc_publisher_handle_map_.begin(); it != rtc_publisher_handle_map_.end(); ++it) {
                if (it->second != nullptr) {
                    DestroyClient(it->first);
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

    bool CreateClient(const RtcPublisherBrtc::CreateParam& param);
    bool DestroyClient(const std::string& stream_name);
    bool SendFrame(
            std::map<std::string, std::shared_ptr<apollo::drivers::Image>>& frames,
            const std::vector<std::string>& stream_names);
    bool SendFrame(std::string stream_name, std::shared_ptr<apollo::drivers::Image> frame);
    bool SendUserMessage(const std::string& message);
    bool RecvUserMessage(std::string& message, bool& is_new_msg);

    void RequestSyncFrame(std::string stream_name);

    void FrameReady(std::string name, uint8_t* data, int size, VideoEncoder::FrameType frame_type, uint64_t timestamp);

private:
    RtcPublisherBrtc() = default;
    std::map<std::string, std::shared_ptr<RtcPublisherBrtc::RtcPublisherHandle>> rtc_publisher_handle_map_;

    ImageUtil::Rect stitch_rect_[6]
            = {{480, 0, 960, 720},
               {1440, 0, 480, 360},
               {1440, 360, 480, 360},
               {800, 0, 320, 180},
               {0, 360, 480, 360},
               {0, 0, 480, 360}};

    std::map<std::string, int> cam_idx_map_
            = {{"front", 0}, {"right_front", 1}, {"right", 2}, {"left", 4}, {"left_front", 5}, {"rear", 3}};
    std::vector<std::string> cam_order_list_ = {"front", "right_front", "right", "left", "left_front", "rear"};
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