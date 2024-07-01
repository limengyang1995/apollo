load("//tools:apollo_package.bzl", "apollo_cc_binary", "apollo_cc_library", "apollo_cc_test", "apollo_component", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

CANBUS_COPTS = ["-DMODULE_NAME=\\\"canbus\\\""]

apollo_cc_library(
    name = "apollo_canbus_vehicle_venus",
    srcs = [
        "venus_controller.cc",
        "venus_message_manager.cc",
        "venus_vehicle_factory.cc",
        
        "protocol/acu1_529.cc",
        "protocol/acu2_532.cc",
        "protocol/acu3_534.cc",
        "protocol/vcu1_56f.cc",
        "protocol/vcu3_2_56d.cc",
        "protocol/vcu5_56a.cc",
        "protocol/vcu6_56c.cc",
        "protocol/vcu7_569.cc",
        "protocol/vector__independent_sig_msg_0.cc",
    ],
    hdrs = [
        "venus_controller.h",
        "venus_message_manager.h",
        "venus_vehicle_factory.h",
        
        "protocol/acu1_529.h",
        "protocol/acu2_532.h",
        "protocol/acu3_534.h",
        "protocol/vcu1_56f.h",
        "protocol/vcu3_2_56d.h",
        "protocol/vcu5_56a.h",
        "protocol/vcu6_56c.h",
        "protocol/vcu7_569.h",
        "protocol/vector__independent_sig_msg_0.h",
    ],
    copts = CANBUS_COPTS,
    deps = [
        "//modules/canbus:apollo_canbus",
        "//modules/canbus/proto:canbus_conf_cc_proto",
        "//modules/canbus/proto:vehicle_parameter_cc_proto",
        "//modules/canbus_vehicle/venus/proto:venus_proto",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common/status",
        "//modules/common_msgs/basic_msgs:error_code_cc_proto",
        "//modules/common_msgs/chassis_msgs:chassis_cc_proto",
        "//modules/common_msgs/control_msgs:control_cmd_cc_proto",
        "//modules/drivers/canbus:apollo_drivers_canbus",
    ],
)

apollo_component(
    name = "libvenus_vehicle_factory_lib.so",
    deps = [":apollo_canbus_vehicle_venus"],
)

filegroup(
    name = "runtime_data",
    srcs = glob([
        "testdata/**",
    ]),
)

apollo_package()
cpplint()
