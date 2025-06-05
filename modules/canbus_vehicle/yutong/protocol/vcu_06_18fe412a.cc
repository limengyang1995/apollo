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

#include "modules/canbus_vehicle/yutong/protocol/vcu_06_18fe412a.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Vcu0618fe412a::ID = 0x18fe412a;

// public
Vcu0618fe412a::Vcu0618fe412a() { Reset(); }

uint32_t Vcu0618fe412a::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Vcu0618fe412a::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_vcu_06_18fe412a()->set_low_beam_headlights(low_beam_headlights(bytes, length));
  chassis->mutable_vcu_06_18fe412a()->set_headlights(headlights(bytes, length));
  chassis->mutable_vcu_06_18fe412a()->set_front_fog_lamp(front_fog_lamp(bytes, length));
  chassis->mutable_vcu_06_18fe412a()->set_left_turn_signal(left_turn_signal(bytes, length));
  chassis->mutable_vcu_06_18fe412a()->set_right_turn_indicator_light(right_turn_indicator_light(bytes, length));
  chassis->mutable_vcu_06_18fe412a()->set_position_lights(position_lights(bytes, length));
  chassis->mutable_vcu_06_18fe412a()->set_double_flash_lights(double_flash_lights(bytes, length));
  chassis->mutable_vcu_06_18fe412a()->set_counter(counter(bytes, length));
  chassis->mutable_vcu_06_18fe412a()->set_checksum(checksum(bytes, length));
}

void Vcu0618fe412a::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Vcu0618fe412a::UpdateData(uint8_t* data) {
  set_p_low_beam_headlights(data, low_beam_headlights_);
  set_p_headlights(data, headlights_);
  set_p_front_fog_lamp(data, front_fog_lamp_);
  set_p_left_turn_signal(data, left_turn_signal_);
  set_p_right_turn_indicator_light(data, right_turn_indicator_light_);
  set_p_position_lights(data, position_lights_);
  set_p_double_flash_lights(data, double_flash_lights_);
  set_p_counter(data, counter_);
  set_p_checksum(data, checksum_);
}

void Vcu0618fe412a::Reset() {
  // TODO(All) :  you should check this manually
  low_beam_headlights_ = Vcu_06_18fe412a::LOW_BEAM_HEADLIGHTS_OFF;
  headlights_ = Vcu_06_18fe412a::HEADLIGHTS_OFF;
  front_fog_lamp_ = Vcu_06_18fe412a::FRONT_FOG_LAMP_OFF;
  left_turn_signal_ = Vcu_06_18fe412a::LEFT_TURN_SIGNAL_OFF;
  right_turn_indicator_light_ = Vcu_06_18fe412a::RIGHT_TURN_INDICATOR_LIGHT_OFF;
  position_lights_ = Vcu_06_18fe412a::POSITION_LIGHTS_OFF;
  double_flash_lights_ = Vcu_06_18fe412a::DOUBLE_FLASH_LIGHTS_OFF;
  counter_ = 0;
  checksum_ = 0;
}

Vcu0618fe412a* Vcu0618fe412a::set_low_beam_headlights(
    Vcu_06_18fe412a::Low_beam_headlightsType low_beam_headlights) {
  low_beam_headlights_ = low_beam_headlights;
  return this;
 }

// config detail: {'bit': 4, 'enum': {0: 'LOW_BEAM_HEADLIGHTS_', 1: 'LOW_BEAM_HEADLIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Low_beam_headlights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0618fe412a::set_p_low_beam_headlights(uint8_t* data,
    Vcu_06_18fe412a::Low_beam_headlightsType low_beam_headlights) {
  int x = low_beam_headlights;

  Byte to_set(data + 0);
  to_set.set_value(x, 4, 2);
}


Vcu0618fe412a* Vcu0618fe412a::set_headlights(
    Vcu_06_18fe412a::HeadlightsType headlights) {
  headlights_ = headlights;
  return this;
 }

// config detail: {'bit': 6, 'enum': {0: 'HEADLIGHTS_', 1: 'HEADLIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Headlights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0618fe412a::set_p_headlights(uint8_t* data,
    Vcu_06_18fe412a::HeadlightsType headlights) {
  int x = headlights;

  Byte to_set(data + 0);
  to_set.set_value(x, 6, 2);
}


Vcu0618fe412a* Vcu0618fe412a::set_front_fog_lamp(
    Vcu_06_18fe412a::Front_fog_lampType front_fog_lamp) {
  front_fog_lamp_ = front_fog_lamp;
  return this;
 }

// config detail: {'bit': 8, 'enum': {0: 'FRONT_FOG_LAMP_', 1: 'FRONT_FOG_LAMP_'}, 'is_signed_var': False, 'len': 2, 'name': 'Front_fog_lamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0618fe412a::set_p_front_fog_lamp(uint8_t* data,
    Vcu_06_18fe412a::Front_fog_lampType front_fog_lamp) {
  int x = front_fog_lamp;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 2);
}


Vcu0618fe412a* Vcu0618fe412a::set_left_turn_signal(
    Vcu_06_18fe412a::Left_turn_signalType left_turn_signal) {
  left_turn_signal_ = left_turn_signal;
  return this;
 }

