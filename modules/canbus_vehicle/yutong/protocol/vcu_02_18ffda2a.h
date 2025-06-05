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

class Vcu0218ffda2a : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;

  Vcu0218ffda2a();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 0, 'enum': {0: 'ADCONTROLMODE_', 1: 'ADCONTROLMODE_', 3: 'ADCONTROLMODE_'}, 'is_signed_var': False, 'len': 3, 'name': 'ADControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0218ffda2a* set_adcontrolmode(Vcu_02_18ffda2a::AdcontrolmodeType adcontrolmode);

  // config detail: {'bit': 40, 'enum': {0: 'SLOWSPDLEVERGEARCONTROL_1', 1: 'SLOWSPDLEVERGEARCONTROL_16', 2: 'SLOWSPDLEVERGEARCONTROL_17', 3: 'SLOWSPDLEVERGEARCONTROL_256'}, 'is_signed_var': False, 'len': 3, 'name': 'SlowSpdLeverGearControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0218ffda2a* set_slowspdlevergearcontrol(Vcu_02_18ffda2a::SlowspdlevergearcontrolType slowspdlevergearcontrol);

 private:

  // config detail: {'bit': 0, 'enum': {0: 'ADCONTROLMODE_', 1: 'ADCONTROLMODE_', 3: 'ADCONTROLMODE_'}, 'is_signed_var': False, 'len': 3, 'name': 'ADControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_adcontrolmode(uint8_t* data, Vcu_02_18ffda2a::AdcontrolmodeType adcontrolmode);

  // config detail: {'bit': 40, 'enum': {0: 'SLOWSPDLEVERGEARCONTROL_1', 1: 'SLOWSPDLEVERGEARCONTROL_16', 2: 'SLOWSPDLEVERGEARCONTROL_17', 3: 'SLOWSPDLEVERGEARCONTROL_256'}, 'is_signed_var': False, 'len': 3, 'name': 'SlowSpdLeverGearControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_slowspdlevergearcontrol(uint8_t* data, Vcu_02_18ffda2a::SlowspdlevergearcontrolType slowspdlevergearcontrol);

  Vcu_02_18ffda2a::AdcontrolmodeType adcontrolmode(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_02_18ffda2a::SlowspdlevergearcontrolType slowspdlevergearcontrol(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Vcu_02_18ffda2a::AdcontrolmodeType adcontrolmode_;
  Vcu_02_18ffda2a::SlowspdlevergearcontrolType slowspdlevergearcontrol_;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


