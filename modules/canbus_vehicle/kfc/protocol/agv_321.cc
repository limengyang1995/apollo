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

#include "modules/canbus_vehicle/kfc/protocol/agv_321.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace kfc {

using ::apollo::drivers::canbus::Byte;

Agv321::Agv321() {}
const int32_t Agv321::ID = 0x321;

void Agv321::Parse(const std::uint8_t* bytes, int32_t length,
                         Kfc* chassis) const {
  chassis->mutable_agv_321()->set_agv_message_st(agv_message_st(bytes, length));
}

// config detail: {'bit': 0, 'enum': {0: 'AGV_MESSAGE_ST_INIVD', 1: 'AGV_MESSAGE_ST_STOP', 2: 'AGV_MESSAGE_ST_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'agv_message_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Agv_321::Agv_message_stType Agv321::agv_message_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Agv_321::Agv_message_stType ret =  static_cast<Agv_321::Agv_message_stType>(x);
  return ret;
}
}  // namespace kfc
}  // namespace canbus
}  // namespace apollo
