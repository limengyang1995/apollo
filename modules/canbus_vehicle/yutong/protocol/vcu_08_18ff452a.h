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

class Vcu0818ff452a : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;

  Vcu0818ff452a();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 0, 'enum': {0: 'DEFROSTING_', 1: 'DEFROSTING_'}, 'is_signed_var': False, 'len': 2, 'name': 'defrosting', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0818ff452a* set_defrosting(Vcu_08_18ff452a::DefrostingType defrosting);

  // config detail: {'bit': 2, 'enum': {0: 'HEATING_HEATING_ENABLED_', 2: 'HEATING_HEATING_ENABLED_'}, 'is_signed_var': False, 'len': 2, 'name': 'Heating_heating_enabled', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0818ff452a* set_heating_heating_enabled(Vcu_08_18ff452a::Heating_heating_enabledType heating_heating_enabled);

  // config detail: {'bit': 4, 'enum': {0: 'COOLING_GEAR_', 2: 'COOLING_GEAR_', 3: 'COOLING_GEAR_'}, 'is_signed_var': False, 'len': 2, 'name': 'Cooling_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0818ff452a* set_cooling_gear(Vcu_08_18ff452a::Cooling_gearType cooling_gear);

  // config detail: {'bit': 6, 'enum': {0: 'HEATING_GEAR_'}, 'is_signed_var': False, 'len': 2, 'name': 'Heating_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0818ff452a* set_heating_gear(Vcu_08_18ff452a::Heating_gearType heating_gear);

 private:

  // config detail: {'bit': 0, 'enum': {0: 'DEFROSTING_', 1: 'DEFROSTING_'}, 'is_signed_var': False, 'len': 2, 'name': 'defrosting', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_defrosting(uint8_t* data, Vcu_08_18ff452a::DefrostingType defrosting);

  // config detail: {'bit': 2, 'enum': {0: 'HEATING_HEATING_ENABLED_', 2: 'HEATING_HEATING_ENABLED_'}, 'is_signed_var': False, 'len': 2, 'name': 'Heating_heating_enabled', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_heating_heating_enabled(uint8_t* data, Vcu_08_18ff452a::Heating_heating_enabledType heating_heating_enabled);

  // config detail: {'bit': 4, 'enum': {0: 'COOLING_GEAR_', 2: 'COOLING_GEAR_', 3: 'COOLING_GEAR_'}, 'is_signed_var': False, 'len': 2, 'name': 'Cooling_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_cooling_gear(uint8_t* data, Vcu_08_18ff452a::Cooling_gearType cooling_gear);

  // config detail: {'bit': 6, 'enum': {0: 'HEATING_GEAR_'}, 'is_signed_var': False, 'len': 2, 'name': 'Heating_gear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_heating_gear(uint8_t* data, Vcu_08_18ff452a::Heating_gearType heating_gear);

  Vcu_08_18ff452a::DefrostingType defrosting(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_08_18ff452a::Heating_heating_enabledType heating_heating_enabled(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_08_18ff452a::Cooling_gearType cooling_gear(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_08_18ff452a::Heating_gearType heating_gear(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Vcu_08_18ff452a::DefrostingType defrosting_;
  Vcu_08_18ff452a::Heating_heating_enabledType heating_heating_enabled_;
  Vcu_08_18ff452a::Cooling_gearType cooling_gear_;
  Vcu_08_18ff452a::Heating_gearType heating_gear_;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


