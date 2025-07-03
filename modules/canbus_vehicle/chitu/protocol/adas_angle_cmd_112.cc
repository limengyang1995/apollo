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

#include "modules/canbus_vehicle/chitu/protocol/adas_angle_cmd_112.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

const int32_t Adasanglecmd112::ID = 0x112;

// public
Adasanglecmd112::Adasanglecmd112() { Reset(); }

uint32_t Adasanglecmd112::GetPeriod() const {
  // TODO(All) : modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Adasanglecmd112::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_adas_angle_cmd_112()->set_steering_angle(steering_angle(bytes, length));
  chassis->mutable_adas_angle_cmd_112()->set_ac_steering_speed(ac_steering_speed(bytes, length));
}

void Adasanglecmd112::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) : you should add the heartbeat manually
}

void Adasanglecmd112::UpdateData(uint8_t* data) {
  set_p_steering_angle(data, steering_angle_);
  set_p_ac_steering_speed(data, ac_steering_speed_);
}

void Adasanglecmd112::Reset() {
  // TODO(All) :  you should check this manually
  steering_angle_ = 0.0;
  ac_steering_speed_ = 0.0;
}

Adasanglecmd112* Adasanglecmd112::set_steering_angle(
    double steering_angle) {
  steering_angle_ = steering_angle;
  return this;
 }

// config detail: {'bit': 7, 'is_signed_var': True, 'len': 16, 'name': 'steering_angle', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-37.2|30.7]', 'physical_unit': 'degrees', 'precision': 0.002, 'type': 'double'}
void Adasanglecmd112::set_p_steering_angle(uint8_t* data,
    double steering_angle) {
  steering_angle = ProtocolData::BoundedValue(-37.2, 30.7, steering_angle);
  int x = steering_angle / 0.002000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 1);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 0);
  to_set1.set_value(t, 0, 8);
}


Adasanglecmd112* Adasanglecmd112::set_ac_steering_speed(
    double ac_steering_speed) {
  ac_steering_speed_ = ac_steering_speed;
  return this;
 }

// config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Ac_steering_speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-14.4|14.4]', 'physical_unit': 'degrees/s', 'precision': 0.001, 'type': 'double'}
void Adasanglecmd112::set_p_ac_steering_speed(uint8_t* data,
    double ac_steering_speed) {
  ac_steering_speed = ProtocolData::BoundedValue(-14.4, 14.4, ac_steering_speed);
  int x = ac_steering_speed / 0.001000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 3);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 2);
  to_set1.set_value(t, 0, 8);
}


double Adasanglecmd112::steering_angle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 1);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.002000;
  return ret;
}

double Adasanglecmd112::ac_steering_speed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.001000;
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
