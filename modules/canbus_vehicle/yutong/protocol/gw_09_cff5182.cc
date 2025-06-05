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

#include "modules/canbus_vehicle/yutong/protocol/gw_09_cff5182.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw09cff5182::Gw09cff5182() {}
const int32_t Gw09cff5182::ID = 0xcff5182;

void Gw09cff5182::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_09_cff5182()->set_actual_motor_torque(actual_motor_torque(bytes, length));
  chassis->mutable_gw_09_cff5182()->set_motor_speed(motor_speed(bytes, length));
  chassis->mutable_gw_09_cff5182()->set_main_motor_temp(main_motor_temp(bytes, length));
  chassis->mutable_gw_09_cff5182()->set_main_motor_borad_temp(main_motor_borad_temp(bytes, length));
  chassis->mutable_gw_09_cff5182()->set_fault_code(fault_code(bytes, length));
  chassis->mutable_gw_09_cff5182()->set_failurelevel(failurelevel(bytes, length));
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 16, 'name': 'actual_motor_torque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'Nm', 'precision': 1.0, 'type': 'int'}
int Gw09cff5182::actual_motor_torque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 16, 'name': 'motor_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'rmp', 'precision': 0.25, 'type': 'double'}
double Gw09cff5182::motor_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.250000;
  return ret;
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'main_motor_temp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Gw09cff5182::main_motor_temp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'main_motor_borad_temp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Gw09cff5182::main_motor_borad_temp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'enum': {0: 'FAULT_CODE_'}, 'is_signed_var': False, 'len': 6, 'name': 'fault_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|63]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_09_cff5182::Fault_codeType Gw09cff5182::fault_code(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 6);

  Gw_09_cff5182::Fault_codeType ret =  static_cast<Gw_09_cff5182::Fault_codeType>(x);
  return ret;
}

// config detail: {'bit': 62, 'enum': {0: 'FAILURELEVEL_', 1: 'FAILURELEVEL_Һ', 2: 'FAILURELEVEL_', 3: 'FAILURELEVEL_'}, 'is_signed_var': False, 'len': 2, 'name': 'failurelevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_09_cff5182::FailurelevelType Gw09cff5182::failurelevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(6, 2);

  Gw_09_cff5182::FailurelevelType ret =  static_cast<Gw_09_cff5182::FailurelevelType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
