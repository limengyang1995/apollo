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

#include "modules/canbus_vehicle/middlecar/protocol/fsd_vcu_cmd2_6a2.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace middlecar {

using ::apollo::drivers::canbus::Byte;

const int32_t Fsdvcucmd26a2::ID = 0x6A2;

// public
Fsdvcucmd26a2::Fsdvcucmd26a2() { Reset(); }

uint32_t Fsdvcucmd26a2::GetPeriod() const {
  // TODO(All) : modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Fsdvcucmd26a2::Parse(const std::uint8_t* bytes, int32_t length,
                         Middlecar* chassis) const {
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_acceleration(fsd_vcu_acceleration(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_loadonline(fsd_vcu_loadonline(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_fsderrorlevel(fsd_vcu_fsderrorlevel(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_loaderrorlevel(fsd_vcu_loaderrorlevel(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_positionlamp(fsd_vcu_positionlamp(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_cameracleaning(fsd_vcu_cameracleaning(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_infraredlamp(fsd_vcu_infraredlamp(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_foglamp(fsd_vcu_foglamp(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_rearlamp(fsd_vcu_rearlamp(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_headlamp(fsd_vcu_headlamp(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_nearlylamp(fsd_vcu_nearlylamp(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_horn(fsd_vcu_horn(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_leftturnlamp(fsd_vcu_leftturnlamp(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_rightturnlamp(fsd_vcu_rightturnlamp(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_standbyenable(fsd_vcu_standbyenable(bytes, length));
  chassis->mutable_fsd_vcu_cmd2_6a2()->set_fsd_vcu_roulingcounter(fsd_vcu_roulingcounter(bytes, length));
}

void Fsdvcucmd26a2::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) : you should add the heartbeat manually
}

void Fsdvcucmd26a2::UpdateData(uint8_t* data) {
  set_p_fsd_vcu_acceleration(data, fsd_vcu_acceleration_);
  set_p_fsd_vcu_loadonline(data, fsd_vcu_loadonline_);
  set_p_fsd_vcu_fsderrorlevel(data, fsd_vcu_fsderrorlevel_);
  set_p_fsd_vcu_loaderrorlevel(data, fsd_vcu_loaderrorlevel_);
  set_p_fsd_vcu_positionlamp(data, fsd_vcu_positionlamp_);
  set_p_fsd_vcu_cameracleaning(data, fsd_vcu_cameracleaning_);
  set_p_fsd_vcu_infraredlamp(data, fsd_vcu_infraredlamp_);
  set_p_fsd_vcu_foglamp(data, fsd_vcu_foglamp_);
  set_p_fsd_vcu_rearlamp(data, fsd_vcu_rearlamp_);
  set_p_fsd_vcu_headlamp(data, fsd_vcu_headlamp_);
  set_p_fsd_vcu_nearlylamp(data, fsd_vcu_nearlylamp_);
  set_p_fsd_vcu_horn(data, fsd_vcu_horn_);
  set_p_fsd_vcu_leftturnlamp(data, fsd_vcu_leftturnlamp_);
  set_p_fsd_vcu_rightturnlamp(data, fsd_vcu_rightturnlamp_);
  set_p_fsd_vcu_standbyenable(data, fsd_vcu_standbyenable_);
  set_p_fsd_vcu_roulingcounter(data, fsd_vcu_roulingcounter_);
}

void Fsdvcucmd26a2::Reset() {
  // TODO(All) :  you should check this manually
  fsd_vcu_acceleration_ = 0.0;
  fsd_vcu_loadonline_ = Fsd_vcu_cmd2_6a2::FSD_VCU_LOADONLINE_OFFLINE;
  fsd_vcu_fsderrorlevel_ = Fsd_vcu_cmd2_6a2::FSD_VCU_FSDERRORLEVEL_NO_FAULT;
  fsd_vcu_loaderrorlevel_ = Fsd_vcu_cmd2_6a2::FSD_VCU_LOADERRORLEVEL_NO_FAULT;
  fsd_vcu_positionlamp_ = Fsd_vcu_cmd2_6a2::FSD_VCU_POSITIONLAMP_DISABLE;
  fsd_vcu_cameracleaning_ = Fsd_vcu_cmd2_6a2::FSD_VCU_CAMERACLEANING_DISABLE;
  fsd_vcu_infraredlamp_ = Fsd_vcu_cmd2_6a2::FSD_VCU_INFRAREDLAMP_DISABLE;
  fsd_vcu_foglamp_ = Fsd_vcu_cmd2_6a2::FSD_VCU_FOGLAMP_DISABLE;
  fsd_vcu_rearlamp_ = Fsd_vcu_cmd2_6a2::FSD_VCU_REARLAMP_DISABLE;
  fsd_vcu_headlamp_ = Fsd_vcu_cmd2_6a2::FSD_VCU_HEADLAMP_DISABLE;
  fsd_vcu_nearlylamp_ = Fsd_vcu_cmd2_6a2::FSD_VCU_NEARLYLAMP_DISABLE;
  fsd_vcu_horn_ = Fsd_vcu_cmd2_6a2::FSD_VCU_HORN_DISABLE;
  fsd_vcu_leftturnlamp_ = Fsd_vcu_cmd2_6a2::FSD_VCU_LEFTTURNLAMP_DISABLE;
  fsd_vcu_rightturnlamp_ = Fsd_vcu_cmd2_6a2::FSD_VCU_RIGHTTURNLAMP_DISABLE;
  fsd_vcu_standbyenable_ = Fsd_vcu_cmd2_6a2::FSD_VCU_STANDBYENABLE_DISABLE;
  fsd_vcu_roulingcounter_ = 0;
}

Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_acceleration(
    double fsd_vcu_acceleration) {
  fsd_vcu_acceleration_ = fsd_vcu_acceleration;
  return this;
 }

// config detail: {'bit': 40, 'description': 'Reserved_acceleration_control', 'is_signed_var': False, 'len': 16, 'name': 'FSD_VCU_Acceleration', 'offset': -5.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
void Fsdvcucmd26a2::set_p_fsd_vcu_acceleration(uint8_t* data,
    double fsd_vcu_acceleration) {
  fsd_vcu_acceleration = ProtocolData::BoundedValue(0.0, 0.0, fsd_vcu_acceleration);
  int x = (fsd_vcu_acceleration - -5.000000) / 0.100000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 5);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 6);
  to_set1.set_value(t, 0, 8);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_loadonline(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType fsd_vcu_loadonline) {
  fsd_vcu_loadonline_ = fsd_vcu_loadonline;
  return this;
 }

// config detail: {'bit': 16, 'description': 'Load_online_status', 'enum': {0: 'FSD_VCU_LOADONLINE_OFFLINE', 1: 'FSD_VCU_LOADONLINE_ONLINE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_LoadOnline', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_loadonline(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType fsd_vcu_loadonline) {
  int x = fsd_vcu_loadonline;

  Byte to_set(data + 2);
  to_set.set_value(x, 0, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_fsderrorlevel(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType fsd_vcu_fsderrorlevel) {
  fsd_vcu_fsderrorlevel_ = fsd_vcu_fsderrorlevel;
  return this;
 }

// config detail: {'bit': 13, 'description': 'FSD_fault_level', 'enum': {0: 'FSD_VCU_FSDERRORLEVEL_NO_FAULT', 1: 'FSD_VCU_FSDERRORLEVEL_MINOR_FAULT', 2: 'FSD_VCU_FSDERRORLEVEL_GENERAL_FAULT', 3: 'FSD_VCU_FSDERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_FSDErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_fsderrorlevel(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType fsd_vcu_fsderrorlevel) {
  int x = fsd_vcu_fsderrorlevel;

  Byte to_set(data + 1);
  to_set.set_value(x, 5, 2);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_loaderrorlevel(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType fsd_vcu_loaderrorlevel) {
  fsd_vcu_loaderrorlevel_ = fsd_vcu_loaderrorlevel;
  return this;
 }

// config detail: {'bit': 11, 'description': 'Load_fault_level', 'enum': {0: 'FSD_VCU_LOADERRORLEVEL_NO_FAULT', 1: 'FSD_VCU_LOADERRORLEVEL_MINOR_FAULT', 2: 'FSD_VCU_LOADERRORLEVEL_GENERAL_FAULT', 3: 'FSD_VCU_LOADERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_LoadErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_loaderrorlevel(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType fsd_vcu_loaderrorlevel) {
  int x = fsd_vcu_loaderrorlevel;

  Byte to_set(data + 1);
  to_set.set_value(x, 3, 2);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_positionlamp(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType fsd_vcu_positionlamp) {
  fsd_vcu_positionlamp_ = fsd_vcu_positionlamp;
  return this;
 }

// config detail: {'bit': 0, 'description': 'position_light', 'enum': {0: 'FSD_VCU_POSITIONLAMP_DISABLE', 1: 'FSD_VCU_POSITIONLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_PositionLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_positionlamp(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType fsd_vcu_positionlamp) {
  int x = fsd_vcu_positionlamp;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_cameracleaning(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType fsd_vcu_cameracleaning) {
  fsd_vcu_cameracleaning_ = fsd_vcu_cameracleaning;
  return this;
 }

// config detail: {'bit': 10, 'description': 'Camera_cleaning', 'enum': {0: 'FSD_VCU_CAMERACLEANING_DISABLE', 1: 'FSD_VCU_CAMERACLEANING_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_CameraCleaning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_cameracleaning(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType fsd_vcu_cameracleaning) {
  int x = fsd_vcu_cameracleaning;

  Byte to_set(data + 1);
  to_set.set_value(x, 2, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_infraredlamp(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType fsd_vcu_infraredlamp) {
  fsd_vcu_infraredlamp_ = fsd_vcu_infraredlamp;
  return this;
 }

// config detail: {'bit': 9, 'description': 'infrared_lamp', 'enum': {0: 'FSD_VCU_INFRAREDLAMP_DISABLE', 1: 'FSD_VCU_INFRAREDLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_InfraredLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_infraredlamp(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType fsd_vcu_infraredlamp) {
  int x = fsd_vcu_infraredlamp;

  Byte to_set(data + 1);
  to_set.set_value(x, 1, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_foglamp(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType fsd_vcu_foglamp) {
  fsd_vcu_foglamp_ = fsd_vcu_foglamp;
  return this;
 }

// config detail: {'bit': 1, 'description': 'fog_light', 'enum': {0: 'FSD_VCU_FOGLAMP_DISABLE', 1: 'FSD_VCU_FOGLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_FogLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_foglamp(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType fsd_vcu_foglamp) {
  int x = fsd_vcu_foglamp;

  Byte to_set(data + 0);
  to_set.set_value(x, 1, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_rearlamp(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType fsd_vcu_rearlamp) {
  fsd_vcu_rearlamp_ = fsd_vcu_rearlamp;
  return this;
 }

// config detail: {'bit': 8, 'description': 'reversing_light', 'enum': {0: 'FSD_VCU_REARLAMP_DISABLE', 1: 'FSD_VCU_REARLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_RearLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_rearlamp(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType fsd_vcu_rearlamp) {
  int x = fsd_vcu_rearlamp;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_headlamp(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType fsd_vcu_headlamp) {
  fsd_vcu_headlamp_ = fsd_vcu_headlamp;
  return this;
 }

// config detail: {'bit': 3, 'description': 'high_beam', 'enum': {0: 'FSD_VCU_HEADLAMP_DISABLE', 1: 'FSD_VCU_HEADLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_HeadLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_headlamp(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType fsd_vcu_headlamp) {
  int x = fsd_vcu_headlamp;

  Byte to_set(data + 0);
  to_set.set_value(x, 3, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_nearlylamp(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType fsd_vcu_nearlylamp) {
  fsd_vcu_nearlylamp_ = fsd_vcu_nearlylamp;
  return this;
 }

// config detail: {'bit': 4, 'description': 'low_beam', 'enum': {0: 'FSD_VCU_NEARLYLAMP_DISABLE', 1: 'FSD_VCU_NEARLYLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_NearlyLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_nearlylamp(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType fsd_vcu_nearlylamp) {
  int x = fsd_vcu_nearlylamp;

  Byte to_set(data + 0);
  to_set.set_value(x, 4, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_horn(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType fsd_vcu_horn) {
  fsd_vcu_horn_ = fsd_vcu_horn;
  return this;
 }

// config detail: {'bit': 5, 'description': 'horn', 'enum': {0: 'FSD_VCU_HORN_DISABLE', 1: 'FSD_VCU_HORN_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_Horn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_horn(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType fsd_vcu_horn) {
  int x = fsd_vcu_horn;

  Byte to_set(data + 0);
  to_set.set_value(x, 5, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_leftturnlamp(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType fsd_vcu_leftturnlamp) {
  fsd_vcu_leftturnlamp_ = fsd_vcu_leftturnlamp;
  return this;
 }

// config detail: {'bit': 6, 'description': 'Left_Turn_lamp', 'enum': {0: 'FSD_VCU_LEFTTURNLAMP_DISABLE', 1: 'FSD_VCU_LEFTTURNLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_LeftTurnLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_leftturnlamp(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType fsd_vcu_leftturnlamp) {
  int x = fsd_vcu_leftturnlamp;

  Byte to_set(data + 0);
  to_set.set_value(x, 6, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_rightturnlamp(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType fsd_vcu_rightturnlamp) {
  fsd_vcu_rightturnlamp_ = fsd_vcu_rightturnlamp;
  return this;
 }

// config detail: {'bit': 7, 'description': 'Right_turn_lamp', 'enum': {0: 'FSD_VCU_RIGHTTURNLAMP_DISABLE', 1: 'FSD_VCU_RIGHTTURNLAMP_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_RightTurnLamp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_rightturnlamp(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType fsd_vcu_rightturnlamp) {
  int x = fsd_vcu_rightturnlamp;

  Byte to_set(data + 0);
  to_set.set_value(x, 7, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_standbyenable(
    Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType fsd_vcu_standbyenable) {
  fsd_vcu_standbyenable_ = fsd_vcu_standbyenable;
  return this;
 }

// config detail: {'bit': 2, 'description': 'Standby_Enable', 'enum': {0: 'FSD_VCU_STANDBYENABLE_DISABLE', 1: 'FSD_VCU_STANDBYENABLE_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_StandbyEnable', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd26a2::set_p_fsd_vcu_standbyenable(uint8_t* data,
    Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType fsd_vcu_standbyenable) {
  int x = fsd_vcu_standbyenable;

  Byte to_set(data + 0);
  to_set.set_value(x, 2, 1);
}


Fsdvcucmd26a2* Fsdvcucmd26a2::set_fsd_vcu_roulingcounter(
    int fsd_vcu_roulingcounter) {
  fsd_vcu_roulingcounter_ = fsd_vcu_roulingcounter;
  return this;
 }

// config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'FSD_VCU_RoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Fsdvcucmd26a2::set_p_fsd_vcu_roulingcounter(uint8_t* data,
    int fsd_vcu_roulingcounter) {
  fsd_vcu_roulingcounter = ProtocolData::BoundedValue(0, 15, fsd_vcu_roulingcounter);
  int x = fsd_vcu_roulingcounter;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


double Fsdvcucmd26a2::fsd_vcu_acceleration(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -5.000000;
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType Fsdvcucmd26a2::fsd_vcu_loadonline(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_loadonlineType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType Fsdvcucmd26a2::fsd_vcu_fsderrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(5, 2);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_fsderrorlevelType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType Fsdvcucmd26a2::fsd_vcu_loaderrorlevel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(3, 2);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_loaderrorlevelType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType Fsdvcucmd26a2::fsd_vcu_positionlamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_positionlampType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType Fsdvcucmd26a2::fsd_vcu_cameracleaning(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_cameracleaningType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType Fsdvcucmd26a2::fsd_vcu_infraredlamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(1, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_infraredlampType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType Fsdvcucmd26a2::fsd_vcu_foglamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(1, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_foglampType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType Fsdvcucmd26a2::fsd_vcu_rearlamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_rearlampType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType Fsdvcucmd26a2::fsd_vcu_headlamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(3, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_headlampType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType Fsdvcucmd26a2::fsd_vcu_nearlylamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(4, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_nearlylampType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType Fsdvcucmd26a2::fsd_vcu_horn(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(5, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_hornType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType Fsdvcucmd26a2::fsd_vcu_leftturnlamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(6, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_leftturnlampType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType Fsdvcucmd26a2::fsd_vcu_rightturnlamp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(7, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_rightturnlampType>(x);
  return ret;
}

Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType Fsdvcucmd26a2::fsd_vcu_standbyenable(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(2, 1);

  Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType ret =  static_cast<Fsd_vcu_cmd2_6a2::Fsd_vcu_standbyenableType>(x);
  return ret;
}

int Fsdvcucmd26a2::fsd_vcu_roulingcounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}
}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo
