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

class Vcu1210 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Vcu1210();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 48, 'description': 'The signal indicates the actual applied overlay toque in EPS.', 'is_signed_var': False, 'len': 11, 'name': 'VCU1_OverlayInputTorque', 'offset': -10.0, 'order': 'intel', 'physical_range': '[-10|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
    double vcu1_overlayinputtorque(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 36, 'description': 'The signal indicates the torque measured by the torque sensor at the steering wheel', 'is_signed_var': False, 'len': 11, 'name': 'VCU1_HandSteeringTorque', 'offset': -10.0, 'order': 'intel', 'physical_range': '[-10|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
    double vcu1_handsteeringtorque(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'VCU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int vcu1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'VCU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int vcu1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 22, 'description': 'This signal indicates the teering wheel rotation speed. anticlockwise=negative, clockwise=positive', 'is_signed_var': False, 'len': 14, 'name': 'VCU1_SteeringSpeed', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg/s', 'precision': 0.1, 'signal_type': 'speed', 'type': 'double'}
    double vcu1_steeringspeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal indicates the angle of steering wheel. anticlockwise=negative, clockwise=positive', 'is_signed_var': False, 'len': 14, 'name': 'VCU1_SteeringAngle', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
    double vcu1_steeringangle(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


