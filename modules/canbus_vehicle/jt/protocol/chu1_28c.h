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

class Chu128c : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Chu128c();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'CHU1_Temperature', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|210]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int chu1_temperature(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'is_signed_var': False, 'len': 2, 'name': 'CHU1_Status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int chu1_status(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 45, 'is_signed_var': False, 'len': 1, 'name': 'CHU1_RechargeRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool chu1_rechargerequest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'is_signed_var': False, 'len': 10, 'name': 'CHU1_OutputVoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
    int chu1_outputvoltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'is_signed_var': False, 'len': 10, 'name': 'CHU1_OutputCurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'A', 'precision': 0.1, 'type': 'double'}
    double chu1_outputcurrent(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 42, 'is_signed_var': False, 'len': 2, 'name': 'CHU1_Mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int chu1_mode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'CHU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int chu1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'is_signed_var': False, 'len': 1, 'name': 'CHU1_CPStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool chu1_cpstatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'CHU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int chu1_checksum(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


