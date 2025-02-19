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

#include "modules/canbus_vehicle/jt/protocol/ur1_3b1.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Ur13b1::Ur13b1() {}
const int32_t Ur13b1::ID = 0x3B1;

void Ur13b1::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_ur1_3b1()->set_ur1_livecounter(ur1_livecounter(bytes, length));
  chassis->mutable_ur1_3b1()->set_ur1_distancevalue_fr(ur1_distancevalue_fr(bytes, length));
  chassis->mutable_ur1_3b1()->set_ur1_distancevalue_fmr(ur1_distancevalue_fmr(bytes, length));
  chassis->mutable_ur1_3b1()->set_ur1_distancevalue_fml(ur1_distancevalue_fml(bytes, length));
  chassis->mutable_ur1_3b1()->set_ur1_distancevalue_fl(ur1_distancevalue_fl(bytes, length));
  chassis->mutable_ur1_3b1()->set_ur1_checksum(ur1_checksum(bytes, length));
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ur1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Ur13b1::ur1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 38, 'description': 'This signal indicates the obstacle detection distance by front right radar', 'is_signed_var': False, 'len': 10, 'name': 'ur1_distancevalue_fr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
int Ur13b1::ur1_distancevalue_fr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(6, 2);
  x <<= 2;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 28, 'description': 'This signal indicates the obstacle detection distance by front middle right radar', 'is_signed_var': False, 'len': 10, 'name': 'ur1_distancevalue_fmr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
int Ur13b1::ur1_distancevalue_fmr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 18, 'description': 'This signal indicates the obstacle detection distance by front middle left radar', 'is_signed_var': False, 'len': 10, 'name': 'ur1_distancevalue_fml', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
int Ur13b1::ur1_distancevalue_fml(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(2, 6);
  x <<= 6;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal indicates the obstacle detection distance by front left radar', 'is_signed_var': False, 'len': 10, 'name': 'ur1_distancevalue_fl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
int Ur13b1::ur1_distancevalue_fl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ur1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Ur13b1::ur1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
