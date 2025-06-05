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

#include "modules/canbus_vehicle/yutong/protocol/gw_15_18febf0b.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw1518febf0b::Gw1518febf0b() {}
const int32_t Gw1518febf0b::ID = 0x18febf0b;

void Gw1518febf0b::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_15_18febf0b()->set_longitudinal_velocity(longitudinal_velocity(bytes, length));
  chassis->mutable_gw_15_18febf0b()->set_fl_wheel_speed(fl_wheel_speed(bytes, length));
  chassis->mutable_gw_15_18febf0b()->set_fr_wheel_speed(fr_wheel_speed(bytes, length));
  chassis->mutable_gw_15_18febf0b()->set_rl_wheel_speed(rl_wheel_speed(bytes, length));
  chassis->mutable_gw_15_18febf0b()->set_rr_wheel_speed(rr_wheel_speed(bytes, length));
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'longitudinal_velocity', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255.99609375]', 'physical_unit': 'km/h', 'precision': 0.00390625, 'type': 'double'}
double Gw1518febf0b::longitudinal_velocity(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.003906;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 8, 'name': 'fl_wheel_speed', 'offset': -7.8125, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'km/h', 'precision': 0.0625, 'type': 'double'}
double Gw1518febf0b::fl_wheel_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.062500 + -7.812500;
  return ret;
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 8, 'name': 'fr_wheel_speed', 'offset': -7.8125, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'km/h', 'precision': 0.0625, 'type': 'double'}
double Gw1518febf0b::fr_wheel_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.062500 + -7.812500;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'rl_wheel_speed', 'offset': -7.8125, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'km/h', 'precision': 0.0625, 'type': 'double'}
double Gw1518febf0b::rl_wheel_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.062500 + -7.812500;
  return ret;
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'rr_wheel_speed', 'offset': -7.8125, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'km/h', 'precision': 0.0625, 'type': 'double'}
double Gw1518febf0b::rr_wheel_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.062500 + -7.812500;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
