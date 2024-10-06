load("//tools:apollo_package.bzl", "apollo_cc_binary", "apollo_cc_library", "apollo_cc_test", "apollo_component", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

CANBUS_COPTS = ["-DMODULE_NAME=\\\"canbus\\\""]

apollo_cc_library(
    name = "apollo_canbus_vehicle_kfc",
    srcs = [
        "kfc_controller.cc",
        "kfc_message_manager.cc",
        "kfc_vehicle_factory.cc",
        "protocol/acu1_310.cc",
        "protocol/agv_321.cc",
        "protocol/vcu1_320.cc",
        "protocol/vector__independent_sig_msg_0.cc",
    ],
    hdrs = [
        "kfc_controller.h",
        "kfc_message_manager.h",
        "kfc_vehicle_factory.h",
        "protocol/acu1_310.h",
        "protocol/agv_321.h",
        "protocol/vcu1_320.h",
        "protocol/vector__independent_sig_msg_0.h",
    ],
    copts = CANBUS_COPTS,
    deps = [
        "//modules/canbus:apollo_canbus",
        "//modules/canbus/proto:canbus_conf_cc_proto",
        "//modules/canbus/proto:vehicle_parameter_cc_proto",
        "//modules/canbus_vehicle/kfc/proto:kfc_proto",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common/status",
        "//modules/common_msgs/basic_msgs:error_code_cc_proto",
        "//modules/common_msgs/chassis_msgs:chassis_cc_proto",
        "//modules/common_msgs/control_msgs:control_cmd_cc_proto",
        "//modules/drivers/canbus:apollo_drivers_canbus",
    ],
)

apollo_component(
    name = "libkfc_vehicle_factory_lib.so",
    deps = [":apollo_canbus_vehicle_kfc"],
)

filegroup(
    name = "runtime_data",
    srcs = glob([
        "testdata/**",
    ]),
)

apollo_package()
cpplint()
