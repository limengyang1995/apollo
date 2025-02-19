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

class Ur33b3 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Ur33b3();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'UR3_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int ur3_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 38, 'description': 'This signal indicates the obstacle detection distance by rear right side radar', 'is_signed_var': False, 'len': 10, 'name': 'UR3_DistanceValue_RRS', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
    int ur3_distancevalue_rrs(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'description': 'This signal indicates the obstacle detection distance by rear left side radar', 'is_signed_var': False, 'len': 10, 'name': 'UR3_DistanceValue_RLS', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
    int ur3_distancevalue_rls(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'description': 'This signal indicates the obstacle detection distance by front right side radar', 'is_signed_var': False, 'len': 10, 'name': 'UR3_DistanceValue_FRS', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
    int ur3_distancevalue_frs(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal indicates the obstacle detection distance by front left side radar', 'is_signed_var': False, 'len': 10, 'name': 'UR3_DistanceValue_FLS', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
    int ur3_distancevalue_fls(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'UR3_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int ur3_checksum(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


