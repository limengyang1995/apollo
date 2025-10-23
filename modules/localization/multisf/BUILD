load("//tools:apollo_package.bzl", "apollo_cc_library", "apollo_cc_binary", "apollo_package", "apollo_component")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "multisf_files",
    srcs = glob([
        "dag/**",
        "launch/**",
        "conf/**",
    ]),
)

cc_library(
    name = "suitesparse",
    copts = ["/usr/include/suitesparse",],
    linkopts = [
        "-L/usr/lib/x86_64-linux-gnu",  # 添加库搜索路径
        "-lcholmod",                    # 链接 CHOLMOD 库
        "-lamd",                        # 链接 AMD 库
        "-lcolamd",                     # 链接 COLAMD 库
        "-lopenblas",                   # 链接 BLAS 库
        "-lrt",                         # 可能需要的其他系统库
        "-lm",
    ],
)

apollo_component(
    name = "libmultisf_component.so",
    srcs = [
        "multisf_component.cc",
        "imu_tool.cpp",
        "eskf_flow.cpp",
        "eskf.cpp",
        "observability_analysis.cpp",
        '//modules/localization/multisf/fastgicp:fast_gicp.cpp',
        '//modules/localization/multisf/fastgicp:fast_vgicp.cpp',
    ],
    hdrs = [
        "//modules/localization/multisf:multisf_component.h",
        "//modules/localization/multisf:imu_data.h",
        "//modules/localization/multisf:imu_tool.h",
        "//modules/localization/multisf:common_tool.h",
        "//modules/localization/multisf:config_parameters.h",
        "//modules/localization/multisf:eskf_flow.h",
        "//modules/localization/multisf:eskf.h",
        "//modules/localization/multisf:gps_data.h",
        "//modules/localization/multisf:observability_analysis.h",
        '//modules/localization/msf/local_tool/local_visualization/online_visual:online_visualizer_component.h',
        "//modules/localization/common:gnss_compensator.h",
        '//modules/localization/ndt:ndt_localization.h',
        '//modules/localization/ndt:localization_pose_buffer.h',
        '//modules/localization/ndt/ndt_locator:ndt_solver.h',
        '//modules/localization/ndt/ndt_locator:ndt_solver.hpp',
        '//modules/localization/multisf/fastgicp:fast_gicp.h',
        '//modules/localization/multisf/fastgicp:fast_vgicp.h',
    ],
    linkstatic = True,
    deps = [
        "//cyber",
        "//modules/localization/FAST_LIO:fsdlidarodometry",
        "//modules/localization/multisf/proto:multisf_proto",
        "//modules/localization/common:localization_gflags",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common/math",
        "//modules/common_msgs/basic_msgs:geometry_cc_proto",
        "//modules/common/status",
        "//modules/common/util:common_util",
        "//modules/common_msgs/sensor_msgs:pointcloud_cc_proto",
        "//modules/localization/msf:apollo_localization_msf",
        "//modules/common_msgs/localization_msgs:localization_cc_proto",
        "//modules/localization/proto:localization_config_cc_proto",
        "//modules/common/monitor_log",
        "//modules/common/util:util_tool",
        "//modules/common_msgs/sensor_msgs:gnss_best_pose_cc_proto",
        "//modules/common_msgs/sensor_msgs:gnss_cc_proto",
        "//modules/common_msgs/sensor_msgs:ins_cc_proto",
        "//modules/localization/ndt/ndt_locator:ndt_lidar_locator",
        "//modules/common_msgs/localization_msgs:gps_cc_proto",
        "//modules/transform:apollo_transform",
        "//modules/common_msgs/sensor_msgs:gnss_best_pose_cc_proto",
        "//modules/common_msgs/sensor_msgs:gnss_cc_proto",
        "//modules/common_msgs/sensor_msgs:ins_cc_proto",
        "//modules/localization/multisf/fastgicp:fast_gicp",
        "//modules/localization/msf:cereal_test",
        '//third_party/sophus:sophus',
        "@eigen",
        "@local_config_pcl//:pcl",
        "suitesparse",
    ],
)

apollo_package()

cpplint()