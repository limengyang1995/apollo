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

class Chu228d : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Chu228d();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'CHU2_RemainingChargeTime', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'Min', 'precision': 5.0, 'type': 'double'}
    double chu2_remainingchargetime(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'CHU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int chu2_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 48, 'is_signed_var': False, 'len': 2, 'name': 'CHU2_InsulationMonitorWarning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int chu2_insulationmonitorwarning(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'is_signed_var': False, 'len': 12, 'name': 'CHU2_InstantPowerConsumption', 'offset': -500.0, 'order': 'intel', 'physical_range': '[-500|1500]', 'physical_unit': 'Kw', 'precision': 0.5, 'type': 'double'}
    double chu2_instantpowerconsumption(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'CHU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int chu2_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 54, 'is_signed_var': False, 'len': 2, 'name': 'CHU2_ChargeStationStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int chu2_chargestationstatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 50, 'is_signed_var': False, 'len': 2, 'name': 'CHU2_ChargeStationParameterConfi', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int chu2_chargestationparameterconfi(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'is_signed_var': False, 'len': 10, 'name': 'CHU2_ChargeStationOutputVoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
    int chu2_chargestationoutputvoltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'is_signed_var': False, 'len': 10, 'name': 'CHU2_ChargeStationOutputCurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
    int chu2_chargestationoutputcurrent(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 52, 'is_signed_var': False, 'len': 2, 'name': 'CHU2_ChargeStationHandShakeStatu', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int chu2_chargestationhandshakestatu(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


