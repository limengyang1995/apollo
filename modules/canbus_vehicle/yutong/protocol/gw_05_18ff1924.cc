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

#include "modules/canbus_vehicle/yutong/protocol/gw_05_18ff1924.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw0518ff1924::Gw0518ff1924() {}
const int32_t Gw0518ff1924::ID = 0x18ff1924;

void Gw0518ff1924::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_05_18ff1924()->set_brake_light_control(brake_light_control(bytes, length));
  chassis->mutable_gw_05_18ff1924()->set_lift_fault_code(lift_fault_code(bytes, length));
  chassis->mutable_gw_05_18ff1924()->set_pto_working_state(pto_working_state(bytes, length));
}

// config detail: {'bit': 0, 'enum': {0: 'BRAKE_LIGHT_CONTROL_', 1: 'BRAKE_LIGHT_CONTROL_'}, 'is_signed_var': False, 'len': 2, 'name': 'brake_light_control', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_05_18ff1924::Brake_light_controlType Gw0518ff1924::brake_light_control(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Gw_05_18ff1924::Brake_light_controlType ret =  static_cast<Gw_05_18ff1924::Brake_light_controlType>(x);
  return ret;
}

// config detail: {'bit': 40, 'enum': {0: 'LIFT_FAULT_CODE_', 1: 'LIFT_FAULT_CODE_'}, 'is_signed_var': False, 'len': 4, 'name': 'lift_fault_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_05_18ff1924::Lift_fault_codeType Gw0518ff1924::lift_fault_code(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 4);

  Gw_05_18ff1924::Lift_fault_codeType ret =  static_cast<Gw_05_18ff1924::Lift_fault_codeType>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': 'PTO״̬', 'enum': {0: 'PTO_WORKING_STATE_', 1: 'PTO_WORKING_STATE_', 2: 'PTO_WORKING_STATE_', 3: 'PTO_WORKING_STATE_', 4: 'PTO_WORKING_STATE_'}, 'is_signed_var': False, 'len': 4, 'name': 'pto_working_state', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_05_18ff1924::Pto_working_stateType Gw0518ff1924::pto_working_state(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 4);

  Gw_05_18ff1924::Pto_working_stateType ret =  static_cast<Gw_05_18ff1924::Pto_working_stateType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
