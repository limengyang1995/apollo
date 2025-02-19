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

#pragma once

#include "modules/canbus_vehicle/jt/proto/jt.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace jt {

class Bcm2200 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Bcm2200();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 1, 'is_signed_var': False, 'len': 1, 'name': 'Key_Unlock', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool key_unlock(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'Key_Lock', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool key_lock(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


