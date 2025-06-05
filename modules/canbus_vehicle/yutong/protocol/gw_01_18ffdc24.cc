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

#include "modules/canbus_vehicle/yutong/protocol/gw_01_18ffdc24.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw0118ffdc24::Gw0118ffdc24() {}
const int32_t Gw0118ffdc24::ID = 0x18ffdc24;

void Gw0118ffdc24::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_01_18ffdc24()->set_pedal_opening(pedal_opening(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_vehicle_speed(vehicle_speed(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_driver_commands_gear(driver_commands_gear(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_current_gear(current_gear(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_actual_accpedalpos(actual_accpedalpos(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_responds_accepedalpos(responds_accepedalpos(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_counter(counter(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_driving_mode_feedback(driving_mode_feedback(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_autopilot_exit_reasons(autopilot_exit_reasons(bytes, length));
  chassis->mutable_gw_01_18ffdc24()->set_emergency_stop(emergency_stop(bytes, length));
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'pedal_opening', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '-', 'precision': 0.4, 'type': 'double'}
double Gw0118ffdc24::pedal_opening(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 16, 'name': 'vehicle_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '-', 'precision': 0.00390625, 'type': 'double'}
double Gw0118ffdc24::vehicle_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.003906;
  return ret;
}

// config detail: {'bit': 24, 'enum': {0: 'DRIVER_COMMANDS_GEAR_N', 1: 'DRIVER_COMMANDS_GEAR_D', 2: 'DRIVER_COMMANDS_GEAR_R', 3: 'DRIVER_COMMANDS_GEAR_L'}, 'is_signed_var': False, 'len': 4, 'name': 'driver_commands_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_01_18ffdc24::Driver_commands_gearType Gw0118ffdc24::driver_commands_gear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 4);

  Gw_01_18ffdc24::Driver_commands_gearType ret =  static_cast<Gw_01_18ffdc24::Driver_commands_gearType>(x);
  return ret;
}

// config detail: {'bit': 28, 'enum': {0: 'CURRENT_GEAR_N', 1: 'CURRENT_GEAR_D', 2: 'CURRENT_GEAR_R', 3: 'CURRENT_GEAR_L'}, 'is_signed_var': False, 'len': 4, 'name': 'current_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_01_18ffdc24::Current_gearType Gw0118ffdc24::current_gear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 4);

  Gw_01_18ffdc24::Current_gearType ret =  static_cast<Gw_01_18ffdc24::Current_gearType>(x);
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'actual_accpedalpos', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '-', 'precision': 0.4, 'type': 'double'}
double Gw0118ffdc24::actual_accpedalpos(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'responds_accepedalpos', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '-', 'precision': 0.4, 'type': 'double'}
double Gw0118ffdc24::responds_accepedalpos(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'counter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Gw0118ffdc24::counter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'enum': {0: 'DRIVING_MODE_FEEDBACK_', 1: 'DRIVING_MODE_FEEDBACK_', 2: 'DRIVING_MODE_FEEDBACK_'}, 'is_signed_var': False, 'len': 3, 'name': 'driving_mode_feedback', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_01_18ffdc24::Driving_mode_feedbackType Gw0118ffdc24::driving_mode_feedback(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 3);

  Gw_01_18ffdc24::Driving_mode_feedbackType ret =  static_cast<Gw_01_18ffdc24::Driving_mode_feedbackType>(x);
  return ret;
}

// config detail: {'bit': 59, 'enum': {0: 'AUTOPILOT_EXIT_REASONS_', 1: 'AUTOPILOT_EXIT_REASONS_', 2: 'AUTOPILOT_EXIT_REASONS_', 3: 'AUTOPILOT_EXIT_REASONS_', 4: 'AUTOPILOT_EXIT_REASONS_', 5: 'AUTOPILOT_EXIT_REASONS_', 6: 'AUTOPILOT_EXIT_REASONS_', 7: 'AUTOPILOT_EXIT_REASONS_'}, 'is_signed_var': False, 'len': 3, 'name': 'autopilot_exit_reasons', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_01_18ffdc24::Autopilot_exit_reasonsType Gw0118ffdc24::autopilot_exit_reasons(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(3, 3);

  Gw_01_18ffdc24::Autopilot_exit_reasonsType ret =  static_cast<Gw_01_18ffdc24::Autopilot_exit_reasonsType>(x);
  return ret;
}

// config detail: {'bit': 62, 'enum': {0: 'EMERGENCY_STOP_', 1: 'EMERGENCY_STOP_'}, 'is_signed_var': False, 'len': 2, 'name': 'emergency_stop', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_01_18ffdc24::Emergency_stopType Gw0118ffdc24::emergency_stop(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(6, 2);

  Gw_01_18ffdc24::Emergency_stopType ret =  static_cast<Gw_01_18ffdc24::Emergency_stopType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
