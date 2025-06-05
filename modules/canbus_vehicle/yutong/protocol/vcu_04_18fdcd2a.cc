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

#include "modules/canbus_vehicle/yutong/protocol/vcu_04_18fdcd2a.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Vcu0418fdcd2a::ID = 0x18fdcd2a;

// public
Vcu0418fdcd2a::Vcu0418fdcd2a() { Reset(); }

uint32_t Vcu0418fdcd2a::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Vcu0418fdcd2a::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_vcu_04_18fdcd2a()->set_wipercontrol(wipercontrol(bytes, length));
  chassis->mutable_vcu_04_18fdcd2a()->set_washcontrol(washcontrol(bytes, length));
}

void Vcu0418fdcd2a::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Vcu0418fdcd2a::UpdateData(uint8_t* data) {
  set_p_wipercontrol(data, wipercontrol_);
  set_p_washcontrol(data, washcontrol_);
}

void Vcu0418fdcd2a::Reset() {
  // TODO(All) :  you should check this manually
  wipercontrol_ = Vcu_04_18fdcd2a::WIPERCONTROL_;
  washcontrol_ = Vcu_04_18fdcd2a::WASHCONTROL_OF;
}

Vcu0418fdcd2a* Vcu0418fdcd2a::set_wipercontrol(
    Vcu_04_18fdcd2a::WipercontrolType wipercontrol) {
  wipercontrol_ = wipercontrol;
  return this;
 }

// config detail: {'bit': 4, 'enum': {0: 'WIPERCONTROL_'}, 'is_signed_var': False, 'len': 4, 'name': 'WiperControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0418fdcd2a::set_p_wipercontrol(uint8_t* data,
    Vcu_04_18fdcd2a::WipercontrolType wipercontrol) {
  int x = wipercontrol;

  Byte to_set(data + 0);
  to_set.set_value(x, 4, 4);
}


Vcu0418fdcd2a* Vcu0418fdcd2a::set_washcontrol(
    Vcu_04_18fdcd2a::WashcontrolType washcontrol) {
  washcontrol_ = washcontrol;
  return this;
 }

// config detail: {'bit': 45, 'enum': {0: 'WASHCONTROL_OF', 1: 'WASHCONTROL_O'}, 'is_signed_var': False, 'len': 3, 'name': 'WashControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0418fdcd2a::set_p_washcontrol(uint8_t* data,
    Vcu_04_18fdcd2a::WashcontrolType washcontrol) {
  int x = washcontrol;

  Byte to_set(data + 5);
  to_set.set_value(x, 5, 3);
}


Vcu_04_18fdcd2a::WipercontrolType Vcu0418fdcd2a::wipercontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(4, 4);

  Vcu_04_18fdcd2a::WipercontrolType ret =  static_cast<Vcu_04_18fdcd2a::WipercontrolType>(x);
  return ret;
}

Vcu_04_18fdcd2a::WashcontrolType Vcu0418fdcd2a::washcontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(5, 3);

  Vcu_04_18fdcd2a::WashcontrolType ret =  static_cast<Vcu_04_18fdcd2a::WashcontrolType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
