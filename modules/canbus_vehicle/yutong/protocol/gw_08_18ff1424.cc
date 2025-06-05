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

#include "modules/canbus_vehicle/yutong/protocol/gw_08_18ff1424.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw0818ff1424::Gw0818ff1424() {}
const int32_t Gw0818ff1424::ID = 0x18ff1424;

void Gw0818ff1424::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_08_18ff1424()->set_electronic_parking_state(electronic_parking_state(bytes, length));
}

// config detail: {'bit': 40, 'enum': {0: 'ELECTRONIC_PARKING_STATE_', 1: 'ELECTRONIC_PARKING_STATE_'}, 'is_signed_var': False, 'len': 3, 'name': 'electronic_parking_state', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_08_18ff1424::Electronic_parking_stateType Gw0818ff1424::electronic_parking_state(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 3);

  Gw_08_18ff1424::Electronic_parking_stateType ret =  static_cast<Gw_08_18ff1424::Electronic_parking_stateType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
