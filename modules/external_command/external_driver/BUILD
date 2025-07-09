load("//tools:cpplint.bzl", "cpplint")
load("//tools:apollo_package.bzl", "apollo_cc_binary", "apollo_cc_library", "apollo_cc_test", "apollo_component", "apollo_package")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")

package(default_visibility = ["//visibility:public"])

# native.cc_library(
#     name = "rtcClient",
#     srcs = "rtc/lib/libbaidurtc.so",
#     hdrs = [
#         "rtc/rtc_client.h",
#         "rtc/BaiduRtcInterface.h",
#         "rtc/BaiduRtcCommonDefine.h",
#         "rtc/BaiduExternalVideoRendererInterface.h",
#         "rtc/BaiduExternalVideoCapturerInterface.h",
#         "rtc/BaiduExternalDataRendererInterface.h",
#         "rtc/BaiduExternalAudioRendererInterface.h"],
#     tags = ["shared_library"],)

apollo_cc_library(
    name = "baidu_rtc_sdk",
    srcs = [
        "rtc/rtc_client.cc"
    ],
    hdrs = [
    "rtc/rtc_client.h",
    "rtc/BaiduRtcInterface.h",
    "rtc/BaiduRtcCommonDefine.h",
    "rtc/BaiduExternalVideoRendererInterface.h",
    "rtc/BaiduExternalVideoCapturerInterface.h",
    "rtc/BaiduExternalDataRendererInterface.h",
    "rtc/BaiduExternalAudioRendererInterface.h"
    ],
    deps = [
    
        "//cyber",
        "//modules/external_command/external_driver/proto:external_driver_config_cc_proto", 
        # ":rtcClient"
    ],
)

# proto_library(
#     name = "rtc_publisher_proto",
#     srcs = ["rtc_publisher/protos/rtc_publisher.proto"],
# )

# cc_proto_library(
#     name = "rtc_publisher_cc_proto",
#     deps = [":rtc_publisher_proto"],
# )

# cc_grpc_library(
#     name = "rtc_publisher_cc_grpc",
#     srcs = [":rtc_publisher_proto"],
#     grpc_only = True,
#     deps = [":rtc_publisher_cc_proto"],
# )

# proto_library(
#     name = "protos/rtc_publisher_proto",
#     srcs = ["rtc_publisher/protos/rtc_publisher.proto"],
# )

# apollo_cc_library(
#     name = "rtc_publisher_client",
#     srcs = ["rtc_publisher/rtc_publisher_client.cc"],
#     includes = ["rtc_publisher/protos/"],
#      deps = [
#         "//cyber",
#         "//modules/common/util:message_util",
#          ":rtc_publisher_cc_grpc",
#          "//modules/common_msgs/sensor_msgs:sensor_image_cc_proto",
#          "@com_github_grpc_grpc//:grpc++",
#      ],
# )

# apollo_cc_library(
#     name = "rockit",
#     srcs = ["multimedia/rockchip/lib/lib64/librockit.so"],
#     includes = ["multimedia/rockchip/include/"],
#     #hdrs = (["*.h"]),
#     # linkopts = [
#     #     "-L/opt/apollo/neo/lib/modules/external_command/external_driver/",
#     #     "-lrockit",
#     # ],
#     tags = ["shared_library"],
#     linkstatic = 0,
# )

# cc_import(
#   name = "rockit",
#   hdrs = glob([
#     "multimedia/rockchip/include/*.h",
#     "multimedia/rockchip/lib/lib64/rk_defines.h"
#   ]),
# #   includes = ["vendor/curl/include"],
#   shared_library = "multimedia/rockchip/lib/lib64/librockit.so",
# )

# apollo_cc_binary(
#     name = "rtc_publisher_server",
#     srcs = [
        
#         "multimedia/ImageUtil.hpp",
#         "multimedia/VideoEncoder.cc",
#         "multimedia/MultiMedia.cc",
#         "rtc_publisher/rtc_publisher_brtc.cpp",
#         "rtc_publisher/rtc_publisher_server.cc"],
#     includes = [
#         "rtc_publisher/protos/",
#         "multimedia/rockchip/include/",
#         "multimedia/rockchip/lib/lib64/",
#         "multimedia/",
#         "rtc_publisher",
#         "rtc"
#     ],
#     deps = [
#         ":rtc_publisher_cc_grpc",
#         "@com_github_grpc_grpc//:grpc++",
#         "@com_github_grpc_grpc//:grpc++_reflection",
#         ":baidu_rtc_sdk",
#         ":rockit"
#     ],
# )
#apollo_cc_binary(
#    name = "rockchip_platform",
#    includes = [
#        "multimedia/rockchip/include/",
#        "multimedia/rockchip/lib/lib64/"
#    ],
#    srcs = [
#        "multimedia/rockchip/lib/lib64/libgraphic_lsf.so",
#        "multimedia/rockchip/lib/lib64/libjpeg.so",
#        "multimedia/rockchip/lib/lib64/libpanoStitchApp.so",
#        "multimedia/rockchip/lib/lib64/librk_gdc_core.so",
#        "multimedia/rockchip/lib/lib64/librkAlgoDis.so",
#        "multimedia/rockchip/lib/lib64/librkgfx_avs.so",
#        "multimedia/rockchip/lib/lib64/libRkSwCac.so",
#        "multimedia/rockchip/lib/lib64/librockit.so",
#        "multimedia/rockchip/lib/lib64/libturbojpeg.so"
#    ],
#    linkopts = [
#        "-lgraphic_lsf",
#        "-ljpeg",
#        "-lpanoStitchApp",
#        "-lrk_gdc_core",
#        "-lrkAlgoDis",
#        "-lrkgfx_avs",
#        "-lRkSwCac",
#        "-lrockit",
#        "-lturbojpeg"
#    ]
#)


