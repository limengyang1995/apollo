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

#include "modules/canbus_vehicle/kfc/protocol/vector__independent_sig_msg_0.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace kfc {

using ::apollo::drivers::canbus::Byte;

Vectorindependentsigmsg0::Vectorindependentsigmsg0() {}
const int32_t Vectorindependentsigmsg0::ID = 0x0;

void Vectorindependentsigmsg0::Parse(const std::uint8_t* bytes, int32_t length,
                         Kfc* chassis) const {
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu1_remotevalid(vcu1_remotevalid(bytes, length));
}

// config detail: {'bit': 0, 'description': 'Ò£¿ØÆ÷ÓÐÐ§×´Ì¬', 'enum': {0: 'VCU1_REMOTEVALID_INACTIVE', 1: 'VCU1_REMOTEVALID_TEMPORARY', 2: 'VCU1_REMOTEVALID_ACTIVE', 3: 'VCU1_REMOTEVALID_RESERVED'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu1_remotevalid', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Vcu1_remotevalidType Vectorindependentsigmsg0::vcu1_remotevalid(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Vector__independent_sig_msg_0::Vcu1_remotevalidType ret =  static_cast<Vector__independent_sig_msg_0::Vcu1_remotevalidType>(x);
  return ret;
}
}  // namespace kfc
}  // namespace canbus
}  // namespace apollo
