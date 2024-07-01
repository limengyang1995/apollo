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

#include "modules/canbus_vehicle/venus/protocol/acu2_532.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Acu2532::Acu2532() {}
const int32_t Acu2532::ID = 0x532;

void Acu2532::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_acu2_532()->set_acu2_axialautocontrol(acu2_axialautocontrol(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_targetvehiclespeed(acu2_targetvehiclespeed(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_targettorque(acu2_targettorque(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_targetbrakingposition(acu2_targetbrakingposition(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_targetacceleratorposition(acu2_targetacceleratorposition(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_brakingcontrolmode(acu2_brakingcontrolmode(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_acceleratorcontrolmode(acu2_acceleratorcontrolmode(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_targetaxialacceldecel(acu2_targetaxialacceldecel(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_livecounter(acu2_livecounter(bytes, length));
  chassis->mutable_acu2_532()->set_acu2_checksum(acu2_checksum(bytes, length));
}

// config detail: {'bit': 34, 'enum': {0: 'ACU2_AXIALAUTOCONTROL_NOREQUET', 1: 'ACU2_AXIALAUTOCONTROL_REQUEST', 2: 'ACU2_AXIALAUTOCONTROL_RESERVE1', 3: 'ACU2_AXIALAUTOCONTROL_RESERVE2'}, 'is_signed_var': False, 'len': 2, 'name': 'acu2_axialautocontrol', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu2_532::Acu2_axialautocontrolType Acu2532::acu2_axialautocontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(2, 2);

  Acu2_532::Acu2_axialautocontrolType ret =  static_cast<Acu2_532::Acu2_axialautocontrolType>(x);
  return ret;
}

// config detail: {'bit': 50, 'is_signed_var': False, 'len': 10, 'name': 'acu2_targetvehiclespeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'km/h', 'precision': 0.1, 'type': 'double'}
double Acu2532::acu2_targetvehiclespeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(2, 6);
  x <<= 6;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 10, 'name': 'acu2_targettorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
double Acu2532::acu2_targettorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 27, 'is_signed_var': False, 'len': 7, 'name': 'acu2_targetbrakingposition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
int Acu2532::acu2_targetbrakingposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(3, 5);
  x <<= 5;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 20, 'is_signed_var': False, 'len': 7, 'name': 'acu2_targetacceleratorposition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
int Acu2532::acu2_targetacceleratorposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 38, 'enum': {0: 'ACU2_BRAKINGCONTROLMODE_POSITION', 1: 'ACU2_BRAKINGCONTROLMODE_DECELACC', 2: 'ACU2_BRAKINGCONTROLMODE_DECELAEB', 3: 'ACU2_BRAKINGCONTROLMODE_ESP'}, 'is_signed_var': False, 'len': 2, 'name': 'acu2_brakingcontrolmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu2_532::Acu2_brakingcontrolmodeType Acu2532::acu2_brakingcontrolmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(6, 2);

  Acu2_532::Acu2_brakingcontrolmodeType ret =  static_cast<Acu2_532::Acu2_brakingcontrolmodeType>(x);
  return ret;
}

// config detail: {'bit': 36, 'enum': {0: 'ACU2_ACCELERATORCONTROLMODE_POSITION', 1: 'ACU2_ACCELERATORCONTROLMODE_ACCEL', 2: 'ACU2_ACCELERATORCONTROLMODE_TORQUE', 3: 'ACU2_ACCELERATORCONTROLMODE_VEHICLESPEED'}, 'is_signed_var': False, 'len': 2, 'name': 'acu2_acceleratorcontrolmode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu2_532::Acu2_acceleratorcontrolmodeType Acu2532::acu2_acceleratorcontrolmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(4, 2);

  Acu2_532::Acu2_acceleratorcontrolmodeType ret =  static_cast<Acu2_532::Acu2_acceleratorcontrolmodeType>(x);
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 12, 'name': 'acu2_targetaxialacceldecel', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
double Acu2532::acu2_targetaxialacceldecel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -20.000000;
  return ret;
}

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'acu2_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Acu2532::acu2_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acu2_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Acu2532::acu2_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
