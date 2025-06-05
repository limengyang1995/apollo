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

#include "modules/canbus_vehicle/yutong/proto/yutong.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace yutong {

class Gw1118ff2df3 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;
  Gw1118ff2df3();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

 private:

    // config detail: {'bit': 56, 'enum': {0: 'DCDC_CONTROLLER_', 1: 'DCDC_CONTROLLER_', 2: 'DCDC_CONTROLLER_', 3: 'DCDC_CONTROLLER_'}, 'is_signed_var': False, 'len': 2, 'name': 'DCDC_controller', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Gw_11_18ff2df3::Dcdc_controllerType dcdc_controller(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