// config detail: {'bit': 12, 'enum': {0: 'LEFT_TURN_SIGNAL_', 1: 'LEFT_TURN_SIGNAL_'}, 'is_signed_var': False, 'len': 2, 'name': 'Left_turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0618fe412a::set_p_left_turn_signal(uint8_t* data,
    Vcu_06_18fe412a::Left_turn_signalType left_turn_signal) {
  int x = left_turn_signal;

  Byte to_set(data + 1);
  to_set.set_value(x, 4, 2);
}


Vcu0618fe412a* Vcu0618fe412a::set_right_turn_indicator_light(
    Vcu_06_18fe412a::Right_turn_indicator_lightType right_turn_indicator_light) {
  right_turn_indicator_light_ = right_turn_indicator_light;
  return this;
 }

// config detail: {'bit': 14, 'enum': {0: 'RIGHT_TURN_INDICATOR_LIGHT_', 1: 'RIGHT_TURN_INDICATOR_LIGHT_'}, 'is_signed_var': False, 'len': 2, 'name': 'Right_turn_indicator_light', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0618fe412a::set_p_right_turn_indicator_light(uint8_t* data,
    Vcu_06_18fe412a::Right_turn_indicator_lightType right_turn_indicator_light) {
  int x = right_turn_indicator_light;

  Byte to_set(data + 1);
  to_set.set_value(x, 6, 2);
}


Vcu0618fe412a* Vcu0618fe412a::set_position_lights(
    Vcu_06_18fe412a::Position_lightsType position_lights) {
  position_lights_ = position_lights;
  return this;
 }

// config detail: {'bit': 16, 'enum': {0: 'POSITION_LIGHTS_', 1: 'POSITION_LIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Position_lights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0618fe412a::set_p_position_lights(uint8_t* data,
    Vcu_06_18fe412a::Position_lightsType position_lights) {
  int x = position_lights;

  Byte to_set(data + 2);
  to_set.set_value(x, 0, 2);
}


Vcu0618fe412a* Vcu0618fe412a::set_double_flash_lights(
    Vcu_06_18fe412a::Double_flash_lightsType double_flash_lights) {
  double_flash_lights_ = double_flash_lights;
  return this;
 }

// config detail: {'bit': 34, 'enum': {0: 'DOUBLE_FLASH_LIGHTS_', 1: 'DOUBLE_FLASH_LIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Double_flash_lights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0618fe412a::set_p_double_flash_lights(uint8_t* data,
    Vcu_06_18fe412a::Double_flash_lightsType double_flash_lights) {
  int x = double_flash_lights;

  Byte to_set(data + 4);
  to_set.set_value(x, 2, 2);
}


Vcu0618fe412a* Vcu0618fe412a::set_counter(
    int counter) {
  counter_ = counter;
  return this;
 }

// config detail: {'bit': 56, 'is_signed_var': False, 'len': 4, 'name': 'Counter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Vcu0618fe412a::set_p_counter(uint8_t* data,
    int counter) {
  counter = ProtocolData::BoundedValue(0, 15, counter);
  int x = counter;

  Byte to_set(data + 7);
  to_set.set_value(x, 0, 4);
}


Vcu0618fe412a* Vcu0618fe412a::set_checksum(
    int checksum) {
  checksum_ = checksum;
  return this;
 }

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Vcu0618fe412a::set_p_checksum(uint8_t* data,
    int checksum) {
  checksum = ProtocolData::BoundedValue(0, 15, checksum);
  int x = checksum;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


Vcu_06_18fe412a::Low_beam_headlightsType Vcu0618fe412a::low_beam_headlights(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(4, 2);

  Vcu_06_18fe412a::Low_beam_headlightsType ret =  static_cast<Vcu_06_18fe412a::Low_beam_headlightsType>(x);
  return ret;
}

Vcu_06_18fe412a::HeadlightsType Vcu0618fe412a::headlights(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(6, 2);

  Vcu_06_18fe412a::HeadlightsType ret =  static_cast<Vcu_06_18fe412a::HeadlightsType>(x);
  return ret;
}

Vcu_06_18fe412a::Front_fog_lampType Vcu0618fe412a::front_fog_lamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Vcu_06_18fe412a::Front_fog_lampType ret =  static_cast<Vcu_06_18fe412a::Front_fog_lampType>(x);
  return ret;
}

Vcu_06_18fe412a::Left_turn_signalType Vcu0618fe412a::left_turn_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  Vcu_06_18fe412a::Left_turn_signalType ret =  static_cast<Vcu_06_18fe412a::Left_turn_signalType>(x);
  return ret;
}

Vcu_06_18fe412a::Right_turn_indicator_lightType Vcu0618fe412a::right_turn_indicator_light(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(6, 2);

  Vcu_06_18fe412a::Right_turn_indicator_lightType ret =  static_cast<Vcu_06_18fe412a::Right_turn_indicator_lightType>(x);
  return ret;
}

Vcu_06_18fe412a::Position_lightsType Vcu0618fe412a::position_lights(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Vcu_06_18fe412a::Position_lightsType ret =  static_cast<Vcu_06_18fe412a::Position_lightsType>(x);
  return ret;
}

Vcu_06_18fe412a::Double_flash_lightsType Vcu0618fe412a::double_flash_lights(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(2, 2);

  Vcu_06_18fe412a::Double_flash_lightsType ret =  static_cast<Vcu_06_18fe412a::Double_flash_lightsType>(x);
  return ret;
}

int Vcu0618fe412a::counter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

int Vcu0618fe412a::checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
