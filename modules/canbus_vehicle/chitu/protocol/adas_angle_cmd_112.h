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

class Adasanglecmd112 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Chitu> {
 public:
  static const int32_t ID;

  Adasanglecmd112();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Chitu* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 7, 'is_signed_var': True, 'len': 16, 'name': 'steering_angle', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-37.2|30.7]', 'physical_unit': 'degrees', 'precision': 0.002, 'type': 'double'}
  Adasanglecmd112* set_steering_angle(double steering_angle);

  // config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Ac_steering_speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-14.4|14.4]', 'physical_unit': 'degrees/s', 'precision': 0.001, 'type': 'double'}
  Adasanglecmd112* set_ac_steering_speed(double ac_steering_speed);

 private:

  // config detail: {'bit': 7, 'is_signed_var': True, 'len': 16, 'name': 'steering_angle', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-37.2|30.7]', 'physical_unit': 'degrees', 'precision': 0.002, 'type': 'double'}
  void set_p_steering_angle(uint8_t* data, double steering_angle);

  // config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Ac_steering_speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-14.4|14.4]', 'physical_unit': 'degrees/s', 'precision': 0.001, 'type': 'double'}
  void set_p_ac_steering_speed(uint8_t* data, double ac_steering_speed);

  double steering_angle(const std::uint8_t* bytes, const int32_t length) const;

  double ac_steering_speed(const std::uint8_t* bytes, const int32_t length) const;

 private:
  double steering_angle_;
  double ac_steering_speed_;
};

}  // namespace chitu
}  // namespace canbus
}  // namespace apollo


