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

#include "modules/canbus_vehicle/yutong/protocol/gw_12_18ff30f4.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw1218ff30f4::Gw1218ff30f4() {}
const int32_t Gw1218ff30f4::ID = 0x18ff30f4;

void Gw1218ff30f4::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_12_18ff30f4()->set_total_battery_voltage(total_battery_voltage(bytes, length));
  chassis->mutable_gw_12_18ff30f4()->set_total_battery_current(total_battery_current(bytes, length));
  chassis->mutable_gw_12_18ff30f4()->set_battery_capacity_soc(battery_capacity_soc(bytes, length));
  chassis->mutable_gw_12_18ff30f4()->set_battery_system_status(battery_system_status(bytes, length));
  chassis->mutable_gw_12_18ff30f4()->set_fault_code(fault_code(bytes, length));
  chassis->mutable_gw_12_18ff30f4()->set_level_of_failure(level_of_failure(bytes, length));
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'total_battery_voltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
double Gw1218ff30f4::total_battery_voltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'total_battery_current', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'A', 'precision': 0.05, 'type': 'double'}
double Gw1218ff30f4::total_battery_current(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.050000;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'battery_capacity_soc', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
double Gw1218ff30f4::battery_capacity_soc(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

// config detail: {'bit': 44, 'enum': {0: 'BATTERY_SYSTEM_STATUS_', 2: 'BATTERY_SYSTEM_STATUS_', 6: 'BATTERY_SYSTEM_STATUS_DCDC', 12: 'BATTERY_SYSTEM_STATUS_', 14: 'BATTERY_SYSTEM_STATUS_'}, 'is_signed_var': False, 'len': 4, 'name': 'battery_system_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_12_18ff30f4::Battery_system_statusType Gw1218ff30f4::battery_system_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 4);

  Gw_12_18ff30f4::Battery_system_statusType ret =  static_cast<Gw_12_18ff30f4::Battery_system_statusType>(x);
  return ret;
}

// config detail: {'bit': 56, 'description': '0x00', 'is_signed_var': False, 'len': 6, 'name': 'fault_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|63]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Gw1218ff30f4::fault_code(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 6);

  int ret = x;
  return ret;
}

// config detail: {'bit': 62, 'enum': {0: 'LEVEL_OF_FAILURE_', 1: 'LEVEL_OF_FAILURE_', 2: 'LEVEL_OF_FAILURE_', 3: 'LEVEL_OF_FAILURE_'}, 'is_signed_var': False, 'len': 2, 'name': 'level_of_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_12_18ff30f4::Level_of_failureType Gw1218ff30f4::level_of_failure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(6, 2);

  Gw_12_18ff30f4::Level_of_failureType ret =  static_cast<Gw_12_18ff30f4::Level_of_failureType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
