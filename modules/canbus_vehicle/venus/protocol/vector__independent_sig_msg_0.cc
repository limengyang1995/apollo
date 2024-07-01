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

#include "modules/canbus_vehicle/venus/protocol/vector__independent_sig_msg_0.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace venus {

using ::apollo::drivers::canbus::Byte;

Vectorindependentsigmsg0::Vectorindependentsigmsg0() {}
const int32_t Vectorindependentsigmsg0::ID = 0x0;

void Vectorindependentsigmsg0::Parse(const std::uint8_t* bytes, int32_t length,
                         Venus* chassis) const {
  chassis->mutable_vector__independent_sig_msg_0()->set_acu4_conditionertemp(acu4_conditionertemp(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu2_yawrate(vcu2_yawrate(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu2_longitudinalaccel(vcu2_longitudinalaccel(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu2_livecounter(vcu2_livecounter(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu2_lateraaccel(vcu2_lateraaccel(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu2_checksum(vcu2_checksum(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_vehiclemodeindication(vcu4_vehiclemodeindication(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_outputpowerpercent(vcu4_outputpowerpercent(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_livecounter(vcu4_livecounter(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_interlocksystemfault(vcu4_interlocksystemfault(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_insulationmonitorwarning(vcu4_insulationmonitorwarning(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_dcdcstatus(vcu4_dcdcstatus(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_checksum(vcu4_checksum(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_chargerstatus(vcu4_chargerstatus(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_batterypackvoltage(vcu4_batterypackvoltage(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_batterypacktemperature(vcu4_batterypacktemperature(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_batterypacksoc(vcu4_batterypacksoc(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu4_batterypackcurrent(vcu4_batterypackcurrent(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_byd_gearcmd(byd_gearcmd(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_gear_p(gear_p(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_gear_info(gear_info(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu5_wheelspeedrr(acu5_wheelspeedrr(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu5_wheelspeedrl(acu5_wheelspeedrl(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu5_wheelspeedfr(acu5_wheelspeedfr(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu5_wheelspeedfl(acu5_wheelspeedfl(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_signal2(signal2(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_pulse1(pulse1(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_action6(acu3_action6(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_action5(acu3_action5(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_action4(acu3_action4(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_action3(acu3_action3(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_action2(acu3_action2(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_action1(acu3_action1(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_wiper(acu3_wiper(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_widthlight(acu3_widthlight(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_livecounter(acu3_livecounter(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_ignition(acu3_ignition(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_hornlight(acu3_hornlight(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_horn(acu3_horn(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_doorlock(acu3_doorlock(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu3_artisticlight(acu3_artisticlight(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acu1_standstillst(acu1_standstillst(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_moder(eps1_moder(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_mode(eps1_mode(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_autocontrolr(eps1_autocontrolr(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_autocontrolf(eps1_autocontrolf(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_errorr(eps1_errorr(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_errorf(eps1_errorf(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_currentspeedr(eps1_currentspeedr(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_currentspeedf(eps1_currentspeedf(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_currentangler(eps1_currentangler(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_currentanglef(eps1_currentanglef(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bcm_engstartst(bcm_engstartst(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bcm_lampst(bcm_lampst(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bcm_fuelremain(bcm_fuelremain(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bcm_diflock(bcm_diflock(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bcm_enginestartrequest(bcm_enginestartrequest(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu3_esppresure(vcu3_esppresure(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_vcu3_espposition(vcu3_espposition(bytes, length));
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'acu4_conditionertemp', 'offset': 15.0, 'order': 'intel', 'physical_range': '[15|30]', 'physical_unit': '¡æ', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acu4_conditionertemp(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x + 15.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 12, 'name': 'vcu2_yawrate', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|100]', 'physical_unit': 'deg/s', 'precision': 0.05, 'type': 'double'}
double Vectorindependentsigmsg0::vcu2_yawrate(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.050000 + -100.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 12, 'name': 'vcu2_longitudinalaccel', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::vcu2_longitudinalaccel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -20.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'vcu2_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu2_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 12, 'name': 'vcu2_lateraaccel', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::vcu2_lateraaccel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -20.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu2_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu2_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'VCU4_VEHICLEMODEINDICATION_NORMAL', 1: 'VCU4_VEHICLEMODEINDICATION_ECO', 2: 'VCU4_VEHICLEMODEINDICATION_SPORT', 3: 'VCU4_VEHICLEMODEINDICATION_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu4_vehiclemodeindication', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Vcu4_vehiclemodeindicationType Vectorindependentsigmsg0::vcu4_vehiclemodeindication(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vector__independent_sig_msg_0::Vcu4_vehiclemodeindicationType ret =  static_cast<Vector__independent_sig_msg_0::Vcu4_vehiclemodeindicationType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu4_outputpowerpercent', 'offset': -50.0, 'order': 'intel', 'physical_range': '[-50|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu4_outputpowerpercent(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -50.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'vcu4_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu4_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'VCU4_INTERLOCKSYSTEMFAULT_NOFAULT', 1: 'VCU4_INTERLOCKSYSTEMFAULT_FAULT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu4_interlocksystemfault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Vcu4_interlocksystemfaultType Vectorindependentsigmsg0::vcu4_interlocksystemfault(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Vector__independent_sig_msg_0::Vcu4_interlocksystemfaultType ret =  static_cast<Vector__independent_sig_msg_0::Vcu4_interlocksystemfaultType>(x);
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'VCU4_INSULATIONMONITORWARNING_NORMAL', 1: 'VCU4_INSULATIONMONITORWARNING_SECONDWARNING', 2: 'VCU4_INSULATIONMONITORWARNING_FIRSTWARNING', 3: 'VCU4_INSULATIONMONITORWARNING_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu4_insulationmonitorwarning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Vcu4_insulationmonitorwarningType Vectorindependentsigmsg0::vcu4_insulationmonitorwarning(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vector__independent_sig_msg_0::Vcu4_insulationmonitorwarningType ret =  static_cast<Vector__independent_sig_msg_0::Vcu4_insulationmonitorwarningType>(x);
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'VCU4_DCDCSTATUS_NOTWORKING', 1: 'VCU4_DCDCSTATUS_WORKING', 2: 'VCU4_DCDCSTATUS_NORMALERROR', 3: 'VCU4_DCDCSTATUS_CRITICALERROR'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu4_dcdcstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Vcu4_dcdcstatusType Vectorindependentsigmsg0::vcu4_dcdcstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vector__independent_sig_msg_0::Vcu4_dcdcstatusType ret =  static_cast<Vector__independent_sig_msg_0::Vcu4_dcdcstatusType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu4_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu4_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'VCU4_CHARGERSTATUS_NOTCHARGE', 1: 'VCU4_CHARGERSTATUS_CHARGING', 2: 'VCU4_CHARGERSTATUS_CHARGEFINISH', 3: 'VCU4_CHARGERSTATUS_CHARGEFAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu4_chargerstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Vcu4_chargerstatusType Vectorindependentsigmsg0::vcu4_chargerstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vector__independent_sig_msg_0::Vcu4_chargerstatusType ret =  static_cast<Vector__independent_sig_msg_0::Vcu4_chargerstatusType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 9, 'name': 'vcu4_batterypackvoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu4_batterypackvoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 1);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu4_batterypacktemperature', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|210]', 'physical_unit': '¡ãC', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu4_batterypacktemperature(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu4_batterypacksoc', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu4_batterypacksoc(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 10, 'name': 'vcu4_batterypackcurrent', 'offset': -500.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu4_batterypackcurrent(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x + -500.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'byd_gearcmd', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::byd_gearcmd(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'gear_p', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::gear_p(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'gear_info', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::gear_info(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'acu5_wheelspeedrr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::acu5_wheelspeedrr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'acu5_wheelspeedrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::acu5_wheelspeedrl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'acu5_wheelspeedfr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::acu5_wheelspeedfr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'acu5_wheelspeedfl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::acu5_wheelspeedfl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 7);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 32, 'name': 'signal2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::signal2(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t2(bytes + 1);
  t = t2.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t3(bytes + 0);
  t = t3.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 32, 'name': 'pulse1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::pulse1(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t2(bytes + 1);
  t = t2.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t3(bytes + 0);
  t = t3.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'acu3_action6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acu3_action6(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'acu3_action5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acu3_action5(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'acu3_action4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acu3_action4(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'acu3_action3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acu3_action3(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'acu3_action2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acu3_action2(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'acu3_action1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acu3_action1(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'ACU3_WIPER_NOREQUEST', 1: 'ACU3_WIPER_SPEED1', 2: 'ACU3_WIPER_SPEED2', 3: 'ACU3_WIPER_SPEED3', 4: 'ACU3_WIPER_SPEED4', 5: 'ACU3_WIPER_AUTO', 6: 'ACU3_WIPER_WASH', 7: 'ACU3_WIPER_OFF'}, 'is_signed_var': False, 'len': 3, 'name': 'acu3_wiper', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Acu3_wiperType Vectorindependentsigmsg0::acu3_wiper(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  Vector__independent_sig_msg_0::Acu3_wiperType ret =  static_cast<Vector__independent_sig_msg_0::Acu3_wiperType>(x);
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'ACU3_WIDTHLIGHT_NOREQUEST', 1: 'ACU3_WIDTHLIGHT_ON', 2: 'ACU3_WIDTHLIGHT_OFF', 3: 'ACU3_WIDTHLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_widthlight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Acu3_widthlightType Vectorindependentsigmsg0::acu3_widthlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vector__independent_sig_msg_0::Acu3_widthlightType ret =  static_cast<Vector__independent_sig_msg_0::Acu3_widthlightType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'acu3_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acu3_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'ACU3_IGNITION_NOREQUEST', 1: 'ACU3_IGNITION_ON', 2: 'ACU3_IGNITION_START', 3: 'ACU3_IGNITION_OFF', 4: 'ACU3_IGNITION_IG1', 5: 'ACU3_IGNITION_IG2', 6: 'ACU3_IGNITION_RESERVED1', 7: 'ACU3_IGNITION_RESERVED2'}, 'is_signed_var': False, 'len': 3, 'name': 'acu3_ignition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Acu3_ignitionType Vectorindependentsigmsg0::acu3_ignition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  Vector__independent_sig_msg_0::Acu3_ignitionType ret =  static_cast<Vector__independent_sig_msg_0::Acu3_ignitionType>(x);
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'ACU3_HORNLIGHT_NOREQUEST', 1: 'ACU3_HORNLIGHT_ON', 2: 'ACU3_HORNLIGHT_OFF', 3: 'ACU3_HORNLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_hornlight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Acu3_hornlightType Vectorindependentsigmsg0::acu3_hornlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vector__independent_sig_msg_0::Acu3_hornlightType ret =  static_cast<Vector__independent_sig_msg_0::Acu3_hornlightType>(x);
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'ACU3_HORN_NOREQUEST', 1: 'ACU3_HORN_ON', 2: 'ACU3_HORN_OFF', 3: 'ACU3_HORN_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_horn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Acu3_hornType Vectorindependentsigmsg0::acu3_horn(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vector__independent_sig_msg_0::Acu3_hornType ret =  static_cast<Vector__independent_sig_msg_0::Acu3_hornType>(x);
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'ACU3_DOORLOCK_NOREQUEST', 1: 'ACU3_DOORLOCK_LOCK', 2: 'ACU3_DOORLOCK_UNLOCK', 3: 'ACU3_DOORLOCK_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'acu3_doorlock', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Acu3_doorlockType Vectorindependentsigmsg0::acu3_doorlock(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  Vector__independent_sig_msg_0::Acu3_doorlockType ret =  static_cast<Vector__independent_sig_msg_0::Acu3_doorlockType>(x);
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'ACU3_ARTISTICLIGHT_NOREQUEST', 1: 'ACU3_ARTISTICLIGHT_EFFECT1', 2: 'ACU3_ARTISTICLIGHT_EFFECT2', 3: 'ACU3_ARTISTICLIGHT_EFFECT3', 4: 'ACU3_ARTISTICLIGHT_EFFECT4', 5: 'ACU3_ARTISTICLIGHT_EFFECT5', 6: 'ACU3_ARTISTICLIGHT_EFFECT6', 7: 'ACU3_ARTISTICLIGHT_EFFECT7', 8: 'ACU3_ARTISTICLIGHT_EFFECT8', 9: 'ACU3_ARTISTICLIGHT_EFFECT9', 10: 'ACU3_ARTISTICLIGHT_EFFECT10', 11: 'ACU3_ARTISTICLIGHT_EFFECT11', 12: 'ACU3_ARTISTICLIGHT_EFFECT12', 13: 'ACU3_ARTISTICLIGHT_EFFECT13', 14: 'ACU3_ARTISTICLIGHT_EFFECT14', 15: 'ACU3_ARTISTICLIGHT_OFF'}, 'is_signed_var': False, 'len': 4, 'name': 'acu3_artisticlight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Acu3_artisticlightType Vectorindependentsigmsg0::acu3_artisticlight(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  Vector__independent_sig_msg_0::Acu3_artisticlightType ret =  static_cast<Vector__independent_sig_msg_0::Acu3_artisticlightType>(x);
  return ret;
}

// config detail: {'bit': 0, 'enum': {0: 'ACU1_STANDSTILLST_INACTIVE', 1: 'ACU1_STANDSTILLST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu1_standstillst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Acu1_standstillstType Vectorindependentsigmsg0::acu1_standstillst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Vector__independent_sig_msg_0::Acu1_standstillstType ret =  static_cast<Vector__independent_sig_msg_0::Acu1_standstillstType>(x);
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'eps1_moder', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::eps1_moder(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'eps1_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::eps1_mode(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'eps1_autocontrolr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::eps1_autocontrolr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'eps1_autocontrolf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::eps1_autocontrolf(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'eps1_errorr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::eps1_errorr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'eps1_errorf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::eps1_errorf(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'eps1_currentspeedr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': '', 'precision': 4.0, 'type': 'double'}
double Vectorindependentsigmsg0::eps1_currentspeedr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 4.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'eps1_currentspeedf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': '', 'precision': 4.0, 'type': 'double'}
double Vectorindependentsigmsg0::eps1_currentspeedf(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 4.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 14, 'name': 'eps1_currentangler', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
double Vectorindependentsigmsg0::eps1_currentangler(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -600.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 14, 'name': 'eps1_currentanglef', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
double Vectorindependentsigmsg0::eps1_currentanglef(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 6);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -600.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bcm_engstartst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bcm_engstartst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'bcm_lampst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bcm_lampst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'bcm_fuelremain', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bcm_fuelremain(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bcm_diflock', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bcm_diflock(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'bcm_enginestartrequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bcm_enginestartrequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu3_esppresure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu3_esppresure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vcu3_espposition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::vcu3_espposition(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}
}  // namespace venus
}  // namespace canbus
}  // namespace apollo
