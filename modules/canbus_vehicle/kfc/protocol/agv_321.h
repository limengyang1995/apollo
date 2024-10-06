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

#include "modules/canbus_vehicle/kfc/proto/kfc.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace kfc {

class Agv321 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Kfc> {
 public:
  static const int32_t ID;
  Agv321();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Kfc* chassis) const override;

 private:

    // config detail: {'bit': 0, 'enum': {0: 'AGV_MESSAGE_ST_INIVD', 1: 'AGV_MESSAGE_ST_STOP', 2: 'AGV_MESSAGE_ST_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'Agv_Message_St', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Agv_321::Agv_message_stType agv_message_st(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace kfc
}  // namespace canbus
}  // namespace apollo


