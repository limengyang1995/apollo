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

#include "modules/canbus_vehicle/middlecar/proto/middlecar.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace middlecar {

class Vcufsdstatus2686 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Middlecar> {
 public:
  static const int32_t ID;
  Vcufsdstatus2686();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Middlecar* chassis) const override;

 private:

    // config detail: {'bit': 32, 'description': 'Vehicle_roll_angle', 'is_signed_var': False, 'len': 12, 'name': 'VCU_FSD_VehRoll', 'offset': -180.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
    double vcu_fsd_vehroll(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'description': 'Vehicle_pitch_angle', 'is_signed_var': False, 'len': 12, 'name': 'VCU_FSD_VehPitch', 'offset': -180.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
    double vcu_fsd_vehpitch(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 21, 'description': 'Current_rear_axle_virtual_steering_wheel_angle', 'is_signed_var': False, 'len': 11, 'name': 'VCU_FSD_VehRearAngle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu_fsd_vehrearangle(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Current_vehicle_speed', 'is_signed_var': False, 'len': 10, 'name': 'VCU_FSD_VehSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|102.3]', 'physical_unit': '', 'precision': 0.1, 'signal_type': 'speed', 'type': 'double'}
    double vcu_fsd_vehspeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'VCU_FSD_RoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu_fsd_roulingcounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 10, 'description': 'Current_virtual_steering_wheel_angle_of_front_axle', 'is_signed_var': False, 'len': 11, 'name': 'VCU_FSD_VehFrontAngle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu_fsd_vehfrontangle(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo


