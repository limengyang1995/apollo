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

#include "modules/canbus_vehicle/jt/protocol/acu2_152.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

const int32_t Acu2152::ID = 0x152;

// public
Acu2152::Acu2152() { Reset(); }

uint32_t Acu2152::GetPeriod() const {
  // TODO(All) : modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Acu2152::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_acu2_152()->set_acu2_drivingtargetspeed(acu2_drivingtargetspeed(bytes, length));
  chassis->mutable_acu2_152()->set_acu2_drivingtargettorque(acu2_drivingtargettorque(bytes, length));
  chassis->mutable_acu2_152()->set_acu2_drivingtargetthrottle(acu2_drivingtargetthrottle(bytes, length));
  chassis->mutable_acu2_152()->set_acu2_drivingcontrolflag(acu2_drivingcontrolflag(bytes, length));
  chassis->mutable_acu2_152()->set_acu2_drivingtargetacceleration(acu2_drivingtargetacceleration(bytes, length));
  chassis->mutable_acu2_152()->set_acu2_livecounter(acu2_livecounter(bytes, length));
  chassis->mutable_acu2_152()->set_acu2_checksum(acu2_checksum(bytes, length));
}

void Acu2152::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) : you should add the heartbeat manually
}

void Acu2152::UpdateData(uint8_t* data) {
  set_p_acu2_drivingtargetspeed(data, acu2_drivingtargetspeed_);
  set_p_acu2_drivingtargettorque(data, acu2_drivingtargettorque_);
  set_p_acu2_drivingtargetthrottle(data, acu2_drivingtargetthrottle_);
  set_p_acu2_drivingcontrolflag(data, acu2_drivingcontrolflag_);
  set_p_acu2_drivingtargetacceleration(data, acu2_drivingtargetacceleration_);
  set_p_acu2_livecounter(data, acu2_livecounter_);
  set_p_acu2_checksum(data, acu2_checksum_);
}

void Acu2152::Reset() {
  // TODO(All) :  you should check this manually
  acu2_drivingtargetspeed_ = 0.0;
  acu2_drivingtargettorque_ = 0.0;
  acu2_drivingtargetthrottle_ = 0.0;
  acu2_drivingcontrolflag_ = Acu2_152::ACU2_DRIVINGCONTROLFLAG_NO_REQUEST;
  acu2_drivingtargetacceleration_ = 0.0;
  acu2_livecounter_ = 0;
  acu2_checksum_ = 0;
}

Acu2152* Acu2152::set_acu2_drivingtargetspeed(
    double acu2_drivingtargetspeed) {
  acu2_drivingtargetspeed_ = acu2_drivingtargetspeed;
  return this;
 }

// config detail: {'bit': 18, 'is_signed_var': False, 'len': 6, 'name': 'ACU2_DrivingTargetSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|126]', 'physical_unit': 'km/h', 'precision': 2.0, 'type': 'double'}
void Acu2152::set_p_acu2_drivingtargetspeed(uint8_t* data,
    double acu2_drivingtargetspeed) {
  acu2_drivingtargetspeed = ProtocolData::BoundedValue(0.0, 126.0, acu2_drivingtargetspeed);
  int x = acu2_drivingtargetspeed / 2.000000;

  Byte to_set(data + 2);
  to_set.set_value(x, 2, 6);
}


Acu2152* Acu2152::set_acu2_drivingtargettorque(
    double acu2_drivingtargettorque) {
  acu2_drivingtargettorque_ = acu2_drivingtargettorque;
  return this;
 }

// config detail: {'bit': 40, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 11, 'name': 'ACU2_DrivingTargetTorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|350]', 'physical_unit': 'Nm', 'precision': 0.25, 'type': 'double'}
void Acu2152::set_p_acu2_drivingtargettorque(uint8_t* data,
    double acu2_drivingtargettorque) {
  acu2_drivingtargettorque = ProtocolData::BoundedValue(0.0, 350.0, acu2_drivingtargettorque);
  int x = acu2_drivingtargettorque / 0.250000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 5);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x7;
  Byte to_set1(data + 6);
  to_set1.set_value(t, 0, 3);
}


