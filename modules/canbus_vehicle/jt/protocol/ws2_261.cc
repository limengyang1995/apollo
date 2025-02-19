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

#include "modules/canbus_vehicle/jt/protocol/ws2_261.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Ws2261::Ws2261() {}
const int32_t Ws2261::ID = 0x261;

void Ws2261::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_ws2_261()->set_ws2_livecounter(ws2_livecounter(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_checksum(ws2_checksum(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_wheelspeeddirection_rr(ws2_wheelspeeddirection_rr(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_wheelspeeddirection_rl(ws2_wheelspeeddirection_rl(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_wheelspeeddirection_fr(ws2_wheelspeeddirection_fr(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_wheelspeeddirection_fl(ws2_wheelspeeddirection_fl(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_wheelpulse_rr(ws2_wheelpulse_rr(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_wheelpulse_rl(ws2_wheelpulse_rl(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_wheelpulse_fr(ws2_wheelpulse_fr(bytes, length));
  chassis->mutable_ws2_261()->set_ws2_wheelpulse_fl(ws2_wheelpulse_fl(bytes, length));
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ws2_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Ws2261::ws2_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ws2_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Ws2261::ws2_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 46, 'description': 'This signal is the the rear right  wheel speed direction.', 'enum': {0: 'WS2_WHEELSPEEDDIRECTION_RR_STOP', 1: 'WS2_WHEELSPEEDDIRECTION_RR_FORWARD', 2: 'WS2_WHEELSPEEDDIRECTION_RR_BACKWARD', 3: 'WS2_WHEELSPEEDDIRECTION_RR_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'ws2_wheelspeeddirection_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
Ws2_261::Ws2_wheelspeeddirection_rrType Ws2261::ws2_wheelspeeddirection_rr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(6, 2);

  Ws2_261::Ws2_wheelspeeddirection_rrType ret =  static_cast<Ws2_261::Ws2_wheelspeeddirection_rrType>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': 'This signal is the the rear left wheel speed direction.', 'enum': {0: 'WS2_WHEELSPEEDDIRECTION_RL_STOP', 1: 'WS2_WHEELSPEEDDIRECTION_RL_FORWARD', 2: 'WS2_WHEELSPEEDDIRECTION_RL_BACKWARD', 3: 'WS2_WHEELSPEEDDIRECTION_RL_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'ws2_wheelspeeddirection_rl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
Ws2_261::Ws2_wheelspeeddirection_rlType Ws2261::ws2_wheelspeeddirection_rl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(4, 2);

  Ws2_261::Ws2_wheelspeeddirection_rlType ret =  static_cast<Ws2_261::Ws2_wheelspeeddirection_rlType>(x);
  return ret;
}

// config detail: {'bit': 42, 'description': 'This signal is the the front right wheel speed direction.', 'enum': {0: 'WS2_WHEELSPEEDDIRECTION_FR_STOP', 1: 'WS2_WHEELSPEEDDIRECTION_FR_FORWARD', 2: 'WS2_WHEELSPEEDDIRECTION_FR_BACKWARD', 3: 'WS2_WHEELSPEEDDIRECTION_FR_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'ws2_wheelspeeddirection_fr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
Ws2_261::Ws2_wheelspeeddirection_frType Ws2261::ws2_wheelspeeddirection_fr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(2, 2);

  Ws2_261::Ws2_wheelspeeddirection_frType ret =  static_cast<Ws2_261::Ws2_wheelspeeddirection_frType>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': 'This signal is the the front left wheel speed direction.', 'enum': {0: 'WS2_WHEELSPEEDDIRECTION_FL_STOP', 1: 'WS2_WHEELSPEEDDIRECTION_FL_FORWARD', 2: 'WS2_WHEELSPEEDDIRECTION_FL_BACKWARD', 3: 'WS2_WHEELSPEEDDIRECTION_FL_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'ws2_wheelspeeddirection_fl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
Ws2_261::Ws2_wheelspeeddirection_flType Ws2261::ws2_wheelspeeddirection_fl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 2);

  Ws2_261::Ws2_wheelspeeddirection_flType ret =  static_cast<Ws2_261::Ws2_wheelspeeddirection_flType>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': 'This signal is the rear right wheel speed pulse(raw data).', 'is_signed_var': False, 'len': 8, 'name': 'ws2_wheelpulse_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'pulse', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
int Ws2261::ws2_wheelpulse_rr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 24, 'description': 'This signal is the rear left wheel speed pulse(raw data).', 'is_signed_var': False, 'len': 8, 'name': 'ws2_wheelpulse_rl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'pulse', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
int Ws2261::ws2_wheelpulse_rl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 16, 'description': 'This signal is the front right wheel speed pulse(raw data).', 'is_signed_var': False, 'len': 8, 'name': 'ws2_wheelpulse_fr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'pulse', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
int Ws2261::ws2_wheelpulse_fr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal is the front left wheel speed pulse(raw data).', 'is_signed_var': False, 'len': 8, 'name': 'ws2_wheelpulse_fl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'pulse', 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
int Ws2261::ws2_wheelpulse_fl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
