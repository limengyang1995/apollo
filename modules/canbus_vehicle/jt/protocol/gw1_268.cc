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

#include "modules/canbus_vehicle/jt/protocol/gw1_268.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Gw1268::Gw1268() {}
const int32_t Gw1268::ID = 0x268;

void Gw1268::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_gw1_268()->set_gw1_evready(gw1_evready(bytes, length));
  chassis->mutable_gw1_268()->set_gw1_hvready(gw1_hvready(bytes, length));
  chassis->mutable_gw1_268()->set_gw1_livecounter(gw1_livecounter(bytes, length));
  chassis->mutable_gw1_268()->set_gw1_checksum(gw1_checksum(bytes, length));
  chassis->mutable_gw1_268()->set_gw1_odometervalue(gw1_odometervalue(bytes, length));
  chassis->mutable_gw1_268()->set_gw1_ignitionofftime(gw1_ignitionofftime(bytes, length));
  chassis->mutable_gw1_268()->set_gw1_fuelvalue(gw1_fuelvalue(bytes, length));
}

// config detail: {'bit': 30, 'is_signed_var': False, 'len': 2, 'name': 'gw1_evready', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Gw1268::gw1_evready(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(6, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 28, 'is_signed_var': False, 'len': 2, 'name': 'gw1_hvready', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Gw1268::gw1_hvready(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'gw1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Gw1268::gw1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'gw1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Gw1268::gw1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 32, 'description': 'This signal is drive distance since prime start', 'is_signed_var': False, 'len': 25, 'name': 'gw1_odometervalue', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3355443]', 'physical_unit': 'km', 'precision': 0.1, 'type': 'double'}
double Gw1268::gw1_odometervalue(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 1);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t2(bytes + 5);
  t = t2.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t3(bytes + 4);
  t = t3.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 16, 'description': 'Indicates the time between last KL15 Off and this KL15 on', 'is_signed_var': False, 'len': 12, 'name': 'gw1_ignitionofftime', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4093]', 'physical_unit': 'minute', 'precision': 1.0, 'type': 'int'}
int Gw1268::gw1_ignitionofftime(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal indicates fuel value, used for powertrain diagnostic.', 'is_signed_var': False, 'len': 8, 'name': 'gw1_fuelvalue', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'L', 'precision': 1.0, 'type': 'int'}
int Gw1268::gw1_fuelvalue(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
