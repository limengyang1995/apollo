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

#include "modules/canbus_vehicle/jt/protocol/acs1_20c.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Acs120c::Acs120c() {}
const int32_t Acs120c::ID = 0x20C;

void Acs120c::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_acs1_20c()->set_acs1_workmode(acs1_workmode(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_steeringstatemachine(acs1_steeringstatemachine(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_gearstatemachine(acs1_gearstatemachine(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_drivingstatemachine(acs1_drivingstatemachine(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_brakingstatemachine(acs1_brakingstatemachine(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_geartakeoverst(acs1_geartakeoverst(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_gearfailurest(acs1_gearfailurest(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_gearautocontrolst(acs1_gearautocontrolst(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_steeringtakeoverst(acs1_steeringtakeoverst(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_steeringfailurest(acs1_steeringfailurest(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_steeringautocontrolst(acs1_steeringautocontrolst(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_livecounter(acs1_livecounter(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_drivingtakeoverst(acs1_drivingtakeoverst(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_drivingfailurest(acs1_drivingfailurest(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_drivingautocontrolst(acs1_drivingautocontrolst(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_checksum(acs1_checksum(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_brakingtakeoverst(acs1_brakingtakeoverst(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_brakingfailurest(acs1_brakingfailurest(bytes, length));
  chassis->mutable_acs1_20c()->set_acs1_brakingautocontrolst(acs1_brakingautocontrolst(bytes, length));
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 2, 'name': 'acs1_workmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Acs120c::acs1_workmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 12, 'description': 'This signal indicates the state machine of steering.', 'is_signed_var': False, 'len': 4, 'name': 'acs1_steeringstatemachine', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'value', 'precision': 1.0, 'type': 'int'}
int Acs120c::acs1_steeringstatemachine(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 36, 'description': 'This signal indicates the state machine of gear.', 'is_signed_var': False, 'len': 4, 'name': 'acs1_gearstatemachine', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'value', 'precision': 1.0, 'type': 'int'}
int Acs120c::acs1_gearstatemachine(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 20, 'description': 'This signal indicates the state machine of driving.', 'enum': {0: 'ACS1_DRIVINGSTATEMACHINE_IDLE', 1: 'ACS1_DRIVINGSTATEMACHINE_CHECK', 2: 'ACS1_DRIVINGSTATEMACHINE_MANUAL', 3: 'ACS1_DRIVINGSTATEMACHINE_REMOTE', 4: 'ACS1_DRIVINGSTATEMACHINE_IPC', 5: 'ACS1_DRIVINGSTATEMACHINE_INTERVENTION', 6: 'ACS1_DRIVINGSTATEMACHINE_EMERGENCY', 7: 'ACS1_DRIVINGSTATEMACHINE_ERROR'}, 'is_signed_var': False, 'len': 4, 'name': 'acs1_drivingstatemachine', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'value', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_drivingstatemachineType Acs120c::acs1_drivingstatemachine(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 4);

  Acs1_20c::Acs1_drivingstatemachineType ret =  static_cast<Acs1_20c::Acs1_drivingstatemachineType>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': 'This signal indicates the state machine of braking.', 'is_signed_var': False, 'len': 4, 'name': 'acs1_brakingstatemachine', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'value', 'precision': 1.0, 'type': 'int'}
int Acs120c::acs1_brakingstatemachine(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 34, 'description': 'This signal indicates the gear is under maunal taking over.', 'enum': {0: 'ACS1_GEARTAKEOVERST_INACTIVE', 1: 'ACS1_GEARTAKEOVERST_TEMP_ACTIVE', 2: 'ACS1_GEARTAKEOVERST_ACTIVE', 3: 'ACS1_GEARTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_geartakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_geartakeoverstType Acs120c::acs1_geartakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(2, 2);

  Acs1_20c::Acs1_geartakeoverstType ret =  static_cast<Acs1_20c::Acs1_geartakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 46, 'description': 'This signal indicates the gear is in fault status', 'enum': {0: 'ACS1_GEARFAILUREST_NO_FAIL', 1: 'ACS1_GEARFAILUREST_EGSM_FAIL', 2: 'ACS1_GEARFAILUREST_HCU_FAIL', 3: 'ACS1_GEARFAILUREST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_gearfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_gearfailurestType Acs120c::acs1_gearfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(6, 2);

  Acs1_20c::Acs1_gearfailurestType ret =  static_cast<Acs1_20c::Acs1_gearfailurestType>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': 'This signal indicates the gear is under automatical control or not.', 'enum': {0: 'ACS1_GEARAUTOCONTROLST_INACTIVE', 1: 'ACS1_GEARAUTOCONTROLST_ACTIVE', 2: 'ACS1_GEARAUTOCONTROLST_RESERVED', 3: 'ACS1_GEARAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_gearautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_gearautocontrolstType Acs120c::acs1_gearautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Acs1_20c::Acs1_gearautocontrolstType ret =  static_cast<Acs1_20c::Acs1_gearautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': 'This signal indicates the steering is under maunal taking over.', 'enum': {0: 'ACS1_STEERINGTAKEOVERST_INACTIVE', 1: 'ACS1_STEERINGTAKEOVERST_TEMP_ACTIVE', 2: 'ACS1_STEERINGTAKEOVERST_ACTIVE', 3: 'ACS1_STEERINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_steeringtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_steeringtakeoverstType Acs120c::acs1_steeringtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 2);

  Acs1_20c::Acs1_steeringtakeoverstType ret =  static_cast<Acs1_20c::Acs1_steeringtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': 'This signal indicates the steering is in fault status', 'enum': {0: 'ACS1_STEERINGFAILUREST_NO_FAIL', 1: 'ACS1_STEERINGFAILUREST_EPS_FAIL', 2: 'ACS1_STEERINGFAILUREST_SAS_FAIL', 3: 'ACS1_STEERINGFAILUREST_APA_FAIL'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_steeringfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_steeringfailurestType Acs120c::acs1_steeringfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 2);

  Acs1_20c::Acs1_steeringfailurestType ret =  static_cast<Acs1_20c::Acs1_steeringfailurestType>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal indicates the steering is under automatical control or not.', 'enum': {0: 'ACS1_STEERINGAUTOCONTROLST_INACTIVE', 1: 'ACS1_STEERINGAUTOCONTROLST_ACTIVE', 2: 'ACS1_STEERINGAUTOCONTROLST_RESERVED', 3: 'ACS1_STEERINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_steeringautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_steeringautocontrolstType Acs120c::acs1_steeringautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Acs1_20c::Acs1_steeringautocontrolstType ret =  static_cast<Acs1_20c::Acs1_steeringautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'acs1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Acs120c::acs1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 18, 'description': 'This signal indicates the driving is under maunal taking over.', 'enum': {0: 'ACS1_DRIVINGTAKEOVERST_INACTIVE', 1: 'ACS1_DRIVINGTAKEOVERST_TEMP_ACTIVE', 2: 'ACS1_DRIVINGTAKEOVERST_ACTIVE', 3: 'ACS1_DRIVINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_drivingtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_drivingtakeoverstType Acs120c::acs1_drivingtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 2);

  Acs1_20c::Acs1_drivingtakeoverstType ret =  static_cast<Acs1_20c::Acs1_drivingtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 42, 'description': 'This signal indicates the driving is in fault status', 'enum': {0: 'ACS1_DRIVINGFAILUREST_NO_FAIL', 1: 'ACS1_DRIVINGFAILUREST_HCU_FAIL', 2: 'ACS1_DRIVINGFAILUREST_RESERVED', 3: 'ACS1_DRIVINGFAILUREST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_drivingfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_drivingfailurestType Acs120c::acs1_drivingfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(2, 2);

  Acs1_20c::Acs1_drivingfailurestType ret =  static_cast<Acs1_20c::Acs1_drivingfailurestType>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': 'This signal indicates the driving is under automatical control or not.', 'enum': {0: 'ACS1_DRIVINGAUTOCONTROLST_INACTIVE', 1: 'ACS1_DRIVINGAUTOCONTROLST_ACTIVE', 2: 'ACS1_DRIVINGAUTOCONTROLST_RESERVED', 3: 'ACS1_DRIVINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_drivingautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_drivingautocontrolstType Acs120c::acs1_drivingautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Acs1_20c::Acs1_drivingautocontrolstType ret =  static_cast<Acs1_20c::Acs1_drivingautocontrolstType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'acs1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Acs120c::acs1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 26, 'description': 'This signal indicates the braking is under maunal taking over.', 'enum': {0: 'ACS1_BRAKINGTAKEOVERST_INACTIVE', 1: 'ACS1_BRAKINGTAKEOVERST_TEMP_ACTIVE', 2: 'ACS1_BRAKINGTAKEOVERST_ACTIVE', 3: 'ACS1_BRAKINGTAKEOVERST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_brakingtakeoverst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_brakingtakeoverstType Acs120c::acs1_brakingtakeoverst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(2, 2);

  Acs1_20c::Acs1_brakingtakeoverstType ret =  static_cast<Acs1_20c::Acs1_brakingtakeoverstType>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': 'This signal indicates the braking is in fault status', 'enum': {0: 'ACS1_BRAKINGFAILUREST_NO_FAIL', 1: 'ACS1_BRAKINGFAILUREST_ESP_FAIL', 2: 'ACS1_BRAKINGFAILUREST_SS_FAIL', 3: 'ACS1_BRAKINGFAILUREST_HCU_FAIL'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_brakingfailurest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_brakingfailurestType Acs120c::acs1_brakingfailurest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 2);

  Acs1_20c::Acs1_brakingfailurestType ret =  static_cast<Acs1_20c::Acs1_brakingfailurestType>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': 'This signal indicates the braking is under automatical control or not.', 'enum': {0: 'ACS1_BRAKINGAUTOCONTROLST_INACTIVE', 1: 'ACS1_BRAKINGAUTOCONTROLST_ACTIVE', 2: 'ACS1_BRAKINGAUTOCONTROLST_RESERVED', 3: 'ACS1_BRAKINGAUTOCONTROLST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acs1_brakingautocontrolst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acs1_20c::Acs1_brakingautocontrolstType Acs120c::acs1_brakingautocontrolst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 2);

  Acs1_20c::Acs1_brakingautocontrolstType ret =  static_cast<Acs1_20c::Acs1_brakingautocontrolstType>(x);
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
