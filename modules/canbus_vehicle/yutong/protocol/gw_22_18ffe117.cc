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

#include "modules/canbus_vehicle/yutong/protocol/gw_22_18ffe117.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw2218ffe117::Gw2218ffe117() {}
const int32_t Gw2218ffe117::ID = 0x18ffe117;

void Gw2218ffe117::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_22_18ffe117()->set_small_light_status(small_light_status(bytes, length));
}

// config detail: {'bit': 0, 'enum': {0: 'SMALL_LIGHT_STATUS_', 1: 'SMALL_LIGHT_STATUS_'}, 'is_signed_var': False, 'len': 2, 'name': 'small_light_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_22_18ffe117::Small_light_statusType Gw2218ffe117::small_light_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Gw_22_18ffe117::Small_light_statusType ret =  static_cast<Gw_22_18ffe117::Small_light_statusType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
