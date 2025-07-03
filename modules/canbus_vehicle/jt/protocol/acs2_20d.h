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

class Acs220d : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Acs220d();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 39, 'description': 'This signal indicates the validity of CAN5', 'enum': {0: 'ACS2_VALIDITYCAN7_ACTIVE', 1: 'ACS2_VALIDITYCAN7_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ValidityCAN7', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_validitycan7Type acs2_validitycan7(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 38, 'description': 'This signal indicates the validity of CAN4', 'enum': {0: 'ACS2_VALIDITYCAN6_ACTIVE', 1: 'ACS2_VALIDITYCAN6_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ValidityCAN6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_validitycan6Type acs2_validitycan6(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 37, 'description': 'This signal indicates the validity of CAN5', 'enum': {0: 'ACS2_VALIDITYCAN5_ACTIVE', 1: 'ACS2_VALIDITYCAN5_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ValidityCAN5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_validitycan5Type acs2_validitycan5(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 36, 'description': 'This signal indicates the validity of CAN4', 'enum': {0: 'ACS2_VALIDITYCAN4_ACTIVE', 1: 'ACS2_VALIDITYCAN4_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ValidityCAN4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_validitycan4Type acs2_validitycan4(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 35, 'description': 'This signal indicates the validity of CAN3', 'enum': {0: 'ACS2_VALIDITYCAN3_ACTIVE', 1: 'ACS2_VALIDITYCAN3_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ValidityCAN3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_validitycan3Type acs2_validitycan3(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 34, 'description': 'This signal indicates the validity of CAN2', 'enum': {0: 'ACS2_VALIDITYCAN2_ACTIVE', 1: 'ACS2_VALIDITYCAN2_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ValidityCAN2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_validitycan2Type acs2_validitycan2(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 33, 'description': 'This signal indicates the validity of CAN1', 'enum': {0: 'ACS2_VALIDITYCAN1_ACTIVE', 1: 'ACS2_VALIDITYCAN1_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ValidityCAN1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_validitycan1Type acs2_validitycan1(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'description': 'This signal indicates the validity of CAN0', 'enum': {0: 'ACS2_VALIDITYCAN0_ACTIVE', 1: 'ACS2_VALIDITYCAN0_DEACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ValidityCAN0', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_validitycan0Type acs2_validitycan0(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'description': 'This signal indicates the version of software', 'is_signed_var': False, 'len': 16, 'name': 'ACS2_Version', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|655.35]', 'physical_unit': 'version', 'precision': 0.01, 'type': 'double'}
    double acs2_version(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACS2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int acs2_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal indicates the state of Jerk Button', 'enum': {0: 'ACS2_BUTTONJERK_NO_PRESS', 1: 'ACS2_BUTTONJERK_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_ButtonJerk', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_buttonjerkType acs2_buttonjerk(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACS2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int acs2_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 11, 'description': 'This signal indicates the state of Button2', 'enum': {0: 'ACS2_BUTTON3_NO_PRESS', 1: 'ACS2_BUTTON3_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_Button3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_button3Type acs2_button3(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 10, 'description': 'This signal indicates the state of Button2', 'enum': {0: 'ACS2_BUTTON2_NO_PRESS', 1: 'ACS2_BUTTON2_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_Button2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_button2Type acs2_button2(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 9, 'description': 'This signal indicates the state of Button1', 'enum': {0: 'ACS2_BUTTON1_NO_PRESS', 1: 'ACS2_BUTTON1_PRESS'}, 'is_signed_var': False, 'len': 1, 'name': 'ACS2_Button1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Acs2_20d::Acs2_button1Type acs2_button1(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


