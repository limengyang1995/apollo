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

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Acu3534::Acu3534() {}
const int32_t Acu3534::ID = 0x534;

void Acu3534::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_acu3_534()->set_acu3_steeringlight(acu3_steeringlight(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_hazardlight(acu3_hazardlight(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_checksum(acu3_checksum(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_brakeswitch(acu3_brakeswitch(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_beamlight(acu3_beamlight(bytes, length));
  chassis->mutable_acu3_534()->set_acu3_backuplight(acu3_backuplight(bytes, length));
}

// config detail: {'bit': 8, 'enum': {0: 'ACU3_STEERINGLIGHT_NOREQUEST', 1: 'ACU3_STEERINGLIGHT_LEFT', 2: 'ACU3_STEERINGLIGHT_RIGHT', 3: 'ACU3_STEERINGLIGHT_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_steeringlight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu3_534::Acu3_steeringlightType Acu3534::acu3_steeringlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Acu3_534::Acu3_steeringlightType ret =  static_cast<Acu3_534::Acu3_steeringlightType>(x);
  return ret;
}

// config detail: {'bit': 12, 'enum': {0: 'ACU3_HAZARDLIGHT_NOREQUEST', 1: 'ACU3_HAZARDLIGHT_ON', 2: 'ACU3_HAZARDLIGHT_OFF', 3: 'ACU3_HAZARDLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_hazardlight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu3_534::Acu3_hazardlightType Acu3534::acu3_hazardlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  Acu3_534::Acu3_hazardlightType ret =  static_cast<Acu3_534::Acu3_hazardlightType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acu3_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Acu3534::acu3_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 32, 'enum': {0: 'ACU3_BRAKESWITCH_NOREQUEST', 1: 'ACU3_BRAKESWITCH_ON', 2: 'ACU3_BRAKESWITCH_OFF', 3: 'ACU3_BRAKESWITCH_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_brakeswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu3_534::Acu3_brakeswitchType Acu3534::acu3_brakeswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Acu3_534::Acu3_brakeswitchType ret =  static_cast<Acu3_534::Acu3_brakeswitchType>(x);
  return ret;
}

// config detail: {'bit': 10, 'enum': {0: 'ACU3_BEAMLIGHT_NOREQUEST', 1: 'ACU3_BEAMLIGHT_LOW', 2: 'ACU3_BEAMLIGHT_HIGH', 3: 'ACU3_BEAMLIGHT_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_beamlight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu3_534::Acu3_beamlightType Acu3534::acu3_beamlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 2);

  Acu3_534::Acu3_beamlightType ret =  static_cast<Acu3_534::Acu3_beamlightType>(x);
  return ret;
}

// config detail: {'bit': 18, 'enum': {0: 'ACU3_BACKUPLIGHT_NOREQUEST', 1: 'ACU3_BACKUPLIGHT_ON', 2: 'ACU3_BACKUPLIGHT_OFF', 3: 'ACU3_BACKUPLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_backuplight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Acu3_534::Acu3_backuplightType Acu3534::acu3_backuplight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 2);

  Acu3_534::Acu3_backuplightType ret =  static_cast<Acu3_534::Acu3_backuplightType>(x);
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
