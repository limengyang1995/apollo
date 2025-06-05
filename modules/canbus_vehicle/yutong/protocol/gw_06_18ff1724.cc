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

#include "modules/canbus_vehicle/yutong/protocol/gw_06_18ff1724.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw0618ff1724::Gw0618ff1724() {}
const int32_t Gw0618ff1724::ID = 0x18ff1724;

void Gw0618ff1724::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_06_18ff1724()->set_autohold_status_indicator(autohold_status_indicator(bytes, length));
}

// config detail: {'bit': 20, 'enum': {0: 'AUTOHOLD_STATUS_INDICATOR_', 1: 'AUTOHOLD_STATUS_INDICATOR_'}, 'is_signed_var': False, 'len': 2, 'name': 'autohold_status_indicator', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_06_18ff1724::Autohold_status_indicatorType Gw0618ff1724::autohold_status_indicator(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 2);

  Gw_06_18ff1724::Autohold_status_indicatorType ret =  static_cast<Gw_06_18ff1724::Autohold_status_indicatorType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
