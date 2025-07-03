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

class Vcu2211 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Vcu2211();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 40, 'description': 'The signal indicates the actual pressure in the master cylinder.', 'is_signed_var': False, 'len': 11, 'name': 'VCU2_MasterCylinderPressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|200]', 'physical_unit': 'bar', 'precision': 0.1, 'type': 'double'}
    double vcu2_mastercylinderpressure(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 52, 'description': 'This signal indicates the brake pedal status.', 'enum': {0: 'VCU2_BRAKEPEDALST_NO_ACTUATED', 1: 'VCU2_BRAKEPEDALST_ACTUATED', 2: 'VCU2_BRAKEPEDALST_RESERVED', 3: 'VCU2_BRAKEPEDALST_ERROR'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU2_BrakePedalSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu2_211::Vcu2_brakepedalstType vcu2_brakepedalst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'description': 'The signal describes the raw vehicle speed calculated by ABS.', 'is_signed_var': False, 'len': 15, 'name': 'VCU2_VehicleSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|300]', 'physical_unit': 'km/h', 'precision': 0.01, 'signal_type': 'speed', 'type': 'double'}
    double vcu2_vehiclespeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 54, 'description': 'The signal indicates driving direction of the vehicle.', 'enum': {0: 'VCU2_DRIVINGDIRECTION_STOP', 1: 'VCU2_DRIVINGDIRECTION_FORWARD', 2: 'VCU2_DRIVINGDIRECTION_BACKWARD', 3: 'VCU2_DRIVINGDIRECTION_INVALID_VALUE'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU2_DrivingDirection', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu2_211::Vcu2_drivingdirectionType vcu2_drivingdirection(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'This signal indicates the calculated acceleration pedal position in cruise control mode.', 'is_signed_var': False, 'len': 8, 'name': 'VCU2_CalAccelerationPedalPositio', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
    double vcu2_calaccelerationpedalpositio(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal indicates the actual acceleration pedal position', 'is_signed_var': False, 'len': 8, 'name': 'VCU2_AccelPedalPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
    double vcu2_accelpedalposition(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'VCU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int vcu2_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'VCU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int vcu2_checksum(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


