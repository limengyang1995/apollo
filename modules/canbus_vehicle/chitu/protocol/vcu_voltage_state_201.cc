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

#include "modules/canbus_vehicle/chitu/protocol/vcu_voltage_state_201.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

Vcuvoltagestate201::Vcuvoltagestate201() {}
const int32_t Vcuvoltagestate201::ID = 0x201;

void Vcuvoltagestate201::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_vcu_voltage_state_201()->set__12v_state(_12v_state(bytes, length));
  chassis->mutable_vcu_voltage_state_201()->set__24v_state(_24v_state(bytes, length));
  chassis->mutable_vcu_voltage_state_201()->set__12vbatt_state(_12vbatt_state(bytes, length));
}

// config detail: {'bit': 0, 'enum': {0: '_12V_STATE_ON', 1: '_12V_STATE_OFF'}, 'is_signed_var': False, 'len': 1, 'name': '_12v_state', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_voltage_state_201::_12v_stateType Vcuvoltagestate201::_12v_state(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Vcu_voltage_state_201::_12v_stateType ret =  static_cast<Vcu_voltage_state_201::_12v_stateType>(x);
  return ret;
}

// config detail: {'bit': 8, 'enum': {0: '_24V_STATE_ON', 1: '_24V_STATE_OFF'}, 'is_signed_var': False, 'len': 1, 'name': '_24v_state', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_voltage_state_201::_24v_stateType Vcuvoltagestate201::_24v_state(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 1);

  Vcu_voltage_state_201::_24v_stateType ret =  static_cast<Vcu_voltage_state_201::_24v_stateType>(x);
  return ret;
}

// config detail: {'bit': 17, 'enum': {0: '_12VBATT_STATE_NORMAL', 1: '_12VBATT_STATE_UNDER_VOLTAGE', 3: '_12VBATT_STATE_OVER_VOLTAGE'}, 'is_signed_var': False, 'len': 2, 'name': '_12vbatt_state', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_voltage_state_201::_12vbatt_stateType Vcuvoltagestate201::_12vbatt_state(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Vcu_voltage_state_201::_12vbatt_stateType ret =  static_cast<Vcu_voltage_state_201::_12vbatt_stateType>(x);
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
