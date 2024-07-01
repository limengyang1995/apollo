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

#include "modules/canbus_vehicle/venus/protocol/vcu5_56a.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Vcu556a::Vcu556a() {}
const int32_t Vcu556a::ID = 0x56A;

void Vcu556a::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_vcu5_56a()->set_vcu5_gearautocontrolst(vcu5_gearautocontrolst(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_rearsteeringtorquesign(vcu5_rearsteeringtorquesign(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_rearsteeringtorque(vcu5_rearsteeringtorque(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_rearsteeringactive(vcu5_rearsteeringactive(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_frontsteeringtorquesign(vcu5_frontsteeringtorquesign(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_frontsteeringtorque(vcu5_frontsteeringtorque(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_frontsteeringactive(vcu5_frontsteeringactive(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_rearsteeringtakeoverst(vcu5_rearsteeringtakeoverst(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_rearsteeringfailurest(vcu5_rearsteeringfailurest(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_rearsteeringautocontrolst(vcu5_rearsteeringautocontrolst(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_livecounter(vcu5_livecounter(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_frontsteeringtakeoverst(vcu5_frontsteeringtakeoverst(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_frontsteeringfailurest(vcu5_frontsteeringfailurest(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_frontsteeringautocontrolst(vcu5_frontsteeringautocontrolst(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_drivingtakeoverst(vcu5_drivingtakeoverst(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_drivingfailurest(vcu5_drivingfailurest(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_drivingautocontrolst(vcu5_drivingautocontrolst(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_checksum(vcu5_checksum(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_brakingtakeoverst(vcu5_brakingtakeoverst(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_brakingfailurest(vcu5_brakingfailurest(bytes, length));
  chassis->mutable_vcu5_56a()->set_vcu5_brakingautocontrolst(vcu5_brakingautocontrolst(bytes, length));
}

// config detail: {'bit': 56, 'enum': {0: 'VCU5_GEARAUTOCONTROLST_INACTIVE', 1: 'VCU5_GEARAUTOCONTROLST_ACTIVE', 2: 'VCU5_GEARAUTOCONTROLST_RESERVED1', 3: 'VCU5_GEARAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu5_gearautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_gearautocontrolstType Vcu556a::vcu5_gearautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 2);

  Vcu5_56a::Vcu5_gearautocontrolstType ret =  static_cast<Vcu5_56a::Vcu5_gearautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 54, 'enum': {0: 'VCU5_REARSTEERINGTORQUESIGN_LEFT', 1: 'VCU5_REARSTEERINGTORQUESIGN_RIGHT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu5_rearsteeringtorquesign', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_rearsteeringtorquesignType Vcu556a::vcu5_rearsteeringtorquesign(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(6, 1);

  Vcu5_56a::Vcu5_rearsteeringtorquesignType ret =  static_cast<Vcu5_56a::Vcu5_rearsteeringtorquesignType>(x);
  return ret;
}

// config detail: {'bit': 44, 'is_signed_var': False, 'len': 10, 'name': 'vcu5_rearsteeringtorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
double Vcu556a::vcu5_rearsteeringtorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 55, 'enum': {0: 'VCU5_REARSTEERINGACTIVE_NOACTIVE', 1: 'VCU5_REARSTEERINGACTIVE_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu5_rearsteeringactive', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_rearsteeringactiveType Vcu556a::vcu5_rearsteeringactive(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(7, 1);

  Vcu5_56a::Vcu5_rearsteeringactiveType ret =  static_cast<Vcu5_56a::Vcu5_rearsteeringactiveType>(x);
  return ret;
}

// config detail: {'bit': 42, 'enum': {0: 'VCU5_FRONTSTEERINGTORQUESIGN_LEFT', 1: 'VCU5_FRONTSTEERINGTORQUESIGN_RIGHT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu5_frontsteeringtorquesign', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_frontsteeringtorquesignType Vcu556a::vcu5_frontsteeringtorquesign(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(2, 1);

  Vcu5_56a::Vcu5_frontsteeringtorquesignType ret =  static_cast<Vcu5_56a::Vcu5_frontsteeringtorquesignType>(x);
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 10, 'name': 'vcu5_frontsteeringtorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
double Vcu556a::vcu5_frontsteeringtorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 43, 'enum': {0: 'VCU5_FRONTSTEERINGACTIVE_NOACTIVE', 1: 'VCU5_FRONTSTEERINGACTIVE_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu5_frontsteeringactive', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_frontsteeringactiveType Vcu556a::vcu5_frontsteeringactive(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(3, 1);

  Vcu5_56a::Vcu5_frontsteeringactiveType ret =  static_cast<Vcu5_56a::Vcu5_frontsteeringactiveType>(x);
  return ret;
}

// config detail: {'bit': 31, 'enum': {0: 'VCU5_REARSTEERINGTAKEOVERST_INACTIVE', 1: 'VCU5_REARSTEERINGTAKEOVERST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu5_rearsteeringtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_rearsteeringtakeoverstType Vcu556a::vcu5_rearsteeringtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(7, 1);

  Vcu5_56a::Vcu5_rearsteeringtakeoverstType ret =  static_cast<Vcu5_56a::Vcu5_rearsteeringtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 28, 'enum': {0: 'VCU5_REARSTEERINGFAILUREST_NOTFAIL', 1: 'VCU5_REARSTEERINGFAILUREST_EPSFAIL', 2: 'VCU5_REARSTEERINGFAILUREST_SASFAIL', 3: 'VCU5_REARSTEERINGFAILUREST_STEERTEMPFAIL', 4: 'VCU5_REARSTEERINGFAILUREST_RESERVED1', 5: 'VCU5_REARSTEERINGFAILUREST_RESERVED2', 6: 'VCU5_REARSTEERINGFAILUREST_RESERVED3', 7: 'VCU5_REARSTEERINGFAILUREST_RESERVED4'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu5_rearsteeringfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_rearsteeringfailurestType Vcu556a::vcu5_rearsteeringfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 3);

  Vcu5_56a::Vcu5_rearsteeringfailurestType ret =  static_cast<Vcu5_56a::Vcu5_rearsteeringfailurestType>(x);
  return ret;
}

// config detail: {'bit': 14, 'enum': {0: 'VCU5_REARSTEERINGAUTOCONTROLST_INACTIVE', 1: 'VCU5_REARSTEERINGAUTOCONTROLST_ACTIVE', 2: 'VCU5_REARSTEERINGAUTOCONTROLST_RESERVED1', 3: 'VCU5_REARSTEERINGAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu5_rearsteeringautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_rearsteeringautocontrolstType Vcu556a::vcu5_rearsteeringautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(6, 2);

  Vcu5_56a::Vcu5_rearsteeringautocontrolstType ret =  static_cast<Vcu5_56a::Vcu5_rearsteeringautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'vcu5_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vcu556a::vcu5_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 27, 'enum': {0: 'VCU5_FRONTSTEERINGTAKEOVERST_INACTIVE', 1: 'VCU5_FRONTSTEERINGTAKEOVERST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu5_frontsteeringtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_frontsteeringtakeoverstType Vcu556a::vcu5_frontsteeringtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(3, 1);

  Vcu5_56a::Vcu5_frontsteeringtakeoverstType ret =  static_cast<Vcu5_56a::Vcu5_frontsteeringtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 24, 'enum': {0: 'VCU5_FRONTSTEERINGFAILUREST_NOTFAIL', 1: 'VCU5_FRONTSTEERINGFAILUREST_EPSFAIL', 2: 'VCU5_FRONTSTEERINGFAILUREST_SASFAIL', 3: 'VCU5_FRONTSTEERINGFAILUREST_STEERTEMPFAIL', 4: 'VCU5_FRONTSTEERINGFAILUREST_RESERVED1', 5: 'VCU5_FRONTSTEERINGFAILUREST_RESERVED2', 6: 'VCU5_FRONTSTEERINGFAILUREST_RESERVED3', 7: 'VCU5_FRONTSTEERINGFAILUREST_RESERVED4'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu5_frontsteeringfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_frontsteeringfailurestType Vcu556a::vcu5_frontsteeringfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 3);

  Vcu5_56a::Vcu5_frontsteeringfailurestType ret =  static_cast<Vcu5_56a::Vcu5_frontsteeringfailurestType>(x);
  return ret;
}

// config detail: {'bit': 12, 'enum': {0: 'VCU5_FRONTSTEERINGAUTOCONTROLST_INACTIVE', 1: 'VCU5_FRONTSTEERINGAUTOCONTROLST_ACTIVE', 2: 'VCU5_FRONTSTEERINGAUTOCONTROLST_RESERVED1', 3: 'VCU5_FRONTSTEERINGAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu5_frontsteeringautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_frontsteeringautocontrolstType Vcu556a::vcu5_frontsteeringautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  Vcu5_56a::Vcu5_frontsteeringautocontrolstType ret =  static_cast<Vcu5_56a::Vcu5_frontsteeringautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 19, 'enum': {0: 'VCU5_DRIVINGTAKEOVERST_INACTIVE', 1: 'VCU5_DRIVINGTAKEOVERST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu5_drivingtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_drivingtakeoverstType Vcu556a::vcu5_drivingtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(3, 1);

  Vcu5_56a::Vcu5_drivingtakeoverstType ret =  static_cast<Vcu5_56a::Vcu5_drivingtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 16, 'enum': {0: 'VCU5_DRIVINGFAILUREST_NOTFAIL', 1: 'VCU5_DRIVINGFAILUREST_HCUFAIL', 2: 'VCU5_DRIVINGFAILUREST_SPEEDSENSORFAIL', 3: 'VCU5_DRIVINGFAILUREST_YRSFAIL', 4: 'VCU5_DRIVINGFAILUREST_RESERVED1', 5: 'VCU5_DRIVINGFAILUREST_RESERVED2', 6: 'VCU5_DRIVINGFAILUREST_RESERVED3', 7: 'VCU5_DRIVINGFAILUREST_RESERVED4'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu5_drivingfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_drivingfailurestType Vcu556a::vcu5_drivingfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 3);

  Vcu5_56a::Vcu5_drivingfailurestType ret =  static_cast<Vcu5_56a::Vcu5_drivingfailurestType>(x);
  return ret;
}

// config detail: {'bit': 8, 'enum': {0: 'VCU5_DRIVINGAUTOCONTROLST_INACTIVE', 1: 'VCU5_DRIVINGAUTOCONTROLST_ACTIVE', 2: 'VCU5_DRIVINGAUTOCONTROLST_RESERVED1', 3: 'VCU5_DRIVINGAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu5_drivingautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_drivingautocontrolstType Vcu556a::vcu5_drivingautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Vcu5_56a::Vcu5_drivingautocontrolstType ret =  static_cast<Vcu5_56a::Vcu5_drivingautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu5_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vcu556a::vcu5_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 23, 'enum': {0: 'VCU5_BRAKINGTAKEOVERST_INACTIVE', 1: 'VCU5_BRAKINGTAKEOVERST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu5_brakingtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_brakingtakeoverstType Vcu556a::vcu5_brakingtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(7, 1);

  Vcu5_56a::Vcu5_brakingtakeoverstType ret =  static_cast<Vcu5_56a::Vcu5_brakingtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 20, 'enum': {0: 'VCU5_BRAKINGFAILUREST_NOTFAIL', 1: 'VCU5_BRAKINGFAILUREST_ESPFAIL', 2: 'VCU5_BRAKINGFAILUREST_SPEEDSENSORFAIL', 3: 'VCU5_BRAKINGFAILUREST_YRSFAIL', 4: 'VCU5_BRAKINGFAILUREST_HCUFAIL', 5: 'VCU5_BRAKINGFAILUREST_ESPANDHCUFAIL', 6: 'VCU5_BRAKINGFAILUREST_RESERVED1', 7: 'VCU5_BRAKINGFAILUREST_RESERVED2'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu5_brakingfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_brakingfailurestType Vcu556a::vcu5_brakingfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 3);

  Vcu5_56a::Vcu5_brakingfailurestType ret =  static_cast<Vcu5_56a::Vcu5_brakingfailurestType>(x);
  return ret;
}

// config detail: {'bit': 10, 'enum': {0: 'VCU5_BRAKINGAUTOCONTROLST_INACTIVE', 1: 'VCU5_BRAKINGAUTOCONTROLST_ACTIVE', 2: 'VCU5_BRAKINGAUTOCONTROLST_RESERVED1', 3: 'VCU5_BRAKINGAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu5_brakingautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu5_56a::Vcu5_brakingautocontrolstType Vcu556a::vcu5_brakingautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 2);

  Vcu5_56a::Vcu5_brakingautocontrolstType ret =  static_cast<Vcu5_56a::Vcu5_brakingautocontrolstType>(x);
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
