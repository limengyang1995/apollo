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

#include "modules/canbus_vehicle/venus/proto/venus.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace venus {

class Vcu3256d : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;
  Vcu3256d();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

 private:

    // config detail: {'bit': 48, 'is_signed_var': False, 'len': 15, 'name': 'VCU3_WheelSpeedRR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double vcu3_wheelspeedrr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'is_signed_var': False, 'len': 15, 'name': 'VCU3_WheelSpeedRL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double vcu3_wheelspeedrl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'is_signed_var': False, 'len': 15, 'name': 'VCU3_WheelSpeedFR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double vcu3_wheelspeedfr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'VCU3_WheelSpeedFL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double vcu3_wheelspeedfl(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


