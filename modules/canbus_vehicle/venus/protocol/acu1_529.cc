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

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Acu1529::Acu1529() {}
const int32_t Acu1529::ID = 0x529;

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

// config detail: {'bit': 40, 'enum': {0: 'ACU1_GEARAUTOCONTROL_RESERVED1', 1: 'ACU1_GEARAUTOCONTROL_REQUEST', 2: 'ACU1_GEARAUTOCONTROL_NOREQUEST', 3: 'ACU1_GEARAUTOCONTROL_RESERVED2'}, 'is_signed_var': False, 'len': 2, 'name': 'acu1_gearautocontrol', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu1_529::Acu1_gearautocontrolType Acu1529::acu1_gearautocontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 2);

  Acu1_529::Acu1_gearautocontrolType ret =  static_cast<Acu1_529::Acu1_gearautocontrolType>(x);
  return ret;
}

// config detail: {'bit': 30, 'is_signed_var': False, 'len': 9, 'name': 'acu1_targetsteeringspeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
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

// config detail: {'bit': 19, 'enum': {2047: 'ACU1_TARGETSTEERINGANGLE_R_NOREQUEST'}, 'is_signed_var': False, 'len': 11, 'name': 'acu1_targetsteeringangle_r', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'enum'}
Acu1_529::Acu1_targetsteeringangle_rType Acu1529::acu1_targetsteeringangle_r(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(3, 5);
  x <<= 5;
  x |= t;

  Acu1_529::Acu1_targetsteeringangle_rType ret =  static_cast<Acu1_529::Acu1_targetsteeringangle_rType>(x);
  return ret;
}

// config detail: {'bit': 8, 'enum': {2047: 'ACU1_TARGETSTEERINGANGLE_F_NOREQUEST'}, 'is_signed_var': False, 'len': 11, 'name': 'acu1_targetsteeringangle_f', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'enum'}
Acu1_529::Acu1_targetsteeringangle_fType Acu1529::acu1_targetsteeringangle_f(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Acu1_529::Acu1_targetsteeringangle_fType ret =  static_cast<Acu1_529::Acu1_targetsteeringangle_fType>(x);
  return ret;
}

// config detail: {'bit': 44, 'enum': {0: 'ACU1_TARGETGEAR_NOREQUEST', 1: 'ACU1_TARGETGEAR_P', 2: 'ACU1_TARGETGEAR_R', 3: 'ACU1_TARGETGEAR_N', 4: 'ACU1_TARGETGEAR_D', 5: 'ACU1_TARGETGEAR_RESERVED1', 6: 'ACU1_TARGETGEAR_RESERVED2', 7: 'ACU1_TARGETGEAR_RESERVED3'}, 'is_signed_var': False, 'len': 3, 'name': 'acu1_targetgear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu1_529::Acu1_targetgearType Acu1529::acu1_targetgear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 3);

  Acu1_529::Acu1_targetgearType ret =  static_cast<Acu1_529::Acu1_targetgearType>(x);
  return ret;
}

// config detail: {'bit': 42, 'enum': {0: 'ACU1_TARGETEPB_NOREQUEST', 1: 'ACU1_TARGETEPB_RELEASE', 2: 'ACU1_TARGETEPB_LOCK', 3: 'ACU1_TARGETEPB_RESERVE'}, 'is_signed_var': False, 'len': 2, 'name': 'acu1_targetepb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu1_529::Acu1_targetepbType Acu1529::acu1_targetepb(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(2, 2);

  Acu1_529::Acu1_targetepbType ret =  static_cast<Acu1_529::Acu1_targetepbType>(x);
  return ret;
}

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'acu1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Acu1529::acu1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acu1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Acu1529::acu1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'enum': {0: 'ACU1_STEERINGAUTOCONTROL_NOREQUET', 1: 'ACU1_STEERINGAUTOCONTROL_REQUEST', 2: 'ACU1_STEERINGAUTOCONTROL_RESERVE1', 3: 'ACU1_STEERINGAUTOCONTROL_RESERVE2'}, 'is_signed_var': False, 'len': 2, 'name': 'acu1_steeringautocontrol', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu1_529::Acu1_steeringautocontrolType Acu1529::acu1_steeringautocontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 2);

  Acu1_529::Acu1_steeringautocontrolType ret =  static_cast<Acu1_529::Acu1_steeringautocontrolType>(x);
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