#apollo_cc_library(
#    name = "rockchip_mpp",
#    includes = ["multimedia/rockchip/include/"],
    #hdrs = (["*.h"]),
#    linkopts = [
#        "-L/opt/apollo/neo/src/modules/external_command/external_driver/multimedia/rockchip/lib/lib64",
#        "-lrockchip_mpp",
#    ],
#)
apollo_cc_library(
   name = "rockit",
   includes = ["multimedia/rockchip/include/"],
    # hdrs = (["*.h"]),
   linkopts = [
       "-L/opt/apollo/neo/src/modules/external_command/external_driver/multimedia/rockchip/lib/lib64",
       "-lrockit",
   ],
)

apollo_component(
    name = "libexternal_driver_component.so",
    hdrs = [
        "external_driver_component.h"
        ],
    srcs = ["external_driver_component.cc",
    "multimedia/ImageUtil.hpp",
    "multimedia/VideoEncoder.cc",
    "multimedia/MultiMedia.cc",
    "rtc_publisher/rtc_publisher_brtc.cpp",
    ],
    includes = [
        "rtc_publisher/",
        "multimedia/rockchip/include/",
        "multimedia/rockchip/lib/lib64/",
        "multimedia/",
        "rtc"
    ],
    copts = ["-DMODULE_NAME=\\\"external_command\\\""],

    deps = [
        "//cyber",
        "//modules/common/util:message_util",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common_msgs/external_command_msgs:command_status_cc_proto",
        "//modules/common_msgs/external_command_msgs:action_command_cc_proto",
        "//modules/common_msgs/external_command_msgs:chassis_command_cc_proto",
        "//modules/common_msgs/external_command_msgs:free_space_command_cc_proto",
        "//modules/common_msgs/external_command_msgs:lane_follow_command_cc_proto",
        "//modules/common_msgs/external_command_msgs:path_follow_command_cc_proto",
        "//modules/common_msgs/external_command_msgs:speed_command_cc_proto",
        "//modules/common_msgs/external_command_msgs:valet_parking_command_cc_proto",
        "//modules/common_msgs/planning_msgs:planning_cc_proto",
        "//modules/common_msgs/control_msgs:control_cmd_cc_proto",
        "//modules/external_command/external_driver/proto:sweeper_custom_command_cc_proto",
        "//modules/external_command/external_driver/proto:external_driver_config_cc_proto",
        "//modules/common_msgs/sensor_msgs:sensor_image_cc_proto",
        "@opencv//:imgproc",
        "@opencv//:core",
        "@opencv//:calib3d",
        "@opencv//:imgcodecs",
        "@com_github_nlohmann_json//:json",
        ":baidu_rtc_sdk",
        ":rockit"
        # ":rtc_publisher_client"
    ]
)

# apollo_component(
#     name = "libexternal_command_wrapper_demo_component.so",
#     hdrs = ["external_command_wrapper_demo.h"],
#     srcs = ["external_command_wrapper_demo.cc"],
#     copts = ["-DMODULE_NAME=\\\"external_command\\\""],
#     deps = [
#         "//cyber",
#         "//modules/common/util:message_util",
#         "//modules/common_msgs/external_command_msgs:command_status_cc_proto",
#         "//modules/common_msgs/external_command_msgs:action_command_cc_proto",
#         "//modules/common_msgs/external_command_msgs:chassis_command_cc_proto",
#         "//modules/common_msgs/external_command_msgs:free_space_command_cc_proto",
#         "//modules/common_msgs/external_command_msgs:lane_follow_command_cc_proto",l
#         "//modules/common_msgs/external_command_msgs:path_follow_command_cc_proto",
#         "//modules/common_msgs/external_command_msgs:speed_command_cc_proto",
#         "//modules/common_msgs/external_command_msgs:valet_parking_command_cc_proto",
#         "//modules/common_msgs/planning_msgs:planning_cc_proto",
#         "//modules/common/service_wrapper:client_wrapper",
#         "//modules/external_command/external_driver/proto:sweeper_custom_command_cc_proto",
#         "//modules/external_command/external_driver/proto:external_driver_config_cc_proto",
#     ],
# )

filegroup(
    name = "conf",
    srcs = glob([
        "conf/*",
        "dag/*",
        "launch/*"
    ]),
)

cpplint()
apollo_package()
