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

#include "modules/canbus_vehicle/yutong/protocol/gw_02_19ffcb24.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw0219ffcb24::Gw0219ffcb24() {}
const int32_t Gw0219ffcb24::ID = 0x19ffcb24;

void Gw0219ffcb24::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_02_19ffcb24()->set_average_powerconsumption(average_powerconsumption(bytes, length));
  chassis->mutable_gw_02_19ffcb24()->set_instantaneous_powerconsumption(instantaneous_powerconsumption(bytes, length));
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 11, 'name': 'average_powerconsumption', 'offset': -80.0, 'order': 'intel', 'physical_range': '[0|2047]', 'physical_unit': 'kwh/km', 'precision': 0.1, 'type': 'double'}
double Gw0219ffcb24::average_powerconsumption(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -80.000000;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 11, 'name': 'instantaneous_powerconsumption', 'offset': -100.0, 'order': 'intel', 'physical_range': '[0|2047]', 'physical_unit': 'kwh/km', 'precision': 0.1, 'type': 'double'}
double Gw0219ffcb24::instantaneous_powerconsumption(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -100.000000;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
