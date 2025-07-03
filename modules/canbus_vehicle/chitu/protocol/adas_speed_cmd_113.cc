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

#include "modules/canbus_vehicle/chitu/protocol/adas_speed_cmd_113.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

const int32_t Adasspeedcmd113::ID = 0x113;

// public
Adasspeedcmd113::Adasspeedcmd113() { Reset(); }

uint32_t Adasspeedcmd113::GetPeriod() const {
  // TODO(All) : modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Adasspeedcmd113::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_adas_speed_cmd_113()->set_vehicle_speed(vehicle_speed(bytes, length));
  chassis->mutable_adas_speed_cmd_113()->set_accelerated_speed(accelerated_speed(bytes, length));
}

void Adasspeedcmd113::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) : you should add the heartbeat manually
}

void Adasspeedcmd113::UpdateData(uint8_t* data) {
  set_p_vehicle_speed(data, vehicle_speed_);
  set_p_accelerated_speed(data, accelerated_speed_);
}

void Adasspeedcmd113::Reset() {
  // TODO(All) :  you should check this manually
  vehicle_speed_ = 0.0;
  accelerated_speed_ = 0.0;
}

Adasspeedcmd113* Adasspeedcmd113::set_vehicle_speed(
    double vehicle_speed) {
  vehicle_speed_ = vehicle_speed;
  return this;
 }

// config detail: {'bit': 7, 'is_signed_var': True, 'len': 16, 'name': 'Vehicle_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-6.9|6.9]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
void Adasspeedcmd113::set_p_vehicle_speed(uint8_t* data,
    double vehicle_speed) {
  vehicle_speed = ProtocolData::BoundedValue(-6.9, 6.9, vehicle_speed);
  int x = vehicle_speed / 0.001000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 1);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 0);
  to_set1.set_value(t, 0, 8);
}


Adasspeedcmd113* Adasspeedcmd113::set_accelerated_speed(
    double accelerated_speed) {
  accelerated_speed_ = accelerated_speed;
  return this;
 }

// config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Accelerated_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-2|2]', 'physical_unit': 'm/s2', 'precision': 0.0001, 'type': 'double'}
void Adasspeedcmd113::set_p_accelerated_speed(uint8_t* data,
    double accelerated_speed) {
  accelerated_speed = ProtocolData::BoundedValue(-2.0, 2.0, accelerated_speed);
  int x = accelerated_speed / 0.000100;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 3);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 2);
  to_set1.set_value(t, 0, 8);
}


double Adasspeedcmd113::vehicle_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.001000;
  return ret;
}

double Adasspeedcmd113::accelerated_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.000100;
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
