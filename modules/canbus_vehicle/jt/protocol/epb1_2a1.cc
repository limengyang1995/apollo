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

#include "modules/canbus_vehicle/jt/protocol/epb1_2a1.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Epb12a1::Epb12a1() {}
const int32_t Epb12a1::ID = 0x2A1;

void Epb12a1::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_epb1_2a1()->set_epb1_livecounter(epb1_livecounter(bytes, length));
  chassis->mutable_epb1_2a1()->set_epb1_epbswitch(epb1_epbswitch(bytes, length));
  chassis->mutable_epb1_2a1()->set_epb1_epbstatus(epb1_epbstatus(bytes, length));
  chassis->mutable_epb1_2a1()->set_epb1_checksum(epb1_checksum(bytes, length));
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'epb1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Epb12a1::epb1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 12, 'description': '0:no request 1: lock 2 :release 3: reserved', 'is_signed_var': False, 'len': 2, 'name': 'epb1_epbswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Epb12a1::epb1_epbswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 14, 'description': '0: released 1: locked 2: releasing 3:locking', 'is_signed_var': False, 'len': 2, 'name': 'epb1_epbstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Epb12a1::epb1_epbstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(6, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'epb1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Epb12a1::epb1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
