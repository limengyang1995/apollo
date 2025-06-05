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

class Gw0319ffca24 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw0319ffca24();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 40, 'enum': {0: 'GEARBOX_SYSTEM_FAILURE_', 1: 'GEARBOX_SYSTEM_FAILURE_', 2: 'GEARBOX_SYSTEM_FAILURE_'}, 'is_signed_var': False, 'len': 4, 'name': 'Gearbox_system_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_03_19ffca24::Gearbox_system_failureType gearbox_system_failure(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'enum': {0: 'EPB_SYSTEM_FAILURE_', 1: 'EPB_SYSTEM_FAILURE_', 2: 'EPB_SYSTEM_FAILURE_'}, 'is_signed_var': False, 'len': 4, 'name': 'EPB_system_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_03_19ffca24::Epb_system_failureType epb_system_failure(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 48, 'enum': {0: 'STEERING_SYSTEM_FAILURE_', 1: 'STEERING_SYSTEM_FAILURE_', 2: 'STEERING_SYSTEM_FAILURE_'}, 'is_signed_var': False, 'len': 4, 'name': 'Steering_system_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_03_19ffca24::Steering_system_failureType steering_system_failure(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 52, 'enum': {0: 'HIGH_VOLTAGE_SYSTEM_FAULT_', 1: 'HIGH_VOLTAGE_SYSTEM_FAULT_'}, 'is_signed_var': False, 'len': 4, 'name': 'High_voltage_system_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_03_19ffca24::High_voltage_system_faultType high_voltage_system_fault(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 56, 'enum': {0: 'BRAKE_SYSTEM_FAILURE_', 1: 'BRAKE_SYSTEM_FAILURE_', 2: 'BRAKE_SYSTEM_FAILURE_'}, 'is_signed_var': False, 'len': 4, 'name': 'Brake_system_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_03_19ffca24::Brake_system_failureType brake_system_failure(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'enum': {0: 'DRIVE_SYSTEM_FAULT_', 1: 'DRIVE_SYSTEM_FAULT_', 2: 'DRIVE_SYSTEM_FAULT_', 3: 'DRIVE_SYSTEM_FAULT_'}, 'is_signed_var': False, 'len': 4, 'name': 'Drive_system_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_03_19ffca24::Drive_system_faultType drive_system_fault(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


