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

class Vcu656c : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;
  Vcu656c();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

 private:

    // config detail: {'bit': 48, 'is_signed_var': False, 'len': 12, 'name': 'VCU6_RemainingTimes', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4095]', 'physical_unit': 'times', 'precision': 1.0, 'type': 'int'}
    int vcu6_remainingtimes(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'VCU6_AccelPedalVoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|5]', 'physical_unit': 'V', 'precision': 0.02, 'type': 'double'}
    double vcu6_accelpedalvoltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'VCU6_ThrottlePosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
    double vcu6_throttleposition(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'is_signed_var': False, 'len': 8, 'name': 'VCU6_BrakePosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
    double vcu6_brakeposition(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 20, 'enum': {0: 'VCU6_REMOTESTEERINGMODE_FRONT', 1: 'VCU6_REMOTESTEERINGMODE_REAR', 2: 'VCU6_REMOTESTEERINGMODE_OPPOSITE', 3: 'VCU6_REMOTESTEERINGMODE_SAME'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU6_RemoteSteeringMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu6_56c::Vcu6_remotesteeringmodeType vcu6_remotesteeringmode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 19, 'enum': {0: 'VCU6_REMOTECONNECT_NO_CONNECT', 1: 'VCU6_REMOTECONNECT_CONNECT'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU6_RemoteConnect', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu6_56c::Vcu6_remoteconnectType vcu6_remoteconnect(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'enum': {0: 'VCU6_CONTROLMODE_STOP', 1: 'VCU6_CONTROLMODE_REMOTE', 2: 'VCU6_CONTROLMODE_IPC', 3: 'VCU6_CONTROLMODE_TOGETHER', 4: 'VCU6_CONTROLMODE_RESERVED', 5: 'VCU6_CONTROLMODE_RESERVED', 6: 'VCU6_CONTROLMODE_RESERVED', 7: 'VCU6_CONTROLMODE_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'VCU6_ControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu6_56c::Vcu6_controlmodeType vcu6_controlmode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'VCU6_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int vcu6_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU6_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int vcu6_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'VCU6_BatterySOC', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
    double vcu6_batterysoc(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


