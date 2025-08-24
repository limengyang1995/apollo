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

#include "modules/canbus_vehicle/middlecar/protocol/vcu_errormsg2_682.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace middlecar {

using ::apollo::drivers::canbus::Byte;

Vcuerrormsg2682::Vcuerrormsg2682() {}
const int32_t Vcuerrormsg2682::ID = 0x682;

void Vcuerrormsg2682::Parse(const std::uint8_t* bytes, int32_t length,
                         Middlecar* chassis) const {
  chassis->mutable_vcu_errormsg2_682()->set_vcu_dc24online(vcu_dc24online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_lowvoltageboxonline(vcu_lowvoltageboxonline(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_imuonline(vcu_imuonline(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_loadonline(vcu_loadonline(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_onlineroulingcounter(vcu_onlineroulingcounter(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_errorcode(vcu_errorcode(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_shortrangremote_online(vcu_shortrangremote_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_frontmotor_online(vcu_frontmotor_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_fronteps_online(vcu_fronteps_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_frontbrake_online(vcu_frontbrake_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_leftbattery_online(vcu_leftbattery_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_dc12_600w_online(vcu_dc12_600w_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_dc12_1200w_online(vcu_dc12_1200w_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_rearmotor_online(vcu_rearmotor_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_reareps_online(vcu_reareps_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_rearbrake_online(vcu_rearbrake_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_rightbattery_online(vcu_rightbattery_online(bytes, length));
  chassis->mutable_vcu_errormsg2_682()->set_vcu_fsd_online(vcu_fsd_online(bytes, length));
}

// config detail: {'bit': 12, 'description': 'DC24V_online_status', 'enum': {0: 'VCU_DC24ONLINE_OFFLINE', 1: 'VCU_DC24ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_dc24online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_dc24onlineType Vcuerrormsg2682::vcu_dc24online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 1);

  Vcu_errormsg2_682::Vcu_dc24onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_dc24onlineType>(x);
  return ret;
}

// config detail: {'bit': 14, 'description': 'Low_voltage_distribution_box_online_status', 'enum': {0: 'VCU_LOWVOLTAGEBOXONLINE_OFFLINE', 1: 'VCU_LOWVOLTAGEBOXONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_lowvoltageboxonline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_lowvoltageboxonlineType Vcuerrormsg2682::vcu_lowvoltageboxonline(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(6, 1);

  Vcu_errormsg2_682::Vcu_lowvoltageboxonlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_lowvoltageboxonlineType>(x);
  return ret;
}

// config detail: {'bit': 13, 'description': 'IMU_online_status', 'enum': {0: 'VCU_IMUONLINE_OFFLINE', 1: 'VCU_IMUONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_imuonline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_imuonlineType Vcuerrormsg2682::vcu_imuonline(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(5, 1);

  Vcu_errormsg2_682::Vcu_imuonlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_imuonlineType>(x);
  return ret;
}

// config detail: {'bit': 15, 'description': 'Load_online_status', 'enum': {0: 'VCU_LOADONLINE_OFFLINE', 1: 'VCU_LOADONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_loadonline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_loadonlineType Vcuerrormsg2682::vcu_loadonline(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(7, 1);

  Vcu_errormsg2_682::Vcu_loadonlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_loadonlineType>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'vcu_onlineroulingcounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcuerrormsg2682::vcu_onlineroulingcounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 40, 'description': 'Vehicle_fault_code', 'enum': {0: 'VCU_ERRORCODE_OFFLINE', 1: 'VCU_ERRORCODE_ONLINE'}, 'is_signed_var': False, 'len': 16, 'name': 'vcu_errorcode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_errorcodeType Vcuerrormsg2682::vcu_errorcode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Vcu_errormsg2_682::Vcu_errorcodeType ret =  static_cast<Vcu_errormsg2_682::Vcu_errorcodeType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'Close_range_remote_control_online_status', 'enum': {0: 'VCU_SHORTRANGREMOTE_ONLINE_OFFLINE', 1: 'VCU_SHORTRANGREMOTE_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_shortrangremote_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_shortrangremote_onlineType Vcuerrormsg2682::vcu_shortrangremote_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Vcu_errormsg2_682::Vcu_shortrangremote_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_shortrangremote_onlineType>(x);
  return ret;
}

// config detail: {'bit': 6, 'description': 'Front_drive_motor_online_status', 'enum': {0: 'VCU_FRONTMOTOR_ONLINE_OFFLINE', 1: 'VCU_FRONTMOTOR_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_frontmotor_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_frontmotor_onlineType Vcuerrormsg2682::vcu_frontmotor_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(6, 1);

  Vcu_errormsg2_682::Vcu_frontmotor_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_frontmotor_onlineType>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': 'Front_EPS_online_status', 'enum': {0: 'VCU_FRONTEPS_ONLINE_OFFLINE', 1: 'VCU_FRONTEPS_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_fronteps_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_fronteps_onlineType Vcuerrormsg2682::vcu_fronteps_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 1);

  Vcu_errormsg2_682::Vcu_fronteps_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_fronteps_onlineType>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': 'Front_brake_online_status', 'enum': {0: 'VCU_FRONTBRAKE_ONLINE_OFFLINE', 1: 'VCU_FRONTBRAKE_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_frontbrake_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_frontbrake_onlineType Vcuerrormsg2682::vcu_frontbrake_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(4, 1);

  Vcu_errormsg2_682::Vcu_frontbrake_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_frontbrake_onlineType>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': 'Left_battery_pack_online_status', 'enum': {0: 'VCU_LEFTBATTERY_ONLINE_OFFLINE', 1: 'VCU_LEFTBATTERY_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_leftbattery_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_leftbattery_onlineType Vcuerrormsg2682::vcu_leftbattery_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(2, 1);

  Vcu_errormsg2_682::Vcu_leftbattery_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_leftbattery_onlineType>(x);
  return ret;
}

// config detail: {'bit': 11, 'description': '600W_DCDC_12V_online_status', 'enum': {0: 'VCU_DC12_600W_ONLINE_OFFLINE', 1: 'VCU_DC12_600W_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_dc12_600w_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_dc12_600w_onlineType Vcuerrormsg2682::vcu_dc12_600w_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(3, 1);

  Vcu_errormsg2_682::Vcu_dc12_600w_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_dc12_600w_onlineType>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': '1200W_DCDC_12V_online_status', 'enum': {0: 'VCU_DC12_1200W_ONLINE_OFFLINE', 1: 'VCU_DC12_1200W_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_dc12_1200w_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_dc12_1200w_onlineType Vcuerrormsg2682::vcu_dc12_1200w_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 1);

  Vcu_errormsg2_682::Vcu_dc12_1200w_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_dc12_1200w_onlineType>(x);
  return ret;
}

// config detail: {'bit': 7, 'description': 'Rear_drive_motor_online_status', 'enum': {0: 'VCU_REARMOTOR_ONLINE_OFFLINE', 1: 'VCU_REARMOTOR_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_rearmotor_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_rearmotor_onlineType Vcuerrormsg2682::vcu_rearmotor_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(7, 1);

  Vcu_errormsg2_682::Vcu_rearmotor_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_rearmotor_onlineType>(x);
  return ret;
}

// config detail: {'bit': 9, 'description': 'Rear_EPS_online_status', 'enum': {0: 'VCU_REAREPS_ONLINE_OFFLINE', 1: 'VCU_REAREPS_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_reareps_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_reareps_onlineType Vcuerrormsg2682::vcu_reareps_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(1, 1);

  Vcu_errormsg2_682::Vcu_reareps_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_reareps_onlineType>(x);
  return ret;
}

// config detail: {'bit': 5, 'description': 'Rear_brake_online_status', 'enum': {0: 'VCU_REARBRAKE_ONLINE_OFFLINE', 1: 'VCU_REARBRAKE_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_rearbrake_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_rearbrake_onlineType Vcuerrormsg2682::vcu_rearbrake_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(5, 1);

  Vcu_errormsg2_682::Vcu_rearbrake_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_rearbrake_onlineType>(x);
  return ret;
}

// config detail: {'bit': 3, 'description': 'Right_battery_pack_online_status', 'enum': {0: 'VCU_RIGHTBATTERY_ONLINE_OFFLINE', 1: 'VCU_RIGHTBATTERY_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_rightbattery_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_rightbattery_onlineType Vcuerrormsg2682::vcu_rightbattery_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(3, 1);

  Vcu_errormsg2_682::Vcu_rightbattery_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_rightbattery_onlineType>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': 'FSD_online_status', 'enum': {0: 'VCU_FSD_ONLINE_OFFLINE', 1: 'VCU_FSD_ONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_fsd_online', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg2_682::Vcu_fsd_onlineType Vcuerrormsg2682::vcu_fsd_online(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(1, 1);

  Vcu_errormsg2_682::Vcu_fsd_onlineType ret =  static_cast<Vcu_errormsg2_682::Vcu_fsd_onlineType>(x);
  return ret;
}
}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo
