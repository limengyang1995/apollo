load("//tools:apollo_package.bzl", "apollo_cc_binary", "apollo_cc_library", "apollo_cc_test", "apollo_component", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

CANBUS_COPTS = ["-DMODULE_NAME=\\\"canbus\\\""]

apollo_cc_library(
    name = "apollo_canbus_vehicle_chitu",
    srcs = [
        "chitu_controller.cc",
        "chitu_message_manager.cc",
        "chitu_vehicle_factory.cc",
        "protocol/adas_angle_cmd_112.cc",
        "protocol/adas_emergency_spot_2a0.cc",
        "protocol/adas_speed_cmd_113.cc",
        "protocol/vcu_adas_soc_4a0.cc",
        "protocol/vcu_braking_state_200.cc",
        "protocol/vcu_charge_discharge_4a2.cc",
        "protocol/vcu_diversion_angle_100.cc",
        "protocol/vcu_max_temp_4a1.cc",
        "protocol/vcu_mileage_info_111.cc",
        "protocol/vcu_remote_date1_4a3.cc",
        "protocol/vcu_remote_date2_4a4.cc",
        "protocol/vcu_remote_date3_4a5.cc",
        "protocol/vcu_remote_date4_4a6.cc",
        "protocol/vcu_speed_message_110.cc",
        "protocol/vcu_sw_state_130.cc",
        "protocol/vcu_voltage_state_201.cc",
    ],
    hdrs = [
        "chitu_controller.h",
        "chitu_message_manager.h",
        "chitu_vehicle_factory.h",
        "protocol/adas_angle_cmd_112.h",
        "protocol/adas_emergency_spot_2a0.h",
        "protocol/adas_speed_cmd_113.h",
        "protocol/vcu_adas_soc_4a0.h",
        "protocol/vcu_braking_state_200.h",
        "protocol/vcu_charge_discharge_4a2.h",
        "protocol/vcu_diversion_angle_100.h",
        "protocol/vcu_max_temp_4a1.h",
        "protocol/vcu_mileage_info_111.h",
        "protocol/vcu_remote_date1_4a3.h",
        "protocol/vcu_remote_date2_4a4.h",
        "protocol/vcu_remote_date3_4a5.h",
        "protocol/vcu_remote_date4_4a6.h",
        "protocol/vcu_speed_message_110.h",
        "protocol/vcu_sw_state_130.h",
        "protocol/vcu_voltage_state_201.h",
    ],
    copts = CANBUS_COPTS,
    deps = [
        "//modules/canbus:apollo_canbus",
        "//modules/canbus/proto:canbus_conf_cc_proto",
        "//modules/canbus/proto:vehicle_parameter_cc_proto",
        "//modules/canbus_vehicle/chitu/proto:chitu_proto",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common/status",
        "//modules/common_msgs/basic_msgs:error_code_cc_proto",
        "//modules/common_msgs/chassis_msgs:chassis_cc_proto",
        "//modules/common_msgs/control_msgs:control_cmd_cc_proto",
        "//modules/drivers/canbus:apollo_drivers_canbus",
    ],
)

apollo_component(
    name = "libchitu_vehicle_factory_lib.so",
    deps = [":apollo_canbus_vehicle_chitu"],
)

filegroup(
    name = "runtime_data",
    srcs = glob([
        "testdata/**",
    ]),
)

apollo_package()
cpplint()
