load("//tools:cpplint.bzl", "cpplint")
load("//tools:apollo_package.bzl", "apollo_package", "apollo_plugin")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "runtime_files",
    srcs = glob([
        "conf/**",
    ]),
)

apollo_plugin(
    name = "libpull_over_scenario.so",
    srcs = [
        "pull_over_scenario.cc",
        "stage_approach.cc",
        "stage_retry_approach_parking.cc",
        "stage_retry_parking.cc",
        "util.cc",
    ],
    hdrs = [
        "context.h",
        "pull_over_scenario.h",
        "stage_approach.h",
        "stage_retry_approach_parking.h",
        "stage_retry_parking.h",
        "util.h",
    ],
    copts = ["-DMODULE_NAME=\\\"planning\\\""],
    description = ":plugins.xml",
    deps = [
        "//cyber",
        "//modules/common/util:util_tool",
        "//modules/common/vehicle_state:vehicle_state_provider",
        "//modules/common_msgs/planning_msgs:planning_cc_proto",
        "//modules/planning/planning_interface_base:apollo_planning_planning_interface_base",
        "//modules/planning/scenarios/pull_over/proto:pull_over_cc_proto",
        "@com_github_gflags_gflags//:gflags",
        "@eigen",
    ],
)

apollo_package()

cpplint()
