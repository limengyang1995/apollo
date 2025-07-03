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

class Acu3534 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;

  Acu3534();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 8, 'enum': {0: 'ACU3_STEERINGLIGHT_NOREQUEST', 1: 'ACU3_STEERINGLIGHT_LEFT', 2: 'ACU3_STEERINGLIGHT_RIGHT', 3: 'ACU3_STEERINGLIGHT_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_SteeringLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3534* set_acu3_steeringlight(Acu3_534::Acu3_steeringlightType acu3_steeringlight);

  // config detail: {'bit': 12, 'enum': {0: 'ACU3_HAZARDLIGHT_NOREQUEST', 1: 'ACU3_HAZARDLIGHT_ON', 2: 'ACU3_HAZARDLIGHT_OFF', 3: 'ACU3_HAZARDLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_HazardLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3534* set_acu3_hazardlight(Acu3_534::Acu3_hazardlightType acu3_hazardlight);

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU3_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  Acu3534* set_acu3_checksum(int acu3_checksum);

  // config detail: {'bit': 32, 'enum': {0: 'ACU3_BRAKESWITCH_NOREQUEST', 1: 'ACU3_BRAKESWITCH_ON', 2: 'ACU3_BRAKESWITCH_OFF', 3: 'ACU3_BRAKESWITCH_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BrakeSwitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3534* set_acu3_brakeswitch(Acu3_534::Acu3_brakeswitchType acu3_brakeswitch);

  // config detail: {'bit': 10, 'enum': {0: 'ACU3_BEAMLIGHT_NOREQUEST', 1: 'ACU3_BEAMLIGHT_LOW', 2: 'ACU3_BEAMLIGHT_HIGH', 3: 'ACU3_BEAMLIGHT_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BeamLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3534* set_acu3_beamlight(Acu3_534::Acu3_beamlightType acu3_beamlight);

  // config detail: {'bit': 18, 'enum': {0: 'ACU3_BACKUPLIGHT_NOREQUEST', 1: 'ACU3_BACKUPLIGHT_ON', 2: 'ACU3_BACKUPLIGHT_OFF', 3: 'ACU3_BACKUPLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BackupLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu3534* set_acu3_backuplight(Acu3_534::Acu3_backuplightType acu3_backuplight);

 private:

  // config detail: {'bit': 8, 'enum': {0: 'ACU3_STEERINGLIGHT_NOREQUEST', 1: 'ACU3_STEERINGLIGHT_LEFT', 2: 'ACU3_STEERINGLIGHT_RIGHT', 3: 'ACU3_STEERINGLIGHT_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_SteeringLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_steeringlight(uint8_t* data, Acu3_534::Acu3_steeringlightType acu3_steeringlight);

  // config detail: {'bit': 12, 'enum': {0: 'ACU3_HAZARDLIGHT_NOREQUEST', 1: 'ACU3_HAZARDLIGHT_ON', 2: 'ACU3_HAZARDLIGHT_OFF', 3: 'ACU3_HAZARDLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_HazardLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_hazardlight(uint8_t* data, Acu3_534::Acu3_hazardlightType acu3_hazardlight);

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU3_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  void set_p_acu3_checksum(uint8_t* data, int acu3_checksum);

  // config detail: {'bit': 32, 'enum': {0: 'ACU3_BRAKESWITCH_NOREQUEST', 1: 'ACU3_BRAKESWITCH_ON', 2: 'ACU3_BRAKESWITCH_OFF', 3: 'ACU3_BRAKESWITCH_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BrakeSwitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_brakeswitch(uint8_t* data, Acu3_534::Acu3_brakeswitchType acu3_brakeswitch);

  // config detail: {'bit': 10, 'enum': {0: 'ACU3_BEAMLIGHT_NOREQUEST', 1: 'ACU3_BEAMLIGHT_LOW', 2: 'ACU3_BEAMLIGHT_HIGH', 3: 'ACU3_BEAMLIGHT_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BeamLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_beamlight(uint8_t* data, Acu3_534::Acu3_beamlightType acu3_beamlight);

  // config detail: {'bit': 18, 'enum': {0: 'ACU3_BACKUPLIGHT_NOREQUEST', 1: 'ACU3_BACKUPLIGHT_ON', 2: 'ACU3_BACKUPLIGHT_OFF', 3: 'ACU3_BACKUPLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BackupLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu3_backuplight(uint8_t* data, Acu3_534::Acu3_backuplightType acu3_backuplight);

  Acu3_534::Acu3_steeringlightType acu3_steeringlight(const std::uint8_t* bytes, const int32_t length) const;

  Acu3_534::Acu3_hazardlightType acu3_hazardlight(const std::uint8_t* bytes, const int32_t length) const;

  int acu3_checksum(const std::uint8_t* bytes, const int32_t length) const;

  Acu3_534::Acu3_brakeswitchType acu3_brakeswitch(const std::uint8_t* bytes, const int32_t length) const;

  Acu3_534::Acu3_beamlightType acu3_beamlight(const std::uint8_t* bytes, const int32_t length) const;

  Acu3_534::Acu3_backuplightType acu3_backuplight(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Acu3_534::Acu3_steeringlightType acu3_steeringlight_;
  Acu3_534::Acu3_hazardlightType acu3_hazardlight_;
  int acu3_checksum_;
  Acu3_534::Acu3_brakeswitchType acu3_brakeswitch_;
  Acu3_534::Acu3_beamlightType acu3_beamlight_;
  Acu3_534::Acu3_backuplightType acu3_backuplight_;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


