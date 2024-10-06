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

#include "modules/canbus_vehicle/kfc/protocol/vcu1_320.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace kfc {

using ::apollo::drivers::canbus::Byte;

Vcu1320::Vcu1320() {}
const int32_t Vcu1320::ID = 0x320;

void Vcu1320::Parse(const std::uint8_t* bytes, int32_t length,
                         Kfc* chassis) const {
  chassis->mutable_vcu1_320()->set_vcu1_steeringmode(vcu1_steeringmode(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_drivingmode(vcu1_drivingmode(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_steeringtakeoverst(vcu1_steeringtakeoverst(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_steeringfailurest(vcu1_steeringfailurest(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_steeringautocontrolst(vcu1_steeringautocontrolst(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_drivingtakeoverst(vcu1_drivingtakeoverst(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_drivingfailurest(vcu1_drivingfailurest(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_drivingautocontrolst(vcu1_drivingautocontrolst(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_vehiclespeed(vcu1_vehiclespeed(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_livecounter(vcu1_livecounter(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_gearinfo(vcu1_gearinfo(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_checksum(vcu1_checksum(bytes, length));
  chassis->mutable_vcu1_320()->set_vcu1_brakeinfo(vcu1_brakeinfo(bytes, length));
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 4, 'name': 'vcu1_steeringmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu1320::vcu1_steeringmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 44, 'is_signed_var': False, 'len': 4, 'name': 'vcu1_drivingmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu1320::vcu1_drivingmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 12, 'enum': {0: 'VCU1_STEERINGTAKEOVERST_INACTIVE', 1: 'VCU1_STEERINGTAKEOVERST_TEMPORARY', 2: 'VCU1_STEERINGTAKEOVERST_ACTIVE', 3: 'VCU1_STEERINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu1_steeringtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_320::Vcu1_steeringtakeoverstType Vcu1320::vcu1_steeringtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  Vcu1_320::Vcu1_steeringtakeoverstType ret =  static_cast<Vcu1_320::Vcu1_steeringtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 10, 'enum': {0: 'VCU1_STEERINGFAILUREST_NO_FAIL', 1: 'VCU1_STEERINGFAILUREST_EPS_FAIL', 2: 'VCU1_STEERINGFAILUREST_SAS_FAIL', 3: 'VCU1_STEERINGFAILUREST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu1_steeringfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_320::Vcu1_steeringfailurestType Vcu1320::vcu1_steeringfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 2);

  Vcu1_320::Vcu1_steeringfailurestType ret =  static_cast<Vcu1_320::Vcu1_steeringfailurestType>(x);
  return ret;
}

// config detail: {'bit': 8, 'enum': {0: 'VCU1_STEERINGAUTOCONTROLST_INACTIVE', 1: 'VCU1_STEERINGAUTOCONTROLST_ACTIVE', 2: 'VCU1_STEERINGAUTOCONTROLST_RESERVED', 3: 'VCU1_STEERINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu1_steeringautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_320::Vcu1_steeringautocontrolstType Vcu1320::vcu1_steeringautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Vcu1_320::Vcu1_steeringautocontrolstType ret =  static_cast<Vcu1_320::Vcu1_steeringautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 20, 'enum': {0: 'VCU1_DRIVINGTAKEOVERST_INACTIVE', 1: 'VCU1_DRIVINGTAKEOVERST_TEMPORARY', 2: 'VCU1_DRIVINGTAKEOVERST_TAKE_OVER', 3: 'VCU1_DRIVINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu1_drivingtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_320::Vcu1_drivingtakeoverstType Vcu1320::vcu1_drivingtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 2);

  Vcu1_320::Vcu1_drivingtakeoverstType ret =  static_cast<Vcu1_320::Vcu1_drivingtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 18, 'enum': {0: 'VCU1_DRIVINGFAILUREST_NO_FAIL', 1: 'VCU1_DRIVINGFAILUREST_HCU_FAIL', 2: 'VCU1_DRIVINGFAILUREST_MOTOR_FAIL', 3: 'VCU1_DRIVINGFAILUREST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu1_drivingfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_320::Vcu1_drivingfailurestType Vcu1320::vcu1_drivingfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 2);

  Vcu1_320::Vcu1_drivingfailurestType ret =  static_cast<Vcu1_320::Vcu1_drivingfailurestType>(x);
  return ret;
}

// config detail: {'bit': 16, 'enum': {0: 'VCU1_DRIVINGAUTOCONTROLST_INACTIVE', 1: 'VCU1_DRIVINGAUTOCONTROLST_ACTIVE', 2: 'VCU1_DRIVINGAUTOCONTROLST_RESERVED', 3: 'VCU1_DRIVINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu1_drivingautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_320::Vcu1_drivingautocontrolstType Vcu1320::vcu1_drivingautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Vcu1_320::Vcu1_drivingautocontrolstType ret =  static_cast<Vcu1_320::Vcu1_drivingautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 15, 'name': 'vcu1_vehiclespeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|60]', 'physical_unit': 'km/h', 'precision': 1.0, 'type': 'int'}
int Vcu1320::vcu1_vehiclespeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'vcu1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu1320::vcu1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 14, 'enum': {0: 'VCU1_GEARINFO_P', 1: 'VCU1_GEARINFO_R', 2: 'VCU1_GEARINFO_N', 3: 'VCU1_GEARINFO_D'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu1_gearinfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_320::Vcu1_gearinfoType Vcu1320::vcu1_gearinfo(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(6, 2);

  Vcu1_320::Vcu1_gearinfoType ret =  static_cast<Vcu1_320::Vcu1_gearinfoType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu1320::vcu1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 22, 'enum': {0: 'VCU1_BRAKEINFO_INACTIVE', 1: 'VCU1_BRAKEINFO_ACTIVE', 2: 'VCU1_BRAKEINFO_RESERVED', 3: 'VCU1_BRAKEINFO_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu1_brakeinfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu1_320::Vcu1_brakeinfoType Vcu1320::vcu1_brakeinfo(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(6, 2);

  Vcu1_320::Vcu1_brakeinfoType ret =  static_cast<Vcu1_320::Vcu1_brakeinfoType>(x);
  return ret;
}
}  // namespace kfc
}  // namespace canbus
}  // namespace apollo
