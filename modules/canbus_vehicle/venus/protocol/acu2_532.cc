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

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

const int32_t Acu2532::ID = 0x532;

// public
Acu2532::Acu2532() { Reset(); }

uint32_t Acu2532::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

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

void Acu2532::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Acu2532::UpdateData(uint8_t* data) {
  set_p_acu2_axialautocontrol(data, acu2_axialautocontrol_);
  set_p_acu2_targetvehiclespeed(data, acu2_targetvehiclespeed_);
  set_p_acu2_targettorque(data, acu2_targettorque_);
  set_p_acu2_targetbrakingposition(data, acu2_targetbrakingposition_);
  set_p_acu2_targetacceleratorposition(data, acu2_targetacceleratorposition_);
  set_p_acu2_brakingcontrolmode(data, acu2_brakingcontrolmode_);
  set_p_acu2_acceleratorcontrolmode(data, acu2_acceleratorcontrolmode_);
  set_p_acu2_targetaxialacceldecel(data, acu2_targetaxialacceldecel_);
  set_p_acu2_livecounter(data, acu2_livecounter_);
  set_p_acu2_checksum(data, acu2_checksum_);
}

void Acu2532::Reset() {
  // TODO(All) :  you should check this manually
  acu2_axialautocontrol_ = Acu2_532::ACU2_AXIALAUTOCONTROL_NOREQUET;
  acu2_targetvehiclespeed_ = 0.0;
  acu2_targettorque_ = 0.0;
  acu2_targetbrakingposition_ = 0;
  acu2_targetacceleratorposition_ = 0;
  acu2_brakingcontrolmode_ = Acu2_532::ACU2_BRAKINGCONTROLMODE_POSITION;
  acu2_acceleratorcontrolmode_ = Acu2_532::ACU2_ACCELERATORCONTROLMODE_POSITION;
  acu2_targetaxialacceldecel_ = 0.0;
  acu2_livecounter_ = 0;
  acu2_checksum_ = 0;
}

Acu2532* Acu2532::set_acu2_axialautocontrol(
    Acu2_532::Acu2_axialautocontrolType acu2_axialautocontrol) {
  acu2_axialautocontrol_ = acu2_axialautocontrol;
  return this;
 }

// config detail: {'bit': 34, 'enum': {0: 'ACU2_AXIALAUTOCONTROL_NOREQUET', 1: 'ACU2_AXIALAUTOCONTROL_REQUEST', 2: 'ACU2_AXIALAUTOCONTROL_RESERVE1', 3: 'ACU2_AXIALAUTOCONTROL_RESERVE2'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_AxialAutoControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu2532::set_p_acu2_axialautocontrol(uint8_t* data,
    Acu2_532::Acu2_axialautocontrolType acu2_axialautocontrol) {
  int x = acu2_axialautocontrol;

  Byte to_set(data + 4);
  to_set.set_value(x, 2, 2);
}


Acu2532* Acu2532::set_acu2_targetvehiclespeed(
    double acu2_targetvehiclespeed) {
  acu2_targetvehiclespeed_ = acu2_targetvehiclespeed;
  return this;
 }

// config detail: {'bit': 50, 'is_signed_var': False, 'len': 10, 'name': 'ACU2_TargetVehicleSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'km/h', 'precision': 0.1, 'type': 'double'}
void Acu2532::set_p_acu2_targetvehiclespeed(uint8_t* data,
    double acu2_targetvehiclespeed) {
  acu2_targetvehiclespeed = ProtocolData::BoundedValue(0.0, 100.0, acu2_targetvehiclespeed);
  int x = acu2_targetvehiclespeed / 0.100000;
  uint8_t t = 0;

  t = x & 0x3F;
  Byte to_set0(data + 6);
  to_set0.set_value(t, 2, 6);
  x >>= 6;

  t = x & 0xF;
  Byte to_set1(data + 7);
  to_set1.set_value(t, 0, 4);
}


Acu2532* Acu2532::set_acu2_targettorque(
    double acu2_targettorque) {
  acu2_targettorque_ = acu2_targettorque;
  return this;
 }

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 10, 'name': 'ACU2_TargetTorque', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
void Acu2532::set_p_acu2_targettorque(uint8_t* data,
    double acu2_targettorque) {
  acu2_targettorque = ProtocolData::BoundedValue(0.0, 100.0, acu2_targettorque);
  int x = acu2_targettorque / 0.100000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 5);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0x3;
  Byte to_set1(data + 6);
  to_set1.set_value(t, 0, 2);
}


Acu2532* Acu2532::set_acu2_targetbrakingposition(
    int acu2_targetbrakingposition) {
  acu2_targetbrakingposition_ = acu2_targetbrakingposition;
  return this;
 }

// config detail: {'bit': 27, 'is_signed_var': False, 'len': 7, 'name': 'ACU2_TargetBrakingPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
void Acu2532::set_p_acu2_targetbrakingposition(uint8_t* data,
    int acu2_targetbrakingposition) {
  acu2_targetbrakingposition = ProtocolData::BoundedValue(0, 100, acu2_targetbrakingposition);
  int x = acu2_targetbrakingposition;
  uint8_t t = 0;

  t = x & 0x1F;
  Byte to_set0(data + 3);
  to_set0.set_value(t, 3, 5);
  x >>= 5;

  t = x & 0x3;
  Byte to_set1(data + 4);
  to_set1.set_value(t, 0, 2);
}


