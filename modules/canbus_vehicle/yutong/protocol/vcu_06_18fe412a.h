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

class Vcu0618fe412a : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;

  Vcu0618fe412a();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 4, 'enum': {0: 'LOW_BEAM_HEADLIGHTS_', 1: 'LOW_BEAM_HEADLIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Low_beam_headlights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0618fe412a* set_low_beam_headlights(Vcu_06_18fe412a::Low_beam_headlightsType low_beam_headlights);

  // config detail: {'bit': 6, 'enum': {0: 'HEADLIGHTS_', 1: 'HEADLIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Headlights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0618fe412a* set_headlights(Vcu_06_18fe412a::HeadlightsType headlights);

  // config detail: {'bit': 8, 'enum': {0: 'FRONT_FOG_LAMP_', 1: 'FRONT_FOG_LAMP_'}, 'is_signed_var': False, 'len': 2, 'name': 'Front_fog_lamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0618fe412a* set_front_fog_lamp(Vcu_06_18fe412a::Front_fog_lampType front_fog_lamp);

  // config detail: {'bit': 12, 'enum': {0: 'LEFT_TURN_SIGNAL_', 1: 'LEFT_TURN_SIGNAL_'}, 'is_signed_var': False, 'len': 2, 'name': 'Left_turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0618fe412a* set_left_turn_signal(Vcu_06_18fe412a::Left_turn_signalType left_turn_signal);

  // config detail: {'bit': 14, 'enum': {0: 'RIGHT_TURN_INDICATOR_LIGHT_', 1: 'RIGHT_TURN_INDICATOR_LIGHT_'}, 'is_signed_var': False, 'len': 2, 'name': 'Right_turn_indicator_light', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0618fe412a* set_right_turn_indicator_light(Vcu_06_18fe412a::Right_turn_indicator_lightType right_turn_indicator_light);

  // config detail: {'bit': 16, 'enum': {0: 'POSITION_LIGHTS_', 1: 'POSITION_LIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Position_lights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0618fe412a* set_position_lights(Vcu_06_18fe412a::Position_lightsType position_lights);

  // config detail: {'bit': 34, 'enum': {0: 'DOUBLE_FLASH_LIGHTS_', 1: 'DOUBLE_FLASH_LIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Double_flash_lights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0618fe412a* set_double_flash_lights(Vcu_06_18fe412a::Double_flash_lightsType double_flash_lights);

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 4, 'name': 'Counter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Vcu0618fe412a* set_counter(int counter);

  // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Vcu0618fe412a* set_checksum(int checksum);

 private:

  // config detail: {'bit': 4, 'enum': {0: 'LOW_BEAM_HEADLIGHTS_', 1: 'LOW_BEAM_HEADLIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Low_beam_headlights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_low_beam_headlights(uint8_t* data, Vcu_06_18fe412a::Low_beam_headlightsType low_beam_headlights);

  // config detail: {'bit': 6, 'enum': {0: 'HEADLIGHTS_', 1: 'HEADLIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Headlights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_headlights(uint8_t* data, Vcu_06_18fe412a::HeadlightsType headlights);

  // config detail: {'bit': 8, 'enum': {0: 'FRONT_FOG_LAMP_', 1: 'FRONT_FOG_LAMP_'}, 'is_signed_var': False, 'len': 2, 'name': 'Front_fog_lamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_front_fog_lamp(uint8_t* data, Vcu_06_18fe412a::Front_fog_lampType front_fog_lamp);

  // config detail: {'bit': 12, 'enum': {0: 'LEFT_TURN_SIGNAL_', 1: 'LEFT_TURN_SIGNAL_'}, 'is_signed_var': False, 'len': 2, 'name': 'Left_turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_left_turn_signal(uint8_t* data, Vcu_06_18fe412a::Left_turn_signalType left_turn_signal);

  // config detail: {'bit': 14, 'enum': {0: 'RIGHT_TURN_INDICATOR_LIGHT_', 1: 'RIGHT_TURN_INDICATOR_LIGHT_'}, 'is_signed_var': False, 'len': 2, 'name': 'Right_turn_indicator_light', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_right_turn_indicator_light(uint8_t* data, Vcu_06_18fe412a::Right_turn_indicator_lightType right_turn_indicator_light);

  // config detail: {'bit': 16, 'enum': {0: 'POSITION_LIGHTS_', 1: 'POSITION_LIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Position_lights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_position_lights(uint8_t* data, Vcu_06_18fe412a::Position_lightsType position_lights);

  // config detail: {'bit': 34, 'enum': {0: 'DOUBLE_FLASH_LIGHTS_', 1: 'DOUBLE_FLASH_LIGHTS_'}, 'is_signed_var': False, 'len': 2, 'name': 'Double_flash_lights', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_double_flash_lights(uint8_t* data, Vcu_06_18fe412a::Double_flash_lightsType double_flash_lights);

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 4, 'name': 'Counter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_counter(uint8_t* data, int counter);

  // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_checksum(uint8_t* data, int checksum);

  Vcu_06_18fe412a::Low_beam_headlightsType low_beam_headlights(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_06_18fe412a::HeadlightsType headlights(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_06_18fe412a::Front_fog_lampType front_fog_lamp(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_06_18fe412a::Left_turn_signalType left_turn_signal(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_06_18fe412a::Right_turn_indicator_lightType right_turn_indicator_light(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_06_18fe412a::Position_lightsType position_lights(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_06_18fe412a::Double_flash_lightsType double_flash_lights(const std::uint8_t* bytes, const int32_t length) const;

  int counter(const std::uint8_t* bytes, const int32_t length) const;

  int checksum(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Vcu_06_18fe412a::Low_beam_headlightsType low_beam_headlights_;
  Vcu_06_18fe412a::HeadlightsType headlights_;
  Vcu_06_18fe412a::Front_fog_lampType front_fog_lamp_;
  Vcu_06_18fe412a::Left_turn_signalType left_turn_signal_;
  Vcu_06_18fe412a::Right_turn_indicator_lightType right_turn_indicator_light_;
  Vcu_06_18fe412a::Position_lightsType position_lights_;
  Vcu_06_18fe412a::Double_flash_lightsType double_flash_lights_;
  int counter_;
  int checksum_;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


