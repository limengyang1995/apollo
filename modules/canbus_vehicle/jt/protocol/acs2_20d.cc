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

#include "modules/canbus_vehicle/jt/protocol/acs2_20d.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Acs220d::Acs220d() {}
const int32_t Acs220d::ID = 0x20D;

void Acs220d::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_acs2_20d()->set_acs2_validitycan7(acs2_validitycan7(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_validitycan6(acs2_validitycan6(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_validitycan5(acs2_validitycan5(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_validitycan4(acs2_validitycan4(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_validitycan3(acs2_validitycan3(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_validitycan2(acs2_validitycan2(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_validitycan1(acs2_validitycan1(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_validitycan0(acs2_validitycan0(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_version(acs2_version(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_livecounter(acs2_livecounter(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_buttonjerk(acs2_buttonjerk(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_checksum(acs2_checksum(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_button3(acs2_button3(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_button2(acs2_button2(bytes, length));
  chassis->mutable_acs2_20d()->set_acs2_button1(acs2_button1(bytes, length));
}

// config detail: {'bit': 39, 'description': 'This signal indicates the validity of CAN5', 'enum': {0: 'ACS2_VALIDITYCAN7_ACTIVE', 1: 'ACS2_VALIDITYCAN7_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_validitycan7', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_validitycan7Type Acs220d::acs2_validitycan7(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(7, 1);

  Acs2_20d::Acs2_validitycan7Type ret =  static_cast<Acs2_20d::Acs2_validitycan7Type>(x);
  return ret;
}

// config detail: {'bit': 38, 'description': 'This signal indicates the validity of CAN4', 'enum': {0: 'ACS2_VALIDITYCAN6_ACTIVE', 1: 'ACS2_VALIDITYCAN6_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_validitycan6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_validitycan6Type Acs220d::acs2_validitycan6(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(6, 1);

  Acs2_20d::Acs2_validitycan6Type ret =  static_cast<Acs2_20d::Acs2_validitycan6Type>(x);
  return ret;
}

// config detail: {'bit': 37, 'description': 'This signal indicates the validity of CAN5', 'enum': {0: 'ACS2_VALIDITYCAN5_ACTIVE', 1: 'ACS2_VALIDITYCAN5_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_validitycan5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_validitycan5Type Acs220d::acs2_validitycan5(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(5, 1);

  Acs2_20d::Acs2_validitycan5Type ret =  static_cast<Acs2_20d::Acs2_validitycan5Type>(x);
  return ret;
}

// config detail: {'bit': 36, 'description': 'This signal indicates the validity of CAN4', 'enum': {0: 'ACS2_VALIDITYCAN4_ACTIVE', 1: 'ACS2_VALIDITYCAN4_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_validitycan4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_validitycan4Type Acs220d::acs2_validitycan4(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(4, 1);

  Acs2_20d::Acs2_validitycan4Type ret =  static_cast<Acs2_20d::Acs2_validitycan4Type>(x);
  return ret;
}

// config detail: {'bit': 35, 'description': 'This signal indicates the validity of CAN3', 'enum': {0: 'ACS2_VALIDITYCAN3_ACTIVE', 1: 'ACS2_VALIDITYCAN3_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_validitycan3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_validitycan3Type Acs220d::acs2_validitycan3(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(3, 1);

  Acs2_20d::Acs2_validitycan3Type ret =  static_cast<Acs2_20d::Acs2_validitycan3Type>(x);
  return ret;
}

// config detail: {'bit': 34, 'description': 'This signal indicates the validity of CAN2', 'enum': {0: 'ACS2_VALIDITYCAN2_ACTIVE', 1: 'ACS2_VALIDITYCAN2_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_validitycan2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_validitycan2Type Acs220d::acs2_validitycan2(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(2, 1);

  Acs2_20d::Acs2_validitycan2Type ret =  static_cast<Acs2_20d::Acs2_validitycan2Type>(x);
  return ret;
}

// config detail: {'bit': 33, 'description': 'This signal indicates the validity of CAN1', 'enum': {0: 'ACS2_VALIDITYCAN1_ACTIVE', 1: 'ACS2_VALIDITYCAN1_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_validitycan1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_validitycan1Type Acs220d::acs2_validitycan1(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(1, 1);

  Acs2_20d::Acs2_validitycan1Type ret =  static_cast<Acs2_20d::Acs2_validitycan1Type>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': 'This signal indicates the validity of CAN0', 'enum': {0: 'ACS2_VALIDITYCAN0_ACTIVE', 1: 'ACS2_VALIDITYCAN0_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_validitycan0', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_validitycan0Type Acs220d::acs2_validitycan0(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 1);

  Acs2_20d::Acs2_validitycan0Type ret =  static_cast<Acs2_20d::Acs2_validitycan0Type>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': 'This signal indicates the version of software', 'is_signed_var': False, 'len': 16, 'name': 'acs2_version', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|655.35]', 'physical_unit': 'version', 'precision': 0.01, 'type': 'double'}
double Acs220d::acs2_version(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'acs2_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Acs220d::acs2_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal indicates the state of Jerk Button', 'enum': {0: 'ACS2_BUTTONJERK_NO_PRESS', 1: 'ACS2_BUTTONJERK_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_buttonjerk', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_buttonjerkType Acs220d::acs2_buttonjerk(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 1);

  Acs2_20d::Acs2_buttonjerkType ret =  static_cast<Acs2_20d::Acs2_buttonjerkType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'acs2_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Acs220d::acs2_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 11, 'description': 'This signal indicates the state of Button2', 'enum': {0: 'ACS2_BUTTON3_NO_PRESS', 1: 'ACS2_BUTTON3_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_button3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_button3Type Acs220d::acs2_button3(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(3, 1);

  Acs2_20d::Acs2_button3Type ret =  static_cast<Acs2_20d::Acs2_button3Type>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': 'This signal indicates the state of Button2', 'enum': {0: 'ACS2_BUTTON2_NO_PRESS', 1: 'ACS2_BUTTON2_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_button2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_button2Type Acs220d::acs2_button2(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 1);

  Acs2_20d::Acs2_button2Type ret =  static_cast<Acs2_20d::Acs2_button2Type>(x);
  return ret;
}

// config detail: {'bit': 9, 'description': 'This signal indicates the state of Button1', 'enum': {0: 'ACS2_BUTTON1_NO_PRESS', 1: 'ACS2_BUTTON1_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'acs2_button1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs2_20d::Acs2_button1Type Acs220d::acs2_button1(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(1, 1);

  Acs2_20d::Acs2_button1Type ret =  static_cast<Acs2_20d::Acs2_button1Type>(x);
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
