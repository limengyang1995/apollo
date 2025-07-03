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

class Vcu156f : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;
  Vcu156f();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

 private:

    // config detail: {'bit': 55, 'enum': {0: 'VCU1_JERKST_NOPRESS', 1: 'VCU1_JERKST_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU1_JerkSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_56f::Vcu1_jerkstType vcu1_jerkst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 23, 'enum': {0: 'VCU1_BUTTON2_NOPRESS', 1: 'VCU1_BUTTON2_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU1_Button2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_56f::Vcu1_button2Type vcu1_button2(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 22, 'enum': {0: 'VCU1_BUTTON1_NOPRESS', 1: 'VCU1_BUTTON1_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU1_Button1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_56f::Vcu1_button1Type vcu1_button1(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'is_signed_var': False, 'len': 15, 'name': 'VCU1_VehicleSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|327.67]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double vcu1_vehiclespeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'is_signed_var': False, 'len': 14, 'name': 'VCU1_SteeringAngle_R', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
    double vcu1_steeringangle_r(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'is_signed_var': False, 'len': 14, 'name': 'VCU1_SteeringAngle_F', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
    double vcu1_steeringangle_f(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'VCU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int vcu1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 39, 'enum': {0: 'VCU1_PARKINGBRAKEINFO_RELEASED', 1: 'VCU1_PARKINGBRAKEINFO_LOCKED'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU1_ParkingBrakeInfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_56f::Vcu1_parkingbrakeinfoType vcu1_parkingbrakeinfo(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 56, 'enum': {0: 'VCU1_GEARINFO_NOCONNECTION', 1: 'VCU1_GEARINFO_P', 2: 'VCU1_GEARINFO_R', 3: 'VCU1_GEARINFO_N', 4: 'VCU1_GEARINFO_D', 5: 'VCU1_GEARINFO_RESERVED1', 6: 'VCU1_GEARINFO_RESERVED2', 7: 'VCU1_GEARINFO_RESERVED3'}, 'is_signed_var': False, 'len': 3, 'name': 'VCU1_GearInfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_56f::Vcu1_gearinfoType vcu1_gearinfo(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int vcu1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 38, 'enum': {0: 'VCU1_BRAKEINFO_INACTIVE', 1: 'VCU1_BRAKEINFO_BRAKEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU1_BrakeInfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_56f::Vcu1_brakeinfoType vcu1_brakeinfo(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


