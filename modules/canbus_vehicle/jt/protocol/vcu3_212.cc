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

#include "modules/canbus_vehicle/jt/protocol/vcu3_212.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Vcu3212::Vcu3212() {}
const int32_t Vcu3212::ID = 0x212;

void Vcu3212::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_vcu3_212()->set_vcu3_throttlevoltage(vcu3_throttlevoltage(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_mainswitch(vcu3_mainswitch(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_increasespeedswitch(vcu3_increasespeedswitch(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_increasedistanceswitch(vcu3_increasedistanceswitch(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_decreasespeedswitch(vcu3_decreasespeedswitch(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_decreasedistanceswitch(vcu3_decreasedistanceswitch(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_cancelswitch(vcu3_cancelswitch(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_gearsecuritybutton(vcu3_gearsecuritybutton(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_gearparkbutton(vcu3_gearparkbutton(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_gearleverposition(vcu3_gearleverposition(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_epbswitch(vcu3_epbswitch(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_vacuumpressure(vcu3_vacuumpressure(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_livecounter(vcu3_livecounter(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_leverinfo(vcu3_leverinfo(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_epbstatus(vcu3_epbstatus(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_checksum(vcu3_checksum(bytes, length));
  chassis->mutable_vcu3_212()->set_vcu3_actualgear(vcu3_actualgear(bytes, length));
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 11, 'name': 'vcu3_throttlevoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2000]', 'physical_unit': 'mV', 'precision': 1.0, 'type': 'int'}
int Vcu3212::vcu3_throttlevoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 22, 'description': 'The signal indicates if the  ON/OFF cruise control switch is actived or not.', 'enum': {0: 'VCU3_MAINSWITCH_INACTIVE', 1: 'VCU3_MAINSWITCH_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu3_mainswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_mainswitchType Vcu3212::vcu3_mainswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(6, 1);

  Vcu3_212::Vcu3_mainswitchType ret =  static_cast<Vcu3_212::Vcu3_mainswitchType>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': 'The signal indicates if the increase speed switch is actived or not', 'enum': {0: 'VCU3_INCREASESPEEDSWITCH_INACTIVE', 1: 'VCU3_INCREASESPEEDSWITCH_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu3_increasespeedswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
Vcu3_212::Vcu3_increasespeedswitchType Vcu3212::vcu3_increasespeedswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(2, 1);

  Vcu3_212::Vcu3_increasespeedswitchType ret =  static_cast<Vcu3_212::Vcu3_increasespeedswitchType>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': 'The signal indicates if  increase distance switch is actived or not', 'enum': {0: 'VCU3_INCREASEDISTANCESWITCH_INACTIVE', 1: 'VCU3_INCREASEDISTANCESWITCH_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu3_increasedistanceswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_increasedistanceswitchType Vcu3212::vcu3_increasedistanceswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 1);

  Vcu3_212::Vcu3_increasedistanceswitchType ret =  static_cast<Vcu3_212::Vcu3_increasedistanceswitchType>(x);
  return ret;
}

// config detail: {'bit': 27, 'description': 'The signal indicates if the decrease speed switch is actived or not.', 'enum': {0: 'VCU3_DECREASESPEEDSWITCH_INACTIVE', 1: 'VCU3_DECREASESPEEDSWITCH_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu3_decreasespeedswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
Vcu3_212::Vcu3_decreasespeedswitchType Vcu3212::vcu3_decreasespeedswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(3, 1);

  Vcu3_212::Vcu3_decreasespeedswitchType ret =  static_cast<Vcu3_212::Vcu3_decreasespeedswitchType>(x);
  return ret;
}

// config detail: {'bit': 25, 'description': 'The signal indicates if decrease distance switch is actived or not', 'enum': {0: 'VCU3_DECREASEDISTANCESWITCH_INACTIVE', 1: 'VCU3_DECREASEDISTANCESWITCH_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu3_decreasedistanceswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_decreasedistanceswitchType Vcu3212::vcu3_decreasedistanceswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(1, 1);

  Vcu3_212::Vcu3_decreasedistanceswitchType ret =  static_cast<Vcu3_212::Vcu3_decreasedistanceswitchType>(x);
  return ret;
}

// config detail: {'bit': 23, 'description': 'The signal indicates if the cancel cruise control switch is actived or not', 'enum': {0: 'VCU3_CANCELSWITCH_INACTIVE', 1: 'VCU3_CANCELSWITCH_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu3_cancelswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_cancelswitchType Vcu3212::vcu3_cancelswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(7, 1);

  Vcu3_212::Vcu3_cancelswitchType ret =  static_cast<Vcu3_212::Vcu3_cancelswitchType>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': 'This signal indicate the security button in the knob is pressed or not.', 'enum': {0: 'VCU3_GEARSECURITYBUTTON_NO_PRESSED', 1: 'VCU3_GEARSECURITYBUTTON_PRESSED'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu3_gearsecuritybutton', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_gearsecuritybuttonType Vcu3212::vcu3_gearsecuritybutton(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 1);

  Vcu3_212::Vcu3_gearsecuritybuttonType ret =  static_cast<Vcu3_212::Vcu3_gearsecuritybuttonType>(x);
  return ret;
}

// config detail: {'bit': 21, 'description': 'This signal indicate the park button in the knob is pressed or not.', 'enum': {0: 'VCU3_GEARPARKBUTTON_NO_PRESSED', 1: 'VCU3_GEARPARKBUTTON_PRESSED'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu3_gearparkbutton', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_gearparkbuttonType Vcu3212::vcu3_gearparkbutton(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(5, 1);

  Vcu3_212::Vcu3_gearparkbuttonType ret =  static_cast<Vcu3_212::Vcu3_gearparkbuttonType>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': 'This signal indicate the current lever position.', 'enum': {0: 'VCU3_GEARLEVERPOSITION_POSITION_0', 1: 'VCU3_GEARLEVERPOSITION_POSITION_ADD1', 2: 'VCU3_GEARLEVERPOSITION_POSITION_ADD2', 3: 'VCU3_GEARLEVERPOSITION_POSITION_SUB1', 4: 'VCU3_GEARLEVERPOSITION_POSITION_SUB2', 5: 'VCU3_GEARLEVERPOSITION_RESERVED', 6: 'VCU3_GEARLEVERPOSITION_RESERVED', 7: 'VCU3_GEARLEVERPOSITION_INVALID_VALUE'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu3_gearleverposition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_gearleverpositionType Vcu3212::vcu3_gearleverposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 3);

  Vcu3_212::Vcu3_gearleverpositionType ret =  static_cast<Vcu3_212::Vcu3_gearleverpositionType>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': 'This signal indicate the EPB switch status.', 'enum': {0: 'VCU3_EPBSWITCH_NO_PRESS', 1: 'VCU3_EPBSWITCH_UP', 2: 'VCU3_EPBSWITCH_DOWN', 3: 'VCU3_EPBSWITCH_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu3_epbswitch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_epbswitchType Vcu3212::vcu3_epbswitch(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  Vcu3_212::Vcu3_epbswitchType ret =  static_cast<Vcu3_212::Vcu3_epbswitchType>(x);
  return ret;
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 10, 'name': 'vcu3_vacuumpressure', 'offset': -108.0, 'order': 'intel', 'physical_range': '[-108|96.6]', 'physical_unit': 'kPa', 'precision': 0.2, 'type': 'double'}
double Vcu3212::vcu3_vacuumpressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.200000 + -108.000000;
  return ret;
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'vcu3_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vcu3212::vcu3_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal indicates the lever position information which should be displayed on the dashboard. For H72G, only P,R,N,D,M,no connection.', 'enum': {0: 'VCU3_LEVERINFO_P', 1: 'VCU3_LEVERINFO_R', 2: 'VCU3_LEVERINFO_N', 3: 'VCU3_LEVERINFO_D', 4: 'VCU3_LEVERINFO_S', 5: 'VCU3_LEVERINFO_M', 6: 'VCU3_LEVERINFO_W', 7: 'VCU3_LEVERINFO_E', 8: 'VCU3_LEVERINFO_B', 9: 'VCU3_LEVERINFO_RESERVED', 10: 'VCU3_LEVERINFO_RESERVED', 11: 'VCU3_LEVERINFO_RESERVED', 12: 'VCU3_LEVERINFO_RESERVED', 13: 'VCU3_LEVERINFO_RESERVED', 14: 'VCU3_LEVERINFO_NO_CONNECTION', 15: 'VCU3_LEVERINFO_INVALID_VALUE'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu3_leverinfo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_leverinfoType Vcu3212::vcu3_leverinfo(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Vcu3_212::Vcu3_leverinfoType ret =  static_cast<Vcu3_212::Vcu3_leverinfoType>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': 'The signal indicates the working status of EPB.', 'enum': {0: 'VCU3_EPBSTATUS_RELEASED', 1: 'VCU3_EPBSTATUS_RELEASING_OR_LOCKING', 2: 'VCU3_EPBSTATUS_LOCKED', 3: 'VCU3_EPBSTATUS_UNKNOW'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu3_epbstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_epbstatusType Vcu3212::vcu3_epbstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(6, 2);

  Vcu3_212::Vcu3_epbstatusType ret =  static_cast<Vcu3_212::Vcu3_epbstatusType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'vcu3_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vcu3212::vcu3_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 12, 'description': 'The signal indicates to the actual gear status, it shows in which gear the transmission system is in at the moment (engaged gear).', 'enum': {0: 'VCU3_ACTUALGEAR_P', 1: 'VCU3_ACTUALGEAR_R', 2: 'VCU3_ACTUALGEAR_N', 3: 'VCU3_ACTUALGEAR_1', 4: 'VCU3_ACTUALGEAR_2', 5: 'VCU3_ACTUALGEAR_3', 6: 'VCU3_ACTUALGEAR_4', 7: 'VCU3_ACTUALGEAR_5', 8: 'VCU3_ACTUALGEAR_6', 9: 'VCU3_ACTUALGEAR_7', 10: 'VCU3_ACTUALGEAR_8', 11: 'VCU3_ACTUALGEAR_RESERVED', 12: 'VCU3_ACTUALGEAR_RESERVED', 13: 'VCU3_ACTUALGEAR_RESERVED', 14: 'VCU3_ACTUALGEAR_NO_CONNECTION', 15: 'VCU3_ACTUALGEAR_INVALID_VALUE'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu3_actualgear', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vcu3_212::Vcu3_actualgearType Vcu3212::vcu3_actualgear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 4);

  Vcu3_212::Vcu3_actualgearType ret =  static_cast<Vcu3_212::Vcu3_actualgearType>(x);
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
