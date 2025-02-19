load("//tools:apollo_package.bzl", "apollo_cc_binary", "apollo_cc_library", "apollo_cc_test", "apollo_component", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

CANBUS_COPTS = ["-DMODULE_NAME=\\\"canbus\\\""]

apollo_cc_library(
    name = "apollo_canbus_vehicle_jt",
    srcs = [
        "jt_controller.cc",
        "jt_message_manager.cc",
        "jt_vehicle_factory.cc",
        "protocol/acu1_151.cc",
        "protocol/acu2_152.cc",
        "protocol/acu3_153.cc",
        "protocol/acu4_154.cc",
        "protocol/acs1_20c.cc",
        "protocol/acs2_20d.cc",
        "protocol/bcm1_2a0.cc",
        "protocol/bcm2_200.cc",
        "protocol/bms1_288.cc",
        "protocol/chu1_28c.cc",
        "protocol/chu2_28d.cc",
        "protocol/epb1_2a1.cc",
        "protocol/gw1_268.cc",
        "protocol/ur1_3b1.cc",
        "protocol/ur2_3b2.cc",
        "protocol/ur3_3b3.cc",
        "protocol/vcu1_210.cc",
        "protocol/vcu2_211.cc",
        "protocol/vcu3_212.cc",
        "protocol/vector__independent_sig_msg_0.cc",
        "protocol/ws1_260.cc",
        "protocol/ws2_261.cc",
    ],
    hdrs = [
        "jt_controller.h",
        "jt_message_manager.h",
        "jt_vehicle_factory.h",
        "protocol/acu1_151.h",
        "protocol/acu2_152.h",
        "protocol/acu3_153.h",
        "protocol/acu4_154.h",
        "protocol/acs1_20c.h",
        "protocol/acs2_20d.h",
        "protocol/bcm1_2a0.h",
        "protocol/bcm2_200.h",
        "protocol/bms1_288.h",
        "protocol/chu1_28c.h",
        "protocol/chu2_28d.h",
        "protocol/epb1_2a1.h",
        "protocol/gw1_268.h",
        "protocol/ur1_3b1.h",
        "protocol/ur2_3b2.h",
        "protocol/ur3_3b3.h",
        "protocol/vcu1_210.h",
        "protocol/vcu2_211.h",
        "protocol/vcu3_212.h",
        "protocol/vector__independent_sig_msg_0.h",
        "protocol/ws1_260.h",
        "protocol/ws2_261.h",
    ],
    copts = CANBUS_COPTS,
    deps = [
        "//modules/canbus:apollo_canbus",
        "//modules/canbus/proto:canbus_conf_cc_proto",
        "//modules/canbus/proto:vehicle_parameter_cc_proto",
        "//modules/canbus_vehicle/jt/proto:jt_proto",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common/status",
        "//modules/common_msgs/basic_msgs:error_code_cc_proto",
        "//modules/common_msgs/chassis_msgs:chassis_cc_proto",
        "//modules/common_msgs/control_msgs:control_cmd_cc_proto",
        "//modules/drivers/canbus:apollo_drivers_canbus",
    ],
)

apollo_component(
    name = "libjt_vehicle_factory_lib.so",
    deps = [":apollo_canbus_vehicle_jt"],
)

filegroup(
    name = "runtime_data",
    srcs = glob([
        "testdata/**",
    ]),
)

apollo_package()
cpplint()
