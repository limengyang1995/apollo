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

#include "modules/canbus_vehicle/chitu/proto/chitu.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace chitu {

class Vcuswstate130 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Chitu> {
 public:
  static const int32_t ID;
  Vcuswstate130();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Chitu* chassis) const override;

 private:

    // config detail: {'bit': 0, 'enum': {0: 'VCU_MODE_AUTOMODE', 1: 'VCU_MODE_REMOTE_MODE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_Mode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_sw_state_130::Vcu_modeType vcu_mode(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace chitu
}  // namespace canbus
}  // namespace apollo