Acu2532* Acu2532::set_acu2_targetacceleratorposition(
    int acu2_targetacceleratorposition) {
  acu2_targetacceleratorposition_ = acu2_targetacceleratorposition;
  return this;
 }

// config detail: {'bit': 20, 'is_signed_var': False, 'len': 7, 'name': 'ACU2_TargetAcceleratorPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
void Acu2532::set_p_acu2_targetacceleratorposition(uint8_t* data,
    int acu2_targetacceleratorposition) {
  acu2_targetacceleratorposition = ProtocolData::BoundedValue(0, 100, acu2_targetacceleratorposition);
  int x = acu2_targetacceleratorposition;
  uint8_t t = 0;

  t = x & 0xF;
  Byte to_set0(data + 2);
  to_set0.set_value(t, 4, 4);
  x >>= 4;

  t = x & 0x7;
  Byte to_set1(data + 3);
  to_set1.set_value(t, 0, 3);
}


Acu2532* Acu2532::set_acu2_brakingcontrolmode(
    Acu2_532::Acu2_brakingcontrolmodeType acu2_brakingcontrolmode) {
  acu2_brakingcontrolmode_ = acu2_brakingcontrolmode;
  return this;
 }

// config detail: {'bit': 38, 'enum': {0: 'ACU2_BRAKINGCONTROLMODE_POSITION', 1: 'ACU2_BRAKINGCONTROLMODE_DECELACC', 2: 'ACU2_BRAKINGCONTROLMODE_DECELAEB', 3: 'ACU2_BRAKINGCONTROLMODE_ESP'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_BrakingControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu2532::set_p_acu2_brakingcontrolmode(uint8_t* data,
    Acu2_532::Acu2_brakingcontrolmodeType acu2_brakingcontrolmode) {
  int x = acu2_brakingcontrolmode;

  Byte to_set(data + 4);
  to_set.set_value(x, 6, 2);
}


Acu2532* Acu2532::set_acu2_acceleratorcontrolmode(
    Acu2_532::Acu2_acceleratorcontrolmodeType acu2_acceleratorcontrolmode) {
  acu2_acceleratorcontrolmode_ = acu2_acceleratorcontrolmode;
  return this;
 }

// config detail: {'bit': 36, 'enum': {0: 'ACU2_ACCELERATORCONTROLMODE_POSITION', 1: 'ACU2_ACCELERATORCONTROLMODE_ACCEL', 2: 'ACU2_ACCELERATORCONTROLMODE_TORQUE', 3: 'ACU2_ACCELERATORCONTROLMODE_VEHICLESPEED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU2_AcceleratorControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu2532::set_p_acu2_acceleratorcontrolmode(uint8_t* data,
    Acu2_532::Acu2_acceleratorcontrolmodeType acu2_acceleratorcontrolmode) {
  int x = acu2_acceleratorcontrolmode;

  Byte to_set(data + 4);
  to_set.set_value(x, 4, 2);
}


Acu2532* Acu2532::set_acu2_targetaxialacceldecel(
    double acu2_targetaxialacceldecel) {
  acu2_targetaxialacceldecel_ = acu2_targetaxialacceldecel;
  return this;
 }

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 12, 'name': 'ACU2_TargetAxialAccelDecel', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
void Acu2532::set_p_acu2_targetaxialacceldecel(uint8_t* data,
    double acu2_targetaxialacceldecel) {
  acu2_targetaxialacceldecel = ProtocolData::BoundedValue(-20.0, 20.0, acu2_targetaxialacceldecel);
  int x = (acu2_targetaxialacceldecel - -20.000000) / 0.010000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 1);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xF;
  Byte to_set1(data + 2);
  to_set1.set_value(t, 0, 4);
}


Acu2532* Acu2532::set_acu2_livecounter(
    int acu2_livecounter) {
  acu2_livecounter_ = acu2_livecounter;
  return this;
 }

// config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'ACU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
void Acu2532::set_p_acu2_livecounter(uint8_t* data,
    int acu2_livecounter) {
  acu2_livecounter = ProtocolData::BoundedValue(0, 15, acu2_livecounter);
  int x = acu2_livecounter;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


Acu2532* Acu2532::set_acu2_checksum(
    int acu2_checksum) {
  acu2_checksum_ = acu2_checksum;
  return this;
 }

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
void Acu2532::set_p_acu2_checksum(uint8_t* data,
    int acu2_checksum) {
  acu2_checksum = ProtocolData::BoundedValue(0, 255, acu2_checksum);
  int x = acu2_checksum;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


Acu2_532::Acu2_axialautocontrolType Acu2532::acu2_axialautocontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(2, 2);

  Acu2_532::Acu2_axialautocontrolType ret =  static_cast<Acu2_532::Acu2_axialautocontrolType>(x);
  return ret;
}

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

Acu2_532::Acu2_brakingcontrolmodeType Acu2532::acu2_brakingcontrolmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(6, 2);

  Acu2_532::Acu2_brakingcontrolmodeType ret =  static_cast<Acu2_532::Acu2_brakingcontrolmodeType>(x);
  return ret;
}

Acu2_532::Acu2_acceleratorcontrolmodeType Acu2532::acu2_acceleratorcontrolmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(4, 2);

  Acu2_532::Acu2_acceleratorcontrolmodeType ret =  static_cast<Acu2_532::Acu2_acceleratorcontrolmodeType>(x);
  return ret;
}

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

int Acu2532::acu2_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

int Acu2532::acu2_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
