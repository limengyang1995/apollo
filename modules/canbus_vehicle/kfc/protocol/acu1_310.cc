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

#include "modules/canbus_vehicle/kfc/protocol/acu1_310.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace kfc {

using ::apollo::drivers::canbus::Byte;

const int32_t Acu1310::ID = 0x310;

// public
Acu1310::Acu1310() { Reset(); }

uint32_t Acu1310::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Acu1310::Parse(const std::uint8_t* bytes, int32_t length,
                         Kfc* chassis) const {
  chassis->mutable_acu1_310()->set_acu1_targetbrakingposition(acu1_targetbrakingposition(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_targetthrottleposition(acu1_targetthrottleposition(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_drivingcontrolrequest(acu1_drivingcontrolrequest(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_standstillst(acu1_standstillst(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_targetsteeringspeed(acu1_targetsteeringspeed(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_targetsteeringangle(acu1_targetsteeringangle(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_targetgear(acu1_targetgear(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_livecounter(acu1_livecounter(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_checksum(acu1_checksum(bytes, length));
  chassis->mutable_acu1_310()->set_acu1_steeringcontrolrequest(acu1_steeringcontrolrequest(bytes, length));
}

void Acu1310::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Acu1310::UpdateData(uint8_t* data) {
  set_p_acu1_targetbrakingposition(data, acu1_targetbrakingposition_);
  set_p_acu1_targetthrottleposition(data, acu1_targetthrottleposition_);
  set_p_acu1_drivingcontrolrequest(data, acu1_drivingcontrolrequest_);
  set_p_acu1_standstillst(data, acu1_standstillst_);
  set_p_acu1_targetsteeringspeed(data, acu1_targetsteeringspeed_);
  set_p_acu1_targetsteeringangle(data, acu1_targetsteeringangle_);
  set_p_acu1_targetgear(data, acu1_targetgear_);
  set_p_acu1_livecounter(data, acu1_livecounter_);
  set_p_acu1_checksum(data, acu1_checksum_);
  set_p_acu1_steeringcontrolrequest(data, acu1_steeringcontrolrequest_);
}

void Acu1310::Reset() {
  // TODO(All) :  you should check this manually
  acu1_targetbrakingposition_ = 0;
  acu1_targetthrottleposition_ = 0;
  acu1_drivingcontrolrequest_ = Acu1_310::ACU1_DRIVINGCONTROLREQUEST_NO_REQUET;
  acu1_standstillst_ = Acu1_310::ACU1_STANDSTILLST_INACTIVE;
  acu1_targetsteeringspeed_ = 0;
  acu1_targetsteeringangle_ = 0;
  acu1_targetgear_ = Acu1_310::ACU1_TARGETGEAR_NO_REQUEST;
  acu1_livecounter_ = 0;
  acu1_checksum_ = 0;
  acu1_steeringcontrolrequest_ = Acu1_310::ACU1_STEERINGCONTROLREQUEST_NO_REQUET;
}

Acu1310* Acu1310::set_acu1_targetbrakingposition(
    int acu1_targetbrakingposition) {
  acu1_targetbrakingposition_ = acu1_targetbrakingposition;
  return this;
 }

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 7, 'name': 'ACU1_TargetBrakingPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
void Acu1310::set_p_acu1_targetbrakingposition(uint8_t* data,
    int acu1_targetbrakingposition) {
  acu1_targetbrakingposition = ProtocolData::BoundedValue(0, 100, acu1_targetbrakingposition);
  int x = acu1_targetbrakingposition;

  Byte to_set(data + 5);
  to_set.set_value(x, 0, 7);
}


Acu1310* Acu1310::set_acu1_targetthrottleposition(
    int acu1_targetthrottleposition) {
  acu1_targetthrottleposition_ = acu1_targetthrottleposition;
  return this;
 }

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 7, 'name': 'ACU1_TargetThrottlePosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
void Acu1310::set_p_acu1_targetthrottleposition(uint8_t* data,
    int acu1_targetthrottleposition) {
  acu1_targetthrottleposition = ProtocolData::BoundedValue(0, 100, acu1_targetthrottleposition);
  int x = acu1_targetthrottleposition;

  Byte to_set(data + 4);
  to_set.set_value(x, 0, 7);
}


Acu1310* Acu1310::set_acu1_drivingcontrolrequest(
    Acu1_310::Acu1_drivingcontrolrequestType acu1_drivingcontrolrequest) {
  acu1_drivingcontrolrequest_ = acu1_drivingcontrolrequest;
  return this;
 }

// config detail: {'bit': 30, 'enum': {0: 'ACU1_DRIVINGCONTROLREQUEST_NO_REQUET', 1: 'ACU1_DRIVINGCONTROLREQUEST_REQUEST', 2: 'ACU1_DRIVINGCONTROLREQUEST_RESERVED', 3: 'ACU1_DRIVINGCONTROLREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_DrivingControlRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1310::set_p_acu1_drivingcontrolrequest(uint8_t* data,
    Acu1_310::Acu1_drivingcontrolrequestType acu1_drivingcontrolrequest) {
  int x = acu1_drivingcontrolrequest;

  Byte to_set(data + 3);
  to_set.set_value(x, 6, 2);
}


Acu1310* Acu1310::set_acu1_standstillst(
    Acu1_310::Acu1_standstillstType acu1_standstillst) {
  acu1_standstillst_ = acu1_standstillst;
  return this;
 }

// config detail: {'bit': 59, 'enum': {0: 'ACU1_STANDSTILLST_INACTIVE', 1: 'ACU1_STANDSTILLST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU1_StandStillSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1310::set_p_acu1_standstillst(uint8_t* data,
    Acu1_310::Acu1_standstillstType acu1_standstillst) {
  int x = acu1_standstillst;

  Byte to_set(data + 7);
  to_set.set_value(x, 3, 1);
}


Acu1310* Acu1310::set_acu1_targetsteeringspeed(
    int acu1_targetsteeringspeed) {
  acu1_targetsteeringspeed_ = acu1_targetsteeringspeed;
  return this;
 }

// config detail: {'bit': 19, 'is_signed_var': False, 'len': 9, 'name': 'ACU1_TargetSteeringSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
void Acu1310::set_p_acu1_targetsteeringspeed(uint8_t* data,
    int acu1_targetsteeringspeed) {
  acu1_targetsteeringspeed = ProtocolData::BoundedValue(0, 500, acu1_targetsteeringspeed);
  int x = acu1_targetsteeringspeed;
  uint8_t t = 0;

  t = x & 0x1F;
  Byte to_set0(data + 2);
  to_set0.set_value(t, 3, 5);
  x >>= 5;

  t = x & 0xF;
  Byte to_set1(data + 3);
  to_set1.set_value(t, 0, 4);
}


Acu1310* Acu1310::set_acu1_targetsteeringangle(
    int acu1_targetsteeringangle) {
  acu1_targetsteeringangle_ = acu1_targetsteeringangle;
  return this;
 }

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 11, 'name': 'ACU1_TargetSteeringAngle', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
void Acu1310::set_p_acu1_targetsteeringangle(uint8_t* data,
    int acu1_targetsteeringangle) {
  acu1_targetsteeringangle = ProtocolData::BoundedValue(-600, 600, acu1_targetsteeringangle);
  int x = (acu1_targetsteeringangle - -600.000000);
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 1);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x7;
  Byte to_set1(data + 2);
  to_set1.set_value(t, 0, 3);
}


Acu1310* Acu1310::set_acu1_targetgear(
    Acu1_310::Acu1_targetgearType acu1_targetgear) {
  acu1_targetgear_ = acu1_targetgear;
  return this;
 }

// config detail: {'bit': 56, 'enum': {0: 'ACU1_TARGETGEAR_NO_REQUEST', 1: 'ACU1_TARGETGEAR_P', 2: 'ACU1_TARGETGEAR_D', 3: 'ACU1_TARGETGEAR_N', 4: 'ACU1_TARGETGEAR_R', 5: 'ACU1_TARGETGEAR_RESERVED', 6: 'ACU1_TARGETGEAR_RESERVED', 7: 'ACU1_TARGETGEAR_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU1_TargetGear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1310::set_p_acu1_targetgear(uint8_t* data,
    Acu1_310::Acu1_targetgearType acu1_targetgear) {
  int x = acu1_targetgear;

  Byte to_set(data + 7);
  to_set.set_value(x, 0, 3);
}


Acu1310* Acu1310::set_acu1_livecounter(
    int acu1_livecounter) {
  acu1_livecounter_ = acu1_livecounter;
  return this;
 }

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'ACU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu1310::set_p_acu1_livecounter(uint8_t* data,
    int acu1_livecounter) {
  acu1_livecounter = ProtocolData::BoundedValue(0, 15, acu1_livecounter);
  int x = acu1_livecounter;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


Acu1310* Acu1310::set_acu1_checksum(
    int acu1_checksum) {
  acu1_checksum_ = acu1_checksum;
  return this;
 }

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu1310::set_p_acu1_checksum(uint8_t* data,
    int acu1_checksum) {
  acu1_checksum = ProtocolData::BoundedValue(0, 255, acu1_checksum);
  int x = acu1_checksum;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


Acu1310* Acu1310::set_acu1_steeringcontrolrequest(
    Acu1_310::Acu1_steeringcontrolrequestType acu1_steeringcontrolrequest) {
  acu1_steeringcontrolrequest_ = acu1_steeringcontrolrequest;
  return this;
 }

// config detail: {'bit': 28, 'enum': {0: 'ACU1_STEERINGCONTROLREQUEST_NO_REQUET', 1: 'ACU1_STEERINGCONTROLREQUEST_REQUEST', 2: 'ACU1_STEERINGCONTROLREQUEST_RESERVED', 3: 'ACU1_STEERINGCONTROLREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_SteeringControlRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1310::set_p_acu1_steeringcontrolrequest(uint8_t* data,
    Acu1_310::Acu1_steeringcontrolrequestType acu1_steeringcontrolrequest) {
  int x = acu1_steeringcontrolrequest;

  Byte to_set(data + 3);
  to_set.set_value(x, 4, 2);
}


int Acu1310::acu1_targetbrakingposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 7);

  int ret = x;
  return ret;
}

int Acu1310::acu1_targetthrottleposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 7);

  int ret = x;
  return ret;
}

Acu1_310::Acu1_drivingcontrolrequestType Acu1310::acu1_drivingcontrolrequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(6, 2);

  Acu1_310::Acu1_drivingcontrolrequestType ret =  static_cast<Acu1_310::Acu1_drivingcontrolrequestType>(x);
  return ret;
}

Acu1_310::Acu1_standstillstType Acu1310::acu1_standstillst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(3, 1);

  Acu1_310::Acu1_standstillstType ret =  static_cast<Acu1_310::Acu1_standstillstType>(x);
  return ret;
}

int Acu1310::acu1_targetsteeringspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(3, 5);
  x <<= 5;
  x |= t;

  int ret = x;
  return ret;
}

int Acu1310::acu1_targetsteeringangle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x + -600.000000;
  return ret;
}

Acu1_310::Acu1_targetgearType Acu1310::acu1_targetgear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 3);

  Acu1_310::Acu1_targetgearType ret =  static_cast<Acu1_310::Acu1_targetgearType>(x);
  return ret;
}

int Acu1310::acu1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

int Acu1310::acu1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

Acu1_310::Acu1_steeringcontrolrequestType Acu1310::acu1_steeringcontrolrequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  Acu1_310::Acu1_steeringcontrolrequestType ret =  static_cast<Acu1_310::Acu1_steeringcontrolrequestType>(x);
  return ret;
}
}  // namespace kfc
}  // namespace canbus
}  // namespace apollo
