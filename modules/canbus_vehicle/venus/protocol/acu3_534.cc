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

#include "modules/canbus_vehicle/venus/protocol/acu3_534.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

const int32_t Acu3534::ID = 0x534;

// public
Acu3534::Acu3534() { Reset(); }

uint32_t Acu3534::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Acu3534::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_acu3_534()->set_acu3_steeringlight(acu3_steeringlight(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_hazardlight(acu3_hazardlight(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_checksum(acu3_checksum(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_brakeswitch(acu3_brakeswitch(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_beamlight(acu3_beamlight(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_backuplight(acu3_backuplight(bytes, length));
}

void Acu3534::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Acu3534::UpdateData(uint8_t* data) {
  set_p_acu3_steeringlight(data, acu3_steeringlight_);
  set_p_acu3_hazardlight(data, acu3_hazardlight_);
  set_p_acu3_checksum(data, acu3_checksum_);
  set_p_acu3_brakeswitch(data, acu3_brakeswitch_);
  set_p_acu3_beamlight(data, acu3_beamlight_);
  set_p_acu3_backuplight(data, acu3_backuplight_);
}

void Acu3534::Reset() {
  // TODO(All) :  you should check this manually
  acu3_steeringlight_ = Acu3_534::ACU3_STEERINGLIGHT_NOREQUEST;
  acu3_hazardlight_ = Acu3_534::ACU3_HAZARDLIGHT_NOREQUEST;
  acu3_checksum_ = 0;
  acu3_brakeswitch_ = Acu3_534::ACU3_BRAKESWITCH_NOREQUEST;
  acu3_beamlight_ = Acu3_534::ACU3_BEAMLIGHT_NOREQUEST;
  acu3_backuplight_ = Acu3_534::ACU3_BACKUPLIGHT_NOREQUEST;
}

Acu3534* Acu3534::set_acu3_steeringlight(
    Acu3_534::Acu3_steeringlightType acu3_steeringlight) {
  acu3_steeringlight_ = acu3_steeringlight;
  return this;
 }

// config detail: {'bit': 8, 'enum': {0: 'ACU3_STEERINGLIGHT_NOREQUEST', 1: 'ACU3_STEERINGLIGHT_LEFT', 2: 'ACU3_STEERINGLIGHT_RIGHT', 3: 'ACU3_STEERINGLIGHT_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_SteeringLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3534::set_p_acu3_steeringlight(uint8_t* data,
    Acu3_534::Acu3_steeringlightType acu3_steeringlight) {
  int x = acu3_steeringlight;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 2);
}


Acu3534* Acu3534::set_acu3_hazardlight(
    Acu3_534::Acu3_hazardlightType acu3_hazardlight) {
  acu3_hazardlight_ = acu3_hazardlight;
  return this;
 }

// config detail: {'bit': 12, 'enum': {0: 'ACU3_HAZARDLIGHT_NOREQUEST', 1: 'ACU3_HAZARDLIGHT_ON', 2: 'ACU3_HAZARDLIGHT_OFF', 3: 'ACU3_HAZARDLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_HazardLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3534::set_p_acu3_hazardlight(uint8_t* data,
    Acu3_534::Acu3_hazardlightType acu3_hazardlight) {
  int x = acu3_hazardlight;

  Byte to_set(data + 1);
  to_set.set_value(x, 4, 2);
}


Acu3534* Acu3534::set_acu3_checksum(
    int acu3_checksum) {
  acu3_checksum_ = acu3_checksum;
  return this;
 }

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACU3_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
void Acu3534::set_p_acu3_checksum(uint8_t* data,
    int acu3_checksum) {
  acu3_checksum = ProtocolData::BoundedValue(0, 255, acu3_checksum);
  int x = acu3_checksum;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


Acu3534* Acu3534::set_acu3_brakeswitch(
    Acu3_534::Acu3_brakeswitchType acu3_brakeswitch) {
  acu3_brakeswitch_ = acu3_brakeswitch;
  return this;
 }

// config detail: {'bit': 32, 'enum': {0: 'ACU3_BRAKESWITCH_NOREQUEST', 1: 'ACU3_BRAKESWITCH_ON', 2: 'ACU3_BRAKESWITCH_OFF', 3: 'ACU3_BRAKESWITCH_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BrakeSwitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3534::set_p_acu3_brakeswitch(uint8_t* data,
    Acu3_534::Acu3_brakeswitchType acu3_brakeswitch) {
  int x = acu3_brakeswitch;

  Byte to_set(data + 4);
  to_set.set_value(x, 0, 2);
}


Acu3534* Acu3534::set_acu3_beamlight(
    Acu3_534::Acu3_beamlightType acu3_beamlight) {
  acu3_beamlight_ = acu3_beamlight;
  return this;
 }

// config detail: {'bit': 10, 'enum': {0: 'ACU3_BEAMLIGHT_NOREQUEST', 1: 'ACU3_BEAMLIGHT_LOW', 2: 'ACU3_BEAMLIGHT_HIGH', 3: 'ACU3_BEAMLIGHT_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BeamLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3534::set_p_acu3_beamlight(uint8_t* data,
    Acu3_534::Acu3_beamlightType acu3_beamlight) {
  int x = acu3_beamlight;

  Byte to_set(data + 1);
  to_set.set_value(x, 2, 2);
}


Acu3534* Acu3534::set_acu3_backuplight(
    Acu3_534::Acu3_backuplightType acu3_backuplight) {
  acu3_backuplight_ = acu3_backuplight;
  return this;
 }

// config detail: {'bit': 18, 'enum': {0: 'ACU3_BACKUPLIGHT_NOREQUEST', 1: 'ACU3_BACKUPLIGHT_ON', 2: 'ACU3_BACKUPLIGHT_OFF', 3: 'ACU3_BACKUPLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_BackupLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu3534::set_p_acu3_backuplight(uint8_t* data,
    Acu3_534::Acu3_backuplightType acu3_backuplight) {
  int x = acu3_backuplight;

  Byte to_set(data + 2);
  to_set.set_value(x, 2, 2);
}


Acu3_534::Acu3_steeringlightType Acu3534::acu3_steeringlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Acu3_534::Acu3_steeringlightType ret =  static_cast<Acu3_534::Acu3_steeringlightType>(x);
  return ret;
}

Acu3_534::Acu3_hazardlightType Acu3534::acu3_hazardlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  Acu3_534::Acu3_hazardlightType ret =  static_cast<Acu3_534::Acu3_hazardlightType>(x);
  return ret;
}

int Acu3534::acu3_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

Acu3_534::Acu3_brakeswitchType Acu3534::acu3_brakeswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Acu3_534::Acu3_brakeswitchType ret =  static_cast<Acu3_534::Acu3_brakeswitchType>(x);
  return ret;
}

Acu3_534::Acu3_beamlightType Acu3534::acu3_beamlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 2);

  Acu3_534::Acu3_beamlightType ret =  static_cast<Acu3_534::Acu3_beamlightType>(x);
  return ret;
}

Acu3_534::Acu3_backuplightType Acu3534::acu3_backuplight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 2);

  Acu3_534::Acu3_backuplightType ret =  static_cast<Acu3_534::Acu3_backuplightType>(x);
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
