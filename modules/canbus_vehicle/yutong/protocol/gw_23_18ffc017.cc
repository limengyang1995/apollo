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

#include "modules/canbus_vehicle/yutong/protocol/gw_23_18ffc017.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

Gw2318ffc017::Gw2318ffc017() {}
const int32_t Gw2318ffc017::ID = 0x18ffc017;

void Gw2318ffc017::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_gw_23_18ffc017()->set_fa_brake_pressure(fa_brake_pressure(bytes, length));
  chassis->mutable_gw_23_18ffc017()->set_ra_brake_pressure(ra_brake_pressure(bytes, length));
  chassis->mutable_gw_23_18ffc017()->set_voltage_24v_supply(voltage_24v_supply(bytes, length));
  chassis->mutable_gw_23_18ffc017()->set_on_gear_signal(on_gear_signal(bytes, length));
  chassis->mutable_gw_23_18ffc017()->set_total_fire_signal(total_fire_signal(bytes, length));
}

// config detail: {'bit': 0, 'description': 'ֵ0-1000kpa', 'is_signed_var': False, 'len': 8, 'name': 'fa_brake_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'Kpa', 'precision': 4.0, 'type': 'double'}
double Gw2318ffc017::fa_brake_pressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 4.000000;
  return ret;
}

// config detail: {'bit': 8, 'description': 'ֵ0-1000KPA', 'is_signed_var': False, 'len': 8, 'name': 'ra_brake_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'Kpa', 'precision': 4.0, 'type': 'double'}
double Gw2318ffc017::ra_brake_pressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 4.000000;
  return ret;
}

// config detail: {'bit': 16, 'description': 'ֵ0to32V', 'is_signed_var': False, 'len': 8, 'name': 'voltage_24v_supply', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'V', 'precision': 0.5, 'type': 'double'}
double Gw2318ffc017::voltage_24v_supply(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.500000;
  return ret;
}

// config detail: {'bit': 28, 'enum': {0: 'ON_GEAR_SIGNAL_', 1: 'ON_GEAR_SIGNAL_NO'}, 'is_signed_var': False, 'len': 2, 'name': 'on_gear_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_23_18ffc017::On_gear_signalType Gw2318ffc017::on_gear_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  Gw_23_18ffc017::On_gear_signalType ret =  static_cast<Gw_23_18ffc017::On_gear_signalType>(x);
  return ret;
}

// config detail: {'bit': 62, 'enum': {0: 'TOTAL_FIRE_SIGNAL_', 1: 'TOTAL_FIRE_SIGNAL_'}, 'is_signed_var': False, 'len': 2, 'name': 'total_fire_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Gw_23_18ffc017::Total_fire_signalType Gw2318ffc017::total_fire_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(6, 2);

  Gw_23_18ffc017::Total_fire_signalType ret =  static_cast<Gw_23_18ffc017::Total_fire_signalType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
