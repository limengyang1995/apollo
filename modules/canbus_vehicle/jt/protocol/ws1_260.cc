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

#include "modules/canbus_vehicle/jt/protocol/ws1_260.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Ws1260::Ws1260() {}
const int32_t Ws1260::ID = 0x260;

void Ws1260::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_ws1_260()->set_ws1_wheelspeed_rr(ws1_wheelspeed_rr(bytes, length));
  chassis->mutable_ws1_260()->set_ws1_wheelspeed_rl(ws1_wheelspeed_rl(bytes, length));
  chassis->mutable_ws1_260()->set_ws1_wheelspeed_fr(ws1_wheelspeed_fr(bytes, length));
  chassis->mutable_ws1_260()->set_ws1_wheelspeed_fl(ws1_wheelspeed_fl(bytes, length));
}

// config detail: {'bit': 48, 'description': 'This signal is rear right wheel speed which sent by ABS without filtering.', 'is_signed_var': False, 'len': 15, 'name': 'ws1_wheelspeed_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
double Ws1260::ws1_wheelspeed_rr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 32, 'description': 'This signal is rear left wheel speed which sent by ABS without filtering.', 'is_signed_var': False, 'len': 15, 'name': 'ws1_wheelspeed_rl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
double Ws1260::ws1_wheelspeed_rl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 16, 'description': 'This signal is front right wheel speed which sent by ABS without filtering.', 'is_signed_var': False, 'len': 15, 'name': 'ws1_wheelspeed_fr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
double Ws1260::ws1_wheelspeed_fr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'This signal is front left wheel speed which sent by ABS without filtering.', 'is_signed_var': False, 'len': 15, 'name': 'ws1_wheelspeed_fl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
double Ws1260::ws1_wheelspeed_fl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
