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

#include "modules/canbus_vehicle/kfc/proto/kfc.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace kfc {

class Acu1310 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Kfc> {
 public:
  static const int32_t ID;

  Acu1310();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Kfc* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 40, 'is_signed_var': False, 'len': 7, 'name': 'ACU1_TargetBrakingPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  Acu1310* set_acu1_targetbrakingposition(int acu1_targetbrakingposition);

  // config detail: {'bit': 32, 'is_signed_var': False, 'len': 7, 'name': 'ACU1_TargetThrottlePosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  Acu1310* set_acu1_targetthrottleposition(int acu1_targetthrottleposition);

  // config detail: {'bit': 30, 'enum': {0: 'ACU1_DRIVINGCONTROLREQUEST_NO_REQUET', 1: 'ACU1_DRIVINGCONTROLREQUEST_REQUEST', 2: 'ACU1_DRIVINGCONTROLREQUEST_RESERVED', 3: 'ACU1_DRIVINGCONTROLREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_DrivingControlRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu1310* set_acu1_drivingcontrolrequest(Acu1_310::Acu1_drivingcontrolrequestType acu1_drivingcontrolrequest);

  // config detail: {'bit': 59, 'enum': {0: 'ACU1_STANDSTILLST_INACTIVE', 1: 'ACU1_STANDSTILLST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU1_StandStillSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu1310* set_acu1_standstillst(Acu1_310::Acu1_standstillstType acu1_standstillst);

  // config detail: {'bit': 19, 'is_signed_var': False, 'len': 9, 'name': 'ACU1_TargetSteeringSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
  Acu1310* set_acu1_targetsteeringspeed(int acu1_targetsteeringspeed);

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 11, 'name': 'ACU1_TargetSteeringAngle', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  Acu1310* set_acu1_targetsteeringangle(int acu1_targetsteeringangle);

  // config detail: {'bit': 56, 'enum': {0: 'ACU1_TARGETGEAR_NO_REQUEST', 1: 'ACU1_TARGETGEAR_P', 2: 'ACU1_TARGETGEAR_D', 3: 'ACU1_TARGETGEAR_N', 4: 'ACU1_TARGETGEAR_R', 5: 'ACU1_TARGETGEAR_RESERVED', 6: 'ACU1_TARGETGEAR_RESERVED', 7: 'ACU1_TARGETGEAR_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU1_TargetGear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu1310* set_acu1_targetgear(Acu1_310::Acu1_targetgearType acu1_targetgear);

  // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'ACU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu1310* set_acu1_livecounter(int acu1_livecounter);

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu1310* set_acu1_checksum(int acu1_checksum);

  // config detail: {'bit': 28, 'enum': {0: 'ACU1_STEERINGCONTROLREQUEST_NO_REQUET', 1: 'ACU1_STEERINGCONTROLREQUEST_REQUEST', 2: 'ACU1_STEERINGCONTROLREQUEST_RESERVED', 3: 'ACU1_STEERINGCONTROLREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_SteeringControlRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu1310* set_acu1_steeringcontrolrequest(Acu1_310::Acu1_steeringcontrolrequestType acu1_steeringcontrolrequest);

 private:

  // config detail: {'bit': 40, 'is_signed_var': False, 'len': 7, 'name': 'ACU1_TargetBrakingPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  void set_p_acu1_targetbrakingposition(uint8_t* data, int acu1_targetbrakingposition);

  // config detail: {'bit': 32, 'is_signed_var': False, 'len': 7, 'name': 'ACU1_TargetThrottlePosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  void set_p_acu1_targetthrottleposition(uint8_t* data, int acu1_targetthrottleposition);

  // config detail: {'bit': 30, 'enum': {0: 'ACU1_DRIVINGCONTROLREQUEST_NO_REQUET', 1: 'ACU1_DRIVINGCONTROLREQUEST_REQUEST', 2: 'ACU1_DRIVINGCONTROLREQUEST_RESERVED', 3: 'ACU1_DRIVINGCONTROLREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_DrivingControlRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu1_drivingcontrolrequest(uint8_t* data, Acu1_310::Acu1_drivingcontrolrequestType acu1_drivingcontrolrequest);

