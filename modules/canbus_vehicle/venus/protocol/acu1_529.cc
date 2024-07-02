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

#include "modules/canbus_vehicle/venus/protocol/acu1_529.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

const int32_t Acu1529::ID = 0x529;

// public
Acu1529::Acu1529() { Reset(); }

uint32_t Acu1529::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Acu1529::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_acu1_529()->set_acu1_gearautocontrol(acu1_gearautocontrol(bytes, length));
  chassis->mutable_acu1_529()->set_acu1_targetsteeringspeed(acu1_targetsteeringspeed(bytes, length));
  chassis->mutable_acu1_529()->set_acu1_targetsteeringangle_r(acu1_targetsteeringangle_r(bytes, length));
  chassis->mutable_acu1_529()->set_acu1_targetsteeringangle_f(acu1_targetsteeringangle_f(bytes, length));
  chassis->mutable_acu1_529()->set_acu1_targetgear(acu1_targetgear(bytes, length));
  chassis->mutable_acu1_529()->set_acu1_targetepb(acu1_targetepb(bytes, length));
  chassis->mutable_acu1_529()->set_acu1_livecounter(acu1_livecounter(bytes, length));
  chassis->mutable_acu1_529()->set_acu1_checksum(acu1_checksum(bytes, length));
  chassis->mutable_acu1_529()->set_acu1_steeringautocontrol(acu1_steeringautocontrol(bytes, length));
}

void Acu1529::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Acu1529::UpdateData(uint8_t* data) {
  set_p_acu1_gearautocontrol(data, acu1_gearautocontrol_);
  set_p_acu1_targetsteeringspeed(data, acu1_targetsteeringspeed_);
  set_p_acu1_targetsteeringangle_r(data, acu1_targetsteeringangle_r_);
  set_p_acu1_targetsteeringangle_f(data, acu1_targetsteeringangle_f_);
  set_p_acu1_targetgear(data, acu1_targetgear_);
  set_p_acu1_targetepb(data, acu1_targetepb_);
  set_p_acu1_livecounter(data, acu1_livecounter_);
  set_p_acu1_checksum(data, acu1_checksum_);
  set_p_acu1_steeringautocontrol(data, acu1_steeringautocontrol_);
}

void Acu1529::Reset() {
  // TODO(All) :  you should check this manually
  acu1_gearautocontrol_ = Acu1_529::ACU1_GEARAUTOCONTROL_RESERVED1;
  acu1_targetsteeringspeed_ = 0;
  acu1_targetsteeringangle_r_ = 0;
  acu1_targetsteeringangle_f_ = 0;
  acu1_targetgear_ = Acu1_529::ACU1_TARGETGEAR_NOREQUEST;
  acu1_targetepb_ = Acu1_529::ACU1_TARGETEPB_NOREQUEST;
  acu1_livecounter_ = 0;
  acu1_checksum_ = 0;
  acu1_steeringautocontrol_ = Acu1_529::ACU1_STEERINGAUTOCONTROL_NOREQUET;
}

Acu1529* Acu1529::set_acu1_gearautocontrol(
    Acu1_529::Acu1_gearautocontrolType acu1_gearautocontrol) {
  acu1_gearautocontrol_ = acu1_gearautocontrol;
  return this;
 }

// config detail: {'bit': 40, 'enum': {0: 'ACU1_GEARAUTOCONTROL_RESERVED1', 1: 'ACU1_GEARAUTOCONTROL_REQUEST', 2: 'ACU1_GEARAUTOCONTROL_NOREQUEST', 3: 'ACU1_GEARAUTOCONTROL_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_GearAutoControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1529::set_p_acu1_gearautocontrol(uint8_t* data,
    Acu1_529::Acu1_gearautocontrolType acu1_gearautocontrol) {
  int x = acu1_gearautocontrol;

  Byte to_set(data + 5);
  to_set.set_value(x, 0, 2);
}


