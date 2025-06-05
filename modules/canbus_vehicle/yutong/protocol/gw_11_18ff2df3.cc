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

#include "modules/canbus_vehicle/yutong/protocol/gw_11_18ff2df3.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw1118ff2df3::Gw1118ff2df3() {}
const int32_t Gw1118ff2df3::ID = 0x18ff2df3;

void Gw1118ff2df3::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_11_18ff2df3()->set_dcdc_controller(dcdc_controller(bytes, length));
}

// config detail: {'bit': 56, 'enum': {0: 'DCDC_CONTROLLER_', 1: 'DCDC_CONTROLLER_', 2: 'DCDC_CONTROLLER_', 3: 'DCDC_CONTROLLER_'}, 'is_signed_var': False, 'len': 2, 'name': 'dcdc_controller', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_11_18ff2df3::Dcdc_controllerType Gw1118ff2df3::dcdc_controller(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 2);

  Gw_11_18ff2df3::Dcdc_controllerType ret =  static_cast<Gw_11_18ff2df3::Dcdc_controllerType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
