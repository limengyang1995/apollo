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

class Ur13b1 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Ur13b1();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'UR1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int ur1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 38, 'description': 'This signal indicates the obstacle detection distance by front right radar', 'is_signed_var': False, 'len': 10, 'name': 'UR1_DistanceValue_FR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
    int ur1_distancevalue_fr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'description': 'This signal indicates the obstacle detection distance by front middle right radar', 'is_signed_var': False, 'len': 10, 'name': 'UR1_DistanceValue_FMR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
    int ur1_distancevalue_fmr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'description': 'This signal indicates the obstacle detection distance by front middle left radar', 'is_signed_var': False, 'len': 10, 'name': 'UR1_DistanceValue_FML', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
    int ur1_distancevalue_fml(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal indicates the obstacle detection distance by front left radar', 'is_signed_var': False, 'len': 10, 'name': 'UR1_DistanceValue_FL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'cm', 'precision': 1.0, 'type': 'int'}
    int ur1_distancevalue_fl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'UR1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int ur1_checksum(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


