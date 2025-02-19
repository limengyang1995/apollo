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

#include "modules/canbus_vehicle/jt/protocol/bms1_288.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Bms1288::Bms1288() {}
const int32_t Bms1288::ID = 0x288;

void Bms1288::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_bms1_288()->set_bms1_livecounter(bms1_livecounter(bytes, length));
  chassis->mutable_bms1_288()->set_bms1_heatingrequest(bms1_heatingrequest(bytes, length));
  chassis->mutable_bms1_288()->set_bms1_checksum(bms1_checksum(bytes, length));
  chassis->mutable_bms1_288()->set_bms1_batterypackvoltage(bms1_batterypackvoltage(bytes, length));
  chassis->mutable_bms1_288()->set_bms1_batterypacktemperature(bms1_batterypacktemperature(bytes, length));
  chassis->mutable_bms1_288()->set_bms1_batterypacksoh(bms1_batterypacksoh(bytes, length));
  chassis->mutable_bms1_288()->set_bms1_batterypacksoc(bms1_batterypacksoc(bytes, length));
  chassis->mutable_bms1_288()->set_bms1_batterypackcurrent(bms1_batterypackcurrent(bytes, length));
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'bms1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Bms1288::bms1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 58, 'is_signed_var': False, 'len': 1, 'name': 'bms1_heatingrequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Bms1288::bms1_heatingrequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(2, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'bms1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Bms1288::bms1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 10, 'name': 'bms1_batterypackvoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
int Bms1288::bms1_batterypackvoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'bms1_batterypacktemperature', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|210]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Bms1288::bms1_batterypacktemperature(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'bms1_batterypacksoh', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
int Bms1288::bms1_batterypacksoh(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 10, 'name': 'bms1_batterypacksoc', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
double Bms1288::bms1_batterypacksoc(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 18, 'is_signed_var': False, 'len': 14, 'name': 'bms1_batterypackcurrent', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|800]', 'physical_unit': 'A', 'precision': 0.1, 'type': 'double'}
double Bms1288::bms1_batterypackcurrent(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(2, 6);
  x <<= 6;
  x |= t;

  double ret = x * 0.100000 + -800.000000;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
