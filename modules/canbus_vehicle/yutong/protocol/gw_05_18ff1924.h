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

#pragma once

#include "modules/canbus_vehicle/yutong/proto/yutong.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace yutong {

class Gw0518ff1924 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw0518ff1924();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 0, 'enum': {0: 'BRAKE_LIGHT_CONTROL_', 1: 'BRAKE_LIGHT_CONTROL_'}, 'is_signed_var': False, 'len': 2, 'name': 'Brake_light_control', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_05_18ff1924::Brake_light_controlType brake_light_control(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'enum': {0: 'LIFT_FAULT_CODE_', 1: 'LIFT_FAULT_CODE_'}, 'is_signed_var': False, 'len': 4, 'name': 'Lift_fault_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_05_18ff1924::Lift_fault_codeType lift_fault_code(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'description': 'PTO״̬', 'enum': {0: 'PTO_WORKING_STATE_', 1: 'PTO_WORKING_STATE_', 2: 'PTO_WORKING_STATE_', 3: 'PTO_WORKING_STATE_', 4: 'PTO_WORKING_STATE_'}, 'is_signed_var': False, 'len': 4, 'name': 'PTO_working_state', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_05_18ff1924::Pto_working_stateType pto_working_state(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


