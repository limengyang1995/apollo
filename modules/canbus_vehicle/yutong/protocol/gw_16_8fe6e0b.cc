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

#include "modules/canbus_vehicle/yutong/protocol/gw_16_8fe6e0b.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw168fe6e0b::Gw168fe6e0b() {}
const int32_t Gw168fe6e0b::ID = 0x8fe6e0b;

void Gw168fe6e0b::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_16_8fe6e0b()->set_fl_wheelspeed(fl_wheelspeed(bytes, length));
  chassis->mutable_gw_16_8fe6e0b()->set_fr_wheelspeed(fr_wheelspeed(bytes, length));
  chassis->mutable_gw_16_8fe6e0b()->set_rl_wheelspeed(rl_wheelspeed(bytes, length));
  chassis->mutable_gw_16_8fe6e0b()->set_rr_wheelspeed(rr_wheelspeed(bytes, length));
}

// config detail: {'bit': 0, 'description': 'ֵ0~0xFAFF', 'is_signed_var': False, 'len': 16, 'name': 'fl_wheelspeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '-', 'precision': 0.00390625, 'type': 'double'}
double Gw168fe6e0b::fl_wheelspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.003906;
  return ret;
}

// config detail: {'bit': 16, 'description': 'ֵ0~0xFAFF', 'is_signed_var': False, 'len': 16, 'name': 'fr_wheelspeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '-', 'precision': 0.00390625, 'type': 'double'}
double Gw168fe6e0b::fr_wheelspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.003906;
  return ret;
}

// config detail: {'bit': 32, 'description': 'ֵ0~0xFAFF', 'is_signed_var': False, 'len': 16, 'name': 'rl_wheelspeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '-', 'precision': 0.00390625, 'type': 'double'}
double Gw168fe6e0b::rl_wheelspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.003906;
  return ret;
}

// config detail: {'bit': 48, 'description': 'ֵ0~0xFAFF', 'is_signed_var': False, 'len': 16, 'name': 'rr_wheelspeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '-', 'precision': 0.00390625, 'type': 'double'}
double Gw168fe6e0b::rr_wheelspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.003906;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
