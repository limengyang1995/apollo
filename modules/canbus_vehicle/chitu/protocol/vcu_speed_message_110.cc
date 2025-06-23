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

#include "modules/canbus_vehicle/chitu/protocol/vcu_speed_message_110.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

Vcuspeedmessage110::Vcuspeedmessage110() {}
const int32_t Vcuspeedmessage110::ID = 0x110;

void Vcuspeedmessage110::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_vcu_speed_message_110()->set_actual_speed(actual_speed(bytes, length));
  chassis->mutable_vcu_speed_message_110()->set_accelerated_speed(accelerated_speed(bytes, length));
}

// config detail: {'bit': 7, 'is_signed_var': True, 'len': 16, 'name': 'actual_speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-6.9|6.9]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
double Vcuspeedmessage110::actual_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.001000;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'accelerated_speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-2|2]', 'physical_unit': 'm/s2', 'precision': 0.0001, 'type': 'double'}
double Vcuspeedmessage110::accelerated_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.000100;
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
