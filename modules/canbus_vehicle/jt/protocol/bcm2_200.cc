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

#include "modules/canbus_vehicle/jt/protocol/bcm2_200.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Bcm2200::Bcm2200() {}
const int32_t Bcm2200::ID = 0x200;

void Bcm2200::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_bcm2_200()->set_key_unlock(key_unlock(bytes, length));
  chassis->mutable_bcm2_200()->set_key_lock(key_lock(bytes, length));
}

// config detail: {'bit': 1, 'is_signed_var': False, 'len': 1, 'name': 'key_unlock', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Bcm2200::key_unlock(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(1, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'key_lock', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Bcm2200::key_lock(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
