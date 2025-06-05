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

class Gw2418a70017 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw2418a70017();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 24, 'enum': {0: 'HORN_SIGNAL_OFF', 1: 'HORN_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'Horn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_24_18a70017::Horn_signalType horn_signal(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 27, 'enum': {0: 'FOG_LIGHT_SIGNAL_OFF', 1: 'FOG_LIGHT_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'Fog_light_signal', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_24_18a70017::Fog_light_signalType fog_light_signal(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'enum': {0: 'LOW_BEAM_SIGNAL_OFF', 1: 'LOW_BEAM_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'Low_beam_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_24_18a70017::Low_beam_signalType low_beam_signal(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 30, 'enum': {0: 'HIGH_BEAM_SIGNAL_OFF', 1: 'HIGH_BEAM_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'High_beam_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_24_18a70017::High_beam_signalType high_beam_signal(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'enum': {0: 'LEFT_TURN_SIGNAL_OFF', 1: 'LEFT_TURN_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'Left_turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_24_18a70017::Left_turn_signalType left_turn_signal(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 34, 'enum': {0: 'RIGHT_TURN_SIGNAL_OFF', 1: 'RIGHT_TURN_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'Right_turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_24_18a70017::Right_turn_signalType right_turn_signal(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 36, 'enum': {0: 'BRAKINGSTS_OFF', 1: 'BRAKINGSTS_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'BrakingSts', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_24_18a70017::BrakingstsType brakingsts(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