Acu1529* Acu1529::set_acu1_targetsteeringspeed(
    int acu1_targetsteeringspeed) {
  acu1_targetsteeringspeed_ = acu1_targetsteeringspeed;
  return this;
 }

// config detail: {'bit': 30, 'is_signed_var': False, 'len': 9, 'name': 'ACU1_TargetSteeringSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
void Acu1529::set_p_acu1_targetsteeringspeed(uint8_t* data,
    int acu1_targetsteeringspeed) {
  acu1_targetsteeringspeed = ProtocolData::BoundedValue(0, 500, acu1_targetsteeringspeed);
  int x = acu1_targetsteeringspeed;
  uint8_t t = 0;

  t = x & 0x3;
  Byte to_set0(data + 3);
  to_set0.set_value(t, 6, 2);
  x >>= 2;

  t = x & 0x7F;
  Byte to_set1(data + 4);
  to_set1.set_value(t, 0, 7);
}


Acu1529* Acu1529::set_acu1_targetsteeringangle_r(
    double acu1_targetsteeringangle_r) {
  acu1_targetsteeringangle_r_ = acu1_targetsteeringangle_r;
  return this;
 }

// config detail: {'bit': 19, 'enum': {2047: 'ACU1_TARGETSTEERINGANGLE_R_NOREQUEST'}, 'is_signed_var': False, 'len': 11, 'name': 'ACU1_TargetSteeringAngle_R', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'enum'}
void Acu1529::set_p_acu1_targetsteeringangle_r(uint8_t* data,
    double acu1_targetsteeringangle_r) {
  int x = (acu1_targetsteeringangle_r - -600.000000);
  uint8_t t = 0;

  t = x & 0x1F;
  Byte to_set0(data + 2);
  to_set0.set_value(t, 3, 5);
  x >>= 5;

  t = x & 0x3F;
  Byte to_set1(data + 3);
  to_set1.set_value(t, 0, 6);
}


Acu1529* Acu1529::set_acu1_targetsteeringangle_f(
    double acu1_targetsteeringangle_f) {
  acu1_targetsteeringangle_f_ = acu1_targetsteeringangle_f;
  return this;
 }

// config detail: {'bit': 8, 'enum': {2047: 'ACU1_TARGETSTEERINGANGLE_F_NOREQUEST'}, 'is_signed_var': False, 'len': 11, 'name': 'ACU1_TargetSteeringAngle_F', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'enum'}
void Acu1529::set_p_acu1_targetsteeringangle_f(uint8_t* data,
    double acu1_targetsteeringangle_f) {
  int x = (acu1_targetsteeringangle_f - -600.000000);
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 1);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x7;
  Byte to_set1(data + 2);
  to_set1.set_value(t, 0, 3);
}


Acu1529* Acu1529::set_acu1_targetgear(
    Acu1_529::Acu1_targetgearType acu1_targetgear) {
  acu1_targetgear_ = acu1_targetgear;
  return this;
 }

// config detail: {'bit': 44, 'enum': {0: 'ACU1_TARGETGEAR_NOREQUEST', 1: 'ACU1_TARGETGEAR_P', 2: 'ACU1_TARGETGEAR_R', 3: 'ACU1_TARGETGEAR_N', 4: 'ACU1_TARGETGEAR_D', 5: 'ACU1_TARGETGEAR_RESERVED1', 6: 'ACU1_TARGETGEAR_RESERVED2', 7: 'ACU1_TARGETGEAR_RESERVED3'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU1_TargetGear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1529::set_p_acu1_targetgear(uint8_t* data,
    Acu1_529::Acu1_targetgearType acu1_targetgear) {
  int x = acu1_targetgear;

  Byte to_set(data + 5);
  to_set.set_value(x, 4, 3);
}


Acu1529* Acu1529::set_acu1_targetepb(
    Acu1_529::Acu1_targetepbType acu1_targetepb) {
  acu1_targetepb_ = acu1_targetepb;
  return this;
 }