Acu2152* Acu2152::set_acu2_drivingtargetthrottle(
    double acu2_drivingtargetthrottle) {
  acu2_drivingtargetthrottle_ = acu2_drivingtargetthrottle;
  return this;
 }

// config detail: {'bit': 24, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 10, 'name': 'ACU2_DrivingTargetThrottle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
void Acu2152::set_p_acu2_drivingtargetthrottle(uint8_t* data,
    double acu2_drivingtargetthrottle) {
  acu2_drivingtargetthrottle = ProtocolData::BoundedValue(0.0, 100.0, acu2_drivingtargetthrottle);
  int x = acu2_drivingtargetthrottle / 0.100000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 3);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x3;
  Byte to_set1(data + 4);
  to_set1.set_value(t, 0, 2);
}


Acu2152* Acu2152::set_acu2_drivingcontrolflag(
    Acu2_152::Acu2_drivingcontrolflagType acu2_drivingcontrolflag) {
  acu2_drivingcontrolflag_ = acu2_drivingcontrolflag;
  return this;
 }

// config detail: {'bit': 56, 'description': 'This signal is the status of the driving control request', 'enum': {0: 'ACU2_DRIVINGCONTROLFLAG_NO_REQUEST', 1: 'ACU2_DRIVINGCONTROLFLAG_REQUESTTHROTTLE', 2: 'ACU2_DRIVINGCONTROLFLAG_RESERVEDSPEED', 3: 'ACU2_DRIVINGCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_DrivingControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu2152::set_p_acu2_drivingcontrolflag(uint8_t* data,
    Acu2_152::Acu2_drivingcontrolflagType acu2_drivingcontrolflag) {
  int x = acu2_drivingcontrolflag;

  Byte to_set(data + 7);
  to_set.set_value(x, 0, 2);
}


Acu2152* Acu2152::set_acu2_drivingtargetacceleration(
    double acu2_drivingtargetacceleration) {
  acu2_drivingtargetacceleration_ = acu2_drivingtargetacceleration;
  return this;
 }

// config detail: {'bit': 8, 'description': 'This signal is acceleration pedal position request', 'is_signed_var': False, 'len': 10, 'name': 'ACU2_DrivingTargetAcceleration', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
void Acu2152::set_p_acu2_drivingtargetacceleration(uint8_t* data,
    double acu2_drivingtargetacceleration) {
  acu2_drivingtargetacceleration = ProtocolData::BoundedValue(0.0, 10.0, acu2_drivingtargetacceleration);
  int x = acu2_drivingtargetacceleration / 0.010000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 1);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x3;
  Byte to_set1(data + 2);
  to_set1.set_value(t, 0, 2);
}


Acu2152* Acu2152::set_acu2_livecounter(
    int acu2_livecounter) {
  acu2_livecounter_ = acu2_livecounter;
  return this;
 }

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
void Acu2152::set_p_acu2_livecounter(uint8_t* data,
    int acu2_livecounter) {
  acu2_livecounter = ProtocolData::BoundedValue(0, 15, acu2_livecounter);
  int x = acu2_livecounter;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


Acu2152* Acu2152::set_acu2_checksum(
    int acu2_checksum) {
  acu2_checksum_ = acu2_checksum;
  return this;
 }

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
void Acu2152::set_p_acu2_checksum(uint8_t* data,
    int acu2_checksum) {
  acu2_checksum = ProtocolData::BoundedValue(0, 255, acu2_checksum);
  int x = acu2_checksum;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


double Acu2152::acu2_drivingtargetspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 6);

  double ret = x * 2.000000;
  return ret;
}

double Acu2152::acu2_drivingtargettorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.250000;
  return ret;
}

double Acu2152::acu2_drivingtargetthrottle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

Acu2_152::Acu2_drivingcontrolflagType Acu2152::acu2_drivingcontrolflag(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 2);

  Acu2_152::Acu2_drivingcontrolflagType ret =  static_cast<Acu2_152::Acu2_drivingcontrolflagType>(x);
  return ret;
}

double Acu2152::acu2_drivingtargetacceleration(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

int Acu2152::acu2_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

int Acu2152::acu2_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
