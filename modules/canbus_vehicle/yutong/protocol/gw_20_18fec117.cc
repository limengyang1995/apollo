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

#include "modules/canbus_vehicle/yutong/protocol/gw_20_18fec117.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw2018fec117::Gw2018fec117() {}
const int32_t Gw2018fec117::ID = 0x18fec117;

void Gw2018fec117::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_20_18fec117()->set_total_mileage_info(total_mileage_info(bytes, length));
}

// config detail: {'bit': 0, 'description': 'ֵ0-0xFFFF', 'is_signed_var': False, 'len': 32, 'name': 'total_mileage_info', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4294967295]', 'physical_unit': 'm', 'precision': 5.0, 'type': 'double'}
double Gw2018fec117::total_mileage_info(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t2(bytes + 1);
  t = t2.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t3(bytes + 0);
  t = t3.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 5.000000;
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
