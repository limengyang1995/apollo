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

#include "modules/canbus_vehicle/yutong/protocol/vcu_03_18fefa2d.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Vcu0318fefa2d::ID = 0x18fefa2d;

// public
Vcu0318fefa2d::Vcu0318fefa2d() { Reset(); }

uint32_t Vcu0318fefa2d::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Vcu0318fefa2d::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_vcu_03_18fefa2d()->set_epbreq(epbreq(bytes, length));
  chassis->mutable_vcu_03_18fefa2d()->set_autoholdreq(autoholdreq(bytes, length));
  chassis->mutable_vcu_03_18fefa2d()->set_loadmass(loadmass(bytes, length));
}

void Vcu0318fefa2d::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Vcu0318fefa2d::UpdateData(uint8_t* data) {
  set_p_epbreq(data, epbreq_);
  set_p_autoholdreq(data, autoholdreq_);
  set_p_loadmass(data, loadmass_);
}

void Vcu0318fefa2d::Reset() {
  // TODO(All) :  you should check this manually
  epbreq_ = Vcu_03_18fefa2d::EPBREQ_;
  autoholdreq_ = Vcu_03_18fefa2d::AUTOHOLDREQ_;
  loadmass_ = 0.0;
}

Vcu0318fefa2d* Vcu0318fefa2d::set_epbreq(
    Vcu_03_18fefa2d::EpbreqType epbreq) {
  epbreq_ = epbreq;
  return this;
 }

// config detail: {'bit': 0, 'enum': {0: 'EPBREQ_', 1: 'EPBREQ_EPB', 2: 'EPBREQ_EPB'}, 'is_signed_var': False, 'len': 2, 'name': 'EPBReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0318fefa2d::set_p_epbreq(uint8_t* data,
    Vcu_03_18fefa2d::EpbreqType epbreq) {
  int x = epbreq;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 2);
}


Vcu0318fefa2d* Vcu0318fefa2d::set_autoholdreq(
    Vcu_03_18fefa2d::AutoholdreqType autoholdreq) {
  autoholdreq_ = autoholdreq;
  return this;
 }

// config detail: {'bit': 8, 'enum': {0: 'AUTOHOLDREQ_', 1: 'AUTOHOLDREQ_AUTO_HOLD', 2: 'AUTOHOLDREQ_AUTO_HOLD'}, 'is_signed_var': False, 'len': 2, 'name': 'AutoHoldReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0318fefa2d::set_p_autoholdreq(uint8_t* data,
    Vcu_03_18fefa2d::AutoholdreqType autoholdreq) {
  int x = autoholdreq;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 2);
}


Vcu0318fefa2d* Vcu0318fefa2d::set_loadmass(
    double loadmass) {
  loadmass_ = loadmass;
  return this;
 }

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'LoadMass', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 't', 'precision': 0.01, 'type': 'double'}
void Vcu0318fefa2d::set_p_loadmass(uint8_t* data,
    double loadmass) {
  loadmass = ProtocolData::BoundedValue(0.0, 65535.0, loadmass);
  int x = loadmass / 0.010000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 2);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 3);
  to_set1.set_value(t, 0, 8);
}


Vcu_03_18fefa2d::EpbreqType Vcu0318fefa2d::epbreq(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vcu_03_18fefa2d::EpbreqType ret =  static_cast<Vcu_03_18fefa2d::EpbreqType>(x);
  return ret;
}

Vcu_03_18fefa2d::AutoholdreqType Vcu0318fefa2d::autoholdreq(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Vcu_03_18fefa2d::AutoholdreqType ret =  static_cast<Vcu_03_18fefa2d::AutoholdreqType>(x);
  return ret;
}

double Vcu0318fefa2d::loadmass(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
