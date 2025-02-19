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

class Acu3153 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;

  Acu3153();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 52, 'description': 'This signal is the status of the braking control request', 'enum': {0: 'ACU3_EPBCONTROLFLAG_NO_REQUEST', 1: 'ACU3_EPBCONTROLFLAG_RELEASE', 2: 'ACU3_EPBCONTROLFLAG_LOCK', 3: 'ACU3_EPBCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_EPBControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3153* set_acu3_epbcontrolflag(Acu3_153::Acu3_epbcontrolflagType acu3_epbcontrolflag);

  // config detail: {'bit': 48, 'description': 'This signal is gear request', 'enum': {0: 'ACU3_GEARTARGET_P', 1: 'ACU3_GEARTARGET_R', 2: 'ACU3_GEARTARGET_N', 3: 'ACU3_GEARTARGET_D', 4: 'ACU3_GEARTARGET_RESERVED', 5: 'ACU3_GEARTARGET_RESERVED', 6: 'ACU3_GEARTARGET_RESERVED', 7: 'ACU3_GEARTARGET_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU3_GearTarget', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3153* set_acu3_geartarget(Acu3_153::Acu3_geartargetType acu3_geartarget);

  // config detail: {'bit': 51, 'description': 'This signal is the status of the gear control request', 'enum': {0: 'ACU3_GEARCONTROLFLAG_NO_REQUEST', 1: 'ACU3_GEARCONTROLFLAG_REQUEST'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU3_GearControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3153* set_acu3_gearcontrolflag(Acu3_153::Acu3_gearcontrolflagType acu3_gearcontrolflag);

  // config detail: {'bit': 24, 'description': 'This signal is deceleration request for wheel brake', 'is_signed_var': False, 'len': 10, 'name': 'ACU3_BrakingTargetPressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'Mpa', 'precision': 0.01, 'type': 'double'}
  Acu3153* set_acu3_brakingtargetpressure(double acu3_brakingtargetpressure);

  // config detail: {'bit': 8, 'description': 'This signal is deceleration request for wheel brake', 'is_signed_var': False, 'len': 10, 'name': 'ACU3_BrakingTargetDeceleration', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-10|0]', 'physical_unit': 'm/s2', 'precision': -0.01, 'type': 'double'}
  Acu3153* set_acu3_brakingtargetdeceleration(double acu3_brakingtargetdeceleration);

  // config detail: {'bit': 40, 'description': 'This signal is the status of the braking control request', 'enum': {0: 'ACU3_BRAKINGCONTROLFLAG_NO_REQUEST', 1: 'ACU3_BRAKINGCONTROLFLAG_REQUEST', 2: 'ACU3_BRAKINGCONTROLFLAG_RESERVED', 3: 'ACU3_BRAKINGCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BrakingControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3153* set_acu3_brakingcontrolflag(Acu3_153::Acu3_brakingcontrolflagType acu3_brakingcontrolflag);

  // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU3_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  Acu3153* set_acu3_livecounter(int acu3_livecounter);

  // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU3_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  Acu3153* set_acu3_checksum(int acu3_checksum);

 private:

  // config detail: {'bit': 52, 'description': 'This signal is the status of the braking control request', 'enum': {0: 'ACU3_EPBCONTROLFLAG_NO_REQUEST', 1: 'ACU3_EPBCONTROLFLAG_RELEASE', 2: 'ACU3_EPBCONTROLFLAG_LOCK', 3: 'ACU3_EPBCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_EPBControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_epbcontrolflag(uint8_t* data, Acu3_153::Acu3_epbcontrolflagType acu3_epbcontrolflag);

  // config detail: {'bit': 48, 'description': 'This signal is gear request', 'enum': {0: 'ACU3_GEARTARGET_P', 1: 'ACU3_GEARTARGET_R', 2: 'ACU3_GEARTARGET_N', 3: 'ACU3_GEARTARGET_D', 4: 'ACU3_GEARTARGET_RESERVED', 5: 'ACU3_GEARTARGET_RESERVED', 6: 'ACU3_GEARTARGET_RESERVED', 7: 'ACU3_GEARTARGET_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU3_GearTarget', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_geartarget(uint8_t* data, Acu3_153::Acu3_geartargetType acu3_geartarget);

  // config detail: {'bit': 51, 'description': 'This signal is the status of the gear control request', 'enum': {0: 'ACU3_GEARCONTROLFLAG_NO_REQUEST', 1: 'ACU3_GEARCONTROLFLAG_REQUEST'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU3_GearControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_gearcontrolflag(uint8_t* data, Acu3_153::Acu3_gearcontrolflagType acu3_gearcontrolflag);

  // config detail: {'bit': 24, 'description': 'This signal is deceleration request for wheel brake', 'is_signed_var': False, 'len': 10, 'name': 'ACU3_BrakingTargetPressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'Mpa', 'precision': 0.01, 'type': 'double'}
  void set_p_acu3_brakingtargetpressure(uint8_t* data, double acu3_brakingtargetpressure);

  // config detail: {'bit': 8, 'description': 'This signal is deceleration request for wheel brake', 'is_signed_var': False, 'len': 10, 'name': 'ACU3_BrakingTargetDeceleration', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-10|0]', 'physical_unit': 'm/s2', 'precision': -0.01, 'type': 'double'}
  void set_p_acu3_brakingtargetdeceleration(uint8_t* data, double acu3_brakingtargetdeceleration);

  // config detail: {'bit': 40, 'description': 'This signal is the status of the braking control request', 'enum': {0: 'ACU3_BRAKINGCONTROLFLAG_NO_REQUEST', 1: 'ACU3_BRAKINGCONTROLFLAG_REQUEST', 2: 'ACU3_BRAKINGCONTROLFLAG_RESERVED', 3: 'ACU3_BRAKINGCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BrakingControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_brakingcontrolflag(uint8_t* data, Acu3_153::Acu3_brakingcontrolflagType acu3_brakingcontrolflag);

  // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU3_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  void set_p_acu3_livecounter(uint8_t* data, int acu3_livecounter);

  // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU3_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  void set_p_acu3_checksum(uint8_t* data, int acu3_checksum);

  Acu3_153::Acu3_epbcontrolflagType acu3_epbcontrolflag(const std::uint8_t* bytes, const int32_t length) const;

  Acu3_153::Acu3_geartargetType acu3_geartarget(const std::uint8_t* bytes, const int32_t length) const;

  Acu3_153::Acu3_gearcontrolflagType acu3_gearcontrolflag(const std::uint8_t* bytes, const int32_t length) const;

  double acu3_brakingtargetpressure(const std::uint8_t* bytes, const int32_t length) const;

  double acu3_brakingtargetdeceleration(const std::uint8_t* bytes, const int32_t length) const;

  Acu3_153::Acu3_brakingcontrolflagType acu3_brakingcontrolflag(const std::uint8_t* bytes, const int32_t length) const;

  int acu3_livecounter(const std::uint8_t* bytes, const int32_t length) const;

  int acu3_checksum(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Acu3_153::Acu3_epbcontrolflagType acu3_epbcontrolflag_;
  Acu3_153::Acu3_geartargetType acu3_geartarget_;
  Acu3_153::Acu3_gearcontrolflagType acu3_gearcontrolflag_;
  double acu3_brakingtargetpressure_;
  double acu3_brakingtargetdeceleration_;
  Acu3_153::Acu3_brakingcontrolflagType acu3_brakingcontrolflag_;
  int acu3_livecounter_;
  int acu3_checksum_;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


