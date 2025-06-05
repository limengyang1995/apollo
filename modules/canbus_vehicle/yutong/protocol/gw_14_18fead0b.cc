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

#include "modules/canbus_vehicle/yutong/protocol/gw_14_18fead0b.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw1418fead0b::Gw1418fead0b() {}
const int32_t Gw1418fead0b::ID = 0x18fead0b;

void Gw1418fead0b::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_14_18fead0b()->set_fl_brake_pressure(fl_brake_pressure(bytes, length));
  chassis->mutable_gw_14_18fead0b()->set_fr_brake_pressure(fr_brake_pressure(bytes, length));
  chassis->mutable_gw_14_18fead0b()->set_rl_brake_pressure(rl_brake_pressure(bytes, length));
  chassis->mutable_gw_14_18fead0b()->set_rr_brake_pressure(rr_brake_pressure(bytes, length));
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'fl_brake_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'Kpa', 'precision': 5.0, 'type': 'double'}
double Gw1418fead0b::fl_brake_pressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 5.000000;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'fr_brake_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'Kpa', 'precision': 5.0, 'type': 'double'}
double Gw1418fead0b::fr_brake_pressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 5.000000;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 8, 'name': 'rl_brake_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'Kpa', 'precision': 5.0, 'type': 'double'}
double Gw1418fead0b::rl_brake_pressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 5.000000;
  return ret;
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 8, 'name': 'rr_brake_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'Kpa', 'precision': 5.0, 'type': 'double'}
double Gw1418fead0b::rr_brake_pressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 5.000000;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
