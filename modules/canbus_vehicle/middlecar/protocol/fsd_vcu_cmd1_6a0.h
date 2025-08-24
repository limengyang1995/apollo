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

class Fsdvcucmd16a0 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Middlecar> {
 public:
  static const int32_t ID;

  Fsdvcucmd16a0();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Middlecar* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 41, 'description': 'Rear_axle_virtual_steering_wheel_angle', 'is_signed_var': False, 'len': 11, 'name': 'FSD_VCU_TarVehRearAngle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Fsdvcucmd16a0* set_fsd_vcu_tarvehrearangle(int fsd_vcu_tarvehrearangle);

  // config detail: {'bit': 52, 'description': 'Brake_opening_degree', 'is_signed_var': False, 'len': 8, 'name': 'FSD_VCU_BrakePec', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Fsdvcucmd16a0* set_fsd_vcu_brakepec(int fsd_vcu_brakepec);

  // config detail: {'bit': 0, 'description': 'CmdSource', 'enum': {0: 'FSD_VCU_CMDSOURCE_NOT_SELECTED', 1: 'FSD_VCU_CMDSOURCE_FSD', 2: 'FSD_VCU_CMDSOURCE_CLOSE_RANGE_REMOTE_CONTROL'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_CmdSource', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd16a0* set_fsd_vcu_cmdsource(Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType fsd_vcu_cmdsource);

  // config detail: {'bit': 2, 'description': 'Special_Mode', 'enum': {0: 'FSD_VCU_SPECIALMODE_BENCH_MODE', 1: 'FSD_VCU_SPECIALMODE_ECONOMIC_MODEL', 2: 'FSD_VCU_SPECIALMODE_STANDARD_MODE', 3: 'FSD_VCU_SPECIALMODE_SAND_MODE', 4: 'FSD_VCU_SPECIALMODE_RAMP_MODE', 5: 'FSD_VCU_SPECIALMODE_MUD_MODE'}, 'is_signed_var': False, 'len': 4, 'name': 'FSD_VCU_SpecialMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd16a0* set_fsd_vcu_specialmode(Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType fsd_vcu_specialmode);

  // config detail: {'bit': 6, 'description': 'steering_mode', 'enum': {0: 'FSD_VCU_STEERMODE_FRONT_AXLE_STEERING', 1: 'FSD_VCU_STEERMODE_FULL_BRIDGE_STEERING', 2: 'FSD_VCU_STEERMODE_REAR_AXLE_STEERING'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_SteerMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd16a0* set_fsd_vcu_steermode(Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType fsd_vcu_steermode);

  // config detail: {'bit': 13, 'description': 'Target_speed', 'is_signed_var': False, 'len': 10, 'name': 'FSD_VCU_TarVehSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'signal_type': 'speed', 'type': 'double'}
  Fsdvcucmd16a0* set_fsd_vcu_tarvehspeed(double fsd_vcu_tarvehspeed);

  // config detail: {'bit': 30, 'description': 'Front_axle_virtual_steering_wheel_angle', 'is_signed_var': False, 'len': 11, 'name': 'FSD_VCU_TarVehFrontAngle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Fsdvcucmd16a0* set_fsd_vcu_tarvehfrontangle(int fsd_vcu_tarvehfrontangle);

  // config detail: {'bit': 23, 'description': 'Maximum_speed_limit', 'is_signed_var': False, 'len': 7, 'name': 'FSD_VCU_MaxVehSpeedLmt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|127]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
  Fsdvcucmd16a0* set_fsd_vcu_maxvehspeedlmt(int fsd_vcu_maxvehspeedlmt);

  // config detail: {'bit': 8, 'description': 'Emergency_stop', 'enum': {0: 'FSD_VCU_EMERGSTOP_NO_EMERGENCY_STOP', 1: 'FSD_VCU_EMERGSTOP_EMERGENCY_STOP'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_EmergStop', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd16a0* set_fsd_vcu_emergstop(Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType fsd_vcu_emergstop);

  // config detail: {'bit': 9, 'description': 'Target_gear', 'enum': {0: 'FSD_VCU_TARGEAR_N', 1: 'FSD_VCU_TARGEAR_D', 2: 'FSD_VCU_TARGEAR_R'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_TarGear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd16a0* set_fsd_vcu_targear(Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType fsd_vcu_targear);

  // config detail: {'bit': 11, 'description': 'parking', 'enum': {0: 'FSD_VCU_PARK_PARKING', 1: 'FSD_VCU_PARK_RELEASE_PARKING'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_Park', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd16a0* set_fsd_vcu_park(Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType fsd_vcu_park);

  // config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'FSD_VCU_RoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Fsdvcucmd16a0* set_fsd_vcu_roulingcounter(int fsd_vcu_roulingcounter);

 private:

  // config detail: {'bit': 41, 'description': 'Rear_axle_virtual_steering_wheel_angle', 'is_signed_var': False, 'len': 11, 'name': 'FSD_VCU_TarVehRearAngle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_fsd_vcu_tarvehrearangle(uint8_t* data, int fsd_vcu_tarvehrearangle);

  // config detail: {'bit': 52, 'description': 'Brake_opening_degree', 'is_signed_var': False, 'len': 8, 'name': 'FSD_VCU_BrakePec', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_fsd_vcu_brakepec(uint8_t* data, int fsd_vcu_brakepec);

  // config detail: {'bit': 0, 'description': 'CmdSource', 'enum': {0: 'FSD_VCU_CMDSOURCE_NOT_SELECTED', 1: 'FSD_VCU_CMDSOURCE_FSD', 2: 'FSD_VCU_CMDSOURCE_CLOSE_RANGE_REMOTE_CONTROL'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_CmdSource', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_cmdsource(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType fsd_vcu_cmdsource);

  // config detail: {'bit': 2, 'description': 'Special_Mode', 'enum': {0: 'FSD_VCU_SPECIALMODE_BENCH_MODE', 1: 'FSD_VCU_SPECIALMODE_ECONOMIC_MODEL', 2: 'FSD_VCU_SPECIALMODE_STANDARD_MODE', 3: 'FSD_VCU_SPECIALMODE_SAND_MODE', 4: 'FSD_VCU_SPECIALMODE_RAMP_MODE', 5: 'FSD_VCU_SPECIALMODE_MUD_MODE'}, 'is_signed_var': False, 'len': 4, 'name': 'FSD_VCU_SpecialMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_specialmode(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType fsd_vcu_specialmode);

  // config detail: {'bit': 6, 'description': 'steering_mode', 'enum': {0: 'FSD_VCU_STEERMODE_FRONT_AXLE_STEERING', 1: 'FSD_VCU_STEERMODE_FULL_BRIDGE_STEERING', 2: 'FSD_VCU_STEERMODE_REAR_AXLE_STEERING'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_SteerMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_steermode(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType fsd_vcu_steermode);

  // config detail: {'bit': 13, 'description': 'Target_speed', 'is_signed_var': False, 'len': 10, 'name': 'FSD_VCU_TarVehSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'signal_type': 'speed', 'type': 'double'}
  void set_p_fsd_vcu_tarvehspeed(uint8_t* data, double fsd_vcu_tarvehspeed);

  // config detail: {'bit': 30, 'description': 'Front_axle_virtual_steering_wheel_angle', 'is_signed_var': False, 'len': 11, 'name': 'FSD_VCU_TarVehFrontAngle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_fsd_vcu_tarvehfrontangle(uint8_t* data, int fsd_vcu_tarvehfrontangle);

  // config detail: {'bit': 23, 'description': 'Maximum_speed_limit', 'is_signed_var': False, 'len': 7, 'name': 'FSD_VCU_MaxVehSpeedLmt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|127]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
  void set_p_fsd_vcu_maxvehspeedlmt(uint8_t* data, int fsd_vcu_maxvehspeedlmt);

  // config detail: {'bit': 8, 'description': 'Emergency_stop', 'enum': {0: 'FSD_VCU_EMERGSTOP_NO_EMERGENCY_STOP', 1: 'FSD_VCU_EMERGSTOP_EMERGENCY_STOP'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_EmergStop', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_emergstop(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType fsd_vcu_emergstop);

  // config detail: {'bit': 9, 'description': 'Target_gear', 'enum': {0: 'FSD_VCU_TARGEAR_N', 1: 'FSD_VCU_TARGEAR_D', 2: 'FSD_VCU_TARGEAR_R'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_TarGear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_targear(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType fsd_vcu_targear);

  // config detail: {'bit': 11, 'description': 'parking', 'enum': {0: 'FSD_VCU_PARK_PARKING', 1: 'FSD_VCU_PARK_RELEASE_PARKING'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_Park', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_park(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType fsd_vcu_park);

  // config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'FSD_VCU_RoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_fsd_vcu_roulingcounter(uint8_t* data, int fsd_vcu_roulingcounter);

  int fsd_vcu_tarvehrearangle(const std::uint8_t* bytes, const int32_t length) const;

  int fsd_vcu_brakepec(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType fsd_vcu_cmdsource(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType fsd_vcu_specialmode(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType fsd_vcu_steermode(const std::uint8_t* bytes, const int32_t length) const;

  double fsd_vcu_tarvehspeed(const std::uint8_t* bytes, const int32_t length) const;

  int fsd_vcu_tarvehfrontangle(const std::uint8_t* bytes, const int32_t length) const;

  int fsd_vcu_maxvehspeedlmt(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType fsd_vcu_emergstop(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType fsd_vcu_targear(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType fsd_vcu_park(const std::uint8_t* bytes, const int32_t length) const;

  int fsd_vcu_roulingcounter(const std::uint8_t* bytes, const int32_t length) const;

 private:
  int fsd_vcu_tarvehrearangle_;
  int fsd_vcu_brakepec_;
  Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType fsd_vcu_cmdsource_;
  Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType fsd_vcu_specialmode_;
  Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType fsd_vcu_steermode_;
  double fsd_vcu_tarvehspeed_;
  int fsd_vcu_tarvehfrontangle_;
  int fsd_vcu_maxvehspeedlmt_;
  Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType fsd_vcu_emergstop_;
  Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType fsd_vcu_targear_;
  Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType fsd_vcu_park_;
  int fsd_vcu_roulingcounter_;
};

}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo


