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

#include "modules/canbus_vehicle/chitu/protocol/vcu_adas_soc_4a0.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

Vcuadassoc4a0::Vcuadassoc4a0() {}
const int32_t Vcuadassoc4a0::ID = 0x4A0;

void Vcuadassoc4a0::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_vcu_adas_soc_4a0()->set_battvolt(battvolt(bytes, length));
  chassis->mutable_vcu_adas_soc_4a0()->set_battcurr(battcurr(bytes, length));
  chassis->mutable_vcu_adas_soc_4a0()->set_soc(soc(bytes, length));
  chassis->mutable_vcu_adas_soc_4a0()->set_dischgtime(dischgtime(bytes, length));
}

// config detail: {'bit': 7, 'is_signed_var': False, 'len': 16, 'name': 'battvolt', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1000]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
double Vcuadassoc4a0::battvolt(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name': 'battcurr', 'offset': -400.0, 'order': 'motorola', 'physical_range': '[-400|1000]', 'physical_unit': 'A', 'precision': 0.1, 'type': 'double'}
double Vcuadassoc4a0::battcurr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -400.000000;
  return ret;
}

// config detail: {'bit': 39, 'is_signed_var': False, 'len': 8, 'name': 'soc', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
int Vcuadassoc4a0::soc(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 47, 'is_signed_var': False, 'len': 16, 'name': 'dischgtime', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65535]', 'physical_unit': 'h', 'precision': 1.0, 'type': 'int'}
int Vcuadassoc4a0::dischgtime(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
