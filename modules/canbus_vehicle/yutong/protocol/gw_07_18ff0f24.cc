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

#include "modules/canbus_vehicle/yutong/protocol/gw_07_18ff0f24.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw0718ff0f24::Gw0718ff0f24() {}
const int32_t Gw0718ff0f24::ID = 0x18ff0f24;

void Gw0718ff0f24::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_07_18ff0f24()->set_start_ignition(start_ignition(bytes, length));
}

// config detail: {'bit': 29, 'enum': {0: 'START_IGNITION_', 1: 'START_IGNITION_'}, 'is_signed_var': False, 'len': 1, 'name': 'start_ignition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_07_18ff0f24::Start_ignitionType Gw0718ff0f24::start_ignition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(5, 1);

  Gw_07_18ff0f24::Start_ignitionType ret =  static_cast<Gw_07_18ff0f24::Start_ignitionType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
