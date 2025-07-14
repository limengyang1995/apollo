#include "modules/external_command/external_driver/rtc/rtc_client.h"
#include <typeinfo>

using namespace std;

namespace apollo {
namespace external_command {

void RtcClient::SetListener(baidurtc::BaiduRtcRoomClient* client, MyListener& listener) {
    client->registerRtcMessageListener(&listener);
}

bool RtcClient::CreateClient(const ExternalDriverConfig& config, std::string camera_name) {
    return true;
}

bool RtcClient::CreateClient(
        std::string camera_name,
        std::string app_id,
        std::string cer_path,
        std::string car_id,
        int32_t video_maxkbps,
        int32_t image_width,
        int32_t image_height) {
    void* handle = dlopen(
            "/opt/apollo/neo/src/modules/external_command/external_driver/rtc/lib/libbaidurtc.so",
            RTLD_LAZY | RTLD_DEEPBIND);
    if (handle == nullptr) {
        AERROR << "dlopen libbaidurtc.so failed";
        return false;
    }

    f_createBaiduRtcRoomClient* Client
            = (f_createBaiduRtcRoomClient*)dlsym(handle, "_ZN8baidurtc24createBaiduRtcRoomClientEv");
    f_enable* enableLog = (f_enable*)dlsym(handle, "enableBaiduRtcLog");
    if (enableLog) {
        enableLog(0);
    };
    g_BrtcClient = Client();
    s.HasData = true;
    s.HasVideo = true;
    s.HasAudio = false;
    s.AudioINChannel = 1;
    s.AudioINFrequency = 16000;
    // s.ImageINType = RTC_IMAGE_TYPE_JPEG;
    s.ImageINType = RTC_IMAGE_TYPE_H264;
    s.ImageOUTType = RTC_IMAGE_TYPE_H264;
    s.ConnectionTimeoutMs = 100;
    s.ReadTimeoutMs = 100;

    s.AsPublisher = true;
    s.AsListener = false;
    s.AutoPublish = true;

    s.VideoFps = 15;

    s.VideoMaxkbps = video_maxkbps;
    s.VideoWidth = image_width;
    s.VideoHeight = image_height;
    cer_path = cer_path;
    app_id = app_id;
    // car_id = getenv("CARID");
    std::string car_id_str;
    std::string display_name = car_id + "_" + camera_name;
    // AERROR << "car_id:" << car_id;

    car_id_str = car_id.substr(2);

    g_BrtcClient->setParamSettings(&s, s.RTC_PARAM_SETTINGS_ALL);
    g_BrtcClient->setAppID(app_id.c_str());
    g_BrtcClient->setMediaServerURL("wss://rtc.exp.bcelive.com/janus");
    g_BrtcClient->setCER(cer_path.c_str());
    // g_BrtcClient->enableBaiduRtcLog(config.enable_rtc_log());

    std::string uid;
    std::ostringstream os;
    os << car_id_str + std::to_string(10) + std::to_string(rand() / 1000);
    uid = os.str();

    if (!g_BrtcClient->loginRoom("2131", uid.c_str(), display_name.c_str(), "token")) {
        AERROR << "loginRoom failed";
        AERROR << "RtcPublisherBrtc::CreateClient: [" << camera_name << "] loginRoom failed.";
        return false;
    }

    g_mylistener.SetClientHandle(this);

    // g_BrtcClient->startPublish();
    if (camera_name == "all") {
        AERROR << "listener set for all camera";
        SetListener(g_BrtcClient, g_mylistener);
        AERROR << "RtcPublisherBrtc::CreateClient: [" << camera_name << "] listener set for all camera";
    }

    camera_name_ = camera_name;
    AERROR << "RtcPublisherBrtc::CreateClient: [" << camera_name << "] loginRoom success.";
    // SetListener(g_BrtcClient, g_mylistener);
    return true;
}
void MyListener::OnRtcMessage(RtcMessage& msg) {
    msg_type = msg.msgType;

    // std::lock_guard<std::mutex> lock(msg_mutex);
    switch (msg.msgType) {
    case RtcMessageType::RTC_ROOM_EVENT_ON_USER_JOINED_ROOM:
        AERROR << "OnRtcMessage[" << msg.data.feedId << "] user joined room";
        break;
    case RtcMessageType::RTC_ROOM_EVENT_ON_USER_MESSAGE:

        recieve_msg = msg.extra_info;
        re_mark = true;
        feed_id = msg.data.feedId;
        AERROR << "user message: " << recieve_msg;
        AERROR << "OnRtcMessage[" << feed_id << "]: " << recieve_msg;

        break;

    case RtcMessageType::RTC_ROOM_EVENT_ON_USER_LEAVING_ROOM:
        user_leaving_mark = true;
        leaving_user_id = msg.data.feedId;
        AINFO << msg.data.feedId;
        AERROR << "OnRtcMessage[" << leaving_user_id << "] user is leaving room";
        break;
    case RtcMessageType::RTC_ROOM_EVENT_FORCE_KEY_FRAME:
        AERROR << "OnRtcMessage force key frame!";
        if (client_ != nullptr) {
            client_->request_sync_frame();
        }
        // TODO:处理关键帧的逻辑
        break;
    case RtcMessageType::RTC_ROOM_EVENT_AVAILABLE_SEND_BITRATE:
        AERROR << "OnRtcMessage available send bitrate!";
        // TODO:处理可用发送码率的逻辑
        break;
    default:
        AERROR << "OnRtcMessage[" << msg.msgType << "] unknow message";
        break;
    }
}

}  // namespace external_command
}  // namespace apollo