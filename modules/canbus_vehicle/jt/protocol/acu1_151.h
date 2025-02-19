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

#include "modules/canbus_vehicle/jt/proto/jt.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace jt {

class Acu1151 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;

  Acu1151();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 40, 'description': 'This signal is steering torque request', 'is_signed_var': False, 'len': 12, 'name': 'ACU1_SteeringTargetTorque', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
  Acu1151* set_acu1_steeringtargettorque(double acu1_steeringtargettorque);

  // config detail: {'bit': 24, 'description': 'This signal is steering speed request', 'is_signed_var': False, 'len': 9, 'name': 'ACU1_SteeringTargetSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
  Acu1151* set_acu1_steeringtargetspeed(int acu1_steeringtargetspeed);

  // config detail: {'bit': 56, 'description': 'This signal is the status of steering control request', 'enum': {0: 'ACU1_STEERINGCONTROLFLAG_NO_REQUEST', 1: 'ACU1_STEERINGCONTROLFLAG_REQUEST', 2: 'ACU1_STEERINGCONTROLFLAG_RESERVED', 3: 'ACU1_STEERINGCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_SteeringControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu1151* set_acu1_steeringcontrolflag(Acu1_151::Acu1_steeringcontrolflagType acu1_steeringcontrolflag);

  // config detail: {'bit': 8, 'description': 'This signal is steering angle request', 'is_signed_var': False, 'len': 14, 'name': 'ACU1_SteeringTargetAngle', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  Acu1151* set_acu1_steeringtargetangle(double acu1_steeringtargetangle);

  // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  Acu1151* set_acu1_livecounter(int acu1_livecounter);

  // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  Acu1151* set_acu1_checksum(int acu1_checksum);

 private:

  // config detail: {'bit': 40, 'description': 'This signal is steering torque request', 'is_signed_var': False, 'len': 12, 'name': 'ACU1_SteeringTargetTorque', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
  void set_p_acu1_steeringtargettorque(uint8_t* data, double acu1_steeringtargettorque);

  // config detail: {'bit': 24, 'description': 'This signal is steering speed request', 'is_signed_var': False, 'len': 9, 'name': 'ACU1_SteeringTargetSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
  void set_p_acu1_steeringtargetspeed(uint8_t* data, int acu1_steeringtargetspeed);

  // config detail: {'bit': 56, 'description': 'This signal is the status of steering control request', 'enum': {0: 'ACU1_STEERINGCONTROLFLAG_NO_REQUEST', 1: 'ACU1_STEERINGCONTROLFLAG_REQUEST', 2: 'ACU1_STEERINGCONTROLFLAG_RESERVED', 3: 'ACU1_STEERINGCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_SteeringControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu1_steeringcontrolflag(uint8_t* data, Acu1_151::Acu1_steeringcontrolflagType acu1_steeringcontrolflag);

  // config detail: {'bit': 8, 'description': 'This signal is steering angle request', 'is_signed_var': False, 'len': 14, 'name': 'ACU1_SteeringTargetAngle', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  void set_p_acu1_steeringtargetangle(uint8_t* data, double acu1_steeringtargetangle);

  // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  void set_p_acu1_livecounter(uint8_t* data, int acu1_livecounter);

  // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  void set_p_acu1_checksum(uint8_t* data, int acu1_checksum);

  double acu1_steeringtargettorque(const std::uint8_t* bytes, const int32_t length) const;

  int acu1_steeringtargetspeed(const std::uint8_t* bytes, const int32_t length) const;

  Acu1_151::Acu1_steeringcontrolflagType acu1_steeringcontrolflag(const std::uint8_t* bytes, const int32_t length) const;

  double acu1_steeringtargetangle(const std::uint8_t* bytes, const int32_t length) const;

  int acu1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

  int acu1_checksum(const std::uint8_t* bytes, const int32_t length) const;

 private:
  double acu1_steeringtargettorque_;
  int acu1_steeringtargetspeed_;
  Acu1_151::Acu1_steeringcontrolflagType acu1_steeringcontrolflag_;
  double acu1_steeringtargetangle_;
  int acu1_livecounter_;
  int acu1_checksum_;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


