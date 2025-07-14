#include "rtc_publisher_brtc.h"

namespace apollo {
namespace external_command {

bool RtcPublisherBrtc::CreateClient(const RtcPublisherBrtc::CreateParam& param) {
    if (rtc_publisher_handle_map_.find(param.camera_name) != rtc_publisher_handle_map_.end()) {
        std::cout << "RtcPublisherBrtc::CreateClient: [" << param.camera_name << "] client already exists."
                  << std::endl;
        return false;
    }

    bool is_success = true;
    std::shared_ptr<RtcPublisherHandle> rtc_publisher_handle = std::make_shared<RtcPublisherHandle>();
    rtc_publisher_handle->name = param.camera_name;
    rtc_publisher_handle->p_rtc_client = std::make_shared<RtcClient>();
    rtc_publisher_handle->p_rtc_client->register_sync_frame_cb(
            std::bind(&RtcPublisherBrtc::RequestSyncFrame, this, std::placeholders::_1));
    is_success = rtc_publisher_handle->p_rtc_client->CreateClient(
            param.camera_name,
            param.app_id,
            param.cer_path,
            param.car_id,
            param.video_maxkbps,
            param.image_width,
            param.image_height);
    if (is_success == false) {
        std::cout << "RtcPublisherBrtc::CreateClient: [" << param.camera_name << "] create rtc client failed."
                  << std::endl;
        rtc_publisher_handle->p_rtc_client = nullptr;
        return false;
    }

    rtc_publisher_handle->p_video_encoder = std::make_shared<VideoEncoder>(
            param.camera_name,
            param.pixel_fmt,
            param.origin_width,
            param.origin_height,
            param.encode_codec,
            param.image_width,
            param.image_height);
    rtc_publisher_handle->p_video_encoder->register_encode_frame_ready_cb(
            std::bind(
                    &RtcPublisherBrtc::FrameReady,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4,
                    std::placeholders::_5));
    is_success = rtc_publisher_handle->p_video_encoder->init(param.video_maxkbps, 30);
    if (is_success == false) {
        rtc_publisher_handle->p_video_encoder = nullptr;
        rtc_publisher_handle->p_rtc_client = nullptr;
        AERROR << "RtcPublisherBrtc::CreateClient: [" << param.camera_name << "] create video encoder failed.";
        return false;
    }

    rtc_publisher_handle_map_[param.camera_name] = rtc_publisher_handle;
    std::cout << "RtcPublisherBrtc::CreateClient: [" << param.camera_name << "] create client success.";
    return rtc_publisher_handle->p_video_encoder->start();
}

bool RtcPublisherBrtc::DestroyClient(const std::string& stream_name) {
    auto it = rtc_publisher_handle_map_.find(stream_name);
    if (it == rtc_publisher_handle_map_.end()) {
        std::cout << "RtcPublisherBrtc::DestroyClient: [" << stream_name << "] client not exists.";
        return true;
    }

    it->second->p_video_encoder->stop();
    it->second->p_video_encoder->release();
    it->second->p_video_encoder = nullptr;
    it->second->p_rtc_client = nullptr;
    it->second = nullptr;

    rtc_publisher_handle_map_.erase(it);

    return true;
}

bool RtcPublisherBrtc::SendFrame(
        std::map<std::string, std::shared_ptr<apollo::drivers::Image>>& frames,
        const std::vector<std::string>& stream_names) {
    // std::map<std::string, rtc_publisher::FrameInfo*> image_map;
    // std::map<std::string, RtcPublisherBrtc::FrameInfo*> image_map;
    // for (auto frame : frames) {
    //     image_map.insert(std::make_pair(frame.camera_name, &frame));
    // }

    std::cout << "RtcPublisherBrtc::SendFrame: send all stream start." << std::endl;
    std::vector<ImageUtil::BlendInfo> blend_info_list(6);
    uint32_t color_fmt = RK_FMT_YUV422_YUYV;
    int i = 0;
    // for (auto it = frames.begin(); it != frames.end(); ++it) {
    // for (auto it = cam_idx_map_.begin(); it != cam_idx_map_.end(); ++it) {
    for (auto cam_name : cam_order_list_) {
        if (frames.find(cam_name) == frames.end()) {
            continue;
        }
        // auto image = it->second;
        auto image = frames[cam_name];
        // if (cam_idx_map_.find(it->first) == cam_idx_map_.end()) {
        //     i++;
        //     continue;
        // }
        auto stitch_rect = stitch_rect_[cam_idx_map_[cam_name]];
        if (image == nullptr || image->data().size() == 0) {
            // AERROR << "camera message is nullptr";
            ImageUtil::InitBlendInfo(
                    blend_info_list[i],
                    0,
                    0,
                    color_fmt,
                    nullptr,
                    stitch_rect.x,
                    stitch_rect.y,
                    stitch_rect.width,
                    stitch_rect.height);
            std::cout << "RtcPublisherBrtc::SendFrame: [" << cam_name << "] camera message is nullptr." << std::endl;
        } else {
            ImageUtil::InitBlendInfo(
                    blend_info_list[i],
                    image->width(),
                    image->height(),
                    color_fmt,
                    const_cast<char*>(image->data().data()),
                    stitch_rect.x,
                    stitch_rect.y,
                    stitch_rect.width,
                    stitch_rect.height);
            // if (src_write_done == false) {
            //     std::string filename = "/apollo_workspace/data/log/" + it->first + ".yuv";
            //     write_data_to_file(filename, image->data().data(), image->data().size());
            // }
        }
        i++;
    }
    // src_write_done = true;
    ImageUtil::Image dst_image = {1920, 1080, color_fmt, nullptr, nullptr};
    auto publisher_handle = rtc_publisher_handle_map_["all"];
    dst_image.virtual_addr = publisher_handle->p_video_encoder->get_input_buffer(dst_image.data_block);
    if (dst_image.virtual_addr != nullptr) {
        ImageUtil::Blend(blend_info_list, dst_image);
        // if (stitch_write_done == false) {
        //     std::string filename = std::string("/apollo_workspace/data/log/") + "all" + ".yuv";
        //     write_data_to_file(filename, dst_image.virtual_addr, 1920 * 1080 * 2);
        //     stitch_write_done = true;
        // }
        publisher_handle->p_video_encoder->put_input_buffer(dst_image.data_block);
        for (auto blend_info : blend_info_list) {
            ImageUtil::ReleaseBlendInfo(blend_info);
        }
        std::cout << "RtcPublisherBrtc::SendFrame: send all stream success." << std::endl;
    } else {
        std::cout << "RtcPublisherBrtc::SendFrame: stream all get input buffer failed." << std::endl;
    }

    return true;
    if (stream_names.empty() == true) {
        std::cout << "RtcPublisherBrtc::SendFrame: request_stream_name is empty." << std::endl;
        return false;
    }
#if 1
    // std::cout << "++++______________________________++++" << std::endl;
    // std::cout << "request: frame_info size:" << request.frame_info().size()
    //           << " stream_name size :" << request.request_stream_name().size() << std::endl;
    // for (auto stream_name : request.request_stream_name()) {
    //     std::cout << " stream_name:" << stream_name;
    // }

    // std::cout << std::endl << "----______________________________----" << std::endl;
#endif
    for (auto stream_name : stream_names) {
        if (rtc_publisher_handle_map_.find(stream_name) == rtc_publisher_handle_map_.end()) {
            std::cout << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] stream:" << stream_name
                      << " not exists.";
            continue;
        }

        std::cout << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] send single stream start.";
        // if (image_map.find(stream_name) == image_map.end()) {
        //     continue;
        // }
        auto image = frames[stream_name];
        if (image->data().size() == 0) {
            continue;
        }
        auto publisher_handle = rtc_publisher_handle_map_[stream_name];
        MB_BLK dma_handle;
        void* vir_addr = publisher_handle->p_video_encoder->get_input_buffer(dma_handle);
        if (vir_addr == nullptr) {
            std::cout << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] get input buffer failed.";
            continue;
        } else {
            std::cout << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] get input buffer success.";
        }
        memcpy(vir_addr, image->data().data(),
               image->data().size());  // TODO: attention would cause memory leak
        publisher_handle->p_video_encoder->put_input_buffer(dma_handle);
        std::cout << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] send single stream end.";
    }

    return true;
}

