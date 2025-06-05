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

#include "modules/canbus_vehicle/yutong/protocol/gw_18_19fff103.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw1819fff103::Gw1819fff103() {}
const int32_t Gw1819fff103::ID = 0x19fff103;

void Gw1819fff103::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_18_19fff103()->set_fault_code(fault_code(bytes, length));
  chassis->mutable_gw_18_19fff103()->set_level_of_failure(level_of_failure(bytes, length));
}

// config detail: {'bit': 56, 'description': '0', 'enum': {0: 'FAULT_CODE_'}, 'is_signed_var': False, 'len': 6, 'name': 'fault_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|63]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_18_19fff103::Fault_codeType Gw1819fff103::fault_code(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 6);

  Gw_18_19fff103::Fault_codeType ret =  static_cast<Gw_18_19fff103::Fault_codeType>(x);
  return ret;
}

// config detail: {'bit': 62, 'enum': {0: 'LEVEL_OF_FAILURE_', 1: 'LEVEL_OF_FAILURE_', 2: 'LEVEL_OF_FAILURE_', 3: 'LEVEL_OF_FAILURE_'}, 'is_signed_var': False, 'len': 2, 'name': 'level_of_failure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_18_19fff103::Level_of_failureType Gw1819fff103::level_of_failure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(6, 2);

  Gw_18_19fff103::Level_of_failureType ret =  static_cast<Gw_18_19fff103::Level_of_failureType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
