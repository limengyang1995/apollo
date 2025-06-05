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

#include "modules/canbus_vehicle/yutong/protocol/gw_04_18ff0824.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw0418ff0824::Gw0418ff0824() {}
const int32_t Gw0418ff0824::ID = 0x18ff0824;

void Gw0418ff0824::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_04_18ff0824()->set_state_of_vehicle(state_of_vehicle(bytes, length));
}

// config detail: {'bit': 37, 'enum': {1: 'STATE_OF_VEHICLE_STOP', 2: 'STATE_OF_VEHICLE_READY', 3: 'STATE_OF_VEHICLE_GO'}, 'is_signed_var': False, 'len': 3, 'name': 'state_of_vehicle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_04_18ff0824::State_of_vehicleType Gw0418ff0824::state_of_vehicle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(5, 3);

  Gw_04_18ff0824::State_of_vehicleType ret =  static_cast<Gw_04_18ff0824::State_of_vehicleType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
