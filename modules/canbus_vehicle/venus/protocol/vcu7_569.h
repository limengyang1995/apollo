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

class Vcu7569 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;
  Vcu7569();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

 private:

    // config detail: {'bit': 59, 'enum': {0: 'VCU7_MCUBRAKESTATE_OFF', 1: 'VCU7_MCUBRAKESTATE_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU7_MCUBrakeState', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu7_569::Vcu7_mcubrakestateType vcu7_mcubrakestate(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'is_signed_var': False, 'len': 13, 'name': 'VCU7_BatteryVoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
    double vcu7_batteryvoltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 45, 'is_signed_var': False, 'len': 11, 'name': 'VCU7_BatteryCurrent', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|100]', 'physical_unit': 'A', 'precision': 0.1, 'type': 'double'}
    double vcu7_batterycurrent(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'VCU7_MotorSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
    int vcu7_motorspeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 58, 'enum': {0: 'VCU7_MCUSPEEDMODE_LOW', 1: 'VCU7_MCUSPEEDMODE_HIGH'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU7_MCUSpeedMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu7_569::Vcu7_mcuspeedmodeType vcu7_mcuspeedmode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 57, 'enum': {0: 'VCU7_MCURELAYSTATE_OFF', 1: 'VCU7_MCURELAYSTATE_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU7_MCURelayState', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu7_569::Vcu7_mcurelaystateType vcu7_mcurelaystate(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 56, 'enum': {0: 'VCU7_MCULOWPOWER_INACTIVE', 1: 'VCU7_MCULOWPOWER_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU7_MCULowPower', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu7_569::Vcu7_mculowpowerType vcu7_mculowpower(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'VCU7_MCUErrorCode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu7_mcuerrorcode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'is_signed_var': False, 'len': 4, 'name': 'VCU7_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int vcu7_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU7_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int vcu7_checksum(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


