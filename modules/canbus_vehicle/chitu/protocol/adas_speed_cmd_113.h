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

class Adasspeedcmd113 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Chitu> {
 public:
  static const int32_t ID;

  Adasspeedcmd113();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Chitu* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 7, 'is_signed_var': True, 'len': 16, 'name': 'Vehicle_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-6.9|6.9]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
  Adasspeedcmd113* set_vehicle_speed(double vehicle_speed);

  // config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Accelerated_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-2|2]', 'physical_unit': 'm/s2', 'precision': 0.0001, 'type': 'double'}
  Adasspeedcmd113* set_accelerated_speed(double accelerated_speed);

 private:

  // config detail: {'bit': 7, 'is_signed_var': True, 'len': 16, 'name': 'Vehicle_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-6.9|6.9]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
  void set_p_vehicle_speed(uint8_t* data, double vehicle_speed);

  // config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Accelerated_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-2|2]', 'physical_unit': 'm/s2', 'precision': 0.0001, 'type': 'double'}
  void set_p_accelerated_speed(uint8_t* data, double accelerated_speed);

  double vehicle_speed(const std::uint8_t* bytes, const int32_t length) const;

  double accelerated_speed(const std::uint8_t* bytes, const int32_t length) const;

 private:
  double vehicle_speed_;
  double accelerated_speed_;
};

}  // namespace chitu
}  // namespace canbus
}  // namespace apollo


