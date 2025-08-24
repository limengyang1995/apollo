load("//tools:apollo_package.bzl", "apollo_cc_binary", "apollo_cc_library", "apollo_cc_test", "apollo_component", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

CANBUS_COPTS = ["-DMODULE_NAME=\\\"canbus\\\""]

apollo_cc_library(
    name = "apollo_canbus_vehicle_middlecar",
    srcs = [
        "middlecar_controller.cc",
        "middlecar_message_manager.cc",
        "middlecar_vehicle_factory.cc",
        "protocol/fsd_vcu_cmd1_6a0.cc",
        "protocol/fsd_vcu_cmd2_6a2.cc",
        "protocol/vcu_errormsg1_681.cc",
        "protocol/vcu_errormsg2_682.cc",
        "protocol/vcu_fsd_status1_685.cc",
        "protocol/vcu_fsd_status2_686.cc",
    ],
    hdrs = [
        "middlecar_controller.h",
        "middlecar_message_manager.h",
        "middlecar_vehicle_factory.h",
        "protocol/fsd_vcu_cmd1_6a0.h",
        "protocol/fsd_vcu_cmd2_6a2.h",
        "protocol/vcu_errormsg1_681.h",
        "protocol/vcu_errormsg2_682.h",
        "protocol/vcu_fsd_status1_685.h",
        "protocol/vcu_fsd_status2_686.h",
    ],
    copts = CANBUS_COPTS,
    deps = [
        "//modules/canbus:apollo_canbus",
        "//modules/canbus/proto:canbus_conf_cc_proto",
        "//modules/canbus/proto:vehicle_parameter_cc_proto",
        "//modules/canbus_vehicle/middlecar/proto:middlecar_proto",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common/status",
        "//modules/common_msgs/basic_msgs:error_code_cc_proto",
        "//modules/common_msgs/chassis_msgs:chassis_cc_proto",
        "//modules/common_msgs/control_msgs:control_cmd_cc_proto",
        "//modules/drivers/canbus:apollo_drivers_canbus",
    ],
)

apollo_component(
    name = "libmiddlecar_vehicle_factory_lib.so",
    deps = [":apollo_canbus_vehicle_middlecar"],
)

filegroup(
    name = "runtime_data",
    srcs = glob([
        "testdata/**",
    ]),
)

apollo_package()
cpplint()