bool RtcPublisherBrtc::SendFrame(std::string stream_name, std::shared_ptr<apollo::drivers::Image> frame) {
    if (rtc_publisher_handle_map_.find(stream_name) == rtc_publisher_handle_map_.end()) {
        AERROR << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] stream:" << stream_name << " not exists.";
        return false;
    }

    AERROR << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] send single stream start.";
    // if (frame->data().size() == 0) {
    //     return true;
    // }

    auto publisher_handle = rtc_publisher_handle_map_[stream_name];
    MB_BLK dma_handle;
    void* vir_addr = publisher_handle->p_video_encoder->get_input_buffer(dma_handle);
    if (vir_addr == nullptr) {
        AERROR << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] get input buffer failed.";
        return false;
    }
    if (frame == nullptr || frame->data().size() == 0) {
        uint32_t color_fmt = RK_FMT_YUV422_YUYV;
        ImageUtil::Image dst_image = {1920, 1080, color_fmt, nullptr, nullptr};
        dst_image.virtual_addr = vir_addr;
        dst_image.data_block = dma_handle;
        ImageUtil::QuickFill(dst_image, 0x000000);
    } else {
        memcpy(vir_addr, frame->data().data(), frame->data().size());
    }

    publisher_handle->p_video_encoder->put_input_buffer(dma_handle);
    std::cout << "RtcPublisherBrtc::SendFrame: [" << stream_name << "] send single stream end.";

    return true;
}

