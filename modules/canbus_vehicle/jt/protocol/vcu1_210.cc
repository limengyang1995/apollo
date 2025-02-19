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

#include "modules/canbus_vehicle/jt/protocol/vcu1_210.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Vcu1210::Vcu1210() {}
const int32_t Vcu1210::ID = 0x210;

void Vcu1210::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_vcu1_210()->set_vcu1_overlayinputtorque(vcu1_overlayinputtorque(bytes, length));
  chassis->mutable_vcu1_210()->set_vcu1_handsteeringtorque(vcu1_handsteeringtorque(bytes, length));
  chassis->mutable_vcu1_210()->set_vcu1_livecounter(vcu1_livecounter(bytes, length));
  chassis->mutable_vcu1_210()->set_vcu1_checksum(vcu1_checksum(bytes, length));
  chassis->mutable_vcu1_210()->set_vcu1_steeringspeed(vcu1_steeringspeed(bytes, length));
  chassis->mutable_vcu1_210()->set_vcu1_steeringangle(vcu1_steeringangle(bytes, length));
}

// config detail: {'bit': 48, 'description': 'The signal indicates the actual applied overlay toque in EPS.', 'is_signed_var': False, 'len': 11, 'name': 'vcu1_overlayinputtorque', 'offset': -10.0, 'order': 'intel', 'physical_range': '[-10|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
double Vcu1210::vcu1_overlayinputtorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -10.000000;
  return ret;
}

// config detail: {'bit': 36, 'description': 'The signal indicates the torque measured by the torque sensor at the steering wheel', 'is_signed_var': False, 'len': 11, 'name': 'vcu1_handsteeringtorque', 'offset': -10.0, 'order': 'intel', 'physical_range': '[-10|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
double Vcu1210::vcu1_handsteeringtorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  double ret = x * 0.010000 + -10.000000;
  return ret;
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'vcu1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vcu1210::vcu1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'vcu1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vcu1210::vcu1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 22, 'description': 'This signal indicates the teering wheel rotation speed. anticlockwise=negative, clockwise=positive', 'is_signed_var': False, 'len': 14, 'name': 'vcu1_steeringspeed', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg/s', 'precision': 0.1, 'signal_type': 'speed', 'type': 'double'}
double Vcu1210::vcu1_steeringspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t2(bytes + 2);
  t = t2.get_byte(6, 2);
  x <<= 2;
  x |= t;

  double ret = x * 0.100000 + -600.000000;
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal indicates the angle of steering wheel. anticlockwise=negative, clockwise=positive', 'is_signed_var': False, 'len': 14, 'name': 'vcu1_steeringangle', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
double Vcu1210::vcu1_steeringangle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -600.000000;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
