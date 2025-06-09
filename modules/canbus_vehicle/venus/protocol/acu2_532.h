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

#include "modules/canbus_vehicle/venus/proto/venus.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace venus {

class Acu2532 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;

  Acu2532();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 34, 'enum': {0: 'ACU2_AXIALAUTOCONTROL_NOREQUET', 1: 'ACU2_AXIALAUTOCONTROL_REQUEST', 2: 'ACU2_AXIALAUTOCONTROL_RESERVE1', 3: 'ACU2_AXIALAUTOCONTROL_RESERVE2'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_AxialAutoControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu2532* set_acu2_axialautocontrol(Acu2_532::Acu2_axialautocontrolType acu2_axialautocontrol);

  // config detail: {'bit': 50, 'is_signed_var': False, 'len': 10, 'name': 'ACU2_TargetVehicleSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'km/h', 'precision': 0.1, 'type': 'double'}
  Acu2532* set_acu2_targetvehiclespeed(double acu2_targetvehiclespeed);

  // config detail: {'bit': 40, 'is_signed_var': False, 'len': 10, 'name': 'ACU2_TargetTorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  Acu2532* set_acu2_targettorque(double acu2_targettorque);

  // config detail: {'bit': 27, 'is_signed_var': False, 'len': 7, 'name': 'ACU2_TargetBrakingPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  Acu2532* set_acu2_targetbrakingposition(int acu2_targetbrakingposition);

  // config detail: {'bit': 20, 'is_signed_var': False, 'len': 7, 'name': 'ACU2_TargetAcceleratorPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  Acu2532* set_acu2_targetacceleratorposition(int acu2_targetacceleratorposition);

  // config detail: {'bit': 38, 'enum': {0: 'ACU2_BRAKINGCONTROLMODE_POSITION', 1: 'ACU2_BRAKINGCONTROLMODE_DECELACC', 2: 'ACU2_BRAKINGCONTROLMODE_DECELAEB', 3: 'ACU2_BRAKINGCONTROLMODE_ESP'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_BrakingControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu2532* set_acu2_brakingcontrolmode(Acu2_532::Acu2_brakingcontrolmodeType acu2_brakingcontrolmode);

  // config detail: {'bit': 36, 'enum': {0: 'ACU2_ACCELERATORCONTROLMODE_POSITION', 1: 'ACU2_ACCELERATORCONTROLMODE_ACCEL', 2: 'ACU2_ACCELERATORCONTROLMODE_TORQUE', 3: 'ACU2_ACCELERATORCONTROLMODE_VEHICLESPEED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_AcceleratorControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu2532* set_acu2_acceleratorcontrolmode(Acu2_532::Acu2_acceleratorcontrolmodeType acu2_acceleratorcontrolmode);

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 12, 'name': 'ACU2_TargetAxialAccelDecel', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
  Acu2532* set_acu2_targetaxialacceldecel(double acu2_targetaxialacceldecel);

  // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'ACU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  Acu2532* set_acu2_livecounter(int acu2_livecounter);

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  Acu2532* set_acu2_checksum(int acu2_checksum);

 private:

  // config detail: {'bit': 34, 'enum': {0: 'ACU2_AXIALAUTOCONTROL_NOREQUET', 1: 'ACU2_AXIALAUTOCONTROL_REQUEST', 2: 'ACU2_AXIALAUTOCONTROL_RESERVE1', 3: 'ACU2_AXIALAUTOCONTROL_RESERVE2'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_AxialAutoControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu2_axialautocontrol(uint8_t* data, Acu2_532::Acu2_axialautocontrolType acu2_axialautocontrol);

  // config detail: {'bit': 50, 'is_signed_var': False, 'len': 10, 'name': 'ACU2_TargetVehicleSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'km/h', 'precision': 0.1, 'type': 'double'}
  void set_p_acu2_targetvehiclespeed(uint8_t* data, double acu2_targetvehiclespeed);

  // config detail: {'bit': 40, 'is_signed_var': False, 'len': 10, 'name': 'ACU2_TargetTorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  void set_p_acu2_targettorque(uint8_t* data, double acu2_targettorque);

  // config detail: {'bit': 27, 'is_signed_var': False, 'len': 7, 'name': 'ACU2_TargetBrakingPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  void set_p_acu2_targetbrakingposition(uint8_t* data, int acu2_targetbrakingposition);

  // config detail: {'bit': 20, 'is_signed_var': False, 'len': 7, 'name': 'ACU2_TargetAcceleratorPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  void set_p_acu2_targetacceleratorposition(uint8_t* data, int acu2_targetacceleratorposition);

  // config detail: {'bit': 38, 'enum': {0: 'ACU2_BRAKINGCONTROLMODE_POSITION', 1: 'ACU2_BRAKINGCONTROLMODE_DECELACC', 2: 'ACU2_BRAKINGCONTROLMODE_DECELAEB', 3: 'ACU2_BRAKINGCONTROLMODE_ESP'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_BrakingControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu2_brakingcontrolmode(uint8_t* data, Acu2_532::Acu2_brakingcontrolmodeType acu2_brakingcontrolmode);

  // config detail: {'bit': 36, 'enum': {0: 'ACU2_ACCELERATORCONTROLMODE_POSITION', 1: 'ACU2_ACCELERATORCONTROLMODE_ACCEL', 2: 'ACU2_ACCELERATORCONTROLMODE_TORQUE', 3: 'ACU2_ACCELERATORCONTROLMODE_VEHICLESPEED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_AcceleratorControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu2_acceleratorcontrolmode(uint8_t* data, Acu2_532::Acu2_acceleratorcontrolmodeType acu2_acceleratorcontrolmode);

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 12, 'name': 'ACU2_TargetAxialAccelDecel', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
  void set_p_acu2_targetaxialacceldecel(uint8_t* data, double acu2_targetaxialacceldecel);

  // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'ACU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  void set_p_acu2_livecounter(uint8_t* data, int acu2_livecounter);

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  void set_p_acu2_checksum(uint8_t* data, int acu2_checksum);

  Acu2_532::Acu2_axialautocontrolType acu2_axialautocontrol(const std::uint8_t* bytes, const int32_t length) const;

  double acu2_targetvehiclespeed(const std::uint8_t* bytes, const int32_t length) const;

  double acu2_targettorque(const std::uint8_t* bytes, const int32_t length) const;

  int acu2_targetbrakingposition(const std::uint8_t* bytes, const int32_t length) const;

  int acu2_targetacceleratorposition(const std::uint8_t* bytes, const int32_t length) const;

  Acu2_532::Acu2_brakingcontrolmodeType acu2_brakingcontrolmode(const std::uint8_t* bytes, const int32_t length) const;

  Acu2_532::Acu2_acceleratorcontrolmodeType acu2_acceleratorcontrolmode(const std::uint8_t* bytes, const int32_t length) const;

  double acu2_targetaxialacceldecel(const std::uint8_t* bytes, const int32_t length) const;

  int acu2_livecounter(const std::uint8_t* bytes, const int32_t length) const;

  int acu2_checksum(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Acu2_532::Acu2_axialautocontrolType acu2_axialautocontrol_;
  double acu2_targetvehiclespeed_;
  double acu2_targettorque_;
  int acu2_targetbrakingposition_;
  int acu2_targetacceleratorposition_;
  Acu2_532::Acu2_brakingcontrolmodeType acu2_brakingcontrolmode_;
  Acu2_532::Acu2_acceleratorcontrolmodeType acu2_acceleratorcontrolmode_;
  double acu2_targetaxialacceldecel_;
  int acu2_livecounter_;
  int acu2_checksum_;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


