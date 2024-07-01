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

class Acu1529 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;
  Acu1529();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

 private:

    // config detail: {'bit': 40, 'enum': {0: 'ACU1_GEARAUTOCONTROL_RESERVED1', 1: 'ACU1_GEARAUTOCONTROL_REQUEST', 2: 'ACU1_GEARAUTOCONTROL_NOREQUEST', 3: 'ACU1_GEARAUTOCONTROL_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_GearAutoControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acu1_529::Acu1_gearautocontrolType acu1_gearautocontrol(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 30, 'is_signed_var': False, 'len': 9, 'name': 'ACU1_TargetSteeringSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
    int acu1_targetsteeringspeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 19, 'enum': {2047: 'ACU1_TARGETSTEERINGANGLE_R_NOREQUEST'}, 'is_signed_var': False, 'len': 11, 'name': 'ACU1_TargetSteeringAngle_R', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'enum'}
    Acu1_529::Acu1_targetsteeringangle_rType acu1_targetsteeringangle_r(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'enum': {2047: 'ACU1_TARGETSTEERINGANGLE_F_NOREQUEST'}, 'is_signed_var': False, 'len': 11, 'name': 'ACU1_TargetSteeringAngle_F', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'enum'}
    Acu1_529::Acu1_targetsteeringangle_fType acu1_targetsteeringangle_f(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'enum': {0: 'ACU1_TARGETGEAR_NOREQUEST', 1: 'ACU1_TARGETGEAR_P', 2: 'ACU1_TARGETGEAR_R', 3: 'ACU1_TARGETGEAR_N', 4: 'ACU1_TARGETGEAR_D', 5: 'ACU1_TARGETGEAR_RESERVED1', 6: 'ACU1_TARGETGEAR_RESERVED2', 7: 'ACU1_TARGETGEAR_RESERVED3'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU1_TargetGear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acu1_529::Acu1_targetgearType acu1_targetgear(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 42, 'enum': {0: 'ACU1_TARGETEPB_NOREQUEST', 1: 'ACU1_TARGETEPB_RELEASE', 2: 'ACU1_TARGETEPB_LOCK', 3: 'ACU1_TARGETEPB_RESERVE'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_TargetEPB', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acu1_529::Acu1_targetepbType acu1_targetepb(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'ACU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int acu1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int acu1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 56, 'enum': {0: 'ACU1_STEERINGAUTOCONTROL_NOREQUET', 1: 'ACU1_STEERINGAUTOCONTROL_REQUEST', 2: 'ACU1_STEERINGAUTOCONTROL_RESERVE1', 3: 'ACU1_STEERINGAUTOCONTROL_RESERVE2'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_SteeringAutoControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acu1_529::Acu1_steeringautocontrolType acu1_steeringautocontrol(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


