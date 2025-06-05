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

#include "modules/canbus_vehicle/yutong/protocol/vcu_02_18ffda2a.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::Byte;

const int32_t Vcu0218ffda2a::ID = 0x18ffda2a;

// public
Vcu0218ffda2a::Vcu0218ffda2a() { Reset(); }

uint32_t Vcu0218ffda2a::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Vcu0218ffda2a::Parse(const std::uint8_t* bytes, int32_t length,
                         Yutong* chassis) const {
  chassis->mutable_vcu_02_18ffda2a()->set_adcontrolmode(adcontrolmode(bytes, length));
  chassis->mutable_vcu_02_18ffda2a()->set_slowspdlevergearcontrol(slowspdlevergearcontrol(bytes, length));
}

void Vcu0218ffda2a::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) :  you should add the heartbeat manually
}

void Vcu0218ffda2a::UpdateData(uint8_t* data) {
  set_p_adcontrolmode(data, adcontrolmode_);
  set_p_slowspdlevergearcontrol(data, slowspdlevergearcontrol_);
}

void Vcu0218ffda2a::Reset() {
  // TODO(All) :  you should check this manually
  adcontrolmode_ = Vcu_02_18ffda2a::ADCONTROLMODE_STANDBY;
  slowspdlevergearcontrol_ = Vcu_02_18ffda2a::SLOWSPDLEVERGEARCONTROL_1;
}

Vcu0218ffda2a* Vcu0218ffda2a::set_adcontrolmode(
    Vcu_02_18ffda2a::AdcontrolmodeType adcontrolmode) {
  adcontrolmode_ = adcontrolmode;
  return this;
 }

// config detail: {'bit': 0, 'enum': {0: 'ADCONTROLMODE_', 1: 'ADCONTROLMODE_', 3: 'ADCONTROLMODE_'}, 'is_signed_var': False, 'len': 3, 'name': 'ADControlMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0218ffda2a::set_p_adcontrolmode(uint8_t* data,
    Vcu_02_18ffda2a::AdcontrolmodeType adcontrolmode) {
  int x = adcontrolmode;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 3);
}


Vcu0218ffda2a* Vcu0218ffda2a::set_slowspdlevergearcontrol(
    Vcu_02_18ffda2a::SlowspdlevergearcontrolType slowspdlevergearcontrol) {
  slowspdlevergearcontrol_ = slowspdlevergearcontrol;
  return this;
 }

// config detail: {'bit': 40, 'enum': {0: 'SLOWSPDLEVERGEARCONTROL_1', 1: 'SLOWSPDLEVERGEARCONTROL_16', 2: 'SLOWSPDLEVERGEARCONTROL_17', 3: 'SLOWSPDLEVERGEARCONTROL_256'}, 'is_signed_var': False, 'len': 3, 'name': 'SlowSpdLeverGearControl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vcu0218ffda2a::set_p_slowspdlevergearcontrol(uint8_t* data,
    Vcu_02_18ffda2a::SlowspdlevergearcontrolType slowspdlevergearcontrol) {
  int x = slowspdlevergearcontrol;

  Byte to_set(data + 5);
  to_set.set_value(x, 0, 3);
}


Vcu_02_18ffda2a::AdcontrolmodeType Vcu0218ffda2a::adcontrolmode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  Vcu_02_18ffda2a::AdcontrolmodeType ret =  static_cast<Vcu_02_18ffda2a::AdcontrolmodeType>(x);
  return ret;
}

Vcu_02_18ffda2a::SlowspdlevergearcontrolType Vcu0218ffda2a::slowspdlevergearcontrol(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 3);

  Vcu_02_18ffda2a::SlowspdlevergearcontrolType ret =  static_cast<Vcu_02_18ffda2a::SlowspdlevergearcontrolType>(x);
  return ret;
}
}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
