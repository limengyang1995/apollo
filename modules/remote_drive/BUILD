load("//tools:apollo_package.bzl", "apollo_cc_library", "apollo_cc_binary", "apollo_package", "apollo_component")
load("//tools:cpplint.bzl", "cpplint")
load("//tools/platform:build_defs.bzl", "if_profiler")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "remote_drive_files",
    srcs = glob([
        "dag/**",
        "launch/**",
        "conf/**",
    ]),
)

apollo_component(
    name = "libremote_drive_component.so",
    srcs = [
        "remote_drive_component.cc",
    ],
    hdrs = [
        "remote_drive_component.h",
        "include/BaiduRtcInterface.h",
        "include/BaiduRtcCommonDefine.h",
        "include/BaiduExternalVideoRendererInterface.h",
        "include/BaiduExternalVideoCapturerInterface.h",
        "include/BaiduExternalDataRendererInterface.h",
        "include/BaiduExternalAudioRendererInterface.h",

    ],
    linkstatic = True,

    deps = [
        "//cyber",
        "//modules/remote_drive/proto:remote_drive_proto",
        "//modules/common_msgs/sensor_msgs:sensor_image_cc_proto",
        "//modules/common_msgs/control_msgs:control_cmd_cc_proto",
        "@opencv//:imgproc",
        "@opencv//:core",
        "@opencv//:highgui",
        "@opencv//:calib3d",
        "@opencv//:imgcodecs",
    ],
)

apollo_package()

cpplint()