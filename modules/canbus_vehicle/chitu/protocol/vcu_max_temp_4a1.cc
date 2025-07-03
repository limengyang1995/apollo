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

#include "modules/canbus_vehicle/chitu/protocol/vcu_max_temp_4a1.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

Vcumaxtemp4a1::Vcumaxtemp4a1() {}
const int32_t Vcumaxtemp4a1::ID = 0x4A1;

void Vcumaxtemp4a1::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_vcu_max_temp_4a1()->set_max_cell_temp(max_cell_temp(bytes, length));
  chassis->mutable_vcu_max_temp_4a1()->set_avrgcelltemp(avrgcelltemp(bytes, length));
}

// config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'max_cell_temp', 'offset': -50.0, 'order': 'motorola', 'physical_range': '[-50|250]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcumaxtemp4a1::max_cell_temp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -50.000000;
  return ret;
}

// config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'avrgcelltemp', 'offset': -50.0, 'order': 'motorola', 'physical_range': '[-50|250]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcumaxtemp4a1::avrgcelltemp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -50.000000;
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
