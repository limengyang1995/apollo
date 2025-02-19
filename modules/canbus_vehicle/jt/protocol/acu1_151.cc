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

#include "modules/canbus_vehicle/jt/protocol/acu1_151.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

const int32_t Acu1151::ID = 0x151;

// public
Acu1151::Acu1151() { Reset(); }

uint32_t Acu1151::GetPeriod() const {
  // TODO(All) : modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Acu1151::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_acu1_151()->set_acu1_steeringtargettorque(acu1_steeringtargettorque(bytes, length));
  chassis->mutable_acu1_151()->set_acu1_steeringtargetspeed(acu1_steeringtargetspeed(bytes, length));
  chassis->mutable_acu1_151()->set_acu1_steeringcontrolflag(acu1_steeringcontrolflag(bytes, length));
  chassis->mutable_acu1_151()->set_acu1_steeringtargetangle(acu1_steeringtargetangle(bytes, length));
  chassis->mutable_acu1_151()->set_acu1_livecounter(acu1_livecounter(bytes, length));
  chassis->mutable_acu1_151()->set_acu1_checksum(acu1_checksum(bytes, length));
}

void Acu1151::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) : you should add the heartbeat manually
}

void Acu1151::UpdateData(uint8_t* data) {
  set_p_acu1_steeringtargettorque(data, acu1_steeringtargettorque_);
  set_p_acu1_steeringtargetspeed(data, acu1_steeringtargetspeed_);
  set_p_acu1_steeringcontrolflag(data, acu1_steeringcontrolflag_);
  set_p_acu1_steeringtargetangle(data, acu1_steeringtargetangle_);
  set_p_acu1_livecounter(data, acu1_livecounter_);
  set_p_acu1_checksum(data, acu1_checksum_);
}

void Acu1151::Reset() {
  // TODO(All) :  you should check this manually
  acu1_steeringtargettorque_ = 0.0;
  acu1_steeringtargetspeed_ = 0;
  acu1_steeringcontrolflag_ = Acu1_151::ACU1_STEERINGCONTROLFLAG_NO_REQUEST;
  acu1_steeringtargetangle_ = 0.0;
  acu1_livecounter_ = 0;
  acu1_checksum_ = 0;
}

Acu1151* Acu1151::set_acu1_steeringtargettorque(
    double acu1_steeringtargettorque) {
  acu1_steeringtargettorque_ = acu1_steeringtargettorque;
  return this;
 }

// config detail: {'bit': 40, 'description': 'This signal is steering torque request', 'is_signed_var': False, 'len': 12, 'name': 'ACU1_SteeringTargetTorque', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
void Acu1151::set_p_acu1_steeringtargettorque(uint8_t* data,
    double acu1_steeringtargettorque) {
  acu1_steeringtargettorque = ProtocolData::BoundedValue(-20.0, 20.0, acu1_steeringtargettorque);
  int x = (acu1_steeringtargettorque - -20.000000) / 0.010000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 5);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xF;
  Byte to_set1(data + 6);
  to_set1.set_value(t, 0, 4);
}


Acu1151* Acu1151::set_acu1_steeringtargetspeed(
    int acu1_steeringtargetspeed) {
  acu1_steeringtargetspeed_ = acu1_steeringtargetspeed;
  return this;
 }

// config detail: {'bit': 24, 'description': 'This signal is steering speed request', 'is_signed_var': False, 'len': 9, 'name': 'ACU1_SteeringTargetSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
void Acu1151::set_p_acu1_steeringtargetspeed(uint8_t* data,
    int acu1_steeringtargetspeed) {
  acu1_steeringtargetspeed = ProtocolData::BoundedValue(0, 500, acu1_steeringtargetspeed);
  int x = acu1_steeringtargetspeed;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 3);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x1;
  Byte to_set1(data + 4);
  to_set1.set_value(t, 0, 1);
}


Acu1151* Acu1151::set_acu1_steeringcontrolflag(
    Acu1_151::Acu1_steeringcontrolflagType acu1_steeringcontrolflag) {
  acu1_steeringcontrolflag_ = acu1_steeringcontrolflag;
  return this;
 }

// config detail: {'bit': 56, 'description': 'This signal is the status of steering control request', 'enum': {0: 'ACU1_STEERINGCONTROLFLAG_NO_REQUEST', 1: 'ACU1_STEERINGCONTROLFLAG_REQUEST', 2: 'ACU1_STEERINGCONTROLFLAG_RESERVED', 3: 'ACU1_STEERINGCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_SteeringControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1151::set_p_acu1_steeringcontrolflag(uint8_t* data,
    Acu1_151::Acu1_steeringcontrolflagType acu1_steeringcontrolflag) {
  int x = acu1_steeringcontrolflag;

  Byte to_set(data + 7);
  to_set.set_value(x, 0, 2);
}


Acu1151* Acu1151::set_acu1_steeringtargetangle(
    double acu1_steeringtargetangle) {
  acu1_steeringtargetangle_ = acu1_steeringtargetangle;
  return this;
 }

// config detail: {'bit': 8, 'description': 'This signal is steering angle request', 'is_signed_var': False, 'len': 14, 'name': 'ACU1_SteeringTargetAngle', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
void Acu1151::set_p_acu1_steeringtargetangle(uint8_t* data,
    double acu1_steeringtargetangle) {
  acu1_steeringtargetangle = ProtocolData::BoundedValue(-600.0, 600.0, acu1_steeringtargetangle);
  int x = (acu1_steeringtargetangle - -600.000000) / 0.100000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 1);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x3F;
  Byte to_set1(data + 2);
  to_set1.set_value(t, 0, 6);
}


Acu1151* Acu1151::set_acu1_livecounter(
    int acu1_livecounter) {
  acu1_livecounter_ = acu1_livecounter;
  return this;
 }

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
void Acu1151::set_p_acu1_livecounter(uint8_t* data,
    int acu1_livecounter) {
  acu1_livecounter = ProtocolData::BoundedValue(0, 15, acu1_livecounter);
  int x = acu1_livecounter;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


Acu1151* Acu1151::set_acu1_checksum(
    int acu1_checksum) {
  acu1_checksum_ = acu1_checksum;
  return this;
 }

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
void Acu1151::set_p_acu1_checksum(uint8_t* data,
    int acu1_checksum) {
  acu1_checksum = ProtocolData::BoundedValue(0, 255, acu1_checksum);
  int x = acu1_checksum;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


double Acu1151::acu1_steeringtargettorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -20.000000;
  return ret;
}

int Acu1151::acu1_steeringtargetspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 1);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

Acu1_151::Acu1_steeringcontrolflagType Acu1151::acu1_steeringcontrolflag(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 2);

  Acu1_151::Acu1_steeringcontrolflagType ret =  static_cast<Acu1_151::Acu1_steeringcontrolflagType>(x);
  return ret;
}

double Acu1151::acu1_steeringtargetangle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -600.000000;
  return ret;
}

int Acu1151::acu1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

int Acu1151::acu1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