// config detail: {'bit': 42, 'enum': {0: 'ACU1_TARGETEPB_NOREQUEST', 1: 'ACU1_TARGETEPB_RELEASE', 2: 'ACU1_TARGETEPB_LOCK', 3: 'ACU1_TARGETEPB_RESERVE'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_TargetEPB', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1529::set_p_acu1_targetepb(uint8_t* data,
    Acu1_529::Acu1_targetepbType acu1_targetepb) {
  int x = acu1_targetepb;

  Byte to_set(data + 5);
  to_set.set_value(x, 2, 2);
}


Acu1529* Acu1529::set_acu1_livecounter(
    int acu1_livecounter) {
  acu1_livecounter_ = acu1_livecounter;
  return this;
 }

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'ACU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
void Acu1529::set_p_acu1_livecounter(uint8_t* data,
    int acu1_livecounter) {
  acu1_livecounter = ProtocolData::BoundedValue(0, 15, acu1_livecounter);
  int x = acu1_livecounter;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


Acu1529* Acu1529::set_acu1_checksum(
    int acu1_checksum) {
  acu1_checksum_ = acu1_checksum;
  return this;
 }

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
void Acu1529::set_p_acu1_checksum(uint8_t* data,
    int acu1_checksum) {
  acu1_checksum = ProtocolData::BoundedValue(0, 255, acu1_checksum);
  int x = acu1_checksum;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


Acu1529* Acu1529::set_acu1_steeringautocontrol(
    Acu1_529::Acu1_steeringautocontrolType acu1_steeringautocontrol) {
  acu1_steeringautocontrol_ = acu1_steeringautocontrol;
  return this;
 }

// config detail: {'bit': 56, 'enum': {0: 'ACU1_STEERINGAUTOCONTROL_NOREQUET', 1: 'ACU1_STEERINGAUTOCONTROL_REQUEST', 2: 'ACU1_STEERINGAUTOCONTROL_RESERVE1', 3: 'ACU1_STEERINGAUTOCONTROL_RESERVE2'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU1_SteeringAutoControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu1529::set_p_acu1_steeringautocontrol(uint8_t* data,
    Acu1_529::Acu1_steeringautocontrolType acu1_steeringautocontrol) {
  int x = acu1_steeringautocontrol;

  Byte to_set(data + 7);
  to_set.set_value(x, 0, 2);
}


Acu1_529::Acu1_gearautocontrolType Acu1529::acu1_gearautocontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 2);

  Acu1_529::Acu1_gearautocontrolType ret =  static_cast<Acu1_529::Acu1_gearautocontrolType>(x);
  return ret;
}

int Acu1529::acu1_targetsteeringspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(6, 2);
  x <<= 2;
  x |= t;

  int ret = x;
  return ret;
}

double Acu1529::acu1_targetsteeringangle_r(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(3, 5);
  x <<= 5;
  x |= t;

  double ret =  static_cast<double>(x);
  return ret;
}

double Acu1529::acu1_targetsteeringangle_f(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret =  static_cast<double>(x);
  return ret;
}

Acu1_529::Acu1_targetgearType Acu1529::acu1_targetgear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 3);

  Acu1_529::Acu1_targetgearType ret =  static_cast<Acu1_529::Acu1_targetgearType>(x);
  return ret;
}

Acu1_529::Acu1_targetepbType Acu1529::acu1_targetepb(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(2, 2);

  Acu1_529::Acu1_targetepbType ret =  static_cast<Acu1_529::Acu1_targetepbType>(x);
  return ret;
}

int Acu1529::acu1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

int Acu1529::acu1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

Acu1_529::Acu1_steeringautocontrolType Acu1529::acu1_steeringautocontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 2);

  Acu1_529::Acu1_steeringautocontrolType ret =  static_cast<Acu1_529::Acu1_steeringautocontrolType>(x);
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
