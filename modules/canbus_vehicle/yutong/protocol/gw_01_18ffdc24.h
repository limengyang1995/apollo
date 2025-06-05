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

class Gw0118ffdc24 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw0118ffdc24();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'Pedal_opening', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '-', 'precision': 0.4, 'type': 'double'}
    double pedal_opening(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'is_signed_var': False, 'len': 16, 'name': 'Vehicle_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '-', 'precision': 0.00390625, 'type': 'double'}
    double vehicle_speed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'enum': {0: 'DRIVER_COMMANDS_GEAR_N', 1: 'DRIVER_COMMANDS_GEAR_D', 2: 'DRIVER_COMMANDS_GEAR_R', 3: 'DRIVER_COMMANDS_GEAR_L'}, 'is_signed_var': False, 'len': 4, 'name': 'Driver_commands_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_01_18ffdc24::Driver_commands_gearType driver_commands_gear(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'enum': {0: 'CURRENT_GEAR_N', 1: 'CURRENT_GEAR_D', 2: 'CURRENT_GEAR_R', 3: 'CURRENT_GEAR_L'}, 'is_signed_var': False, 'len': 4, 'name': 'Current_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_01_18ffdc24::Current_gearType current_gear(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'Actual_AccPedalPos', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '-', 'precision': 0.4, 'type': 'double'}
    double actual_accpedalpos(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'Responds_AccepedalPos', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '-', 'precision': 0.4, 'type': 'double'}
    double responds_accepedalpos(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'counter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int counter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 56, 'enum': {0: 'DRIVING_MODE_FEEDBACK_', 1: 'DRIVING_MODE_FEEDBACK_', 2: 'DRIVING_MODE_FEEDBACK_'}, 'is_signed_var': False, 'len': 3, 'name': 'Driving_mode_feedback', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_01_18ffdc24::Driving_mode_feedbackType driving_mode_feedback(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 59, 'enum': {0: 'AUTOPILOT_EXIT_REASONS_', 1: 'AUTOPILOT_EXIT_REASONS_', 2: 'AUTOPILOT_EXIT_REASONS_', 3: 'AUTOPILOT_EXIT_REASONS_', 4: 'AUTOPILOT_EXIT_REASONS_', 5: 'AUTOPILOT_EXIT_REASONS_', 6: 'AUTOPILOT_EXIT_REASONS_', 7: 'AUTOPILOT_EXIT_REASONS_'}, 'is_signed_var': False, 'len': 3, 'name': 'Autopilot_exit_reasons', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_01_18ffdc24::Autopilot_exit_reasonsType autopilot_exit_reasons(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 62, 'enum': {0: 'EMERGENCY_STOP_', 1: 'EMERGENCY_STOP_'}, 'is_signed_var': False, 'len': 2, 'name': 'Emergency_stop', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_01_18ffdc24::Emergency_stopType emergency_stop(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


