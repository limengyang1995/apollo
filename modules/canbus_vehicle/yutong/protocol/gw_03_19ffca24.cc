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

#include "modules/canbus_vehicle/yutong/protocol/gw_03_19ffca24.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw0319ffca24::Gw0319ffca24() {}
const int32_t Gw0319ffca24::ID = 0x19ffca24;

void Gw0319ffca24::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_03_19ffca24()->set_gearbox_system_failure(gearbox_system_failure(bytes, length));
  chassis->mutable_gw_03_19ffca24()->set_epb_system_failure(epb_system_failure(bytes, length));
  chassis->mutable_gw_03_19ffca24()->set_steering_system_failure(steering_system_failure(bytes, length));
  chassis->mutable_gw_03_19ffca24()->set_high_voltage_system_fault(high_voltage_system_fault(bytes, length));
  chassis->mutable_gw_03_19ffca24()->set_brake_system_failure(brake_system_failure(bytes, length));
  chassis->mutable_gw_03_19ffca24()->set_drive_system_fault(drive_system_fault(bytes, length));
}

// config detail: {'bit': 40, 'enum': {0: 'GEARBOX_SYSTEM_FAILURE_', 1: 'GEARBOX_SYSTEM_FAILURE_', 2: 'GEARBOX_SYSTEM_FAILURE_'}, 'is_signed_var': False, 'len': 4, 'name': 'gearbox_system_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_03_19ffca24::Gearbox_system_failureType Gw0319ffca24::gearbox_system_failure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 4);

  Gw_03_19ffca24::Gearbox_system_failureType ret =  static_cast<Gw_03_19ffca24::Gearbox_system_failureType>(x);
  return ret;
}

// config detail: {'bit': 44, 'enum': {0: 'EPB_SYSTEM_FAILURE_', 1: 'EPB_SYSTEM_FAILURE_', 2: 'EPB_SYSTEM_FAILURE_'}, 'is_signed_var': False, 'len': 4, 'name': 'epb_system_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_03_19ffca24::Epb_system_failureType Gw0319ffca24::epb_system_failure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 4);

  Gw_03_19ffca24::Epb_system_failureType ret =  static_cast<Gw_03_19ffca24::Epb_system_failureType>(x);
  return ret;
}

// config detail: {'bit': 48, 'enum': {0: 'STEERING_SYSTEM_FAILURE_', 1: 'STEERING_SYSTEM_FAILURE_', 2: 'STEERING_SYSTEM_FAILURE_'}, 'is_signed_var': False, 'len': 4, 'name': 'steering_system_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_03_19ffca24::Steering_system_failureType Gw0319ffca24::steering_system_failure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 4);

  Gw_03_19ffca24::Steering_system_failureType ret =  static_cast<Gw_03_19ffca24::Steering_system_failureType>(x);
  return ret;
}

// config detail: {'bit': 52, 'enum': {0: 'HIGH_VOLTAGE_SYSTEM_FAULT_', 1: 'HIGH_VOLTAGE_SYSTEM_FAULT_'}, 'is_signed_var': False, 'len': 4, 'name': 'high_voltage_system_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_03_19ffca24::High_voltage_system_faultType Gw0319ffca24::high_voltage_system_fault(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(4, 4);

  Gw_03_19ffca24::High_voltage_system_faultType ret =  static_cast<Gw_03_19ffca24::High_voltage_system_faultType>(x);
  return ret;
}

// config detail: {'bit': 56, 'enum': {0: 'BRAKE_SYSTEM_FAILURE_', 1: 'BRAKE_SYSTEM_FAILURE_', 2: 'BRAKE_SYSTEM_FAILURE_'}, 'is_signed_var': False, 'len': 4, 'name': 'brake_system_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_03_19ffca24::Brake_system_failureType Gw0319ffca24::brake_system_failure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 4);

  Gw_03_19ffca24::Brake_system_failureType ret =  static_cast<Gw_03_19ffca24::Brake_system_failureType>(x);
  return ret;
}

// config detail: {'bit': 60, 'enum': {0: 'DRIVE_SYSTEM_FAULT_', 1: 'DRIVE_SYSTEM_FAULT_', 2: 'DRIVE_SYSTEM_FAULT_', 3: 'DRIVE_SYSTEM_FAULT_'}, 'is_signed_var': False, 'len': 4, 'name': 'drive_system_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_03_19ffca24::Drive_system_faultType Gw0319ffca24::drive_system_fault(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  Gw_03_19ffca24::Drive_system_faultType ret =  static_cast<Gw_03_19ffca24::Drive_system_faultType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
