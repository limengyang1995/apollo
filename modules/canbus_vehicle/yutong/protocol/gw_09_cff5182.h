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

class Gw09cff5182 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw09cff5182();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 8, 'is_signed_var': False, 'len': 16, 'name': 'Actual_motor_torque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'Nm', 'precision': 1.0, 'type': 'int'}
    int actual_motor_torque(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'is_signed_var': False, 'len': 16, 'name': 'Motor_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'rmp', 'precision': 0.25, 'type': 'double'}
    double motor_speed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'Main_motor_temp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int main_motor_temp(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'Main_motor_borad_temp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int main_motor_borad_temp(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 56, 'enum': {0: 'FAULT_CODE_'}, 'is_signed_var': False, 'len': 6, 'name': 'Fault_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|63]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_09_cff5182::Fault_codeType fault_code(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 62, 'enum': {0: 'FAILURELEVEL_', 1: 'FAILURELEVEL_Һ', 2: 'FAILURELEVEL_', 3: 'FAILURELEVEL_'}, 'is_signed_var': False, 'len': 2, 'name': 'FailureLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_09_cff5182::FailurelevelType failurelevel(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


