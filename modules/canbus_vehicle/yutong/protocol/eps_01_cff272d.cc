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

#include "modules/canbus_vehicle/yutong/protocol/eps_01_cff272d.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Eps01cff272d::ID = 0xcff272d;

// public
Eps01cff272d::Eps01cff272d() { Reset(); }

uint32_t Eps01cff272d::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Eps01cff272d::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_eps_01_cff272d()->set_epssteerangreq(epssteerangreq(bytes, length));
  chassis->mutable_eps_01_cff272d()->set_epsctrlreq(epsctrlreq(bytes, length));
}

void Eps01cff272d::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Eps01cff272d::UpdateData(uint8_t* data) {
  set_p_epssteerangreq(data, epssteerangreq_);
  set_p_epsctrlreq(data, epsctrlreq_);
}

void Eps01cff272d::Reset() {
  // TODO(All) :  you should check this manually
  epssteerangreq_ = 0.0;
  epsctrlreq_ = Eps_01_cff272d::EPSCTRLREQ_INVALID;
}

Eps01cff272d* Eps01cff272d::set_epssteerangreq(
    double epssteerangreq) {
  epssteerangreq_ = epssteerangreq;
  return this;
 }

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'EPSSteerAngReq', 'offset': -40.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
void Eps01cff272d::set_p_epssteerangreq(uint8_t* data,
    double epssteerangreq) {
  epssteerangreq = ProtocolData::BoundedValue(0.0, 65535.0, epssteerangreq);
  int x = (epssteerangreq - -40.000000) / 0.100000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 0);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 1);
  to_set1.set_value(t, 0, 8);
}


Eps01cff272d* Eps01cff272d::set_epsctrlreq(
    Eps_01_cff272d::EpsctrlreqType epsctrlreq) {
  epsctrlreq_ = epsctrlreq;
  return this;
 }

// config detail: {'bit': 16, 'enum': {0: 'EPSCTRLREQ_', 1: 'EPSCTRLREQ_'}, 'is_signed_var': False, 'len': 2, 'name': 'EPSCtrlReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Eps01cff272d::set_p_epsctrlreq(uint8_t* data,
    Eps_01_cff272d::EpsctrlreqType epsctrlreq) {
  int x = epsctrlreq;

  Byte to_set(data + 2);
  to_set.set_value(x, 0, 2);
}


double Eps01cff272d::epssteerangreq(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -40.000000;
  return ret;
}

Eps_01_cff272d::EpsctrlreqType Eps01cff272d::epsctrlreq(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Eps_01_cff272d::EpsctrlreqType ret =  static_cast<Eps_01_cff272d::EpsctrlreqType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