  // config detail: {'bit': 59, 'enum': {0: 'ACU1_STANDSTILLST_INACTIVE', 1: 'ACU1_STANDSTILLST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU1_StandStillSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu1_standstillst(uint8_t* data, Acu1_310::Acu1_standstillstType acu1_standstillst);

  // config detail: {'bit': 19, 'is_signed_var': False, 'len': 9, 'name': 'ACU1_TargetSteeringSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
  void set_p_acu1_targetsteeringspeed(uint8_t* data, int acu1_targetsteeringspeed);

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 11, 'name': 'ACU1_TargetSteeringAngle', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  void set_p_acu1_targetsteeringangle(uint8_t* data, int acu1_targetsteeringangle);

  // config detail: {'bit': 56, 'enum': {0: 'ACU1_TARGETGEAR_NO_REQUEST', 1: 'ACU1_TARGETGEAR_P', 2: 'ACU1_TARGETGEAR_D', 3: 'ACU1_TARGETGEAR_N', 4: 'ACU1_TARGETGEAR_R', 5: 'ACU1_TARGETGEAR_RESERVED', 6: 'ACU1_TARGETGEAR_RESERVED', 7: 'ACU1_TARGETGEAR_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU1_TargetGear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu1_targetgear(uint8_t* data, Acu1_310::Acu1_targetgearType acu1_targetgear);

  // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'ACU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu1_livecounter(uint8_t* data, int acu1_livecounter);

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu1_checksum(uint8_t* data, int acu1_checksum);

  // config detail: {'bit': 28, 'enum': {0: 'ACU1_STEERINGCONTROLREQUEST_NO_REQUET', 1: 'ACU1_STEERINGCONTROLREQUEST_REQUEST', 2: 'ACU1_STEERINGCONTROLREQUEST_RESERVED', 3: 'ACU1_STEERINGCONTROLREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_SteeringControlRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu1_steeringcontrolrequest(uint8_t* data, Acu1_310::Acu1_steeringcontrolrequestType acu1_steeringcontrolrequest);

  int acu1_targetbrakingposition(const std::uint8_t* bytes, const int32_t length) const;

  int acu1_targetthrottleposition(const std::uint8_t* bytes, const int32_t length) const;

  Acu1_310::Acu1_drivingcontrolrequestType acu1_drivingcontrolrequest(const std::uint8_t* bytes, const int32_t length) const;

  Acu1_310::Acu1_standstillstType acu1_standstillst(const std::uint8_t* bytes, const int32_t length) const;

  int acu1_targetsteeringspeed(const std::uint8_t* bytes, const int32_t length) const;

  int acu1_targetsteeringangle(const std::uint8_t* bytes, const int32_t length) const;

  Acu1_310::Acu1_targetgearType acu1_targetgear(const std::uint8_t* bytes, const int32_t length) const;

  int acu1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

  int acu1_checksum(const std::uint8_t* bytes, const int32_t length) const;

  Acu1_310::Acu1_steeringcontrolrequestType acu1_steeringcontrolrequest(const std::uint8_t* bytes, const int32_t length) const;

 private:
  int acu1_targetbrakingposition_;
  int acu1_targetthrottleposition_;
  Acu1_310::Acu1_drivingcontrolrequestType acu1_drivingcontrolrequest_;
  Acu1_310::Acu1_standstillstType acu1_standstillst_;
  int acu1_targetsteeringspeed_;
  int acu1_targetsteeringangle_;
  Acu1_310::Acu1_targetgearType acu1_targetgear_;
  int acu1_livecounter_;
  int acu1_checksum_;
  Acu1_310::Acu1_steeringcontrolrequestType acu1_steeringcontrolrequest_;
};

}  // namespace kfc
}  // namespace canbus
}  // namespace apollo


