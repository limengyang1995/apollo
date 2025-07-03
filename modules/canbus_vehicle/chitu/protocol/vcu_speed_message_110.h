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

#include "modules/canbus_vehicle/chitu/proto/chitu.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace chitu {

class Vcuspeedmessage110 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Chitu> {
 public:
  static const int32_t ID;
  Vcuspeedmessage110();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Chitu* chassis) const override;

 private:

    // config detail: {'bit': 7, 'is_signed_var': True, 'len': 16, 'name': 'Actual_speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-6.9|6.9]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
    double actual_speed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Accelerated_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-2|2]', 'physical_unit': 'm/s2', 'precision': 0.0001, 'type': 'double'}
    double accelerated_speed(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace chitu
}  // namespace canbus
}  // namespace apollo


