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

class Vcu1320 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Kfc> {
 public:
  static const int32_t ID;
  Vcu1320();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Kfc* chassis) const override;

 private:

    // config detail: {'bit': 40, 'is_signed_var': False, 'len': 4, 'name': 'VCU1_SteeringMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu1_steeringmode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'is_signed_var': False, 'len': 4, 'name': 'VCU1_DrivingMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu1_drivingmode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 12, 'enum': {0: 'VCU1_STEERINGTAKEOVERST_INACTIVE', 1: 'VCU1_STEERINGTAKEOVERST_TEMPORARY', 2: 'VCU1_STEERINGTAKEOVERST_ACTIVE', 3: 'VCU1_STEERINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU1_SteeringTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_320::Vcu1_steeringtakeoverstType vcu1_steeringtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 10, 'enum': {0: 'VCU1_STEERINGFAILUREST_NO_FAIL', 1: 'VCU1_STEERINGFAILUREST_EPS_FAIL', 2: 'VCU1_STEERINGFAILUREST_SAS_FAIL', 3: 'VCU1_STEERINGFAILUREST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU1_SteeringFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_320::Vcu1_steeringfailurestType vcu1_steeringfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'enum': {0: 'VCU1_STEERINGAUTOCONTROLST_INACTIVE', 1: 'VCU1_STEERINGAUTOCONTROLST_ACTIVE', 2: 'VCU1_STEERINGAUTOCONTROLST_RESERVED', 3: 'VCU1_STEERINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU1_SteeringAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_320::Vcu1_steeringautocontrolstType vcu1_steeringautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 20, 'enum': {0: 'VCU1_DRIVINGTAKEOVERST_INACTIVE', 1: 'VCU1_DRIVINGTAKEOVERST_TEMPORARY', 2: 'VCU1_DRIVINGTAKEOVERST_TAKE_OVER', 3: 'VCU1_DRIVINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU1_DrivingTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_320::Vcu1_drivingtakeoverstType vcu1_drivingtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'enum': {0: 'VCU1_DRIVINGFAILUREST_NO_FAIL', 1: 'VCU1_DRIVINGFAILUREST_HCU_FAIL', 2: 'VCU1_DRIVINGFAILUREST_MOTOR_FAIL', 3: 'VCU1_DRIVINGFAILUREST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU1_DrivingFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_320::Vcu1_drivingfailurestType vcu1_drivingfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'enum': {0: 'VCU1_DRIVINGAUTOCONTROLST_INACTIVE', 1: 'VCU1_DRIVINGAUTOCONTROLST_ACTIVE', 2: 'VCU1_DRIVINGAUTOCONTROLST_RESERVED', 3: 'VCU1_DRIVINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU1_DrivingAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_320::Vcu1_drivingautocontrolstType vcu1_drivingautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'is_signed_var': False, 'len': 15, 'name': 'VCU1_VehicleSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|60]', 'physical_unit': 'km/h', 'precision': 1.0, 'type': 'int'}
    int vcu1_vehiclespeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'VCU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 14, 'enum': {0: 'VCU1_GEARINFO_P', 1: 'VCU1_GEARINFO_R', 2: 'VCU1_GEARINFO_N', 3: 'VCU1_GEARINFO_D'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU1_GearInfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_320::Vcu1_gearinfoType vcu1_gearinfo(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 22, 'enum': {0: 'VCU1_BRAKEINFO_INACTIVE', 1: 'VCU1_BRAKEINFO_ACTIVE', 2: 'VCU1_BRAKEINFO_RESERVED', 3: 'VCU1_BRAKEINFO_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU1_BrakeInfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu1_320::Vcu1_brakeinfoType vcu1_brakeinfo(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace kfc
}  // namespace canbus
}  // namespace apollo


