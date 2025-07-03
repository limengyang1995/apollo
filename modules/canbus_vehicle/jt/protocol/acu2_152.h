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

class Acu2152 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;

  Acu2152();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 18, 'is_signed_var': False, 'len': 6, 'name': 'ACU2_DrivingTargetSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|126]', 'physical_unit': 'km/h', 'precision': 2.0, 'type': 'double'}
  Acu2152* set_acu2_drivingtargetspeed(double acu2_drivingtargetspeed);

  // config detail: {'bit': 40, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 11, 'name': 'ACU2_DrivingTargetTorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|350]', 'physical_unit': 'Nm', 'precision': 0.25, 'type': 'double'}
  Acu2152* set_acu2_drivingtargettorque(double acu2_drivingtargettorque);

  // config detail: {'bit': 24, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 10, 'name': 'ACU2_DrivingTargetThrottle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
  Acu2152* set_acu2_drivingtargetthrottle(double acu2_drivingtargetthrottle);

  // config detail: {'bit': 56, 'description': 'This signal is the status of the driving control request', 'enum': {0: 'ACU2_DRIVINGCONTROLFLAG_NO_REQUEST', 1: 'ACU2_DRIVINGCONTROLFLAG_REQUESTTHROTTLE', 2: 'ACU2_DRIVINGCONTROLFLAG_RESERVEDSPEED', 3: 'ACU2_DRIVINGCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_DrivingControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu2152* set_acu2_drivingcontrolflag(Acu2_152::Acu2_drivingcontrolflagType acu2_drivingcontrolflag);

  // config detail: {'bit': 8, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 10, 'name': 'ACU2_DrivingTargetAcceleration', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
  Acu2152* set_acu2_drivingtargetacceleration(double acu2_drivingtargetacceleration);

  // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  Acu2152* set_acu2_livecounter(int acu2_livecounter);

  // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  Acu2152* set_acu2_checksum(int acu2_checksum);

 private:

  // config detail: {'bit': 18, 'is_signed_var': False, 'len': 6, 'name': 'ACU2_DrivingTargetSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|126]', 'physical_unit': 'km/h', 'precision': 2.0, 'type': 'double'}
  void set_p_acu2_drivingtargetspeed(uint8_t* data, double acu2_drivingtargetspeed);

  // config detail: {'bit': 40, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 11, 'name': 'ACU2_DrivingTargetTorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|350]', 'physical_unit': 'Nm', 'precision': 0.25, 'type': 'double'}
  void set_p_acu2_drivingtargettorque(uint8_t* data, double acu2_drivingtargettorque);

  // config detail: {'bit': 24, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 10, 'name': 'ACU2_DrivingTargetThrottle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
  void set_p_acu2_drivingtargetthrottle(uint8_t* data, double acu2_drivingtargetthrottle);

  // config detail: {'bit': 56, 'description': 'This signal is the status of the driving control request', 'enum': {0: 'ACU2_DRIVINGCONTROLFLAG_NO_REQUEST', 1: 'ACU2_DRIVINGCONTROLFLAG_REQUESTTHROTTLE', 2: 'ACU2_DRIVINGCONTROLFLAG_RESERVEDSPEED', 3: 'ACU2_DRIVINGCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_DrivingControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu2_drivingcontrolflag(uint8_t* data, Acu2_152::Acu2_drivingcontrolflagType acu2_drivingcontrolflag);

  // config detail: {'bit': 8, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 10, 'name': 'ACU2_DrivingTargetAcceleration', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
  void set_p_acu2_drivingtargetacceleration(uint8_t* data, double acu2_drivingtargetacceleration);

  // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  void set_p_acu2_livecounter(uint8_t* data, int acu2_livecounter);

  // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  void set_p_acu2_checksum(uint8_t* data, int acu2_checksum);

  double acu2_drivingtargetspeed(const std::uint8_t* bytes, const int32_t length) const;

  double acu2_drivingtargettorque(const std::uint8_t* bytes, const int32_t length) const;

  double acu2_drivingtargetthrottle(const std::uint8_t* bytes, const int32_t length) const;

  Acu2_152::Acu2_drivingcontrolflagType acu2_drivingcontrolflag(const std::uint8_t* bytes, const int32_t length) const;

  double acu2_drivingtargetacceleration(const std::uint8_t* bytes, const int32_t length) const;

  int acu2_livecounter(const std::uint8_t* bytes, const int32_t length) const;

  int acu2_checksum(const std::uint8_t* bytes, const int32_t length) const;

 private:
  double acu2_drivingtargetspeed_;
  double acu2_drivingtargettorque_;
  double acu2_drivingtargetthrottle_;
  Acu2_152::Acu2_drivingcontrolflagType acu2_drivingcontrolflag_;
  double acu2_drivingtargetacceleration_;
  int acu2_livecounter_;
  int acu2_checksum_;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


