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

#include "modules/canbus_vehicle/jt/protocol/acu3_153.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

const int32_t Acu3153::ID = 0x153;

// public
Acu3153::Acu3153() { Reset(); }

uint32_t Acu3153::GetPeriod() const {
  // TODO(All) : modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Acu3153::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_acu3_153()->set_acu3_brakingtargetposition(acu3_brakingtargetposition(bytes, length));
  chassis->mutable_acu3_153()->set_acu3_epbcontrolflag(acu3_epbcontrolflag(bytes, length));
  chassis->mutable_acu3_153()->set_acu3_geartarget(acu3_geartarget(bytes, length));
  chassis->mutable_acu3_153()->set_acu3_gearcontrolflag(acu3_gearcontrolflag(bytes, length));
  chassis->mutable_acu3_153()->set_acu3_brakingtargetpressure(acu3_brakingtargetpressure(bytes, length));
  chassis->mutable_acu3_153()->set_acu3_brakingtargetdeceleration(acu3_brakingtargetdeceleration(bytes, length));
  chassis->mutable_acu3_153()->set_acu3_brakingcontrolflag(acu3_brakingcontrolflag(bytes, length));
  chassis->mutable_acu3_153()->set_acu3_livecounter(acu3_livecounter(bytes, length));
  chassis->mutable_acu3_153()->set_acu3_checksum(acu3_checksum(bytes, length));
}

void Acu3153::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) : you should add the heartbeat manually
}

void Acu3153::UpdateData(uint8_t* data) {
  set_p_acu3_brakingtargetposition(data, acu3_brakingtargetposition_);
  set_p_acu3_epbcontrolflag(data, acu3_epbcontrolflag_);
  set_p_acu3_geartarget(data, acu3_geartarget_);
  set_p_acu3_gearcontrolflag(data, acu3_gearcontrolflag_);
  set_p_acu3_brakingtargetpressure(data, acu3_brakingtargetpressure_);
  set_p_acu3_brakingtargetdeceleration(data, acu3_brakingtargetdeceleration_);
  set_p_acu3_brakingcontrolflag(data, acu3_brakingcontrolflag_);
  set_p_acu3_livecounter(data, acu3_livecounter_);
  set_p_acu3_checksum(data, acu3_checksum_);
}

void Acu3153::Reset() {
  // TODO(All) :  you should check this manually
  acu3_brakingtargetposition_ = 0.0;
  acu3_epbcontrolflag_ = Acu3_153::ACU3_EPBCONTROLFLAG_NO_REQUEST;
  acu3_geartarget_ = Acu3_153::ACU3_GEARTARGET_P;
  acu3_gearcontrolflag_ = Acu3_153::ACU3_GEARCONTROLFLAG_NO_REQUEST;
  acu3_brakingtargetpressure_ = 0.0;
  acu3_brakingtargetdeceleration_ = 0.0;
  acu3_brakingcontrolflag_ = Acu3_153::ACU3_BRAKINGCONTROLFLAG_NO_REQUEST;
  acu3_livecounter_ = 0;
  acu3_checksum_ = 0;
}

Acu3153* Acu3153::set_acu3_brakingtargetposition(
    double acu3_brakingtargetposition) {
  acu3_brakingtargetposition_ = acu3_brakingtargetposition;
  return this;
 }

// config detail: {'bit': 18, 'is_signed_var': False, 'len': 6, 'name': 'ACU3_BrakingTargetPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 2.0, 'type': 'double'}
void Acu3153::set_p_acu3_brakingtargetposition(uint8_t* data,
    double acu3_brakingtargetposition) {
  acu3_brakingtargetposition = ProtocolData::BoundedValue(0.0, 100.0, acu3_brakingtargetposition);
  int x = acu3_brakingtargetposition / 2.000000;

  Byte to_set(data + 2);
  to_set.set_value(x, 2, 6);
}


Acu3153* Acu3153::set_acu3_epbcontrolflag(
    Acu3_153::Acu3_epbcontrolflagType acu3_epbcontrolflag) {
  acu3_epbcontrolflag_ = acu3_epbcontrolflag;
  return this;
 }

// config detail: {'bit': 52, 'description': 'This signal is the status of the braking control request', 'enum': {0: 'ACU3_EPBCONTROLFLAG_NO_REQUEST', 1: 'ACU3_EPBCONTROLFLAG_RELEASE', 2: 'ACU3_EPBCONTROLFLAG_LOCK', 3: 'ACU3_EPBCONTROLFLAG_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_EPBControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3153::set_p_acu3_epbcontrolflag(uint8_t* data,
    Acu3_153::Acu3_epbcontrolflagType acu3_epbcontrolflag) {
  int x = acu3_epbcontrolflag;

  Byte to_set(data + 6);
  to_set.set_value(x, 4, 2);
}


Acu3153* Acu3153::set_acu3_geartarget(
    Acu3_153::Acu3_geartargetType acu3_geartarget) {
  acu3_geartarget_ = acu3_geartarget;
  return this;
 }

// config detail: {'bit': 48, 'description': 'This signal is gear request', 'enum': {0: 'ACU3_GEARTARGET_P', 1: 'ACU3_GEARTARGET_R', 2: 'ACU3_GEARTARGET_N', 3: 'ACU3_GEARTARGET_D', 4: 'ACU3_GEARTARGET_RESERVED', 5: 'ACU3_GEARTARGET_RESERVED', 6: 'ACU3_GEARTARGET_RESERVED', 7: 'ACU3_GEARTARGET_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU3_GearTarget', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3153::set_p_acu3_geartarget(uint8_t* data,
    Acu3_153::Acu3_geartargetType acu3_geartarget) {
  int x = acu3_geartarget;

  Byte to_set(data + 6);
  to_set.set_value(x, 0, 3);
}


Acu3153* Acu3153::set_acu3_gearcontrolflag(
    Acu3_153::Acu3_gearcontrolflagType acu3_gearcontrolflag) {
  acu3_gearcontrolflag_ = acu3_gearcontrolflag;
  return this;
 }

// config detail: {'bit': 51, 'description': 'This signal is the status of the gear control request', 'enum': {0: 'ACU3_GEARCONTROLFLAG_NO_REQUEST', 1: 'ACU3_GEARCONTROLFLAG_REQUEST'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU3_GearControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3153::set_p_acu3_gearcontrolflag(uint8_t* data,
    Acu3_153::Acu3_gearcontrolflagType acu3_gearcontrolflag) {
  int x = acu3_gearcontrolflag;

  Byte to_set(data + 6);
  to_set.set_value(x, 3, 1);
}


Acu3153* Acu3153::set_acu3_brakingtargetpressure(
    double acu3_brakingtargetpressure) {
  acu3_brakingtargetpressure_ = acu3_brakingtargetpressure;
  return this;
 }

// config detail: {'bit': 24, 'description': 'This signal is deceleration request for wheel brake', 'is_signed_var': False, 'len': 10, 'name': 'ACU3_BrakingTargetPressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'Mpa', 'precision': 0.01, 'type': 'double'}
void Acu3153::set_p_acu3_brakingtargetpressure(uint8_t* data,
    double acu3_brakingtargetpressure) {
  acu3_brakingtargetpressure = ProtocolData::BoundedValue(0.0, 10.0, acu3_brakingtargetpressure);
  int x = acu3_brakingtargetpressure / 0.010000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 3);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x3;
  Byte to_set1(data + 4);
  to_set1.set_value(t, 0, 2);
}


Acu3153* Acu3153::set_acu3_brakingtargetdeceleration(
    double acu3_brakingtargetdeceleration) {
  acu3_brakingtargetdeceleration_ = acu3_brakingtargetdeceleration;
  return this;
 }

