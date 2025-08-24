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

#include "modules/canbus_vehicle/middlecar/proto/middlecar.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace middlecar {

class Vcufsdstatus1685 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Middlecar> {
 public:
  static const int32_t ID;
  Vcufsdstatus1685();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Middlecar* chassis) const override;

 private:

    // config detail: {'bit': 21, 'description': 'work_status', 'enum': {0: 'VCU_FSD_WORKSTATUS_NORMAL_OPERATION', 1: 'VCU_FSD_WORKSTATUS_LIMPING', 2: 'VCU_FSD_WORKSTATUS_FAULT_PARKING'}, 'is_signed_var': False, 'len': 3, 'name': 'VCU_FSD_WorkStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_workstatusType vcu_fsd_workstatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'description': 'Safe_edge_contact_state', 'enum': {0: 'VCU_FSD_TOUCHBORDER_NO_CONTACT', 1: 'VCU_FSD_TOUCHBORDER_CONTACT'}, 'is_signed_var': False, 'len': 3, 'name': 'VCU_FSD_TouchBorder', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_touchborderType vcu_fsd_touchborder(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 12, 'description': 'steering_mode', 'enum': {0: 'VCU_FSD_STEERMODE_FRONT_AXLE_STEERING', 1: 'VCU_FSD_STEERMODE_FULL_BRIDGE_STEERING', 2: 'VCU_FSD_STEERMODE_REAR_AXLE_STEERING'}, 'is_signed_var': False, 'len': 4, 'name': 'VCU_FSD_SteerMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_steermodeType vcu_fsd_steermode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'description': 'Vehicle_power_consumption', 'is_signed_var': False, 'len': 7, 'name': 'VCU_FSD_VehSOC', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|127]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu_fsd_vehsoc(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 6, 'description': 'Parking_brake_status', 'enum': {0: 'VCU_FSD_PARKINGSTATUS_NOT_PARKED', 1: 'VCU_FSD_PARKINGSTATUS_PARKING'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_FSD_ParkingStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_parkingstatusType vcu_fsd_parkingstatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Current_control_source', 'enum': {0: 'VCU_FSD_CMDSOURCE_NOT_SELECTED', 1: 'VCU_FSD_CMDSOURCE_FSD', 2: 'VCU_FSD_CMDSOURCE_CLOSE_RANGE_REMOTE_CONTROL'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_FSD_CmdSource', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_cmdsourceType vcu_fsd_cmdsource(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'VCU_FSD_RoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu_fsd_roulingcounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'gear', 'enum': {0: 'VCU_FSD_GEAR_POSITION_N', 1: 'VCU_FSD_GEAR_POSITION_D', 2: 'VCU_FSD_GEAR_POSITION_R'}, 'is_signed_var': False, 'len': 4, 'name': 'VCU_FSD_Gear_Position', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|6]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_gear_positionType vcu_fsd_gear_position(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 2, 'description': 'Special_mode_feedback', 'enum': {0: 'VCU_FSD_SPECTIONMODE_BENCH_MODE', 1: 'VCU_FSD_SPECTIONMODE_ECONOMIC_MODEL', 2: 'VCU_FSD_SPECTIONMODE_STANDARD_MODE', 3: 'VCU_FSD_SPECTIONMODE_SAND_MODE', 4: 'VCU_FSD_SPECTIONMODE_RAMP_MODE', 5: 'VCU_FSD_SPECTIONMODE_MUD_MODE'}, 'is_signed_var': False, 'len': 4, 'name': 'VCU_FSD_SpectionMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_spectionmodeType vcu_fsd_spectionmode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'High_voltage_status_feedback', 'enum': {0: 'VCU_FSD_HV_HIGH_VOLTAGE_NOT_APPLIED', 1: 'VCU_FSD_HV_HIGH_VOLTAGE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_FSD_HV', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_hvType vcu_fsd_hv(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 17, 'description': 'Standby_state_feedback', 'enum': {0: 'VCU_FSD_STANDBY_STANDBY', 1: 'VCU_FSD_STANDBY_NOT_IN_STANDBY_MODE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_FSD_Standby', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_fsd_status1_685::Vcu_fsd_standbyType vcu_fsd_standby(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo


