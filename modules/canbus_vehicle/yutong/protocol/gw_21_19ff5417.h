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

class Gw2119ff5417 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw2119ff5417();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 6, 'enum': {0: 'STATE_OF_LIFT_', 1: 'STATE_OF_LIFT_'}, 'is_signed_var': False, 'len': 1, 'name': 'State_of_lift', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_21_19ff5417::State_of_liftType state_of_lift(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 12, 'enum': {0: 'INTERAXIS_LOCK_THRESHOLD_STATE_', 1: 'INTERAXIS_LOCK_THRESHOLD_STATE_'}, 'is_signed_var': False, 'len': 2, 'name': 'Interaxis_lock_threshold_state', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_21_19ff5417::Interaxis_lock_threshold_stateType interaxis_lock_threshold_state(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


