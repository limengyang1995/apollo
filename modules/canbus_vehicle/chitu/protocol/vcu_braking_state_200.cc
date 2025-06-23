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

#include "modules/canbus_vehicle/chitu/protocol/vcu_braking_state_200.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

Vcubrakingstate200::Vcubrakingstate200() {}
const int32_t Vcubrakingstate200::ID = 0x200;

void Vcubrakingstate200::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_vcu_braking_state_200()->set_brake_state(brake_state(bytes, length));
}

// config detail: {'bit': 2, 'enum': {0: 'BRAKE_STATE_RESERVED', 1: 'BRAKE_STATE_COLLISION_BRAKING', 2: 'BRAKE_STATE_HARDWARE_EMERGENCY_BRAKING', 3: 'BRAKE_STATE_LOW_LIQUID_LEVEL_BRAKING', 4: 'BRAKE_STATE_SOFTWARE_EMERGENCY_BRAKING', 5: 'BRAKE_STATE_HARDWARE_SOFTWARE_EMERGENCY_BRAKING'}, 'is_signed_var': False, 'len': 3, 'name': 'brake_state', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_braking_state_200::Brake_stateType Vcubrakingstate200::brake_state(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  Vcu_braking_state_200::Brake_stateType ret =  static_cast<Vcu_braking_state_200::Brake_stateType>(x);
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
