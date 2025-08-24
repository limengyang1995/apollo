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

#include "modules/canbus_vehicle/middlecar/protocol/vcu_fsd_status2_686.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace middlecar {

using ::apollo::drivers::canbus::Byte;

Vcufsdstatus2686::Vcufsdstatus2686() {}
const int32_t Vcufsdstatus2686::ID = 0x686;

void Vcufsdstatus2686::Parse(const std::uint8_t* bytes, int32_t length,
                         Middlecar* chassis) const {
  chassis->mutable_vcu_fsd_status2_686()->set_vcu_fsd_vehroll(vcu_fsd_vehroll(bytes, length));
  chassis->mutable_vcu_fsd_status2_686()->set_vcu_fsd_vehpitch(vcu_fsd_vehpitch(bytes, length));
  chassis->mutable_vcu_fsd_status2_686()->set_vcu_fsd_vehrearangle(vcu_fsd_vehrearangle(bytes, length));
  chassis->mutable_vcu_fsd_status2_686()->set_vcu_fsd_vehspeed(vcu_fsd_vehspeed(bytes, length));
  chassis->mutable_vcu_fsd_status2_686()->set_vcu_fsd_roulingcounter(vcu_fsd_roulingcounter(bytes, length));
  chassis->mutable_vcu_fsd_status2_686()->set_vcu_fsd_vehfrontangle(vcu_fsd_vehfrontangle(bytes, length));
}

// config detail: {'bit': 32, 'description': 'Vehicle_roll_angle', 'is_signed_var': False, 'len': 12, 'name': 'vcu_fsd_vehroll', 'offset': -180.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
double Vcufsdstatus2686::vcu_fsd_vehroll(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -180.000000;
  return ret;
}

// config detail: {'bit': 44, 'description': 'Vehicle_pitch_angle', 'is_signed_var': False, 'len': 12, 'name': 'vcu_fsd_vehpitch', 'offset': -180.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
double Vcufsdstatus2686::vcu_fsd_vehpitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  double ret = x * 0.100000 + -180.000000;
  return ret;
}

// config detail: {'bit': 21, 'description': 'Current_rear_axle_virtual_steering_wheel_angle', 'is_signed_var': False, 'len': 11, 'name': 'vcu_fsd_vehrearangle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcufsdstatus2686::vcu_fsd_vehrearangle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(5, 3);
  x <<= 3;
  x |= t;

  int ret = x + -800.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'Current_vehicle_speed', 'is_signed_var': False, 'len': 10, 'name': 'vcu_fsd_vehspeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|102.3]', 'physical_unit': '', 'precision': 0.1, 'signal_type': 'speed', 'type': 'double'}
double Vcufsdstatus2686::vcu_fsd_vehspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name': 'vcu_fsd_roulingcounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcufsdstatus2686::vcu_fsd_roulingcounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 10, 'description': 'Current_virtual_steering_wheel_angle_of_front_axle', 'is_signed_var': False, 'len': 11, 'name': 'vcu_fsd_vehfrontangle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcufsdstatus2686::vcu_fsd_vehfrontangle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 5);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(2, 6);
  x <<= 6;
  x |= t;

  int ret = x + -800.000000;
  return ret;
}
}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo
