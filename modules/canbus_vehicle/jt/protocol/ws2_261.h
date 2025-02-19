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

#include "modules/canbus_vehicle/jt/proto/jt.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace jt {

class Ws2261 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Ws2261();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'WS2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int ws2_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'WS2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int ws2_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 46, 'description': 'This signal is the the rear right  wheel speed direction.', 'enum': {0: 'WS2_WHEELSPEEDDIRECTION_RR_STOP', 1: 'WS2_WHEELSPEEDDIRECTION_RR_FORWARD', 2: 'WS2_WHEELSPEEDDIRECTION_RR_BACKWARD', 3: 'WS2_WHEELSPEEDDIRECTION_RR_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'WS2_WheelSpeedDirection_RR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
    Ws2_261::Ws2_wheelspeeddirection_rrType ws2_wheelspeeddirection_rr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'description': 'This signal is the the rear left wheel speed direction.', 'enum': {0: 'WS2_WHEELSPEEDDIRECTION_RL_STOP', 1: 'WS2_WHEELSPEEDDIRECTION_RL_FORWARD', 2: 'WS2_WHEELSPEEDDIRECTION_RL_BACKWARD', 3: 'WS2_WHEELSPEEDDIRECTION_RL_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'WS2_WheelSpeedDirection_RL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
    Ws2_261::Ws2_wheelspeeddirection_rlType ws2_wheelspeeddirection_rl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 42, 'description': 'This signal is the the front right wheel speed direction.', 'enum': {0: 'WS2_WHEELSPEEDDIRECTION_FR_STOP', 1: 'WS2_WHEELSPEEDDIRECTION_FR_FORWARD', 2: 'WS2_WHEELSPEEDDIRECTION_FR_BACKWARD', 3: 'WS2_WHEELSPEEDDIRECTION_FR_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'WS2_WheelSpeedDirection_FR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
    Ws2_261::Ws2_wheelspeeddirection_frType ws2_wheelspeeddirection_fr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'description': 'This signal is the the front left wheel speed direction.', 'enum': {0: 'WS2_WHEELSPEEDDIRECTION_FL_STOP', 1: 'WS2_WHEELSPEEDDIRECTION_FL_FORWARD', 2: 'WS2_WHEELSPEEDDIRECTION_FL_BACKWARD', 3: 'WS2_WHEELSPEEDDIRECTION_FL_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'WS2_WheelSpeedDirection_FL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
    Ws2_261::Ws2_wheelspeeddirection_flType ws2_wheelspeeddirection_fl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'description': 'This signal is the rear right wheel speed pulse(raw data).', 'is_signed_var': False, 'len': 8, 'name': 'WS2_WheelPulse_RR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'pulse', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
    int ws2_wheelpulse_rr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'description': 'This signal is the rear left wheel speed pulse(raw data).', 'is_signed_var': False, 'len': 8, 'name': 'WS2_WheelPulse_RL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'pulse', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
    int ws2_wheelpulse_rl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'This signal is the front right wheel speed pulse(raw data).', 'is_signed_var': False, 'len': 8, 'name': 'WS2_WheelPulse_FR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'pulse', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
    int ws2_wheelpulse_fr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal is the front left wheel speed pulse(raw data).', 'is_signed_var': False, 'len': 8, 'name': 'WS2_WheelPulse_FL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'pulse', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
    int ws2_wheelpulse_fl(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


