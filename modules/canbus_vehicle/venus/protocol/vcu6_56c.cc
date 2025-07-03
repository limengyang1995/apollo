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

#include "modules/canbus_vehicle/venus/protocol/vcu6_56c.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Vcu656c::Vcu656c() {}
const int32_t Vcu656c::ID = 0x56C;

void Vcu656c::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_vcu6_56c()->set_vcu6_remainingtimes(vcu6_remainingtimes(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_accelpedalvoltage(vcu6_accelpedalvoltage(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_throttleposition(vcu6_throttleposition(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_brakeposition(vcu6_brakeposition(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_remotesteeringmode(vcu6_remotesteeringmode(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_remoteconnect(vcu6_remoteconnect(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_controlmode(vcu6_controlmode(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_livecounter(vcu6_livecounter(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_checksum(vcu6_checksum(bytes, length));
  chassis->mutable_vcu6_56c()->set_vcu6_batterysoc(vcu6_batterysoc(bytes, length));
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 12, 'name': 'vcu6_remainingtimes', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4095]', 'physical_unit': 'times', 'precision': 1.0, 'type': 'int'}
int Vcu656c::vcu6_remainingtimes(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'vcu6_accelpedalvoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|5]', 'physical_unit': 'V', 'precision': 0.02, 'type': 'double'}
double Vcu656c::vcu6_accelpedalvoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.020000;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'vcu6_throttleposition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
double Vcu656c::vcu6_throttleposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 8, 'name': 'vcu6_brakeposition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
double Vcu656c::vcu6_brakeposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

// config detail: {'bit': 20, 'enum': {0: 'VCU6_REMOTESTEERINGMODE_FRONT', 1: 'VCU6_REMOTESTEERINGMODE_REAR', 2: 'VCU6_REMOTESTEERINGMODE_OPPOSITE', 3: 'VCU6_REMOTESTEERINGMODE_SAME'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu6_remotesteeringmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu6_56c::Vcu6_remotesteeringmodeType Vcu656c::vcu6_remotesteeringmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 2);

  Vcu6_56c::Vcu6_remotesteeringmodeType ret =  static_cast<Vcu6_56c::Vcu6_remotesteeringmodeType>(x);
  return ret;
}

// config detail: {'bit': 19, 'enum': {0: 'VCU6_REMOTECONNECT_NO_CONNECT', 1: 'VCU6_REMOTECONNECT_CONNECT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu6_remoteconnect', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu6_56c::Vcu6_remoteconnectType Vcu656c::vcu6_remoteconnect(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(3, 1);

  Vcu6_56c::Vcu6_remoteconnectType ret =  static_cast<Vcu6_56c::Vcu6_remoteconnectType>(x);
  return ret;
}

// config detail: {'bit': 16, 'enum': {0: 'VCU6_CONTROLMODE_STOP', 1: 'VCU6_CONTROLMODE_REMOTE', 2: 'VCU6_CONTROLMODE_IPC', 3: 'VCU6_CONTROLMODE_TOGETHER', 4: 'VCU6_CONTROLMODE_RESERVED', 5: 'VCU6_CONTROLMODE_RESERVED', 6: 'VCU6_CONTROLMODE_RESERVED', 7: 'VCU6_CONTROLMODE_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu6_controlmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu6_56c::Vcu6_controlmodeType Vcu656c::vcu6_controlmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 3);

  Vcu6_56c::Vcu6_controlmodeType ret =  static_cast<Vcu6_56c::Vcu6_controlmodeType>(x);
  return ret;
}

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'vcu6_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vcu656c::vcu6_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu6_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vcu656c::vcu6_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'vcu6_batterysoc', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
double Vcu656c::vcu6_batterysoc(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
