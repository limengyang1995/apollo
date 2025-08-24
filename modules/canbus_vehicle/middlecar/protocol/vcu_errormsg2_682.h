/******************************************************************************
 * Copyright 2023 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include "modules/canbus_vehicle/middlecar/proto/middlecar.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace middlecar {

class Vcuerrormsg2682 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Middlecar> {
 public:
  static const int32_t ID;
  Vcuerrormsg2682();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Middlecar* chassis) const override;

 private:

    // config detail: {'bit': 12, 'description': 'DC24V_online_status', 'enum': {0: 'VCU_DC24ONLINE_OFFLINE', 1: 'VCU_DC24ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_DC24Online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_dc24onlineType vcu_dc24online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 14, 'description': 'Low_voltage_distribution_box_online_status', 'enum': {0: 'VCU_LOWVOLTAGEBOXONLINE_OFFLINE', 1: 'VCU_LOWVOLTAGEBOXONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_LowVoltageBoxOnline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_lowvoltageboxonlineType vcu_lowvoltageboxonline(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 13, 'description': 'IMU_online_status', 'enum': {0: 'VCU_IMUONLINE_OFFLINE', 1: 'VCU_IMUONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_IMUOnline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_imuonlineType vcu_imuonline(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 15, 'description': 'Load_online_status', 'enum': {0: 'VCU_LOADONLINE_OFFLINE', 1: 'VCU_LOADONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_LoadOnline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_loadonlineType vcu_loadonline(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'VCU_OnlineRoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu_onlineroulingcounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'description': 'Vehicle_fault_code', 'enum': {0: 'VCU_ERRORCODE_OFFLINE', 1: 'VCU_ERRORCODE_ONLINE'}, 'is_signed_var': False, 'len': 16, 'name': 'VCU_ErrorCode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_errorcodeType vcu_errorcode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Close_range_remote_control_online_status', 'enum': {0: 'VCU_SHORTRANGREMOTE_ONLINE_OFFLINE', 1: 'VCU_SHORTRANGREMOTE_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_ShortRangRemote_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_shortrangremote_onlineType vcu_shortrangremote_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 6, 'description': 'Front_drive_motor_online_status', 'enum': {0: 'VCU_FRONTMOTOR_ONLINE_OFFLINE', 1: 'VCU_FRONTMOTOR_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_FrontMotor_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_frontmotor_onlineType vcu_frontmotor_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'Front_EPS_online_status', 'enum': {0: 'VCU_FRONTEPS_ONLINE_OFFLINE', 1: 'VCU_FRONTEPS_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_FrontEPS_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_fronteps_onlineType vcu_fronteps_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 4, 'description': 'Front_brake_online_status', 'enum': {0: 'VCU_FRONTBRAKE_ONLINE_OFFLINE', 1: 'VCU_FRONTBRAKE_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_FrontBrake_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_frontbrake_onlineType vcu_frontbrake_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 2, 'description': 'Left_battery_pack_online_status', 'enum': {0: 'VCU_LEFTBATTERY_ONLINE_OFFLINE', 1: 'VCU_LEFTBATTERY_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_LeftBattery_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_leftbattery_onlineType vcu_leftbattery_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 11, 'description': '600W_DCDC_12V_online_status', 'enum': {0: 'VCU_DC12_600W_ONLINE_OFFLINE', 1: 'VCU_DC12_600W_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_DC12_600w_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_dc12_600w_onlineType vcu_dc12_600w_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 10, 'description': '1200W_DCDC_12V_online_status', 'enum': {0: 'VCU_DC12_1200W_ONLINE_OFFLINE', 1: 'VCU_DC12_1200W_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_DC12_1200w_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_dc12_1200w_onlineType vcu_dc12_1200w_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 7, 'description': 'Rear_drive_motor_online_status', 'enum': {0: 'VCU_REARMOTOR_ONLINE_OFFLINE', 1: 'VCU_REARMOTOR_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_RearMotor_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_rearmotor_onlineType vcu_rearmotor_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 9, 'description': 'Rear_EPS_online_status', 'enum': {0: 'VCU_REAREPS_ONLINE_OFFLINE', 1: 'VCU_REAREPS_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_RearEPS_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_reareps_onlineType vcu_reareps_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 5, 'description': 'Rear_brake_online_status', 'enum': {0: 'VCU_REARBRAKE_ONLINE_OFFLINE', 1: 'VCU_REARBRAKE_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_RearBrake_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_rearbrake_onlineType vcu_rearbrake_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 3, 'description': 'Right_battery_pack_online_status', 'enum': {0: 'VCU_RIGHTBATTERY_ONLINE_OFFLINE', 1: 'VCU_RIGHTBATTERY_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_RightBattery_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_rightbattery_onlineType vcu_rightbattery_online(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 1, 'description': 'FSD_online_status', 'enum': {0: 'VCU_FSD_ONLINE_OFFLINE', 1: 'VCU_FSD_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_FSD_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg2_682::Vcu_fsd_onlineType vcu_fsd_online(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo


