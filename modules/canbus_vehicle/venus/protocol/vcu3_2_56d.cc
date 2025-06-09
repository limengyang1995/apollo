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

#include "modules/canbus_vehicle/venus/protocol/vcu3_2_56d.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Vcu3256d::Vcu3256d() {}
const int32_t Vcu3256d::ID = 0x56D;

void Vcu3256d::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_vcu3_2_56d()->set_vcu3_wheelspeedrr(vcu3_wheelspeedrr(bytes, length));
  chassis->mutable_vcu3_2_56d()->set_vcu3_wheelspeedrl(vcu3_wheelspeedrl(bytes, length));
  chassis->mutable_vcu3_2_56d()->set_vcu3_wheelspeedfr(vcu3_wheelspeedfr(bytes, length));
  chassis->mutable_vcu3_2_56d()->set_vcu3_wheelspeedfl(vcu3_wheelspeedfl(bytes, length));
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 15, 'name': 'vcu3_wheelspeedrr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vcu3256d::vcu3_wheelspeedrr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 15, 'name': 'vcu3_wheelspeedrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vcu3256d::vcu3_wheelspeedrl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 15, 'name': 'vcu3_wheelspeedfr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vcu3256d::vcu3_wheelspeedfr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'vcu3_wheelspeedfl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vcu3256d::vcu3_wheelspeedfl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
