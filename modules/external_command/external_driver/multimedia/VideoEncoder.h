#pragma once

#include <string>
#include <functional>
#include <mutex>
#include <thread>
#include <map>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include "rk_type.h"
#include "rk_debug.h"
#include "rk_mpi_sys.h"
#include "rk_mpi_mb.h"
#include "rk_mpi_venc.h"
#include "rk_mpi_tde.h"

namespace apollo {
namespace external_command {

class VideoEncoder {
public:
    enum class FrameType : uint8_t { UNSPECIFIED = 0x0, I_FRAME = 0x1, P_FRAME = 0x2, B_FRAME = 0x3 };
    VideoEncoder(
            const std::string &name,
            uint32_t pixel_fmt,
            uint32_t width,
            uint32_t height,
            uint32_t encode_codec,
            uint32_t encode_width,
            uint32_t encode_height) :
            name_(name),
            pixel_format_(static_cast<PIXEL_FORMAT_E>(pixel_fmt)),
            input_width_(width),
            input_height_(height),
            encode_codec_(static_cast<RK_CODEC_ID_E>(encode_codec)),
            encode_width_(encode_width),
            encode_height_(encode_height) {}
    ~VideoEncoder() {}

    bool init(uint32_t bps, uint32_t gop);
    bool start();
    bool stop();
    bool release();

    int register_encode_frame_ready_cb(
            std::function<void(std::string name, uint8_t *, int, VideoEncoder::FrameType, uint64_t)> callback);

    void *get_input_buffer(MB_BLK &dma_handle);
    int put_input_buffer(MB_BLK &dma_handle);

    static uint32_t get_avail_channel_id();
    static void put_avail_channel_id(uint32_t id);

    bool setTargetBitrate(int64_t bps);
    void requestSyncFrame();

    static std::mutex channel_mutex_;
    static std::map<uint32_t, bool> channel_info_;

private:
    int get_stream();
    VideoEncoder::FrameType get_frame_type(VENC_PACK_S *pack_info);
    bool release_inner();
    int32_t set_one_stream_buffer();
    int32_t create_channel(uint32_t kbps, uint32_t gop);
    int32_t set_bitrate(VENC_RC_ATTR_S *p_rc_attr, uint32_t avg_bitrate, uint32_t max_bitrate, uint32_t min_bitrate);

    std::string name_;

    PIXEL_FORMAT_E pixel_format_;
    uint32_t input_width_;
    uint32_t input_height_;

    RK_CODEC_ID_E encode_codec_;
    uint32_t encode_width_;
    uint32_t encode_height_;

    uint32_t pre_alloc_buffer_size_;

    MB_POOL venc_pool_input_;
    MB_POOL venc_pool_output_;

    RK_U32 venc_channel_id_{0xffffffff};

    bool is_init_{false};
    bool is_started_{false};
    bool is_stop_{false};

    std::function<void(std::string, uint8_t *, uint64_t, VideoEncoder::FrameType, int64_t)> frame_callback_;
    void *frame_callback_param_{nullptr};

    std::thread get_stream_thrd_;
};

}  // namespace external_command
}  // namespace apollo
