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

#include "modules/canbus_vehicle/yutong/protocol/gw_24_18a70017.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw2418a70017::Gw2418a70017() {}
const int32_t Gw2418a70017::ID = 0x18a70017;

void Gw2418a70017::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_24_18a70017()->set_horn_signal(horn_signal(bytes, length));
  chassis->mutable_gw_24_18a70017()->set_fog_light_signal(fog_light_signal(bytes, length));
  chassis->mutable_gw_24_18a70017()->set_low_beam_signal(low_beam_signal(bytes, length));
  chassis->mutable_gw_24_18a70017()->set_high_beam_signal(high_beam_signal(bytes, length));
  chassis->mutable_gw_24_18a70017()->set_left_turn_signal(left_turn_signal(bytes, length));
  chassis->mutable_gw_24_18a70017()->set_right_turn_signal(right_turn_signal(bytes, length));
  chassis->mutable_gw_24_18a70017()->set_brakingsts(brakingsts(bytes, length));
}

// config detail: {'bit': 24, 'enum': {0: 'HORN_SIGNAL_OFF', 1: 'HORN_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'horn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_24_18a70017::Horn_signalType Gw2418a70017::horn_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 2);

  Gw_24_18a70017::Horn_signalType ret =  static_cast<Gw_24_18a70017::Horn_signalType>(x);
  return ret;
}

// config detail: {'bit': 27, 'enum': {0: 'FOG_LIGHT_SIGNAL_OFF', 1: 'FOG_LIGHT_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'fog_light_signal', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_24_18a70017::Fog_light_signalType Gw2418a70017::fog_light_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(2, 2);

  Gw_24_18a70017::Fog_light_signalType ret =  static_cast<Gw_24_18a70017::Fog_light_signalType>(x);
  return ret;
}

// config detail: {'bit': 28, 'enum': {0: 'LOW_BEAM_SIGNAL_OFF', 1: 'LOW_BEAM_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'low_beam_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_24_18a70017::Low_beam_signalType Gw2418a70017::low_beam_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  Gw_24_18a70017::Low_beam_signalType ret =  static_cast<Gw_24_18a70017::Low_beam_signalType>(x);
  return ret;
}

// config detail: {'bit': 30, 'enum': {0: 'HIGH_BEAM_SIGNAL_OFF', 1: 'HIGH_BEAM_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'high_beam_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_24_18a70017::High_beam_signalType Gw2418a70017::high_beam_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(6, 2);

  Gw_24_18a70017::High_beam_signalType ret =  static_cast<Gw_24_18a70017::High_beam_signalType>(x);
  return ret;
}

// config detail: {'bit': 32, 'enum': {0: 'LEFT_TURN_SIGNAL_OFF', 1: 'LEFT_TURN_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'left_turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_24_18a70017::Left_turn_signalType Gw2418a70017::left_turn_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Gw_24_18a70017::Left_turn_signalType ret =  static_cast<Gw_24_18a70017::Left_turn_signalType>(x);
  return ret;
}

// config detail: {'bit': 34, 'enum': {0: 'RIGHT_TURN_SIGNAL_OFF', 1: 'RIGHT_TURN_SIGNAL_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'right_turn_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_24_18a70017::Right_turn_signalType Gw2418a70017::right_turn_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(2, 2);

  Gw_24_18a70017::Right_turn_signalType ret =  static_cast<Gw_24_18a70017::Right_turn_signalType>(x);
  return ret;
}

// config detail: {'bit': 36, 'enum': {0: 'BRAKINGSTS_OFF', 1: 'BRAKINGSTS_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'brakingsts', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_24_18a70017::BrakingstsType Gw2418a70017::brakingsts(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(4, 2);

  Gw_24_18a70017::BrakingstsType ret =  static_cast<Gw_24_18a70017::BrakingstsType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
