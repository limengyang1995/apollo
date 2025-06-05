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

class Gw2318ffc017 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw2318ffc017();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 0, 'description': 'ֵ0-1000kpa', 'is_signed_var': False, 'len': 8, 'name': 'Fa_brake_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'Kpa', 'precision': 4.0, 'type': 'double'}
    double fa_brake_pressure(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'ֵ0-1000KPA', 'is_signed_var': False, 'len': 8, 'name': 'Ra_brake_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'Kpa', 'precision': 4.0, 'type': 'double'}
    double ra_brake_pressure(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'ֵ0to32V', 'is_signed_var': False, 'len': 8, 'name': 'Voltage_24V_supply', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'V', 'precision': 0.5, 'type': 'double'}
    double voltage_24v_supply(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'enum': {0: 'ON_GEAR_SIGNAL_', 1: 'ON_GEAR_SIGNAL_NO'}, 'is_signed_var': False, 'len': 2, 'name': 'ON_gear_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_23_18ffc017::On_gear_signalType on_gear_signal(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 62, 'enum': {0: 'TOTAL_FIRE_SIGNAL_', 1: 'TOTAL_FIRE_SIGNAL_'}, 'is_signed_var': False, 'len': 2, 'name': 'Total_fire_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_23_18ffc017::Total_fire_signalType total_fire_signal(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


