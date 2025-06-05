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

class Gw1218ff30f4 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw1218ff30f4();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'Total_battery_voltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
    double total_battery_voltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'Total_battery_current', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'A', 'precision': 0.05, 'type': 'double'}
    double total_battery_current(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'Battery_capacity_SOC', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
    double battery_capacity_soc(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'enum': {0: 'BATTERY_SYSTEM_STATUS_', 2: 'BATTERY_SYSTEM_STATUS_', 6: 'BATTERY_SYSTEM_STATUS_DCDC', 12: 'BATTERY_SYSTEM_STATUS_', 14: 'BATTERY_SYSTEM_STATUS_'}, 'is_signed_var': False, 'len': 4, 'name': 'Battery_system_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_12_18ff30f4::Battery_system_statusType battery_system_status(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 56, 'description': '0x00', 'is_signed_var': False, 'len': 6, 'name': 'Fault_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|63]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int fault_code(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 62, 'enum': {0: 'LEVEL_OF_FAILURE_', 1: 'LEVEL_OF_FAILURE_', 2: 'LEVEL_OF_FAILURE_', 3: 'LEVEL_OF_FAILURE_'}, 'is_signed_var': False, 'len': 2, 'name': 'Level_of_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_12_18ff30f4::Level_of_failureType level_of_failure(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


