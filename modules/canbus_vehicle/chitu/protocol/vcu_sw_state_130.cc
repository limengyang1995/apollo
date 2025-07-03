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

#include "modules/canbus_vehicle/chitu/protocol/vcu_sw_state_130.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

Vcuswstate130::Vcuswstate130() {}
const int32_t Vcuswstate130::ID = 0x130;

void Vcuswstate130::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_vcu_sw_state_130()->set_vcu_mode(vcu_mode(bytes, length));
}

// config detail: {'bit': 0, 'enum': {0: 'VCU_MODE_AUTOMODE', 1: 'VCU_MODE_REMOTE_MODE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_mode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_sw_state_130::Vcu_modeType Vcuswstate130::vcu_mode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Vcu_sw_state_130::Vcu_modeType ret =  static_cast<Vcu_sw_state_130::Vcu_modeType>(x);
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
