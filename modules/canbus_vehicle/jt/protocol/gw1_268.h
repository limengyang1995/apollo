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

class Gw1268 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Gw1268();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 30, 'is_signed_var': False, 'len': 2, 'name': 'GW1_EVReady', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int gw1_evready(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'is_signed_var': False, 'len': 2, 'name': 'GW1_HVReady', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int gw1_hvready(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'GW1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int gw1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'GW1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int gw1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'description': 'This signal is drive distance since prime start', 'is_signed_var': False, 'len': 25, 'name': 'GW1_OdometerValue', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3355443]', 'physical_unit': 'km', 'precision': 0.1, 'type': 'double'}
    double gw1_odometervalue(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'Indicates the time between last KL15 Off and this KL15 on', 'is_signed_var': False, 'len': 12, 'name': 'GW1_IgnitionOffTime', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4093]', 'physical_unit': 'minute', 'precision': 1.0, 'type': 'int'}
    int gw1_ignitionofftime(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal indicates fuel value, used for powertrain diagnostic.', 'is_signed_var': False, 'len': 8, 'name': 'GW1_FuelValue', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|254]', 'physical_unit': 'L', 'precision': 1.0, 'type': 'int'}
    int gw1_fuelvalue(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


