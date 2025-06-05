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

#include "modules/canbus_vehicle/yutong/protocol/gw_19_18ffcc17.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw1918ffcc17::Gw1918ffcc17() {}
const int32_t Gw1918ffcc17::ID = 0x18ffcc17;

void Gw1918ffcc17::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_19_18ffcc17()->set_feedback_slow_handle_gear(feedback_slow_handle_gear(bytes, length));
}

// config detail: {'bit': 56, 'enum': {0: 'FEEDBACK_SLOW_HANDLE_GEAR_', 1: 'FEEDBACK_SLOW_HANDLE_GEAR_', 2: 'FEEDBACK_SLOW_HANDLE_GEAR_', 3: 'FEEDBACK_SLOW_HANDLE_GEAR_'}, 'is_signed_var': False, 'len': 3, 'name': 'feedback_slow_handle_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_19_18ffcc17::Feedback_slow_handle_gearType Gw1918ffcc17::feedback_slow_handle_gear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 3);

  Gw_19_18ffcc17::Feedback_slow_handle_gearType ret =  static_cast<Gw_19_18ffcc17::Feedback_slow_handle_gearType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
