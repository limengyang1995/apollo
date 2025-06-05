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

#include "modules/canbus_vehicle/yutong/protocol/gw_13_18ff32f4.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw1318ff32f4::Gw1318ff32f4() {}
const int32_t Gw1318ff32f4::ID = 0x18ff32f4;

void Gw1318ff32f4::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_13_18ff32f4()->set_single_cell_maxtemp(single_cell_maxtemp(bytes, length));
  chassis->mutable_gw_13_18ff32f4()->set_single_cell_mintemp(single_cell_mintemp(bytes, length));
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'single_cell_maxtemp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Gw1318ff32f4::single_cell_maxtemp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 8, 'name': 'single_cell_mintemp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Gw1318ff32f4::single_cell_mintemp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
