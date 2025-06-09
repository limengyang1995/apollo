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

#include "modules/canbus_vehicle/venus/protocol/vcu1_56f.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Vcu156f::Vcu156f() {}
const int32_t Vcu156f::ID = 0x56F;

void Vcu156f::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_vcu1_56f()->set_vcu1_jerkst(vcu1_jerkst(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_button2(vcu1_button2(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_button1(vcu1_button1(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_vehiclespeed(vcu1_vehiclespeed(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_steeringangle_r(vcu1_steeringangle_r(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_steeringangle_f(vcu1_steeringangle_f(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_livecounter(vcu1_livecounter(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_parkingbrakeinfo(vcu1_parkingbrakeinfo(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_gearinfo(vcu1_gearinfo(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_checksum(vcu1_checksum(bytes, length));
  chassis->mutable_vcu1_56f()->set_vcu1_brakeinfo(vcu1_brakeinfo(bytes, length));
}

// config detail: {'bit': 55, 'enum': {0: 'VCU1_JERKST_NOPRESS', 1: 'VCU1_JERKST_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu1_jerkst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_56f::Vcu1_jerkstType Vcu156f::vcu1_jerkst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(7, 1);

  Vcu1_56f::Vcu1_jerkstType ret =  static_cast<Vcu1_56f::Vcu1_jerkstType>(x);
  return ret;
}

// config detail: {'bit': 23, 'enum': {0: 'VCU1_BUTTON2_NOPRESS', 1: 'VCU1_BUTTON2_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu1_button2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_56f::Vcu1_button2Type Vcu156f::vcu1_button2(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(7, 1);

  Vcu1_56f::Vcu1_button2Type ret =  static_cast<Vcu1_56f::Vcu1_button2Type>(x);
  return ret;
}

// config detail: {'bit': 22, 'enum': {0: 'VCU1_BUTTON1_NOPRESS', 1: 'VCU1_BUTTON1_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu1_button1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_56f::Vcu1_button1Type Vcu156f::vcu1_button1(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(6, 1);

  Vcu1_56f::Vcu1_button1Type ret =  static_cast<Vcu1_56f::Vcu1_button1Type>(x);
  return ret;
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 15, 'name': 'vcu1_vehiclespeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|327.67]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vcu156f::vcu1_vehiclespeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 14, 'name': 'vcu1_steeringangle_r', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
double Vcu156f::vcu1_steeringangle_r(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -600.000000;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 14, 'name': 'vcu1_steeringangle_f', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
double Vcu156f::vcu1_steeringangle_f(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -600.000000;
  return ret;
}

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'vcu1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vcu156f::vcu1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 39, 'enum': {0: 'VCU1_PARKINGBRAKEINFO_RELEASED', 1: 'VCU1_PARKINGBRAKEINFO_LOCKED'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu1_parkingbrakeinfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_56f::Vcu1_parkingbrakeinfoType Vcu156f::vcu1_parkingbrakeinfo(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(7, 1);

  Vcu1_56f::Vcu1_parkingbrakeinfoType ret =  static_cast<Vcu1_56f::Vcu1_parkingbrakeinfoType>(x);
  return ret;
}

// config detail: {'bit': 56, 'enum': {0: 'VCU1_GEARINFO_NOCONNECTION', 1: 'VCU1_GEARINFO_P', 2: 'VCU1_GEARINFO_R', 3: 'VCU1_GEARINFO_N', 4: 'VCU1_GEARINFO_D', 5: 'VCU1_GEARINFO_RESERVED1', 6: 'VCU1_GEARINFO_RESERVED2', 7: 'VCU1_GEARINFO_RESERVED3'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu1_gearinfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_56f::Vcu1_gearinfoType Vcu156f::vcu1_gearinfo(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 3);

  Vcu1_56f::Vcu1_gearinfoType ret =  static_cast<Vcu1_56f::Vcu1_gearinfoType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vcu156f::vcu1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 38, 'enum': {0: 'VCU1_BRAKEINFO_INACTIVE', 1: 'VCU1_BRAKEINFO_BRAKEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu1_brakeinfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_56f::Vcu1_brakeinfoType Vcu156f::vcu1_brakeinfo(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(6, 1);

  Vcu1_56f::Vcu1_brakeinfoType ret =  static_cast<Vcu1_56f::Vcu1_brakeinfoType>(x);
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
