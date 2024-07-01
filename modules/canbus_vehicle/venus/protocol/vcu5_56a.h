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

class Vcu556a : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;
  Vcu556a();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

 private:

    // config detail: {'bit': 56, 'enum': {0: 'VCU5_GEARAUTOCONTROLST_INACTIVE', 1: 'VCU5_GEARAUTOCONTROLST_ACTIVE', 2: 'VCU5_GEARAUTOCONTROLST_RESERVED1', 3: 'VCU5_GEARAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU5_GearAutoControlST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_gearautocontrolstType vcu5_gearautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 54, 'enum': {0: 'VCU5_REARSTEERINGTORQUESIGN_LEFT', 1: 'VCU5_REARSTEERINGTORQUESIGN_RIGHT'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU5_RearSteeringTorqueSign', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_rearsteeringtorquesignType vcu5_rearsteeringtorquesign(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'is_signed_var': False, 'len': 10, 'name': 'VCU5_RearSteeringTorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
    double vcu5_rearsteeringtorque(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 55, 'enum': {0: 'VCU5_REARSTEERINGACTIVE_NOACTIVE', 1: 'VCU5_REARSTEERINGACTIVE_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU5_RearSteeringActive', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_rearsteeringactiveType vcu5_rearsteeringactive(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 42, 'enum': {0: 'VCU5_FRONTSTEERINGTORQUESIGN_LEFT', 1: 'VCU5_FRONTSTEERINGTORQUESIGN_RIGHT'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU5_FrontSteeringTorqueSign', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_frontsteeringtorquesignType vcu5_frontsteeringtorquesign(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'is_signed_var': False, 'len': 10, 'name': 'VCU5_FrontSteeringTorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
    double vcu5_frontsteeringtorque(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 43, 'enum': {0: 'VCU5_FRONTSTEERINGACTIVE_NOACTIVE', 1: 'VCU5_FRONTSTEERINGACTIVE_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU5_FrontSteeringActive', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_frontsteeringactiveType vcu5_frontsteeringactive(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 31, 'enum': {0: 'VCU5_REARSTEERINGTAKEOVERST_INACTIVE', 1: 'VCU5_REARSTEERINGTAKEOVERST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU5_RearSteeringTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_rearsteeringtakeoverstType vcu5_rearsteeringtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'enum': {0: 'VCU5_REARSTEERINGFAILUREST_NOTFAIL', 1: 'VCU5_REARSTEERINGFAILUREST_EPSFAIL', 2: 'VCU5_REARSTEERINGFAILUREST_SASFAIL', 3: 'VCU5_REARSTEERINGFAILUREST_STEERTEMPFAIL', 4: 'VCU5_REARSTEERINGFAILUREST_RESERVED1', 5: 'VCU5_REARSTEERINGFAILUREST_RESERVED2', 6: 'VCU5_REARSTEERINGFAILUREST_RESERVED3', 7: 'VCU5_REARSTEERINGFAILUREST_RESERVED4'}, 'is_signed_var': False, 'len': 3, 'name': 'VCU5_RearSteeringFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_rearsteeringfailurestType vcu5_rearsteeringfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 14, 'enum': {0: 'VCU5_REARSTEERINGAUTOCONTROLST_INACTIVE', 1: 'VCU5_REARSTEERINGAUTOCONTROLST_ACTIVE', 2: 'VCU5_REARSTEERINGAUTOCONTROLST_RESERVED1', 3: 'VCU5_REARSTEERINGAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU5_RearSteeringAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_rearsteeringautocontrolstType vcu5_rearsteeringautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'VCU5_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int vcu5_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 27, 'enum': {0: 'VCU5_FRONTSTEERINGTAKEOVERST_INACTIVE', 1: 'VCU5_FRONTSTEERINGTAKEOVERST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU5_FrontSteeringTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_frontsteeringtakeoverstType vcu5_frontsteeringtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'enum': {0: 'VCU5_FRONTSTEERINGFAILUREST_NOTFAIL', 1: 'VCU5_FRONTSTEERINGFAILUREST_EPSFAIL', 2: 'VCU5_FRONTSTEERINGFAILUREST_SASFAIL', 3: 'VCU5_FRONTSTEERINGFAILUREST_STEERTEMPFAIL', 4: 'VCU5_FRONTSTEERINGFAILUREST_RESERVED1', 5: 'VCU5_FRONTSTEERINGFAILUREST_RESERVED2', 6: 'VCU5_FRONTSTEERINGFAILUREST_RESERVED3', 7: 'VCU5_FRONTSTEERINGFAILUREST_RESERVED4'}, 'is_signed_var': False, 'len': 3, 'name': 'VCU5_FrontSteeringFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_frontsteeringfailurestType vcu5_frontsteeringfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 12, 'enum': {0: 'VCU5_FRONTSTEERINGAUTOCONTROLST_INACTIVE', 1: 'VCU5_FRONTSTEERINGAUTOCONTROLST_ACTIVE', 2: 'VCU5_FRONTSTEERINGAUTOCONTROLST_RESERVED1', 3: 'VCU5_FRONTSTEERINGAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU5_FrontSteeringAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_frontsteeringautocontrolstType vcu5_frontsteeringautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 19, 'enum': {0: 'VCU5_DRIVINGTAKEOVERST_INACTIVE', 1: 'VCU5_DRIVINGTAKEOVERST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU5_DrivingTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_drivingtakeoverstType vcu5_drivingtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'enum': {0: 'VCU5_DRIVINGFAILUREST_NOTFAIL', 1: 'VCU5_DRIVINGFAILUREST_HCUFAIL', 2: 'VCU5_DRIVINGFAILUREST_SPEEDSENSORFAIL', 3: 'VCU5_DRIVINGFAILUREST_YRSFAIL', 4: 'VCU5_DRIVINGFAILUREST_RESERVED1', 5: 'VCU5_DRIVINGFAILUREST_RESERVED2', 6: 'VCU5_DRIVINGFAILUREST_RESERVED3', 7: 'VCU5_DRIVINGFAILUREST_RESERVED4'}, 'is_signed_var': False, 'len': 3, 'name': 'VCU5_DrivingFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_drivingfailurestType vcu5_drivingfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'enum': {0: 'VCU5_DRIVINGAUTOCONTROLST_INACTIVE', 1: 'VCU5_DRIVINGAUTOCONTROLST_ACTIVE', 2: 'VCU5_DRIVINGAUTOCONTROLST_RESERVED1', 3: 'VCU5_DRIVINGAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU5_DrivingAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_drivingautocontrolstType vcu5_drivingautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU5_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int vcu5_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 23, 'enum': {0: 'VCU5_BRAKINGTAKEOVERST_INACTIVE', 1: 'VCU5_BRAKINGTAKEOVERST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU5_BrakingTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_brakingtakeoverstType vcu5_brakingtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 20, 'enum': {0: 'VCU5_BRAKINGFAILUREST_NOTFAIL', 1: 'VCU5_BRAKINGFAILUREST_ESPFAIL', 2: 'VCU5_BRAKINGFAILUREST_SPEEDSENSORFAIL', 3: 'VCU5_BRAKINGFAILUREST_YRSFAIL', 4: 'VCU5_BRAKINGFAILUREST_HCUFAIL', 5: 'VCU5_BRAKINGFAILUREST_ESPANDHCUFAIL', 6: 'VCU5_BRAKINGFAILUREST_RESERVED1', 7: 'VCU5_BRAKINGFAILUREST_RESERVED2'}, 'is_signed_var': False, 'len': 3, 'name': 'VCU5_BrakingFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_brakingfailurestType vcu5_brakingfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 10, 'enum': {0: 'VCU5_BRAKINGAUTOCONTROLST_INACTIVE', 1: 'VCU5_BRAKINGAUTOCONTROLST_ACTIVE', 2: 'VCU5_BRAKINGAUTOCONTROLST_RESERVED1', 3: 'VCU5_BRAKINGAUTOCONTROLST_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU5_BrakingAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu5_56a::Vcu5_brakingautocontrolstType vcu5_brakingautocontrolst(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


