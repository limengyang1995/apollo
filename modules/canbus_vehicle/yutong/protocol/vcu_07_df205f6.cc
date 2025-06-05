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

#include "modules/canbus_vehicle/yutong/protocol/vcu_07_df205f6.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Vcu07df205f6::ID = 0xdf205f6;

// public
Vcu07df205f6::Vcu07df205f6() { Reset(); }

uint32_t Vcu07df205f6::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Vcu07df205f6::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_vcu_07_df205f6()->set_vehicle_power_supply_ctrl(vehicle_power_supply_ctrl(bytes, length));
}

void Vcu07df205f6::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Vcu07df205f6::UpdateData(uint8_t* data) {
  set_p_vehicle_power_supply_ctrl(data, vehicle_power_supply_ctrl_);
}

void Vcu07df205f6::Reset() {
  // TODO(All) :  you should check this manually
  vehicle_power_supply_ctrl_ = Vcu_07_df205f6::VEHICLE_POWER_SUPPLY_CTRL_OFF;
}

Vcu07df205f6* Vcu07df205f6::set_vehicle_power_supply_ctrl(
    Vcu_07_df205f6::Vehicle_power_supply_ctrlType vehicle_power_supply_ctrl) {
  vehicle_power_supply_ctrl_ = vehicle_power_supply_ctrl;
  return this;
 }

// config detail: {'bit': 4, 'enum': {0: 'VEHICLE_POWER_SUPPLY_CTRL_', 2: 'VEHICLE_POWER_SUPPLY_CTRL_', 3: 'VEHICLE_POWER_SUPPLY_CTRL_REDAY'}, 'is_signed_var': False, 'len': 4, 'name': 'Vehicle_Power_supply_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu07df205f6::set_p_vehicle_power_supply_ctrl(uint8_t* data,
    Vcu_07_df205f6::Vehicle_power_supply_ctrlType vehicle_power_supply_ctrl) {
  int x = vehicle_power_supply_ctrl;

  Byte to_set(data + 0);
  to_set.set_value(x, 4, 4);
}


Vcu_07_df205f6::Vehicle_power_supply_ctrlType Vcu07df205f6::vehicle_power_supply_ctrl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(4, 4);

  Vcu_07_df205f6::Vehicle_power_supply_ctrlType ret =  static_cast<Vcu_07_df205f6::Vehicle_power_supply_ctrlType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
