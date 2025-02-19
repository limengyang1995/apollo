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

#include "modules/canbus_vehicle/jt/protocol/chu2_28d.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Chu228d::Chu228d() {}
const int32_t Chu228d::ID = 0x28D;

void Chu228d::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_chu2_28d()->set_chu2_remainingchargetime(chu2_remainingchargetime(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_livecounter(chu2_livecounter(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_insulationmonitorwarning(chu2_insulationmonitorwarning(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_instantpowerconsumption(chu2_instantpowerconsumption(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_checksum(chu2_checksum(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_chargestationstatus(chu2_chargestationstatus(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_chargestationparameterconfi(chu2_chargestationparameterconfi(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_chargestationoutputvoltage(chu2_chargestationoutputvoltage(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_chargestationoutputcurrent(chu2_chargestationoutputcurrent(bytes, length));
  chassis->mutable_chu2_28d()->set_chu2_chargestationhandshakestatu(chu2_chargestationhandshakestatu(bytes, length));
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'chu2_remainingchargetime', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'Min', 'precision': 5.0, 'type': 'double'}
double Chu228d::chu2_remainingchargetime(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 5.000000;
  return ret;
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'chu2_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Chu228d::chu2_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 2, 'name': 'chu2_insulationmonitorwarning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Chu228d::chu2_insulationmonitorwarning(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 28, 'is_signed_var': False, 'len': 12, 'name': 'chu2_instantpowerconsumption', 'offset': -500.0, 'order': 'intel', 'physical_range': '[-500|1500]', 'physical_unit': 'Kw', 'precision': 0.5, 'type': 'double'}
double Chu228d::chu2_instantpowerconsumption(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  double ret = x * 0.500000 + -500.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'chu2_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Chu228d::chu2_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 54, 'is_signed_var': False, 'len': 2, 'name': 'chu2_chargestationstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Chu228d::chu2_chargestationstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(6, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 50, 'is_signed_var': False, 'len': 2, 'name': 'chu2_chargestationparameterconfi', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Chu228d::chu2_chargestationparameterconfi(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(2, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 18, 'is_signed_var': False, 'len': 10, 'name': 'chu2_chargestationoutputvoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
int Chu228d::chu2_chargestationoutputvoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(2, 6);
  x <<= 6;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 10, 'name': 'chu2_chargestationoutputcurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
int Chu228d::chu2_chargestationoutputcurrent(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 52, 'is_signed_var': False, 'len': 2, 'name': 'chu2_chargestationhandshakestatu', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Chu228d::chu2_chargestationhandshakestatu(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(4, 2);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
