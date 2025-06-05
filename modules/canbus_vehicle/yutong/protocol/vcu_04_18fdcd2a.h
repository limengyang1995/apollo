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

class Vcu0418fdcd2a : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;

  Vcu0418fdcd2a();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 4, 'enum': {0: 'WIPERCONTROL_'}, 'is_signed_var': False, 'len': 4, 'name': 'WiperControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0418fdcd2a* set_wipercontrol(Vcu_04_18fdcd2a::WipercontrolType wipercontrol);

  // config detail: {'bit': 45, 'enum': {0: 'WASHCONTROL_OF', 1: 'WASHCONTROL_O'}, 'is_signed_var': False, 'len': 3, 'name': 'WashControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0418fdcd2a* set_washcontrol(Vcu_04_18fdcd2a::WashcontrolType washcontrol);

 private:

  // config detail: {'bit': 4, 'enum': {0: 'WIPERCONTROL_'}, 'is_signed_var': False, 'len': 4, 'name': 'WiperControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_wipercontrol(uint8_t* data, Vcu_04_18fdcd2a::WipercontrolType wipercontrol);

  // config detail: {'bit': 45, 'enum': {0: 'WASHCONTROL_OF', 1: 'WASHCONTROL_O'}, 'is_signed_var': False, 'len': 3, 'name': 'WashControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_washcontrol(uint8_t* data, Vcu_04_18fdcd2a::WashcontrolType washcontrol);

  Vcu_04_18fdcd2a::WipercontrolType wipercontrol(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_04_18fdcd2a::WashcontrolType washcontrol(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Vcu_04_18fdcd2a::WipercontrolType wipercontrol_;
  Vcu_04_18fdcd2a::WashcontrolType washcontrol_;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


