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

#include "modules/canbus_vehicle/yutong/protocol/gw_21_19ff5417.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw2119ff5417::Gw2119ff5417() {}
const int32_t Gw2119ff5417::ID = 0x19ff5417;

void Gw2119ff5417::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_21_19ff5417()->set_state_of_lift(state_of_lift(bytes, length));
  chassis->mutable_gw_21_19ff5417()->set_interaxis_lock_threshold_state(interaxis_lock_threshold_state(bytes, length));
}

// config detail: {'bit': 6, 'enum': {0: 'STATE_OF_LIFT_', 1: 'STATE_OF_LIFT_'}, 'is_signed_var': False, 'len': 1, 'name': 'state_of_lift', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_21_19ff5417::State_of_liftType Gw2119ff5417::state_of_lift(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(6, 1);

  Gw_21_19ff5417::State_of_liftType ret =  static_cast<Gw_21_19ff5417::State_of_liftType>(x);
  return ret;
}

// config detail: {'bit': 12, 'enum': {0: 'INTERAXIS_LOCK_THRESHOLD_STATE_', 1: 'INTERAXIS_LOCK_THRESHOLD_STATE_'}, 'is_signed_var': False, 'len': 2, 'name': 'interaxis_lock_threshold_state', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_21_19ff5417::Interaxis_lock_threshold_stateType Gw2119ff5417::interaxis_lock_threshold_state(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  Gw_21_19ff5417::Interaxis_lock_threshold_stateType ret =  static_cast<Gw_21_19ff5417::Interaxis_lock_threshold_stateType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
