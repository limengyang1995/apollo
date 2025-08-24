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

#include "modules/canbus_vehicle/middlecar/protocol/vcu_fsd_status1_685.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace middlecar {

using ::apollo::drivers::canbus::Byte;

Vcufsdstatus1685::Vcufsdstatus1685() {}
const int32_t Vcufsdstatus1685::ID = 0x685;

void Vcufsdstatus1685::Parse(const std::uint8_t* bytes, int32_t length,
                         Middlecar* chassis) const {
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_workstatus(vcu_fsd_workstatus(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_touchborder(vcu_fsd_touchborder(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_steermode(vcu_fsd_steermode(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_vehsoc(vcu_fsd_vehsoc(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_parkingstatus(vcu_fsd_parkingstatus(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_cmdsource(vcu_fsd_cmdsource(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_roulingcounter(vcu_fsd_roulingcounter(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_gear_position(vcu_fsd_gear_position(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_spectionmode(vcu_fsd_spectionmode(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_hv(vcu_fsd_hv(bytes, length));
  chassis->mutable_vcu_fsd_status1_685()->set_vcu_fsd_standby(vcu_fsd_standby(bytes, length));
}

// config detail: {'bit': 21, 'description': 'work_status', 'enum': {0: 'VCU_FSD_WORKSTATUS_NORMAL_OPERATION', 1: 'VCU_FSD_WORKSTATUS_LIMPING', 2: 'VCU_FSD_WORKSTATUS_FAULT_PARKING'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu_fsd_workstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_workstatusType Vcufsdstatus1685::vcu_fsd_workstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(5, 3);

  Vcu_fsd_status1_685::Vcu_fsd_workstatusType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_workstatusType>(x);
  return ret;
}

// config detail: {'bit': 18, 'description': 'Safe_edge_contact_state', 'enum': {0: 'VCU_FSD_TOUCHBORDER_NO_CONTACT', 1: 'VCU_FSD_TOUCHBORDER_CONTACT'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu_fsd_touchborder', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_touchborderType Vcufsdstatus1685::vcu_fsd_touchborder(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 3);

  Vcu_fsd_status1_685::Vcu_fsd_touchborderType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_touchborderType>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': 'steering_mode', 'enum': {0: 'VCU_FSD_STEERMODE_FRONT_AXLE_STEERING', 1: 'VCU_FSD_STEERMODE_FULL_BRIDGE_STEERING', 2: 'VCU_FSD_STEERMODE_REAR_AXLE_STEERING'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_fsd_steermode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_steermodeType Vcufsdstatus1685::vcu_fsd_steermode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 4);

  Vcu_fsd_status1_685::Vcu_fsd_steermodeType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_steermodeType>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': 'Vehicle_power_consumption', 'is_signed_var': False, 'len': 7, 'name': 'vcu_fsd_vehsoc', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|127]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcufsdstatus1685::vcu_fsd_vehsoc(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 7);

  int ret = x;
  return ret;
}

// config detail: {'bit': 6, 'description': 'Parking_brake_status', 'enum': {0: 'VCU_FSD_PARKINGSTATUS_NOT_PARKED', 1: 'VCU_FSD_PARKINGSTATUS_PARKING'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_fsd_parkingstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_parkingstatusType Vcufsdstatus1685::vcu_fsd_parkingstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(6, 2);

  Vcu_fsd_status1_685::Vcu_fsd_parkingstatusType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_parkingstatusType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'Current_control_source', 'enum': {0: 'VCU_FSD_CMDSOURCE_NOT_SELECTED', 1: 'VCU_FSD_CMDSOURCE_FSD', 2: 'VCU_FSD_CMDSOURCE_CLOSE_RANGE_REMOTE_CONTROL'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_fsd_cmdsource', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_cmdsourceType Vcufsdstatus1685::vcu_fsd_cmdsource(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vcu_fsd_status1_685::Vcu_fsd_cmdsourceType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_cmdsourceType>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'vcu_fsd_roulingcounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcufsdstatus1685::vcu_fsd_roulingcounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': 'gear', 'enum': {0: 'VCU_FSD_GEAR_POSITION_N', 1: 'VCU_FSD_GEAR_POSITION_D', 2: 'VCU_FSD_GEAR_POSITION_R'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_fsd_gear_position', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|6]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_gear_positionType Vcufsdstatus1685::vcu_fsd_gear_position(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Vcu_fsd_status1_685::Vcu_fsd_gear_positionType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_gear_positionType>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': 'Special_mode_feedback', 'enum': {0: 'VCU_FSD_SPECTIONMODE_BENCH_MODE', 1: 'VCU_FSD_SPECTIONMODE_ECONOMIC_MODEL', 2: 'VCU_FSD_SPECTIONMODE_STANDARD_MODE', 3: 'VCU_FSD_SPECTIONMODE_SAND_MODE', 4: 'VCU_FSD_SPECTIONMODE_RAMP_MODE', 5: 'VCU_FSD_SPECTIONMODE_MUD_MODE'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_fsd_spectionmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_spectionmodeType Vcufsdstatus1685::vcu_fsd_spectionmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(2, 4);

  Vcu_fsd_status1_685::Vcu_fsd_spectionmodeType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_spectionmodeType>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': 'High_voltage_status_feedback', 'enum': {0: 'VCU_FSD_HV_HIGH_VOLTAGE_NOT_APPLIED', 1: 'VCU_FSD_HV_HIGH_VOLTAGE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_fsd_hv', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_hvType Vcufsdstatus1685::vcu_fsd_hv(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 1);

  Vcu_fsd_status1_685::Vcu_fsd_hvType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_hvType>(x);
  return ret;
}

// config detail: {'bit': 17, 'description': 'Standby_state_feedback', 'enum': {0: 'VCU_FSD_STANDBY_STANDBY', 1: 'VCU_FSD_STANDBY_NOT_IN_STANDBY_MODE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_fsd_standby', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_fsd_status1_685::Vcu_fsd_standbyType Vcufsdstatus1685::vcu_fsd_standby(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(1, 1);

  Vcu_fsd_status1_685::Vcu_fsd_standbyType ret =  static_cast<Vcu_fsd_status1_685::Vcu_fsd_standbyType>(x);
  return ret;
}
}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo
