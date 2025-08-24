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

class Fsdvcucmd26a2 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Middlecar> {
 public:
  static const int32_t ID;

  Fsdvcucmd26a2();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Middlecar* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 40, 'description': 'Reserved_acceleration_control', 'is_signed_var': False, 'len': 16, 'name': 'FSD_VCU_Acceleration', 'offset': -5.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
  Fsdvcucmd26a2* set_fsd_vcu_acceleration(double fsd_vcu_acceleration);

  // config detail: {'bit': 16, 'description': 'Load_online_status', 'enum': {0: 'FSD_VCU_LOADONLINE_OFFLINE', 1: 'FSD_VCU_LOADONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_LoadOnline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_loadonline(Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType fsd_vcu_loadonline);

  // config detail: {'bit': 13, 'description': 'FSD_fault_level', 'enum': {0: 'FSD_VCU_FSDERRORLEVEL_NO_FAULT', 1: 'FSD_VCU_FSDERRORLEVEL_MINOR_FAULT', 2: 'FSD_VCU_FSDERRORLEVEL_GENERAL_FAULT', 3: 'FSD_VCU_FSDERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_FSDErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_fsderrorlevel(Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType fsd_vcu_fsderrorlevel);

  // config detail: {'bit': 11, 'description': 'Load_fault_level', 'enum': {0: 'FSD_VCU_LOADERRORLEVEL_NO_FAULT', 1: 'FSD_VCU_LOADERRORLEVEL_MINOR_FAULT', 2: 'FSD_VCU_LOADERRORLEVEL_GENERAL_FAULT', 3: 'FSD_VCU_LOADERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_LoadErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_loaderrorlevel(Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType fsd_vcu_loaderrorlevel);

  // config detail: {'bit': 0, 'description': 'position_light', 'enum': {0: 'FSD_VCU_POSITIONLAMP_DISABLE', 1: 'FSD_VCU_POSITIONLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_PositionLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_positionlamp(Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType fsd_vcu_positionlamp);

  // config detail: {'bit': 10, 'description': 'Camera_cleaning', 'enum': {0: 'FSD_VCU_CAMERACLEANING_DISABLE', 1: 'FSD_VCU_CAMERACLEANING_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_CameraCleaning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_cameracleaning(Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType fsd_vcu_cameracleaning);

  // config detail: {'bit': 9, 'description': 'infrared_lamp', 'enum': {0: 'FSD_VCU_INFRAREDLAMP_DISABLE', 1: 'FSD_VCU_INFRAREDLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_InfraredLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_infraredlamp(Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType fsd_vcu_infraredlamp);

  // config detail: {'bit': 1, 'description': 'fog_light', 'enum': {0: 'FSD_VCU_FOGLAMP_DISABLE', 1: 'FSD_VCU_FOGLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_FogLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_foglamp(Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType fsd_vcu_foglamp);

  // config detail: {'bit': 8, 'description': 'reversing_light', 'enum': {0: 'FSD_VCU_REARLAMP_DISABLE', 1: 'FSD_VCU_REARLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_RearLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_rearlamp(Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType fsd_vcu_rearlamp);

  // config detail: {'bit': 3, 'description': 'high_beam', 'enum': {0: 'FSD_VCU_HEADLAMP_DISABLE', 1: 'FSD_VCU_HEADLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_HeadLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_headlamp(Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType fsd_vcu_headlamp);

  // config detail: {'bit': 4, 'description': 'low_beam', 'enum': {0: 'FSD_VCU_NEARLYLAMP_DISABLE', 1: 'FSD_VCU_NEARLYLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_NearlyLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_nearlylamp(Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType fsd_vcu_nearlylamp);

  // config detail: {'bit': 5, 'description': 'horn', 'enum': {0: 'FSD_VCU_HORN_DISABLE', 1: 'FSD_VCU_HORN_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_Horn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_horn(Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType fsd_vcu_horn);

  // config detail: {'bit': 6, 'description': 'Left_Turn_lamp', 'enum': {0: 'FSD_VCU_LEFTTURNLAMP_DISABLE', 1: 'FSD_VCU_LEFTTURNLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_LeftTurnLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_leftturnlamp(Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType fsd_vcu_leftturnlamp);

  // config detail: {'bit': 7, 'description': 'Right_turn_lamp', 'enum': {0: 'FSD_VCU_RIGHTTURNLAMP_DISABLE', 1: 'FSD_VCU_RIGHTTURNLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_RightTurnLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_rightturnlamp(Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType fsd_vcu_rightturnlamp);

  // config detail: {'bit': 2, 'description': 'Standby_Enable', 'enum': {0: 'FSD_VCU_STANDBYENABLE_DISABLE', 1: 'FSD_VCU_STANDBYENABLE_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_StandbyEnable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Fsdvcucmd26a2* set_fsd_vcu_standbyenable(Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType fsd_vcu_standbyenable);

  // config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'FSD_VCU_RoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Fsdvcucmd26a2* set_fsd_vcu_roulingcounter(int fsd_vcu_roulingcounter);

 private:

  // config detail: {'bit': 40, 'description': 'Reserved_acceleration_control', 'is_signed_var': False, 'len': 16, 'name': 'FSD_VCU_Acceleration', 'offset': -5.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
  void set_p_fsd_vcu_acceleration(uint8_t* data, double fsd_vcu_acceleration);

  // config detail: {'bit': 16, 'description': 'Load_online_status', 'enum': {0: 'FSD_VCU_LOADONLINE_OFFLINE', 1: 'FSD_VCU_LOADONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_LoadOnline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_loadonline(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType fsd_vcu_loadonline);

  // config detail: {'bit': 13, 'description': 'FSD_fault_level', 'enum': {0: 'FSD_VCU_FSDERRORLEVEL_NO_FAULT', 1: 'FSD_VCU_FSDERRORLEVEL_MINOR_FAULT', 2: 'FSD_VCU_FSDERRORLEVEL_GENERAL_FAULT', 3: 'FSD_VCU_FSDERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_FSDErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_fsderrorlevel(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType fsd_vcu_fsderrorlevel);

  // config detail: {'bit': 11, 'description': 'Load_fault_level', 'enum': {0: 'FSD_VCU_LOADERRORLEVEL_NO_FAULT', 1: 'FSD_VCU_LOADERRORLEVEL_MINOR_FAULT', 2: 'FSD_VCU_LOADERRORLEVEL_GENERAL_FAULT', 3: 'FSD_VCU_LOADERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_LoadErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_loaderrorlevel(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType fsd_vcu_loaderrorlevel);

  // config detail: {'bit': 0, 'description': 'position_light', 'enum': {0: 'FSD_VCU_POSITIONLAMP_DISABLE', 1: 'FSD_VCU_POSITIONLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_PositionLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_positionlamp(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType fsd_vcu_positionlamp);

  // config detail: {'bit': 10, 'description': 'Camera_cleaning', 'enum': {0: 'FSD_VCU_CAMERACLEANING_DISABLE', 1: 'FSD_VCU_CAMERACLEANING_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_CameraCleaning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_cameracleaning(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType fsd_vcu_cameracleaning);

  // config detail: {'bit': 9, 'description': 'infrared_lamp', 'enum': {0: 'FSD_VCU_INFRAREDLAMP_DISABLE', 1: 'FSD_VCU_INFRAREDLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_InfraredLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_infraredlamp(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType fsd_vcu_infraredlamp);

  // config detail: {'bit': 1, 'description': 'fog_light', 'enum': {0: 'FSD_VCU_FOGLAMP_DISABLE', 1: 'FSD_VCU_FOGLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_FogLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_foglamp(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType fsd_vcu_foglamp);

  // config detail: {'bit': 8, 'description': 'reversing_light', 'enum': {0: 'FSD_VCU_REARLAMP_DISABLE', 1: 'FSD_VCU_REARLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_RearLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_rearlamp(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType fsd_vcu_rearlamp);

  // config detail: {'bit': 3, 'description': 'high_beam', 'enum': {0: 'FSD_VCU_HEADLAMP_DISABLE', 1: 'FSD_VCU_HEADLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_HeadLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_headlamp(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType fsd_vcu_headlamp);

  // config detail: {'bit': 4, 'description': 'low_beam', 'enum': {0: 'FSD_VCU_NEARLYLAMP_DISABLE', 1: 'FSD_VCU_NEARLYLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_NearlyLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_nearlylamp(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType fsd_vcu_nearlylamp);

  // config detail: {'bit': 5, 'description': 'horn', 'enum': {0: 'FSD_VCU_HORN_DISABLE', 1: 'FSD_VCU_HORN_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_Horn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_horn(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType fsd_vcu_horn);

  // config detail: {'bit': 6, 'description': 'Left_Turn_lamp', 'enum': {0: 'FSD_VCU_LEFTTURNLAMP_DISABLE', 1: 'FSD_VCU_LEFTTURNLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_LeftTurnLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_leftturnlamp(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType fsd_vcu_leftturnlamp);

  // config detail: {'bit': 7, 'description': 'Right_turn_lamp', 'enum': {0: 'FSD_VCU_RIGHTTURNLAMP_DISABLE', 1: 'FSD_VCU_RIGHTTURNLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_RightTurnLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_rightturnlamp(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType fsd_vcu_rightturnlamp);

  // config detail: {'bit': 2, 'description': 'Standby_Enable', 'enum': {0: 'FSD_VCU_STANDBYENABLE_DISABLE', 1: 'FSD_VCU_STANDBYENABLE_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_StandbyEnable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fsd_vcu_standbyenable(uint8_t* data, Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType fsd_vcu_standbyenable);

  // config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'FSD_VCU_RoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_fsd_vcu_roulingcounter(uint8_t* data, int fsd_vcu_roulingcounter);

  double fsd_vcu_acceleration(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType fsd_vcu_loadonline(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType fsd_vcu_fsderrorlevel(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType fsd_vcu_loaderrorlevel(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType fsd_vcu_positionlamp(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType fsd_vcu_cameracleaning(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType fsd_vcu_infraredlamp(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType fsd_vcu_foglamp(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType fsd_vcu_rearlamp(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType fsd_vcu_headlamp(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType fsd_vcu_nearlylamp(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType fsd_vcu_horn(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType fsd_vcu_leftturnlamp(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType fsd_vcu_rightturnlamp(const std::uint8_t* bytes, const int32_t length) const;

  Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType fsd_vcu_standbyenable(const std::uint8_t* bytes, const int32_t length) const;

  int fsd_vcu_roulingcounter(const std::uint8_t* bytes, const int32_t length) const;

 private:
  double fsd_vcu_acceleration_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType fsd_vcu_loadonline_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType fsd_vcu_fsderrorlevel_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType fsd_vcu_loaderrorlevel_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType fsd_vcu_positionlamp_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType fsd_vcu_cameracleaning_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType fsd_vcu_infraredlamp_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType fsd_vcu_foglamp_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType fsd_vcu_rearlamp_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType fsd_vcu_headlamp_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType fsd_vcu_nearlylamp_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType fsd_vcu_horn_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType fsd_vcu_leftturnlamp_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType fsd_vcu_rightturnlamp_;
  Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType fsd_vcu_standbyenable_;
  int fsd_vcu_roulingcounter_;
};

}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo


