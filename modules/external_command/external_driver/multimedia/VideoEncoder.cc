
#include <iostream>
#include "rk_mpi_cal.h"
#include "cyber/common/log.h"
#include "VideoEncoder.h"

namespace apollo {
namespace external_command {

std::map<uint32_t, bool> VideoEncoder::channel_info_;
std::mutex VideoEncoder::channel_mutex_;

bool VideoEncoder::init(uint32_t kbps, uint32_t gop) {
    RK_S32 ret = RK_SUCCESS;
    RK_U32 u32Ch = 0;
    MB_POOL_CONFIG_S stMbPoolCfg;

    if (encode_codec_ != RK_VIDEO_ID_AVC && encode_codec_ != RK_VIDEO_ID_HEVC) {
        // AERROR << "not suported codec: " << encode_codec_;
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: not suported codec: " << encode_codec_ << std::endl;
        return false;
    }

    // AERROR << "src:[" << input_width_ << "|" << input_height_;
    std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: src:[" << input_width_ << "|" << input_height_
              << std::endl;

    PIC_BUF_ATTR_S stPicBufAttr;
    MB_PIC_CAL_S stMbPicCalResult;

    // 获取pixel_format对应的与申请缓冲池buffer大小
    stPicBufAttr.u32Width = input_width_;
    stPicBufAttr.u32Height = input_height_;
    stPicBufAttr.enPixelFormat = pixel_format_;
    stPicBufAttr.enCompMode = COMPRESS_MODE_NONE;
    ret = RK_MPI_CAL_COMM_GetPicBufferSize(&stPicBufAttr, &stMbPicCalResult);
    if (ret != RK_SUCCESS) {
        // AERROR << "get picture buffer size failed, err:0x" << std::hex << ret;
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: get picture buffer size failed, err:0x" << std::hex
                  << ret << std::dec << std::endl;
        return false;
    }
    pre_alloc_buffer_size_ = stMbPicCalResult.u32MBSize;

    std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: calc picture size:" << pre_alloc_buffer_size_
              << " vir_w:" << stMbPicCalResult.u32VirWidth << " vir_h:" << stMbPicCalResult.u32VirHeight << std::endl;

    // AERROR << "calc picture size:" << pre_alloc_buffer_size_;

    // 申请输入缓冲池
    memset(&stMbPoolCfg, 0, sizeof(MB_POOL_CONFIG_S));
    stMbPoolCfg.u64MBSize = pre_alloc_buffer_size_;
    stMbPoolCfg.u32MBCnt = 3;
    stMbPoolCfg.enAllocType = MB_ALLOC_TYPE_DMA;
    stMbPoolCfg.bPreAlloc = RK_TRUE;
    venc_pool_input_ = RK_MPI_MB_CreatePool(&stMbPoolCfg);
    if (venc_pool_input_ == MB_INVALID_POOLID) {
        // AERROR << "create vencPoolInput failed!";
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: create vencPoolInput failed!" << std::endl;
        return false;
    }

    // 设置编码模式
    set_one_stream_buffer();

    // 创建编码通道
    ret = create_channel(kbps, gop);
    if (ret != RK_SUCCESS) {
        // AERROR << "create venc channel failed, err:0x" << std::hex << ret;
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: create venc channel failed, err:0x" << std::hex
                  << ret << std::dec << std::endl;
        return ret;
    }

    memset(&stMbPoolCfg, 0, sizeof(MB_POOL_CONFIG_S));
    stMbPoolCfg.u64MBSize = pre_alloc_buffer_size_;
    stMbPoolCfg.u32MBCnt = 3;
    stMbPoolCfg.enAllocType = MB_ALLOC_TYPE_DMA;
    stMbPoolCfg.bPreAlloc = RK_TRUE;  //  this must prealloc if attach enc output
    venc_pool_output_ = RK_MPI_MB_CreatePool(&stMbPoolCfg);
    if (venc_pool_output_ == MB_INVALID_POOLID) {
        // AERROR << "create vencPoolOutput " << venc_channel_id_ << " failed!";
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: create vencPoolOutput " << venc_channel_id_
                  << " failed!" << std::endl;
        return false;
    }

    ret = RK_MPI_VENC_AttachMbPool(venc_channel_id_, venc_pool_output_);
    if (ret != RK_SUCCESS) {
        // AERROR << "RK_MPI_VENC_AttachMbPool fail:0x" << std::hex << ret;
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: RK_MPI_VENC_AttachMbPool fail:0x" << std::hex << ret
                  << std::dec << std::endl;
        release_inner();
        return false;
    }

    is_init_ = true;

    return true;
}

bool VideoEncoder::start() {
    if (is_init_ == false) {
        return false;
    }

    VENC_RECV_PIC_PARAM_S stRecvParam;
    memset(&stRecvParam, 0, sizeof(VENC_RECV_PIC_PARAM_S));
    stRecvParam.s32RecvPicNum = -1;
    RK_MPI_VENC_StartRecvFrame(venc_channel_id_, &stRecvParam);
    get_stream_thrd_ = std::move(std::thread(std::bind(&VideoEncoder::get_stream, this)));

    is_started_ = true;

    return true;
}

bool VideoEncoder::stop() {
    RK_S32 ret = RK_SUCCESS;
    if (is_started_ == false) {
        return false;
    }

    is_stop_ = true;
    usleep(150000);

    if (get_stream_thrd_.joinable()) {
        get_stream_thrd_.join();
    }

    RK_MPI_VENC_StopRecvFrame(venc_channel_id_);

    ret = RK_MPI_VENC_DetachMbPool(venc_channel_id_);
    if (ret != RK_SUCCESS) {
        // AERROR << "channel:" << venc_channel_id_ << "RK_MPI_VENC_DetachMbPool failed:0x" << std::hex << ret;
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: channel:" << venc_channel_id_
                  << "RK_MPI_VENC_DetachMbPool failed:0x" << std::hex << ret << std::dec << std::endl;
    }

    return true;
}

bool VideoEncoder::release() {
    return release_inner();
}

int VideoEncoder::register_encode_frame_ready_cb(
        std::function<void(std::string, uint8_t *, int, VideoEncoder::FrameType, uint64_t)> frame_callback) {
    frame_callback_ = std::move(frame_callback);
    return 0;
}

void *VideoEncoder::get_input_buffer(MB_BLK &dma_handle) {
    // 从视频编码池中获取MB_BLK块
    MB_BLK blk = RK_MPI_MB_GetMB(venc_pool_input_, pre_alloc_buffer_size_, RK_TRUE);
    if (blk == RK_NULL) {
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: RK_MPI_MB_GetMB failed!" << std::endl;
        return nullptr;
    }
    dma_handle = blk;
    void *vir_addr = RK_MPI_MB_Handle2VirAddr(blk);
    if (vir_addr == nullptr) {
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: RK_MPI_MB_Handle2VirAddr failed!" << std::endl;
        RK_MPI_MB_ReleaseMB(blk);
        return nullptr;
    }
    return vir_addr;
}

int VideoEncoder::put_input_buffer(MB_BLK &dma_handle) {
    RK_S32 ret;
    if (dma_handle == RK_NULL) {
        std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: dma_handle is null!" << std::endl;
        return -1;
    }
    RK_MPI_SYS_MmzFlushCache(dma_handle, RK_FALSE);
    std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]---------------------------" << std::endl;
    VIDEO_FRAME_INFO_S stFrame;
    memset(&stFrame, 0, sizeof(VIDEO_FRAME_INFO_S));

    stFrame.stVFrame.pMbBlk = dma_handle;
    stFrame.stVFrame.u32Width = input_width_;
    stFrame.stVFrame.u32Height = input_height_;
    stFrame.stVFrame.u32VirWidth = input_width_;
    stFrame.stVFrame.u32VirHeight = input_height_;
    stFrame.stVFrame.enPixelFormat = pixel_format_;
    ret = RK_MPI_VENC_SendFrame(venc_channel_id_, &stFrame, 150);  // warnning: if failed, this frame would be lost
    RK_MPI_MB_ReleaseMB(dma_handle);
    std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]---------------------------" << std::endl;
    return ret;
}

uint32_t VideoEncoder::get_avail_channel_id() {
    uint32_t id = 0xffffffff;
    std::lock_guard<std::mutex> lock(channel_mutex_);
    if (channel_info_.empty()) {
        for (uint32_t idx = 0; idx < VENC_MAX_CHN_NUM; idx++) {
            channel_info_.insert(std::make_pair(idx, false));
        }
    }

    for (auto iter = channel_info_.begin(); iter != channel_info_.end(); ++iter) {
        if (iter->second == false) {
            id = iter->first;
            iter->second = true;
            break;
        }
    }

    return id;
}
void VideoEncoder::put_avail_channel_id(uint32_t id) {
    if (id >= VENC_MAX_CHN_NUM || channel_info_.empty()) {
        return;
    }

    std::lock_guard<std::mutex> lock(channel_mutex_);
    auto iter = channel_info_.find(id);
    if (iter != channel_info_.end()) {
        iter->second = false;
    }
}

bool VideoEncoder::setTargetBitrate(int64_t bps) {
    return true;
}
void VideoEncoder::requestSyncFrame() {}

int VideoEncoder::get_stream() {
#if 0
    std::string thread_name = name_ + "_venc";
    os::thread_name(thread_name);
#endif
    if (is_init_ == false) {
        // AERROR << "VideoEncoder is not init";
        return -1;
    }

    VENC_STREAM_S frame;
    RK_S32 ret = RK_SUCCESS;
    frame.pstPack = reinterpret_cast<VENC_PACK_S *>(malloc(sizeof(VENC_PACK_S)));

    while (!is_stop_) {
        frame.u32PackCount = 1;
        ret = RK_MPI_VENC_GetStream(venc_channel_id_, &frame, 150);
        if (ret == RK_SUCCESS) {
            // std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]---------------------------" << std::endl;
            if (frame_callback_) {
                // std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]---------------------------" << std::endl;
                VideoEncoder::FrameType frame_type = get_frame_type(frame.pstPack);
                void *p_data = RK_MPI_MB_Handle2VirAddr(frame.pstPack->pMbBlk);
                uint32_t data_len = frame.pstPack->u32Len;
                uint64_t pts = frame.pstPack->u64PTS;
                frame_callback_(name_, static_cast<uint8_t *>(p_data), data_len, frame_type, pts);
                // std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]---------------------------" << std::endl;
            }
            RK_MPI_VENC_ReleaseStream(venc_channel_id_, &frame);
            // std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]---------------------------" << std::endl;
        } else {
            if (is_stop_) {
                break;
            }

            // AERROR << "chn(" << venc_channel_id_ << ") get stream err:0x" << std::hex << ret;
            // std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]: chn(" << venc_channel_id_
            //           << ") get stream err:0x" << std::hex << ret << std::dec << std::endl;
            usleep(1000llu);
        }
    }
    return 0;
}

VideoEncoder::FrameType VideoEncoder::get_frame_type(VENC_PACK_S *pack_info) {
    VideoEncoder::FrameType frame_type = VideoEncoder::FrameType::P_FRAME;
    if (encode_codec_ == RK_VIDEO_ID_AVC) {
        for (RK_U32 i = 0; i < pack_info->u32DataNum; i++) {
            if (pack_info->stPackInfo[i].u32PackType.enH264EType == H264E_NALU_IDRSLICE
                || pack_info->stPackInfo[i].u32PackType.enH264EType == H264E_NALU_ISLICE) {
                frame_type = VideoEncoder::FrameType::I_FRAME;
                break;
            }
        }
    } else if (encode_codec_ == RK_VIDEO_ID_HEVC) {
        for (RK_U32 i = 0; i < pack_info->u32DataNum; i++) {
            if (pack_info->stPackInfo[i].u32PackType.enH265EType == H265E_NALU_IDRSLICE
                || pack_info->stPackInfo[i].u32PackType.enH265EType == H265E_NALU_ISLICE) {
                frame_type = VideoEncoder::FrameType::I_FRAME;
                break;
            }
        }
    } else {
        return VideoEncoder::FrameType::UNSPECIFIED;
    }

    return frame_type;
}

bool VideoEncoder::release_inner() {
    if (is_started_ == true) {
        stop();
    }

    if (venc_channel_id_ != 0xffffffff) {
        RK_MPI_VENC_DestroyChn(venc_channel_id_);
    }

    if (venc_pool_output_ != MB_INVALID_POOLID) {
        RK_MPI_MB_DestroyPool(venc_pool_output_);
    }

    if (venc_pool_input_ != MB_INVALID_POOLID) {
        RK_MPI_MB_DestroyPool(venc_pool_input_);
    }

    return true;
}

int32_t VideoEncoder::set_one_stream_buffer() {
    VENC_PARAM_MOD_S stModParam;
    RK_S32 ret = RK_FAILURE;

    switch (encode_codec_) {
    case RK_VIDEO_ID_AVC:
        stModParam.enVencModType = MODTYPE_H264E;
        stModParam.stH264eModParam.u32OneStreamBuffer = 1;
        ret = RK_MPI_VENC_SetModParam(&stModParam);
        break;
    case RK_VIDEO_ID_HEVC:
        stModParam.enVencModType = MODTYPE_H265E;
        stModParam.stH265eModParam.u32OneStreamBuffer = 1;
        ret = RK_MPI_VENC_SetModParam(&stModParam);
        break;
        /*
      case RK_VIDEO_ID_JPEG:
      case RK_VIDEO_ID_MJPEG:
        stModParam.enVencModType = MODTYPE_JPEGE;
        stModParam.stJpegeModParam.u32OneStreamBuffer = 1;
        ret = RK_MPI_VENC_SetModParam(&stModParam);
        break;
        */
    default:
        break;
    }

    return ret;
}

int32_t VideoEncoder::create_channel(uint32_t kbps, uint32_t gop) {
    RK_S32 ret = RK_SUCCESS;
    VENC_CHN_ATTR_S ch_attr;
    VENC_RC_MODE_E encode_rc_mode = VENC_RC_MODE_H264VBR;

    memset(&ch_attr, 0, sizeof(VENC_CHN_ATTR_S));

    switch (encode_codec_) {
    case RK_VIDEO_ID_AVC:
        encode_rc_mode = VENC_RC_MODE_H264VBR;
        break;
    case RK_VIDEO_ID_HEVC:
        encode_rc_mode = VENC_RC_MODE_H265VBR;
        break;
    default:
        break;
    }

    ch_attr.stRcAttr.enRcMode = encode_rc_mode;
    uint32_t max_bitrate = kbps * 12 / 10;
    uint32_t min_bitrate = kbps * 8 / 10;
    set_bitrate(&ch_attr.stRcAttr, kbps, max_bitrate, min_bitrate);

    ch_attr.stVencAttr.enType = encode_codec_;
    ch_attr.stVencAttr.u32Profile = H264E_PROFILE_HIGH;
    ch_attr.stVencAttr.enPixelFormat = pixel_format_;
    ch_attr.stVencAttr.u32PicWidth = input_width_;
    ch_attr.stVencAttr.u32PicHeight = input_height_;
    ch_attr.stVencAttr.enMirror = MIRROR_NONE;
    ch_attr.stVencAttr.u32VirWidth = input_width_;
    ch_attr.stVencAttr.u32VirHeight = input_height_;
    ch_attr.stVencAttr.u32StreamBufCnt = 8;
    ch_attr.stVencAttr.u32BufSize = pre_alloc_buffer_size_;

    uint32_t channel_id = get_avail_channel_id();
    if (channel_id >= VENC_MAX_CHN_NUM) {
        // AERROR << "no available venc channel";:1
        return -1;
    }

    ret = RK_MPI_VENC_CreateChn(channel_id, &ch_attr);
    if (ret != RK_SUCCESS) {
        put_avail_channel_id(channel_id);
        return ret;
    }

    venc_channel_id_ = channel_id;

    return 0;
}

int32_t VideoEncoder::set_bitrate(
        VENC_RC_ATTR_S *p_rc_attr,
        uint32_t avg_bitrate,
        uint32_t max_bitrate,
        uint32_t min_bitrate) {
    switch (p_rc_attr->enRcMode) {
    case VENC_RC_MODE_MJPEGCBR:
        p_rc_attr->stMjpegCbr.u32BitRate = avg_bitrate;
        break;
    case VENC_RC_MODE_H264CBR:
        p_rc_attr->stH264Cbr.u32BitRate = avg_bitrate;
        break;
    case VENC_RC_MODE_H265CBR:
        p_rc_attr->stH265Cbr.u32BitRate = avg_bitrate;
        break;
    case VENC_RC_MODE_MJPEGVBR:
        p_rc_attr->stMjpegVbr.u32BitRate = avg_bitrate;
        p_rc_attr->stMjpegVbr.u32MaxBitRate = max_bitrate;
        p_rc_attr->stMjpegVbr.u32MinBitRate = min_bitrate;
        break;
    case VENC_RC_MODE_H264VBR:
        p_rc_attr->stH264Vbr.u32BitRate = avg_bitrate;
        p_rc_attr->stH264Vbr.u32MaxBitRate = max_bitrate;
        p_rc_attr->stH264Vbr.u32MinBitRate = min_bitrate;
        break;
    case VENC_RC_MODE_H265VBR:
        p_rc_attr->stH265Vbr.u32BitRate = avg_bitrate;
        p_rc_attr->stH265Vbr.u32MaxBitRate = max_bitrate;
        p_rc_attr->stH265Vbr.u32MinBitRate = min_bitrate;
        break;
    case VENC_RC_MODE_H264AVBR:
        p_rc_attr->stH264Avbr.u32BitRate = avg_bitrate;
        p_rc_attr->stH264Avbr.u32MaxBitRate = max_bitrate;
        p_rc_attr->stH264Avbr.u32MinBitRate = min_bitrate;
        break;
    case VENC_RC_MODE_H265AVBR:
        p_rc_attr->stH265Avbr.u32BitRate = avg_bitrate;
        p_rc_attr->stH265Avbr.u32MaxBitRate = max_bitrate;
        p_rc_attr->stH265Avbr.u32MinBitRate = min_bitrate;
        break;
    default:
        return RK_ERR_VENC_NOT_SUPPORT;
    }

    return RK_SUCCESS;
}

}  // namespace external_command
}  // namespace apollo
