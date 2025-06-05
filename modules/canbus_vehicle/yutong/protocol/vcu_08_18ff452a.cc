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

#include "modules/canbus_vehicle/yutong/protocol/vcu_08_18ff452a.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Vcu0818ff452a::ID = 0x18ff452a;

// public
Vcu0818ff452a::Vcu0818ff452a() { Reset(); }

uint32_t Vcu0818ff452a::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Vcu0818ff452a::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_vcu_08_18ff452a()->set_defrosting(defrosting(bytes, length));
  chassis->mutable_vcu_08_18ff452a()->set_heating_heating_enabled(heating_heating_enabled(bytes, length));
  chassis->mutable_vcu_08_18ff452a()->set_cooling_gear(cooling_gear(bytes, length));
  chassis->mutable_vcu_08_18ff452a()->set_heating_gear(heating_gear(bytes, length));
}

void Vcu0818ff452a::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Vcu0818ff452a::UpdateData(uint8_t* data) {
  set_p_defrosting(data, defrosting_);
  set_p_heating_heating_enabled(data, heating_heating_enabled_);
  set_p_cooling_gear(data, cooling_gear_);
  set_p_heating_gear(data, heating_gear_);
}

void Vcu0818ff452a::Reset() {
  // TODO(All) :  you should check this manually
  defrosting_ = Vcu_08_18ff452a::DEFROSTING_OFF;
  heating_heating_enabled_ = Vcu_08_18ff452a::HEATING_HEATING_ENABLED_OFF;
  cooling_gear_ = Vcu_08_18ff452a::COOLING_GEAR_OFF;
  heating_gear_ = Vcu_08_18ff452a::HEATING_GEAR_;
}

Vcu0818ff452a* Vcu0818ff452a::set_defrosting(
    Vcu_08_18ff452a::DefrostingType defrosting) {
  defrosting_ = defrosting;
  return this;
 }

// config detail: {'bit': 0, 'enum': {0: 'DEFROSTING_', 1: 'DEFROSTING_'}, 'is_signed_var': False, 'len': 2, 'name': 'defrosting', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0818ff452a::set_p_defrosting(uint8_t* data,
    Vcu_08_18ff452a::DefrostingType defrosting) {
  int x = defrosting;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 2);
}


Vcu0818ff452a* Vcu0818ff452a::set_heating_heating_enabled(
    Vcu_08_18ff452a::Heating_heating_enabledType heating_heating_enabled) {
  heating_heating_enabled_ = heating_heating_enabled;
  return this;
 }

// config detail: {'bit': 2, 'enum': {0: 'HEATING_HEATING_ENABLED_', 2: 'HEATING_HEATING_ENABLED_'}, 'is_signed_var': False, 'len': 2, 'name': 'Heating_heating_enabled', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0818ff452a::set_p_heating_heating_enabled(uint8_t* data,
    Vcu_08_18ff452a::Heating_heating_enabledType heating_heating_enabled) {
  int x = heating_heating_enabled;

  Byte to_set(data + 0);
  to_set.set_value(x, 2, 2);
}


Vcu0818ff452a* Vcu0818ff452a::set_cooling_gear(
    Vcu_08_18ff452a::Cooling_gearType cooling_gear) {
  cooling_gear_ = cooling_gear;
  return this;
 }

// config detail: {'bit': 4, 'enum': {0: 'COOLING_GEAR_', 2: 'COOLING_GEAR_', 3: 'COOLING_GEAR_'}, 'is_signed_var': False, 'len': 2, 'name': 'Cooling_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0818ff452a::set_p_cooling_gear(uint8_t* data,
    Vcu_08_18ff452a::Cooling_gearType cooling_gear) {
  int x = cooling_gear;

  Byte to_set(data + 0);
  to_set.set_value(x, 4, 2);
}


Vcu0818ff452a* Vcu0818ff452a::set_heating_gear(
    Vcu_08_18ff452a::Heating_gearType heating_gear) {
  heating_gear_ = heating_gear;
  return this;
 }

// config detail: {'bit': 6, 'enum': {0: 'HEATING_GEAR_'}, 'is_signed_var': False, 'len': 2, 'name': 'Heating_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0818ff452a::set_p_heating_gear(uint8_t* data,
    Vcu_08_18ff452a::Heating_gearType heating_gear) {
  int x = heating_gear;

  Byte to_set(data + 0);
  to_set.set_value(x, 6, 2);
}


Vcu_08_18ff452a::DefrostingType Vcu0818ff452a::defrosting(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vcu_08_18ff452a::DefrostingType ret =  static_cast<Vcu_08_18ff452a::DefrostingType>(x);
  return ret;
}

Vcu_08_18ff452a::Heating_heating_enabledType Vcu0818ff452a::heating_heating_enabled(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(2, 2);

  Vcu_08_18ff452a::Heating_heating_enabledType ret =  static_cast<Vcu_08_18ff452a::Heating_heating_enabledType>(x);
  return ret;
}

Vcu_08_18ff452a::Cooling_gearType Vcu0818ff452a::cooling_gear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(4, 2);

  Vcu_08_18ff452a::Cooling_gearType ret =  static_cast<Vcu_08_18ff452a::Cooling_gearType>(x);
  return ret;
}

Vcu_08_18ff452a::Heating_gearType Vcu0818ff452a::heating_gear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(6, 2);

  Vcu_08_18ff452a::Heating_gearType ret =  static_cast<Vcu_08_18ff452a::Heating_gearType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
