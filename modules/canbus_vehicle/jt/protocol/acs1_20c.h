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

class Acs120c : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Acs120c();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 48, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_WorkMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs1_workmode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 12, 'description': 'This signal indicates the state machine of steering.', 'is_signed_var': False, 'len': 4, 'name': 'ACS1_SteeringStateMachine', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'value', 'precision': 1.0, 'type': 'int'}
    int acs1_steeringstatemachine(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 36, 'description': 'This signal indicates the state machine of gear.', 'is_signed_var': False, 'len': 4, 'name': 'ACS1_GearStateMachine', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'value', 'precision': 1.0, 'type': 'int'}
    int acs1_gearstatemachine(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 20, 'description': 'This signal indicates the state machine of driving.', 'enum': {0: 'ACS1_DRIVINGSTATEMACHINE_IDLE', 1: 'ACS1_DRIVINGSTATEMACHINE_CHECK', 2: 'ACS1_DRIVINGSTATEMACHINE_MANUAL', 3: 'ACS1_DRIVINGSTATEMACHINE_REMOTE', 4: 'ACS1_DRIVINGSTATEMACHINE_IPC', 5: 'ACS1_DRIVINGSTATEMACHINE_INTERVENTION', 6: 'ACS1_DRIVINGSTATEMACHINE_EMERGENCY', 7: 'ACS1_DRIVINGSTATEMACHINE_ERROR'}, 'is_signed_var': False, 'len': 4, 'name': 'ACS1_DrivingStateMachine', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'value', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_drivingstatemachineType acs1_drivingstatemachine(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'description': 'This signal indicates the state machine of braking.', 'is_signed_var': False, 'len': 4, 'name': 'ACS1_BrakingStateMachine', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'value', 'precision': 1.0, 'type': 'int'}
    int acs1_brakingstatemachine(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 34, 'description': 'This signal indicates the gear is under maunal taking over.', 'enum': {0: 'ACS1_GEARTAKEOVERST_INACTIVE', 1: 'ACS1_GEARTAKEOVERST_TEMP_ACTIVE', 2: 'ACS1_GEARTAKEOVERST_ACTIVE', 3: 'ACS1_GEARTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_GearTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_geartakeoverstType acs1_geartakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 46, 'description': 'This signal indicates the gear is in fault status', 'enum': {0: 'ACS1_GEARFAILUREST_NO_FAIL', 1: 'ACS1_GEARFAILUREST_EGSM_FAIL', 2: 'ACS1_GEARFAILUREST_HCU_FAIL', 3: 'ACS1_GEARFAILUREST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_GearFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_gearfailurestType acs1_gearfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'description': 'This signal indicates the gear is under automatical control or not.', 'enum': {0: 'ACS1_GEARAUTOCONTROLST_INACTIVE', 1: 'ACS1_GEARAUTOCONTROLST_ACTIVE', 2: 'ACS1_GEARAUTOCONTROLST_RESERVED', 3: 'ACS1_GEARAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_GearAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_gearautocontrolstType acs1_gearautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 10, 'description': 'This signal indicates the steering is under maunal taking over.', 'enum': {0: 'ACS1_STEERINGTAKEOVERST_INACTIVE', 1: 'ACS1_STEERINGTAKEOVERST_TEMP_ACTIVE', 2: 'ACS1_STEERINGTAKEOVERST_ACTIVE', 3: 'ACS1_STEERINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_SteeringTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_steeringtakeoverstType acs1_steeringtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'description': 'This signal indicates the steering is in fault status', 'enum': {0: 'ACS1_STEERINGFAILUREST_NO_FAIL', 1: 'ACS1_STEERINGFAILUREST_EPS_FAIL', 2: 'ACS1_STEERINGFAILUREST_SAS_FAIL', 3: 'ACS1_STEERINGFAILUREST_APA_FAIL'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_SteeringFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_steeringfailurestType acs1_steeringfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal indicates the steering is under automatical control or not.', 'enum': {0: 'ACS1_STEERINGAUTOCONTROLST_INACTIVE', 1: 'ACS1_STEERINGAUTOCONTROLST_ACTIVE', 2: 'ACS1_STEERINGAUTOCONTROLST_RESERVED', 3: 'ACS1_STEERINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_SteeringAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_steeringautocontrolstType acs1_steeringautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACS1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int acs1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'description': 'This signal indicates the driving is under maunal taking over.', 'enum': {0: 'ACS1_DRIVINGTAKEOVERST_INACTIVE', 1: 'ACS1_DRIVINGTAKEOVERST_TEMP_ACTIVE', 2: 'ACS1_DRIVINGTAKEOVERST_ACTIVE', 3: 'ACS1_DRIVINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_DrivingTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_drivingtakeoverstType acs1_drivingtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 42, 'description': 'This signal indicates the driving is in fault status', 'enum': {0: 'ACS1_DRIVINGFAILUREST_NO_FAIL', 1: 'ACS1_DRIVINGFAILUREST_HCU_FAIL', 2: 'ACS1_DRIVINGFAILUREST_RESERVED', 3: 'ACS1_DRIVINGFAILUREST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_DrivingFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_drivingfailurestType acs1_drivingfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'This signal indicates the driving is under automatical control or not.', 'enum': {0: 'ACS1_DRIVINGAUTOCONTROLST_INACTIVE', 1: 'ACS1_DRIVINGAUTOCONTROLST_ACTIVE', 2: 'ACS1_DRIVINGAUTOCONTROLST_RESERVED', 3: 'ACS1_DRIVINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_DrivingAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_drivingautocontrolstType acs1_drivingautocontrolst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACS1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int acs1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 26, 'description': 'This signal indicates the braking is under maunal taking over.', 'enum': {0: 'ACS1_BRAKINGTAKEOVERST_INACTIVE', 1: 'ACS1_BRAKINGTAKEOVERST_TEMP_ACTIVE', 2: 'ACS1_BRAKINGTAKEOVERST_ACTIVE', 3: 'ACS1_BRAKINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_BrakingTakeOverSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_brakingtakeoverstType acs1_brakingtakeoverst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'description': 'This signal indicates the braking is in fault status', 'enum': {0: 'ACS1_BRAKINGFAILUREST_NO_FAIL', 1: 'ACS1_BRAKINGFAILUREST_ESP_FAIL', 2: 'ACS1_BRAKINGFAILUREST_SS_FAIL', 3: 'ACS1_BRAKINGFAILUREST_HCU_FAIL'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_BrakingFailureSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_brakingfailurestType acs1_brakingfailurest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'description': 'This signal indicates the braking is under automatical control or not.', 'enum': {0: 'ACS1_BRAKINGAUTOCONTROLST_INACTIVE', 1: 'ACS1_BRAKINGAUTOCONTROLST_ACTIVE', 2: 'ACS1_BRAKINGAUTOCONTROLST_RESERVED', 3: 'ACS1_BRAKINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACS1_BrakingAutoControlSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs1_20c::Acs1_brakingautocontrolstType acs1_brakingautocontrolst(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