void RtcPublisherBrtc::RequestSyncFrame(std::string stream_name) {
    if (rtc_publisher_handle_map_.find(stream_name) == rtc_publisher_handle_map_.end()) {
        AERROR << "RtcPublisherBrtc::RequestSyncFrame: [" << stream_name << "] stream:" << stream_name
               << " not exists.";
        return;
    }
    AERROR << "RtcPublisherBrtc::RequestSyncFrame: [" << stream_name << "] request sync frame.";
    auto publisher_handle = rtc_publisher_handle_map_[stream_name];
    if (publisher_handle->p_video_encoder != nullptr)
        publisher_handle->p_video_encoder->requestSyncFrame();
}

bool RtcPublisherBrtc::SendUserMessage(const std::string& message) {
    if (rtc_publisher_handle_map_.find("all") == rtc_publisher_handle_map_.end()) {
        return false;
    }

    auto handle = rtc_publisher_handle_map_["all"];
    auto p_rtc_client = handle->p_rtc_client;
    std::string id = std::to_string(p_rtc_client->g_mylistener.feed_id);
    if (id != "0") {
        if (std::find(rtc_id_list_.begin(), rtc_id_list_.end(), id) == rtc_id_list_.end()) {
            rtc_id_list_.push_back(id);
        }
        if (rtc_id_list_.size() > 3) {
            rtc_id_list_.erase(rtc_id_list_.begin());
        }

        for (const auto& id : rtc_id_list_) {
            // AINFO << "id : " << id << "id size: " << rtc_id_list_.size();
            p_rtc_client->g_BrtcClient->sendMessageToUser(message.c_str(), id.c_str());
        }
    }
    return true;
}

bool RtcPublisherBrtc::RecvUserMessage(std::string& message, bool& is_new_msg) {
    if (rtc_publisher_handle_map_.find("all") == rtc_publisher_handle_map_.end()) {
        is_new_msg = false;
        return false;
    }
    auto handle = rtc_publisher_handle_map_["all"];
    auto p_rtc_client = handle->p_rtc_client;
    message = p_rtc_client->g_mylistener.recieve_msg;
    is_new_msg = p_rtc_client->g_mylistener.re_mark;
    p_rtc_client->g_mylistener.re_mark = false;
    return true;
}

void RtcPublisherBrtc::FrameReady(
        std::string name,
        uint8_t* data,
        int size,
        VideoEncoder::FrameType frame_type,
        uint64_t timestamp) {
    // ExternalDriver* p_this = static_cast<ExternalDriver*>(user_data);
    if (rtc_publisher_handle_map_.find(name) == rtc_publisher_handle_map_.end()) {
        return;
    }

    // AERROR << "RtcPublisherBrtc::FrameReady: [" << name
    //        << "] frame ready. frame_type:" << unsigned(static_cast<uint8_t>(frame_type));
    auto publisher_handle = rtc_publisher_handle_map_[name];

    // TODO:
    publisher_handle->p_rtc_client->g_BrtcClient->sendImage(reinterpret_cast<const char*>(data), size);
}

}  // namespace external_command
}  // namespace apollo
