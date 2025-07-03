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

#include "modules/canbus_vehicle/jt/protocol/vcu2_211.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Vcu2211::Vcu2211() {}
const int32_t Vcu2211::ID = 0x211;

void Vcu2211::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_vcu2_211()->set_vcu2_mastercylinderpressure(vcu2_mastercylinderpressure(bytes, length));
  chassis->mutable_vcu2_211()->set_vcu2_brakepedalst(vcu2_brakepedalst(bytes, length));
  chassis->mutable_vcu2_211()->set_vcu2_vehiclespeed(vcu2_vehiclespeed(bytes, length));
  chassis->mutable_vcu2_211()->set_vcu2_drivingdirection(vcu2_drivingdirection(bytes, length));
  chassis->mutable_vcu2_211()->set_vcu2_calaccelerationpedalpositio(vcu2_calaccelerationpedalpositio(bytes, length));
  chassis->mutable_vcu2_211()->set_vcu2_accelpedalposition(vcu2_accelpedalposition(bytes, length));
  chassis->mutable_vcu2_211()->set_vcu2_livecounter(vcu2_livecounter(bytes, length));
  chassis->mutable_vcu2_211()->set_vcu2_checksum(vcu2_checksum(bytes, length));
}

// config detail: {'bit': 40, 'description': 'The signal indicates the actual pressure in the master cylinder.', 'is_signed_var': False, 'len': 11, 'name': 'vcu2_mastercylinderpressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|200]', 'physical_unit': 'bar', 'precision': 0.1, 'type': 'double'}
double Vcu2211::vcu2_mastercylinderpressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 52, 'description': 'This signal indicates the brake pedal status.', 'enum': {0: 'VCU2_BRAKEPEDALST_NO_ACTUATED', 1: 'VCU2_BRAKEPEDALST_ACTUATED', 2: 'VCU2_BRAKEPEDALST_RESERVED', 3: 'VCU2_BRAKEPEDALST_ERROR'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu2_brakepedalst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu2_211::Vcu2_brakepedalstType Vcu2211::vcu2_brakepedalst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(4, 2);

  Vcu2_211::Vcu2_brakepedalstType ret =  static_cast<Vcu2_211::Vcu2_brakepedalstType>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': 'The signal describes the raw vehicle speed calculated by ABS.', 'is_signed_var': False, 'len': 15, 'name': 'vcu2_vehiclespeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
double Vcu2211::vcu2_vehiclespeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 54, 'description': 'The signal indicates driving direction of the vehicle.', 'enum': {0: 'VCU2_DRIVINGDIRECTION_STOP', 1: 'VCU2_DRIVINGDIRECTION_FORWARD', 2: 'VCU2_DRIVINGDIRECTION_BACKWARD', 3: 'VCU2_DRIVINGDIRECTION_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu2_drivingdirection', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu2_211::Vcu2_drivingdirectionType Vcu2211::vcu2_drivingdirection(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(6, 2);

  Vcu2_211::Vcu2_drivingdirectionType ret =  static_cast<Vcu2_211::Vcu2_drivingdirectionType>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': 'This signal indicates the calculated acceleration pedal position in cruise control mode.', 'is_signed_var': False, 'len': 8, 'name': 'vcu2_calaccelerationpedalpositio', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
double Vcu2211::vcu2_calaccelerationpedalpositio(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal indicates the actual acceleration pedal position', 'is_signed_var': False, 'len': 8, 'name': 'vcu2_accelpedalposition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
double Vcu2211::vcu2_accelpedalposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.400000;
  return ret;
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'vcu2_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vcu2211::vcu2_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'vcu2_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vcu2211::vcu2_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
