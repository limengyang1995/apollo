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

#include "modules/canbus_vehicle/yutong/protocol/gw_17_18f0090b.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw1718f0090b::Gw1718f0090b() {}
const int32_t Gw1718f0090b::ID = 0x18f0090b;

void Gw1718f0090b::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_17_18f0090b()->set_longitudinal_acceleration(longitudinal_acceleration(bytes, length));
}

// config detail: {'bit': 56, 'description': 'ֵ-12.5~12.5m/s2', 'is_signed_var': False, 'len': 8, 'name': 'longitudinal_acceleration', 'offset': -12.5, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'm/s2', 'precision': 0.1, 'type': 'double'}
double Gw1718f0090b::longitudinal_acceleration(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.100000 + -12.500000;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
