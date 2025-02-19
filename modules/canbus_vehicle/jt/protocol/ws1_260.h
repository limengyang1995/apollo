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

class Ws1260 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Ws1260();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 48, 'description': 'This signal is rear right wheel speed which sent by ABS without filtering.', 'is_signed_var': False, 'len': 15, 'name': 'WS1_WheelSpeed_RR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
    double ws1_wheelspeed_rr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'description': 'This signal is rear left wheel speed which sent by ABS without filtering.', 'is_signed_var': False, 'len': 15, 'name': 'WS1_WheelSpeed_RL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
    double ws1_wheelspeed_rl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'This signal is front right wheel speed which sent by ABS without filtering.', 'is_signed_var': False, 'len': 15, 'name': 'WS1_WheelSpeed_FR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
    double ws1_wheelspeed_fr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'This signal is front left wheel speed which sent by ABS without filtering.', 'is_signed_var': False, 'len': 15, 'name': 'WS1_WheelSpeed_FL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
    double ws1_wheelspeed_fl(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


