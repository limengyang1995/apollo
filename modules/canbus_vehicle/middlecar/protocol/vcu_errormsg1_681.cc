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

#include "modules/canbus_vehicle/middlecar/protocol/vcu_errormsg1_681.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace middlecar {

using ::apollo::drivers::canbus::Byte;

Vcuerrormsg1681::Vcuerrormsg1681() {}
const int32_t Vcuerrormsg1681::ID = 0x681;

void Vcuerrormsg1681::Parse(const std::uint8_t* bytes, int32_t length,
                         Middlecar* chassis) const {
  chassis->mutable_vcu_errormsg1_681()->set_vcu_dc24errorlevel(vcu_dc24errorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_lowvoltageboxerrorlevel(vcu_lowvoltageboxerrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_imuerrorlevel(vcu_imuerrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_canbuserror(vcu_canbuserror(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_vehicleerrorlevel(vcu_vehicleerrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_frontmotorerrorlevel(vcu_frontmotorerrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_rearmotorerrorlevel(vcu_rearmotorerrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_rightbatteryerrorlevel(vcu_rightbatteryerrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_dc12_1200werrorlevel(vcu_dc12_1200werrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_rightpowererrorlevel(vcu_rightpowererrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_leftpowererrorlevel(vcu_leftpowererrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_fsderrorlevel(vcu_fsderrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_frontaxleerrorlevel(vcu_frontaxleerrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_chassiscontrolboxlevel(vcu_chassiscontrolboxlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_rearaxleerrorlevel(vcu_rearaxleerrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_leftbatterylevel(vcu_leftbatterylevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_dc12_600wlevel(vcu_dc12_600wlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_frontepslevel(vcu_frontepslevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_rearepslevel(vcu_rearepslevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_frontbrakelevel(vcu_frontbrakelevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_rearbrakelevel(vcu_rearbrakelevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_loaderrorlevel(vcu_loaderrorlevel(bytes, length));
  chassis->mutable_vcu_errormsg1_681()->set_vcu_remoteerrorlevel(vcu_remoteerrorlevel(bytes, length));
}

// config detail: {'bit': 34, 'description': 'DCDC_24V_fault_level', 'enum': {0: 'VCU_DC24ERRORLEVEL_NO_FAULT', 1: 'VCU_DC24ERRORLEVEL_MINOR_FAULT', 2: 'VCU_DC24ERRORLEVEL_GENERAL_FAULT', 3: 'VCU_DC24ERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_dc24errorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_dc24errorlevelType Vcuerrormsg1681::vcu_dc24errorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(2, 2);

  Vcu_errormsg1_681::Vcu_dc24errorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_dc24errorlevelType>(x);
  return ret;
}

// config detail: {'bit': 36, 'description': 'Fault_level_of_low-voltage_distribution_box', 'enum': {0: 'VCU_LOWVOLTAGEBOXERRORLEVEL_NO_FAULT', 1: 'VCU_LOWVOLTAGEBOXERRORLEVEL_MINOR_FAULT', 2: 'VCU_LOWVOLTAGEBOXERRORLEVEL_GENERAL_FAULT', 3: 'VCU_LOWVOLTAGEBOXERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_lowvoltageboxerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_lowvoltageboxerrorlevelType Vcuerrormsg1681::vcu_lowvoltageboxerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(4, 2);

  Vcu_errormsg1_681::Vcu_lowvoltageboxerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_lowvoltageboxerrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 38, 'description': 'IMU_fault_level', 'enum': {0: 'VCU_IMUERRORLEVEL_NO_FAULT', 1: 'VCU_IMUERRORLEVEL_MINOR_FAULT', 2: 'VCU_IMUERRORLEVEL_GENERAL_FAULT', 3: 'VCU_IMUERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_imuerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_imuerrorlevelType Vcuerrormsg1681::vcu_imuerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(6, 2);

  Vcu_errormsg1_681::Vcu_imuerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_imuerrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 42, 'description': 'CAN_bus_fault', 'enum': {0: 'VCU_CANBUSERROR_FCANBUS_FAULT', 1: 'VCU_CANBUSERROR_RCANBUS_FAULT', 2: 'VCU_CANBUSERROR_FRCANBUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_canbuserror', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_canbuserrorType Vcuerrormsg1681::vcu_canbuserror(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(2, 2);

  Vcu_errormsg1_681::Vcu_canbuserrorType ret =  static_cast<Vcu_errormsg1_681::Vcu_canbuserrorType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'Vehicle_fault_level', 'enum': {0: 'VCU_VEHICLEERRORLEVEL_NO_FAULT', 1: 'VCU_VEHICLEERRORLEVEL_MINOR_FAULT', 2: 'VCU_VEHICLEERRORLEVEL_GENERAL_FAULT', 3: 'VCU_VEHICLEERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicleerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_vehicleerrorlevelType Vcuerrormsg1681::vcu_vehicleerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vcu_errormsg1_681::Vcu_vehicleerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_vehicleerrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 14, 'description': 'Fault_level_of_front_drive_motor', 'enum': {0: 'VCU_FRONTMOTORERRORLEVEL_NO_FAULT', 1: 'VCU_FRONTMOTORERRORLEVEL_MINOR_FAULT', 2: 'VCU_FRONTMOTORERRORLEVEL_GENERAL_FAULT', 3: 'VCU_FRONTMOTORERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_frontmotorerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_frontmotorerrorlevelType Vcuerrormsg1681::vcu_frontmotorerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(6, 2);

  Vcu_errormsg1_681::Vcu_frontmotorerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_frontmotorerrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': 'Fault_level_of_rear_drive_motor', 'enum': {0: 'VCU_REARMOTORERRORLEVEL_NO_FAULT', 1: 'VCU_REARMOTORERRORLEVEL_MINOR_FAULT', 2: 'VCU_REARMOTORERRORLEVEL_GENERAL_FAULT', 3: 'VCU_REARMOTORERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_rearmotorerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_rearmotorerrorlevelType Vcuerrormsg1681::vcu_rearmotorerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Vcu_errormsg1_681::Vcu_rearmotorerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_rearmotorerrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': 'Right_battery_pack_fault_level', 'enum': {0: 'VCU_RIGHTBATTERYERRORLEVEL_NO_FAULT', 1: 'VCU_RIGHTBATTERYERRORLEVEL_MINOR_FAULT', 2: 'VCU_RIGHTBATTERYERRORLEVEL_GENERAL_FAULT', 3: 'VCU_RIGHTBATTERYERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_rightbatteryerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_rightbatteryerrorlevelType Vcuerrormsg1681::vcu_rightbatteryerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 2);

  Vcu_errormsg1_681::Vcu_rightbatteryerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_rightbatteryerrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '1200w_DCDC_12V_fault_level', 'enum': {0: 'VCU_DC12_1200WERRORLEVEL_NO_FAULT', 1: 'VCU_DC12_1200WERRORLEVEL_MINOR_FAULT', 2: 'VCU_DC12_1200WERRORLEVEL_GENERAL_FAULT', 3: 'VCU_DC12_1200WERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_dc12_1200werrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_dc12_1200werrorlevelType Vcuerrormsg1681::vcu_dc12_1200werrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Vcu_errormsg1_681::Vcu_dc12_1200werrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_dc12_1200werrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': 'Fault_level_of_right_battery_box', 'enum': {0: 'VCU_RIGHTPOWERERRORLEVEL_NO_FAULT', 1: 'VCU_RIGHTPOWERERRORLEVEL_MINOR_FAULT', 2: 'VCU_RIGHTPOWERERRORLEVEL_GENERAL_FAULT', 3: 'VCU_RIGHTPOWERERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_rightpowererrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_rightpowererrorlevelType Vcuerrormsg1681::vcu_rightpowererrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  Vcu_errormsg1_681::Vcu_rightpowererrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_rightpowererrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': 'Left_battery_box_fault_level', 'enum': {0: 'VCU_LEFTPOWERERRORLEVEL_NO_FAULT', 1: 'VCU_LEFTPOWERERRORLEVEL_MINOR_FAULT', 2: 'VCU_LEFTPOWERERRORLEVEL_GENERAL_FAULT', 3: 'VCU_LEFTPOWERERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_leftpowererrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_leftpowererrorlevelType Vcuerrormsg1681::vcu_leftpowererrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 2);

  Vcu_errormsg1_681::Vcu_leftpowererrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_leftpowererrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': 'FSD_module_fault_level', 'enum': {0: 'VCU_FSDERRORLEVEL_FCANBUS_FAULT', 1: 'VCU_FSDERRORLEVEL_RCANBUS_FAULT', 2: 'VCU_FSDERRORLEVEL_FRCANBUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_fsderrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_fsderrorlevelType Vcuerrormsg1681::vcu_fsderrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Vcu_errormsg1_681::Vcu_fsderrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_fsderrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': 'Front_axle_fault_level', 'enum': {0: 'VCU_FRONTAXLEERRORLEVEL_NO_FAULT', 1: 'VCU_FRONTAXLEERRORLEVEL_MINOR_FAULT', 2: 'VCU_FRONTAXLEERRORLEVEL_GENERAL_FAULT', 3: 'VCU_FRONTAXLEERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_frontaxleerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_frontaxleerrorlevelType Vcuerrormsg1681::vcu_frontaxleerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(2, 2);

  Vcu_errormsg1_681::Vcu_frontaxleerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_frontaxleerrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 6, 'description': 'Fault_level_of_chassis_control_box', 'enum': {0: 'VCU_CHASSISCONTROLBOXLEVEL_NO_FAULT', 1: 'VCU_CHASSISCONTROLBOXLEVEL_MINOR_FAULT', 2: 'VCU_CHASSISCONTROLBOXLEVEL_GENERAL_FAULT', 3: 'VCU_CHASSISCONTROLBOXLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassiscontrolboxlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_chassiscontrolboxlevelType Vcuerrormsg1681::vcu_chassiscontrolboxlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(6, 2);

  Vcu_errormsg1_681::Vcu_chassiscontrolboxlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_chassiscontrolboxlevelType>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': 'Rear_axle_fault_level', 'enum': {0: 'VCU_REARAXLEERRORLEVEL_NO_FAULT', 1: 'VCU_REARAXLEERRORLEVEL_MINOR_FAULT', 2: 'VCU_REARAXLEERRORLEVEL_GENERAL_FAULT', 3: 'VCU_REARAXLEERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_rearaxleerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_rearaxleerrorlevelType Vcuerrormsg1681::vcu_rearaxleerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(4, 2);

  Vcu_errormsg1_681::Vcu_rearaxleerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_rearaxleerrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 18, 'description': 'Left_battery_pack_fault_level', 'enum': {0: 'VCU_LEFTBATTERYLEVEL_NO_FAULT', 1: 'VCU_LEFTBATTERYLEVEL_MINOR_FAULT', 2: 'VCU_LEFTBATTERYLEVEL_GENERAL_FAULT', 3: 'VCU_LEFTBATTERYLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_leftbatterylevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_leftbatterylevelType Vcuerrormsg1681::vcu_leftbatterylevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 2);

  Vcu_errormsg1_681::Vcu_leftbatterylevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_leftbatterylevelType>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': '600W_DCDC_12V_fault_level', 'enum': {0: 'VCU_DC12_600WLEVEL_NO_FAULT', 1: 'VCU_DC12_600WLEVEL_MINOR_FAULT', 2: 'VCU_DC12_600WLEVEL_GENERAL_FAULT', 3: 'VCU_DC12_600WLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_dc12_600wlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_dc12_600wlevelType Vcuerrormsg1681::vcu_dc12_600wlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(6, 2);

  Vcu_errormsg1_681::Vcu_dc12_600wlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_dc12_600wlevelType>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': 'Front_EPS_fault_level', 'enum': {0: 'VCU_FRONTEPSLEVEL_NO_FAULT', 1: 'VCU_FRONTEPSLEVEL_MINOR_FAULT', 2: 'VCU_FRONTEPSLEVEL_GENERAL_FAULT', 3: 'VCU_FRONTEPSLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_frontepslevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_frontepslevelType Vcuerrormsg1681::vcu_frontepslevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(2, 2);

  Vcu_errormsg1_681::Vcu_frontepslevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_frontepslevelType>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': 'rear_EPS_fault_level', 'enum': {0: 'VCU_REAREPSLEVEL_NO_FAULT', 1: 'VCU_REAREPSLEVEL_MINOR_FAULT', 2: 'VCU_REAREPSLEVEL_GENERAL_FAULT', 3: 'VCU_REAREPSLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_rearepslevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_rearepslevelType Vcuerrormsg1681::vcu_rearepslevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  Vcu_errormsg1_681::Vcu_rearepslevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_rearepslevelType>(x);
  return ret;
}

// config detail: {'bit': 22, 'description': 'Front_brake_fault_level', 'enum': {0: 'VCU_FRONTBRAKELEVEL_NO_FAULT', 1: 'VCU_FRONTBRAKELEVEL_MINOR_FAULT', 2: 'VCU_FRONTBRAKELEVEL_GENERAL_FAULT', 3: 'VCU_FRONTBRAKELEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_frontbrakelevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_frontbrakelevelType Vcuerrormsg1681::vcu_frontbrakelevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(6, 2);

  Vcu_errormsg1_681::Vcu_frontbrakelevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_frontbrakelevelType>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': 'Rear_brake_fault_level', 'enum': {0: 'VCU_REARBRAKELEVEL_NO_FAULT', 1: 'VCU_REARBRAKELEVEL_MINOR_FAULT', 2: 'VCU_REARBRAKELEVEL_GENERAL_FAULT', 3: 'VCU_REARBRAKELEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_rearbrakelevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_rearbrakelevelType Vcuerrormsg1681::vcu_rearbrakelevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 2);

  Vcu_errormsg1_681::Vcu_rearbrakelevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_rearbrakelevelType>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': 'Load_fault_level', 'enum': {0: 'VCU_LOADERRORLEVEL_NO_FAULT', 1: 'VCU_LOADERRORLEVEL_MINOR_FAULT', 2: 'VCU_LOADERRORLEVEL_GENERAL_FAULT', 3: 'VCU_LOADERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_loaderrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_loaderrorlevelType Vcuerrormsg1681::vcu_loaderrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 2);

  Vcu_errormsg1_681::Vcu_loaderrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_loaderrorlevelType>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': 'Remote_control_fault_level', 'enum': {0: 'VCU_REMOTEERRORLEVEL_NO_FAULT', 1: 'VCU_REMOTEERRORLEVEL_MINOR_FAULT', 2: 'VCU_REMOTEERRORLEVEL_GENERAL_FAULT', 3: 'VCU_REMOTEERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_remoteerrorlevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_errormsg1_681::Vcu_remoteerrorlevelType Vcuerrormsg1681::vcu_remoteerrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 2);

  Vcu_errormsg1_681::Vcu_remoteerrorlevelType ret =  static_cast<Vcu_errormsg1_681::Vcu_remoteerrorlevelType>(x);
  return ret;
}
}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo
