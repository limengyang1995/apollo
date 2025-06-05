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

#include "modules/canbus_vehicle/yutong/protocol/vcu_05_18ff422a.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Vcu0518ff422a::ID = 0x18ff422a;

// public
Vcu0518ff422a::Vcu0518ff422a() { Reset(); }

uint32_t Vcu0518ff422a::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Vcu0518ff422a::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_vcu_05_18ff422a()->set_lifting_control_of_the_cargo_box(lifting_control_of_the_cargo_box(bytes, length));
  chassis->mutable_vcu_05_18ff422a()->set_horn_control(horn_control(bytes, length));
  chassis->mutable_vcu_05_18ff422a()->set_lighting_enablement(lighting_enablement(bytes, length));
  chassis->mutable_vcu_05_18ff422a()->set_gear_enable(gear_enable(bytes, length));
  chassis->mutable_vcu_05_18ff422a()->set_lift_enable(lift_enable(bytes, length));
  chassis->mutable_vcu_05_18ff422a()->set_inter_axis_locking_threshold(inter_axis_locking_threshold(bytes, length));
}

void Vcu0518ff422a::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Vcu0518ff422a::UpdateData(uint8_t* data) {
  set_p_lifting_control_of_the_cargo_box(data, lifting_control_of_the_cargo_box_);
  set_p_horn_control(data, horn_control_);
  set_p_lighting_enablement(data, lighting_enablement_);
  set_p_gear_enable(data, gear_enable_);
  set_p_lift_enable(data, lift_enable_);
  set_p_inter_axis_locking_threshold(data, inter_axis_locking_threshold_);
}

void Vcu0518ff422a::Reset() {
  // TODO(All) :  you should check this manually
  lifting_control_of_the_cargo_box_ = Vcu_05_18ff422a::LIFTING_CONTROL_OF_THE_CARGO_BOX_NO_ACTION;
  horn_control_ = Vcu_05_18ff422a::HORN_CONTROL_OFF;
  lighting_enablement_ = Vcu_05_18ff422a::LIGHTING_ENABLEMENT_OFF;
  gear_enable_ = Vcu_05_18ff422a::GEAR_ENABLE_OFF;
  lift_enable_ = Vcu_05_18ff422a::LIFT_ENABLE_OFF;
  inter_axis_locking_threshold_ = Vcu_05_18ff422a::INTER_AXIS_LOCKING_THRESHOLD_OFF;
}

Vcu0518ff422a* Vcu0518ff422a::set_lifting_control_of_the_cargo_box(
    Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType lifting_control_of_the_cargo_box) {
  lifting_control_of_the_cargo_box_ = lifting_control_of_the_cargo_box;
  return this;
 }

// config detail: {'bit': 16, 'enum': {0: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 1: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 2: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 3: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_'}, 'is_signed_var': False, 'len': 4, 'name': 'Lifting_control_of_the_cargo_box', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0518ff422a::set_p_lifting_control_of_the_cargo_box(uint8_t* data,
    Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType lifting_control_of_the_cargo_box) {
  int x = lifting_control_of_the_cargo_box;

  Byte to_set(data + 2);
  to_set.set_value(x, 0, 4);
}


Vcu0518ff422a* Vcu0518ff422a::set_horn_control(
    Vcu_05_18ff422a::Horn_controlType horn_control) {
  horn_control_ = horn_control;
  return this;
 }

// config detail: {'bit': 20, 'enum': {0: 'HORN_CONTROL_', 1: 'HORN_CONTROL_'}, 'is_signed_var': False, 'len': 4, 'name': 'Horn_control', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0518ff422a::set_p_horn_control(uint8_t* data,
    Vcu_05_18ff422a::Horn_controlType horn_control) {
  int x = horn_control;

  Byte to_set(data + 2);
  to_set.set_value(x, 4, 4);
}


Vcu0518ff422a* Vcu0518ff422a::set_lighting_enablement(
    Vcu_05_18ff422a::Lighting_enablementType lighting_enablement) {
  lighting_enablement_ = lighting_enablement;
  return this;
 }

// config detail: {'bit': 24, 'enum': {0: 'LIGHTING_ENABLEMENT_', 1: 'LIGHTING_ENABLEMENT_'}, 'is_signed_var': False, 'len': 2, 'name': 'Lighting_enablement', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0518ff422a::set_p_lighting_enablement(uint8_t* data,
    Vcu_05_18ff422a::Lighting_enablementType lighting_enablement) {
  int x = lighting_enablement;

  Byte to_set(data + 3);
  to_set.set_value(x, 0, 2);
}


Vcu0518ff422a* Vcu0518ff422a::set_gear_enable(
    Vcu_05_18ff422a::Gear_enableType gear_enable) {
  gear_enable_ = gear_enable;
  return this;
 }

// config detail: {'bit': 26, 'enum': {0: 'GEAR_ENABLE_', 1: 'GEAR_ENABLE_'}, 'is_signed_var': False, 'len': 2, 'name': 'Gear_enable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0518ff422a::set_p_gear_enable(uint8_t* data,
    Vcu_05_18ff422a::Gear_enableType gear_enable) {
  int x = gear_enable;

  Byte to_set(data + 3);
  to_set.set_value(x, 2, 2);
}


Vcu0518ff422a* Vcu0518ff422a::set_lift_enable(
    Vcu_05_18ff422a::Lift_enableType lift_enable) {
  lift_enable_ = lift_enable;
  return this;
 }

// config detail: {'bit': 28, 'enum': {0: 'LIFT_ENABLE_', 1: 'LIFT_ENABLE_'}, 'is_signed_var': False, 'len': 2, 'name': 'Lift_enable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0518ff422a::set_p_lift_enable(uint8_t* data,
    Vcu_05_18ff422a::Lift_enableType lift_enable) {
  int x = lift_enable;

  Byte to_set(data + 3);
  to_set.set_value(x, 4, 2);
}


Vcu0518ff422a* Vcu0518ff422a::set_inter_axis_locking_threshold(
    Vcu_05_18ff422a::Inter_axis_locking_thresholdType inter_axis_locking_threshold) {
  inter_axis_locking_threshold_ = inter_axis_locking_threshold;
  return this;
 }

// config detail: {'bit': 36, 'enum': {0: 'INTER_AXIS_LOCKING_THRESHOLD_', 1: 'INTER_AXIS_LOCKING_THRESHOLD_'}, 'is_signed_var': False, 'len': 2, 'name': 'Inter_axis_locking_threshold', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0518ff422a::set_p_inter_axis_locking_threshold(uint8_t* data,
    Vcu_05_18ff422a::Inter_axis_locking_thresholdType inter_axis_locking_threshold) {
  int x = inter_axis_locking_threshold;

  Byte to_set(data + 4);
  to_set.set_value(x, 4, 2);
}


Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType Vcu0518ff422a::lifting_control_of_the_cargo_box(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 4);

  Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType ret =  static_cast<Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType>(x);
  return ret;
}

Vcu_05_18ff422a::Horn_controlType Vcu0518ff422a::horn_control(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 4);

  Vcu_05_18ff422a::Horn_controlType ret =  static_cast<Vcu_05_18ff422a::Horn_controlType>(x);
  return ret;
}

Vcu_05_18ff422a::Lighting_enablementType Vcu0518ff422a::lighting_enablement(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 2);

  Vcu_05_18ff422a::Lighting_enablementType ret =  static_cast<Vcu_05_18ff422a::Lighting_enablementType>(x);
  return ret;
}

Vcu_05_18ff422a::Gear_enableType Vcu0518ff422a::gear_enable(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(2, 2);

  Vcu_05_18ff422a::Gear_enableType ret =  static_cast<Vcu_05_18ff422a::Gear_enableType>(x);
  return ret;
}

Vcu_05_18ff422a::Lift_enableType Vcu0518ff422a::lift_enable(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  Vcu_05_18ff422a::Lift_enableType ret =  static_cast<Vcu_05_18ff422a::Lift_enableType>(x);
  return ret;
}

Vcu_05_18ff422a::Inter_axis_locking_thresholdType Vcu0518ff422a::inter_axis_locking_threshold(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(4, 2);

  Vcu_05_18ff422a::Inter_axis_locking_thresholdType ret =  static_cast<Vcu_05_18ff422a::Inter_axis_locking_thresholdType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
