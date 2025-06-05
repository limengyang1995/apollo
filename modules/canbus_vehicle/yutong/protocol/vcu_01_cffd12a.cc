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

#include "modules/canbus_vehicle/yutong/protocol/vcu_01_cffd12a.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Vcu01cffd12a::ID = 0xcffd12a;

// public
Vcu01cffd12a::Vcu01cffd12a() { Reset(); }

uint32_t Vcu01cffd12a::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Vcu01cffd12a::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_vcu_01_cffd12a()->set_accpedalposreq(accpedalposreq(bytes, length));
  chassis->mutable_vcu_01_cffd12a()->set_gearreq(gearreq(bytes, length));
  chassis->mutable_vcu_01_cffd12a()->set_brakeactivereq(brakeactivereq(bytes, length));
  chassis->mutable_vcu_01_cffd12a()->set_accactivests(accactivests(bytes, length));
  chassis->mutable_vcu_01_cffd12a()->set_decelerationreq(decelerationreq(bytes, length));
  chassis->mutable_vcu_01_cffd12a()->set_msgcnt(msgcnt(bytes, length));
  chassis->mutable_vcu_01_cffd12a()->set_checkcum(checkcum(bytes, length));
}

void Vcu01cffd12a::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Vcu01cffd12a::UpdateData(uint8_t* data) {
  set_p_accpedalposreq(data, accpedalposreq_);
  set_p_gearreq(data, gearreq_);
  set_p_brakeactivereq(data, brakeactivereq_);
  set_p_accactivests(data, accactivests_);
  set_p_decelerationreq(data, decelerationreq_);
  set_p_msgcnt(data, msgcnt_);
  set_p_checkcum(data, checkcum_);
}

void Vcu01cffd12a::Reset() {
  // TODO(All) :  you should check this manually
  accpedalposreq_ = 0.0;
  gearreq_ = Vcu_01_cffd12a::GEARREQ_N;
  brakeactivereq_ = Vcu_01_cffd12a::BRAKEACTIVEREQ_OFF;
  accactivests_ = Vcu_01_cffd12a::ACCACTIVESTS_OFF;
  decelerationreq_ = 0.0;
  msgcnt_ = 0;
  checkcum_ = 0;
}

Vcu01cffd12a* Vcu01cffd12a::set_accpedalposreq(
    double accpedalposreq) {
  accpedalposreq_ = accpedalposreq;
  return this;
 }

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACCpedalPosReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
void Vcu01cffd12a::set_p_accpedalposreq(uint8_t* data,
    double accpedalposreq) {
  accpedalposreq = ProtocolData::BoundedValue(0.0, 255.0, accpedalposreq);
  int x = accpedalposreq / 0.400000;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


Vcu01cffd12a* Vcu01cffd12a::set_gearreq(
    Vcu_01_cffd12a::GearreqType gearreq) {
  gearreq_ = gearreq;
  return this;
 }

// config detail: {'bit': 8, 'enum': {0: 'GEARREQ_N', 32: 'GEARREQ_D', 64: 'GEARREQ_R', 96: 'GEARREQ_L'}, 'is_signed_var': False, 'len': 8, 'name': 'GearReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu01cffd12a::set_p_gearreq(uint8_t* data,
    Vcu_01_cffd12a::GearreqType gearreq) {
  int x = gearreq;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 8);
}


Vcu01cffd12a* Vcu01cffd12a::set_brakeactivereq(
    Vcu_01_cffd12a::BrakeactivereqType brakeactivereq) {
  brakeactivereq_ = brakeactivereq;
  return this;
 }

// config detail: {'bit': 16, 'enum': {0: 'BRAKEACTIVEREQ_', 1: 'BRAKEACTIVEREQ_'}, 'is_signed_var': False, 'len': 4, 'name': 'BrakeActiveReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu01cffd12a::set_p_brakeactivereq(uint8_t* data,
    Vcu_01_cffd12a::BrakeactivereqType brakeactivereq) {
  int x = brakeactivereq;

  Byte to_set(data + 2);
  to_set.set_value(x, 0, 4);
}


Vcu01cffd12a* Vcu01cffd12a::set_accactivests(
    Vcu_01_cffd12a::AccactivestsType accactivests) {
  accactivests_ = accactivests;
  return this;
 }

// config detail: {'bit': 20, 'enum': {0: 'ACCACTIVESTS_', 1: 'ACCACTIVESTS_'}, 'is_signed_var': False, 'len': 4, 'name': 'ACCactiveSts', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu01cffd12a::set_p_accactivests(uint8_t* data,
    Vcu_01_cffd12a::AccactivestsType accactivests) {
  int x = accactivests;

  Byte to_set(data + 2);
  to_set.set_value(x, 4, 4);
}


Vcu01cffd12a* Vcu01cffd12a::set_decelerationreq(
    double decelerationreq) {
  decelerationreq_ = decelerationreq;
  return this;
 }

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 16, 'name': 'DecelerationReq', 'offset': -15.687, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'm/s2', 'precision': 0.000488281, 'type': 'double'}
void Vcu01cffd12a::set_p_decelerationreq(uint8_t* data,
    double decelerationreq) {
  decelerationreq = ProtocolData::BoundedValue(0.0, 65535.0, decelerationreq);
  int x = (decelerationreq - -15.687000) / 0.000488;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 3);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 4);
  to_set1.set_value(t, 0, 8);
}


Vcu01cffd12a* Vcu01cffd12a::set_msgcnt(
    int msgcnt) {
  msgcnt_ = msgcnt;
  return this;
 }

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'MsgCnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Vcu01cffd12a::set_p_msgcnt(uint8_t* data,
    int msgcnt) {
  msgcnt = ProtocolData::BoundedValue(0, 255, msgcnt);
  int x = msgcnt;

  Byte to_set(data + 6);
  to_set.set_value(x, 0, 8);
}


Vcu01cffd12a* Vcu01cffd12a::set_checkcum(
    int checkcum) {
  checkcum_ = checkcum;
  return this;
 }

// config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'Checkcum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Vcu01cffd12a::set_p_checkcum(uint8_t* data,
    int checkcum) {
  checkcum = ProtocolData::BoundedValue(0, 255, checkcum);
  int x = checkcum;

  Byte to_set(data + 7);
  to_set.set_value(x, 0, 8);
}


double Vcu01cffd12a::accpedalposreq(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

Vcu_01_cffd12a::GearreqType Vcu01cffd12a::gearreq(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Vcu_01_cffd12a::GearreqType ret =  static_cast<Vcu_01_cffd12a::GearreqType>(x);
  return ret;
}

Vcu_01_cffd12a::BrakeactivereqType Vcu01cffd12a::brakeactivereq(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 4);

  Vcu_01_cffd12a::BrakeactivereqType ret =  static_cast<Vcu_01_cffd12a::BrakeactivereqType>(x);
  return ret;
}

Vcu_01_cffd12a::AccactivestsType Vcu01cffd12a::accactivests(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 4);

  Vcu_01_cffd12a::AccactivestsType ret =  static_cast<Vcu_01_cffd12a::AccactivestsType>(x);
  return ret;
}

double Vcu01cffd12a::decelerationreq(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.000488 + -15.687000;
  return ret;
}

int Vcu01cffd12a::msgcnt(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

int Vcu01cffd12a::checkcum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
