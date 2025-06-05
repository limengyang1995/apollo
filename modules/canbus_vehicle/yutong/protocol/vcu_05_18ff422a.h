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

class Vcu0518ff422a : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;

  Vcu0518ff422a();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 16, 'enum': {0: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 1: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 2: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 3: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_'}, 'is_signed_var': False, 'len': 4, 'name': 'Lifting_control_of_the_cargo_box', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0518ff422a* set_lifting_control_of_the_cargo_box(Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType lifting_control_of_the_cargo_box);

  // config detail: {'bit': 20, 'enum': {0: 'HORN_CONTROL_', 1: 'HORN_CONTROL_'}, 'is_signed_var': False, 'len': 4, 'name': 'Horn_control', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0518ff422a* set_horn_control(Vcu_05_18ff422a::Horn_controlType horn_control);

  // config detail: {'bit': 24, 'enum': {0: 'LIGHTING_ENABLEMENT_', 1: 'LIGHTING_ENABLEMENT_'}, 'is_signed_var': False, 'len': 2, 'name': 'Lighting_enablement', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0518ff422a* set_lighting_enablement(Vcu_05_18ff422a::Lighting_enablementType lighting_enablement);

  // config detail: {'bit': 26, 'enum': {0: 'GEAR_ENABLE_', 1: 'GEAR_ENABLE_'}, 'is_signed_var': False, 'len': 2, 'name': 'Gear_enable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0518ff422a* set_gear_enable(Vcu_05_18ff422a::Gear_enableType gear_enable);

  // config detail: {'bit': 28, 'enum': {0: 'LIFT_ENABLE_', 1: 'LIFT_ENABLE_'}, 'is_signed_var': False, 'len': 2, 'name': 'Lift_enable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0518ff422a* set_lift_enable(Vcu_05_18ff422a::Lift_enableType lift_enable);

  // config detail: {'bit': 36, 'enum': {0: 'INTER_AXIS_LOCKING_THRESHOLD_', 1: 'INTER_AXIS_LOCKING_THRESHOLD_'}, 'is_signed_var': False, 'len': 2, 'name': 'Inter_axis_locking_threshold', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0518ff422a* set_inter_axis_locking_threshold(Vcu_05_18ff422a::Inter_axis_locking_thresholdType inter_axis_locking_threshold);

 private:

  // config detail: {'bit': 16, 'enum': {0: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 1: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 2: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_', 3: 'LIFTING_CONTROL_OF_THE_CARGO_BOX_'}, 'is_signed_var': False, 'len': 4, 'name': 'Lifting_control_of_the_cargo_box', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_lifting_control_of_the_cargo_box(uint8_t* data, Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType lifting_control_of_the_cargo_box);

  // config detail: {'bit': 20, 'enum': {0: 'HORN_CONTROL_', 1: 'HORN_CONTROL_'}, 'is_signed_var': False, 'len': 4, 'name': 'Horn_control', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_horn_control(uint8_t* data, Vcu_05_18ff422a::Horn_controlType horn_control);

  // config detail: {'bit': 24, 'enum': {0: 'LIGHTING_ENABLEMENT_', 1: 'LIGHTING_ENABLEMENT_'}, 'is_signed_var': False, 'len': 2, 'name': 'Lighting_enablement', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_lighting_enablement(uint8_t* data, Vcu_05_18ff422a::Lighting_enablementType lighting_enablement);

  // config detail: {'bit': 26, 'enum': {0: 'GEAR_ENABLE_', 1: 'GEAR_ENABLE_'}, 'is_signed_var': False, 'len': 2, 'name': 'Gear_enable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_gear_enable(uint8_t* data, Vcu_05_18ff422a::Gear_enableType gear_enable);

  // config detail: {'bit': 28, 'enum': {0: 'LIFT_ENABLE_', 1: 'LIFT_ENABLE_'}, 'is_signed_var': False, 'len': 2, 'name': 'Lift_enable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_lift_enable(uint8_t* data, Vcu_05_18ff422a::Lift_enableType lift_enable);

  // config detail: {'bit': 36, 'enum': {0: 'INTER_AXIS_LOCKING_THRESHOLD_', 1: 'INTER_AXIS_LOCKING_THRESHOLD_'}, 'is_signed_var': False, 'len': 2, 'name': 'Inter_axis_locking_threshold', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_inter_axis_locking_threshold(uint8_t* data, Vcu_05_18ff422a::Inter_axis_locking_thresholdType inter_axis_locking_threshold);

  Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType lifting_control_of_the_cargo_box(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_05_18ff422a::Horn_controlType horn_control(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_05_18ff422a::Lighting_enablementType lighting_enablement(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_05_18ff422a::Gear_enableType gear_enable(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_05_18ff422a::Lift_enableType lift_enable(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_05_18ff422a::Inter_axis_locking_thresholdType inter_axis_locking_threshold(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Vcu_05_18ff422a::Lifting_control_of_the_cargo_boxType lifting_control_of_the_cargo_box_;
  Vcu_05_18ff422a::Horn_controlType horn_control_;
  Vcu_05_18ff422a::Lighting_enablementType lighting_enablement_;
  Vcu_05_18ff422a::Gear_enableType gear_enable_;
  Vcu_05_18ff422a::Lift_enableType lift_enable_;
  Vcu_05_18ff422a::Inter_axis_locking_thresholdType inter_axis_locking_threshold_;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


