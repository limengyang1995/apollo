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

#include "modules/canbus_vehicle/venus/protocol/vcu7_569.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Vcu7569::Vcu7569() {}
const int32_t Vcu7569::ID = 0x569;

void Vcu7569::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_vcu7_569()->set_vcu7_mcubrakestate(vcu7_mcubrakestate(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_batteryvoltage(vcu7_batteryvoltage(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_batterycurrent(vcu7_batterycurrent(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_motorspeed(vcu7_motorspeed(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_mcuspeedmode(vcu7_mcuspeedmode(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_mcurelaystate(vcu7_mcurelaystate(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_mculowpower(vcu7_mculowpower(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_mcuerrorcode(vcu7_mcuerrorcode(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_livecounter(vcu7_livecounter(bytes, length));
  chassis->mutable_vcu7_569()->set_vcu7_checksum(vcu7_checksum(bytes, length));
}

// config detail: {'bit': 59, 'enum': {0: 'VCU7_MCUBRAKESTATE_OFF', 1: 'VCU7_MCUBRAKESTATE_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu7_mcubrakestate', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu7_569::Vcu7_mcubrakestateType Vcu7569::vcu7_mcubrakestate(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(3, 1);

  Vcu7_569::Vcu7_mcubrakestateType ret =  static_cast<Vcu7_569::Vcu7_mcubrakestateType>(x);
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 13, 'name': 'vcu7_batteryvoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
double Vcu7569::vcu7_batteryvoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 5);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 45, 'is_signed_var': False, 'len': 11, 'name': 'vcu7_batterycurrent', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|100]', 'physical_unit': 'A', 'precision': 0.1, 'type': 'double'}
double Vcu7569::vcu7_batterycurrent(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(5, 3);
  x <<= 3;
  x |= t;

  double ret = x * 0.100000 + -100.000000;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'vcu7_motorspeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
int Vcu7569::vcu7_motorspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 58, 'enum': {0: 'VCU7_MCUSPEEDMODE_LOW', 1: 'VCU7_MCUSPEEDMODE_HIGH'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu7_mcuspeedmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu7_569::Vcu7_mcuspeedmodeType Vcu7569::vcu7_mcuspeedmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(2, 1);

  Vcu7_569::Vcu7_mcuspeedmodeType ret =  static_cast<Vcu7_569::Vcu7_mcuspeedmodeType>(x);
  return ret;
}

// config detail: {'bit': 57, 'enum': {0: 'VCU7_MCURELAYSTATE_OFF', 1: 'VCU7_MCURELAYSTATE_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu7_mcurelaystate', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu7_569::Vcu7_mcurelaystateType Vcu7569::vcu7_mcurelaystate(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(1, 1);

  Vcu7_569::Vcu7_mcurelaystateType ret =  static_cast<Vcu7_569::Vcu7_mcurelaystateType>(x);
  return ret;
}

// config detail: {'bit': 56, 'enum': {0: 'VCU7_MCULOWPOWER_INACTIVE', 1: 'VCU7_MCULOWPOWER_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu7_mculowpower', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu7_569::Vcu7_mculowpowerType Vcu7569::vcu7_mculowpower(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 1);

  Vcu7_569::Vcu7_mculowpowerType ret =  static_cast<Vcu7_569::Vcu7_mculowpowerType>(x);
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'vcu7_mcuerrorcode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu7569::vcu7_mcuerrorcode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'vcu7_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vcu7569::vcu7_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu7_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vcu7569::vcu7_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
