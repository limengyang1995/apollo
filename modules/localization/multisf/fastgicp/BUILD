load("//tools:apollo_package.bzl", "apollo_cc_library", "apollo_cc_binary", "apollo_package", "apollo_component")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

apollo_cc_library(
    name = "fast_gicp",
    srcs = [
            "fast_gicp.cpp",
            "fast_vgicp.cpp",
            "lsq_registration.cpp",
            ],
    hdrs = [
        'fast_gicp.h',
        'lsq_registration.h',
        'gicp_settings.h',
        'so3.h',
        'fast_vgicp_voxel.h',
        'fast_vgicp.h',
    ],
    deps = [
        "//cyber",
        "@boost",
        "@com_google_absl//:absl",
        "@eigen",
        "@local_config_pcl//:pcl",
    ],
    copts = ["-fopenmp"],  
    linkopts = ["-fopenmp"],
)

apollo_cc_binary(
    name = "test_fvgicp",
    srcs = ["test.cpp",],
    deps = ["fast_gicp",],
)
apollo_cc_binary(
    name = "calculate_covariances",
    srcs = ["calculate_covariances.cpp",],
    deps = ["fast_gicp",
            "//modules/localization/msf:cereal_test",],
)
apollo_cc_binary(
    name = "fastvgicpexe",
    srcs = ["fastvgicpexe.cpp",],
    deps = ["fast_gicp",
            "//modules/localization/msf:cereal_test",],
)


apollo_package()

cpplint()