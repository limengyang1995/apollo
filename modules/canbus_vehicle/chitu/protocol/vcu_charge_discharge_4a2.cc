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

#include "modules/canbus_vehicle/chitu/protocol/vcu_charge_discharge_4a2.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

Vcuchargedischarge4a2::Vcuchargedischarge4a2() {}
const int32_t Vcuchargedischarge4a2::ID = 0x4A2;

void Vcuchargedischarge4a2::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_vcu_charge_discharge_4a2()->set_bms_status(bms_status(bytes, length));
}

// config detail: {'bit': 1, 'enum': {0: 'BMS_STATUS_NOCHARGEING_NO_DISCHARGEING', 1: 'BMS_STATUS_DISCHARGEING', 2: 'BMS_STATUS_CHARGEING'}, 'is_signed_var': False, 'len': 2, 'name': 'bms_status', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu_charge_discharge_4a2::Bms_statusType Vcuchargedischarge4a2::bms_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vcu_charge_discharge_4a2::Bms_statusType ret =  static_cast<Vcu_charge_discharge_4a2::Bms_statusType>(x);
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