// config detail: {'bit': 8, 'description': 'This signal is deceleration request for wheel brake', 'is_signed_var': False, 'len': 10, 'name': 'ACU3_BrakingTargetDeceleration', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-10|0]', 'physical_unit': 'm/s2', 'precision': -0.01, 'type': 'double'}
void Acu3153::set_p_acu3_brakingtargetdeceleration(uint8_t* data,
    double acu3_brakingtargetdeceleration) {
  acu3_brakingtargetdeceleration = ProtocolData::BoundedValue(-10.0, 0.0, acu3_brakingtargetdeceleration);
  int x = acu3_brakingtargetdeceleration / -0.010000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 1);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x3;
  Byte to_set1(data + 2);
  to_set1.set_value(t, 0, 2);
}


Acu3153* Acu3153::set_acu3_brakingcontrolflag(
    Acu3_153::Acu3_brakingcontrolflagType acu3_brakingcontrolflag) {
  acu3_brakingcontrolflag_ = acu3_brakingcontrolflag;
  return this;
 }

// config detail: {'bit': 40, 'description': 'This signal is the status of the braking control request', 'enum': {0: 'ACU3_BRAKINGCONTROLFLAG_NO_REQUEST', 1: 'ACU3_BRAKINGCONTROLFLAG_REQUEST_PRESURE', 2: 'ACU3_BRAKINGCONTROLFLAG_REQUEST_DEC', 3: 'ACU3_BRAKINGCONTROLFLAG_REQUEST_POSITION'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BrakingControlFlag', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3153::set_p_acu3_brakingcontrolflag(uint8_t* data,
    Acu3_153::Acu3_brakingcontrolflagType acu3_brakingcontrolflag) {
  int x = acu3_brakingcontrolflag;

  Byte to_set(data + 5);
  to_set.set_value(x, 0, 2);
}


Acu3153* Acu3153::set_acu3_livecounter(
    int acu3_livecounter) {
  acu3_livecounter_ = acu3_livecounter;
  return this;
 }

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU3_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
void Acu3153::set_p_acu3_livecounter(uint8_t* data,
    int acu3_livecounter) {
  acu3_livecounter = ProtocolData::BoundedValue(0, 15, acu3_livecounter);
  int x = acu3_livecounter;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


Acu3153* Acu3153::set_acu3_checksum(
    int acu3_checksum) {
  acu3_checksum_ = acu3_checksum;
  return this;
 }

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU3_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
void Acu3153::set_p_acu3_checksum(uint8_t* data,
    int acu3_checksum) {
  acu3_checksum = ProtocolData::BoundedValue(0, 255, acu3_checksum);
  int x = acu3_checksum;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


double Acu3153::acu3_brakingtargetposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 6);

  double ret = x * 2.000000;
  return ret;
}

Acu3_153::Acu3_epbcontrolflagType Acu3153::acu3_epbcontrolflag(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(4, 2);

  Acu3_153::Acu3_epbcontrolflagType ret =  static_cast<Acu3_153::Acu3_epbcontrolflagType>(x);
  return ret;
}

Acu3_153::Acu3_geartargetType Acu3153::acu3_geartarget(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 3);

  Acu3_153::Acu3_geartargetType ret =  static_cast<Acu3_153::Acu3_geartargetType>(x);
  return ret;
}

Acu3_153::Acu3_gearcontrolflagType Acu3153::acu3_gearcontrolflag(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(3, 1);

  Acu3_153::Acu3_gearcontrolflagType ret =  static_cast<Acu3_153::Acu3_gearcontrolflagType>(x);
  return ret;
}

double Acu3153::acu3_brakingtargetpressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

double Acu3153::acu3_brakingtargetdeceleration(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * -0.010000;
  return ret;
}

Acu3_153::Acu3_brakingcontrolflagType Acu3153::acu3_brakingcontrolflag(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 2);

  Acu3_153::Acu3_brakingcontrolflagType ret =  static_cast<Acu3_153::Acu3_brakingcontrolflagType>(x);
  return ret;
}

int Acu3153::acu3_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

int Acu3153::acu3_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
