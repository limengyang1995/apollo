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

#include "modules/canbus_vehicle/yutong/proto/yutong.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace yutong {

class Gw0219ffcb24 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw0219ffcb24();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 11, 'name': 'Average_powerConsumption', 'offset': -80.0, 'order': 'intel', 'physical_range': '[0|2047]', 'physical_unit': 'kwh/km', 'precision': 0.1, 'type': 'double'}
    double average_powerconsumption(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'is_signed_var': False, 'len': 11, 'name': 'Instantaneous_powerConsumption', 'offset': -100.0, 'order': 'intel', 'physical_range': '[0|2047]', 'physical_unit': 'kwh/km', 'precision': 0.1, 'type': 'double'}
    double instantaneous_powerconsumption(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


