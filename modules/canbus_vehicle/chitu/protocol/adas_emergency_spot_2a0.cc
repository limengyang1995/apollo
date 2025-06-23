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

#include "modules/canbus_vehicle/chitu/protocol/adas_emergency_spot_2a0.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace chitu {

using ::apollo::drivers::canbus::Byte;

const int32_t Adasemergencyspot2a0::ID = 0x2A0;

// public
Adasemergencyspot2a0::Adasemergencyspot2a0() { Reset(); }

uint32_t Adasemergencyspot2a0::GetPeriod() const {
  // TODO(All) : modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Adasemergencyspot2a0::Parse(const std::uint8_t* bytes, int32_t length,
                         Chitu* chassis) const {
  chassis->mutable_adas_emergency_spot_2a0()->set_scram_signal(scram_signal(bytes, length));
}

void Adasemergencyspot2a0::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) : you should add the heartbeat manually
}

void Adasemergencyspot2a0::UpdateData(uint8_t* data) {
  set_p_scram_signal(data, scram_signal_);
}

void Adasemergencyspot2a0::Reset() {
  // TODO(All) :  you should check this manually
  scram_signal_ = Adas_emergency_spot_2a0::SCRAM_SIGNAL_INVALID;
}

Adasemergencyspot2a0* Adasemergencyspot2a0::set_scram_signal(
    Adas_emergency_spot_2a0::Scram_signalType scram_signal) {
  scram_signal_ = scram_signal;
  return this;
 }

// config detail: {'bit': 0, 'enum': {0: 'SCRAM_SIGNAL_INVALID', 1: 'SCRAM_SIGNAL_VALID'}, 'is_signed_var': False, 'len': 1, 'name': 'Scram_Signal', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '/', 'precision': 1.0, 'type': 'enum'}
void Adasemergencyspot2a0::set_p_scram_signal(uint8_t* data,
    Adas_emergency_spot_2a0::Scram_signalType scram_signal) {
  int x = scram_signal;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 1);
}


Adas_emergency_spot_2a0::Scram_signalType Adasemergencyspot2a0::scram_signal(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Adas_emergency_spot_2a0::Scram_signalType ret =  static_cast<Adas_emergency_spot_2a0::Scram_signalType>(x);
  return ret;
}
}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
