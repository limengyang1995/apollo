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

#include "modules/canbus_vehicle/jt/protocol/vector__independent_sig_msg_0.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Vectorindependentsigmsg0::Vectorindependentsigmsg0() {}
const int32_t Vectorindependentsigmsg0::ID = 0x0;

void Vectorindependentsigmsg0::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_vector__independent_sig_msg_0()->set_epb1_checksum_copy_4(epb1_checksum_copy_4(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acs3_data7(acs3_data7(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acs3_data6(acs3_data6(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acs3_data5(acs3_data5(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acs3_data4(acs3_data4(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acs3_data3(acs3_data3(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acs3_data2(acs3_data2(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acs3_data1(acs3_data1(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_acs3_data0(acs3_data0(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_dcdc1_temperature(dcdc1_temperature(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_dcdc1_status(dcdc1_status(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_dcdc1_outputvoltage(dcdc1_outputvoltage(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_dcdc1_outputcurrent(dcdc1_outputcurrent(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_dcdc1_livecounter(dcdc1_livecounter(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_dcdc1_inputvoltage(dcdc1_inputvoltage(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_dcdc1_inputcurrent(dcdc1_inputcurrent(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_dcdc1_checksum(dcdc1_checksum(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_mcu1_tmtorque(mcu1_tmtorque(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_mcu1_tmtemperature(mcu1_tmtemperature(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_mcu1_tmspeed(mcu1_tmspeed(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_mcu1_tmcapacitancevoltage(mcu1_tmcapacitancevoltage(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_mcu1_livecounter(mcu1_livecounter(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_mcu1_checksum(mcu1_checksum(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_esc1_livecounter(esc1_livecounter(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_esc1_checksum(esc1_checksum(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_esc1_yawrate(esc1_yawrate(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_esc1_accelerationx(esc1_accelerationx(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_esc1_accelerationy(esc1_accelerationy(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_livecounter(env1_livecounter(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_checksum(env1_checksum(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_timeyear(env1_timeyear(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_timesecond(env1_timesecond(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_timemonth(env1_timemonth(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_timeminute(env1_timeminute(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_timehour(env1_timehour(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_timeday(env1_timeday(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_rainintensity(env1_rainintensity(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_env1_brightnessh(env1_brightnessh(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_lkastatus(eps1_lkastatus(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_electricload(eps1_electricload(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_apaerrorstatus(eps1_apaerrorstatus(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_aparequestfeedback(eps1_aparequestfeedback(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_apaabortfeedback(eps1_apaabortfeedback(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_overlayinputtorque(eps1_overlayinputtorque(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_livecounter(eps1_livecounter(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_handsteeringtorque(eps1_handsteeringtorque(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_eps1_checksum(eps1_checksum(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdrr_winbuttonrr_st(bdrr_winbuttonrr_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdrl_winbuttonrl_st(bdrl_winbuttonrl_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfr_winbuttonfr_st(bdfr_winbuttonfr_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_a_test_data(a_test_data(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_mirrightbutton_st(bdfl_mirrightbutton_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_mirleftbutton_st(bdfl_mirleftbutton_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_mirbuttonup_st(bdfl_mirbuttonup_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_mirbuttonright_st(bdfl_mirbuttonright_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_mirbuttonleft_st(bdfl_mirbuttonleft_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_mirbuttondown_st(bdfl_mirbuttondown_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_unlockbutton_st(bdfl_unlockbutton_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_lockbutton_st(bdfl_lockbutton_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_bootbuttonfl_st(bdfl_bootbuttonfl_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_winbuttonrr_st(bdfl_winbuttonrr_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_winbuttonrl_st(bdfl_winbuttonrl_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_winbuttonfr_st(bdfl_winbuttonfr_st(bytes, length));
  chassis->mutable_vector__independent_sig_msg_0()->set_bdfl_winbuttonfl_st(bdfl_winbuttonfl_st(bytes, length));
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'epb1_checksum_copy_4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::epb1_checksum_copy_4(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acs3_data7', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acs3_data7(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acs3_data6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acs3_data6(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acs3_data5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acs3_data5(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acs3_data4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acs3_data4(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acs3_data3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acs3_data3(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acs3_data2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acs3_data2(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acs3_data1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acs3_data1(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'acs3_data0', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::acs3_data0(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'dcdc1_temperature', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|210]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::dcdc1_temperature(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'dcdc1_status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::dcdc1_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'dcdc1_outputvoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
double Vectorindependentsigmsg0::dcdc1_outputvoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 10, 'name': 'dcdc1_outputcurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::dcdc1_outputcurrent(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'dcdc1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::dcdc1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 10, 'name': 'dcdc1_inputvoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::dcdc1_inputvoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'dcdc1_inputcurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25]', 'physical_unit': 'A', 'precision': 0.1, 'type': 'double'}
double Vectorindependentsigmsg0::dcdc1_inputcurrent(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'dcdc1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::dcdc1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 12, 'name': 'mcu1_tmtorque', 'offset': -500.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'Nm', 'precision': 0.25, 'type': 'double'}
double Vectorindependentsigmsg0::mcu1_tmtorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.250000 + -500.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'mcu1_tmtemperature', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|210]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::mcu1_tmtemperature(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'mcu1_tmspeed', 'offset': -30000.0, 'order': 'intel', 'physical_range': '[-30000|30000]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::mcu1_tmspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x + -30000.000000;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 9, 'name': 'mcu1_tmcapacitancevoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::mcu1_tmcapacitancevoltage(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 1);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'mcu1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::mcu1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'mcu1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::mcu1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'esc1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::esc1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'esc1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::esc1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'This signal indicates the yaw rate data (real data; sign depends on mounting position).anticlockwise=positive, clockwise=negative', 'is_signed_var': False, 'len': 12, 'name': 'esc1_yawrate', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|100]', 'physical_unit': 'deg/s', 'precision': 0.05, 'type': 'double'}
double Vectorindependentsigmsg0::esc1_yawrate(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.050000 + -100.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The signal is LongitudinalAcceleration(exact value).Positive value represents  forward,  negative value represents backward.', 'is_signed_var': False, 'len': 12, 'name': 'esc1_accelerationx', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::esc1_accelerationx(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -20.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The signal is Lateral Acceleration(exact value).Positive value represents right side of vehicle, negative value represents  left side of vehicle.', 'is_signed_var': False, 'len': 12, 'name': 'esc1_accelerationy', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::esc1_accelerationy(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -20.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'env1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::env1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'env1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::env1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'Indicates the GPS year', 'is_signed_var': False, 'len': 6, 'name': 'env1_timeyear', 'offset': 2000.0, 'order': 'intel', 'physical_range': '[2000|2063]', 'physical_unit': 'Year', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::env1_timeyear(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 6);

  int ret = x + 2000.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'Indicates the GPS second ', 'is_signed_var': False, 'len': 6, 'name': 'env1_timesecond', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|59]', 'physical_unit': 'Second', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::env1_timesecond(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 6);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'Indicates the GPS month', 'is_signed_var': False, 'len': 4, 'name': 'env1_timemonth', 'offset': 1.0, 'order': 'intel', 'physical_range': '[1|12]', 'physical_unit': 'Month', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::env1_timemonth(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x + 1.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'Indicates the GPS minute  ', 'is_signed_var': False, 'len': 6, 'name': 'env1_timeminute', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|59]', 'physical_unit': 'Minute', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::env1_timeminute(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 6);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'Indicates the GPS hour', 'is_signed_var': False, 'len': 5, 'name': 'env1_timehour', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|23]', 'physical_unit': 'Hour', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::env1_timehour(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 5);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'Indicates the GPS day', 'is_signed_var': False, 'len': 5, 'name': 'env1_timeday', 'offset': 1.0, 'order': 'intel', 'physical_range': '[1|31]', 'physical_unit': 'Day', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::env1_timeday(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 5);

  int ret = x + 1.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'This signal delivers information about rain intensity: from 0% (no rain) to 100% (very heavy rain).', 'is_signed_var': False, 'len': 4, 'name': 'env1_rainintensity', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|150]', 'physical_unit': '%', 'precision': 10.0, 'type': 'double'}
double Vectorindependentsigmsg0::env1_rainintensity(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  double ret = x * 10.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'This signal  indicate the high precision light intensity expressed in 10 Bit.', 'is_signed_var': False, 'len': 10, 'name': 'env1_brightnessh', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|6138]', 'physical_unit': 'LUX', 'precision': 6.0, 'type': 'double'}
double Vectorindependentsigmsg0::env1_brightnessh(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 6.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The signal indicates the status of LKA function', 'enum': {0: 'EPS1_LKASTATUS_TEMPORARY_INHIBIT', 1: 'EPS1_LKASTATUS_AVAILABLE_FOR_CONTROL', 2: 'EPS1_LKASTATUS_ACTIVE', 3: 'EPS1_LKASTATUS_PERMANENTLY_FAIL', 4: 'EPS1_LKASTATUS_NOT_CONFIGURED', 5: 'EPS1_LKASTATUS_RESERVED', 6: 'EPS1_LKASTATUS_RESERVED', 7: 'EPS1_LKASTATUS_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'eps1_lkastatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Eps1_lkastatusType Vectorindependentsigmsg0::eps1_lkastatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  Vector__independent_sig_msg_0::Eps1_lkastatusType ret =  static_cast<Vector__independent_sig_msg_0::Eps1_lkastatusType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'The signal indicates the load of the electric steering motor. If the load could not be measured or an error is detected on the motor, the invalid value of the signal is set', 'is_signed_var': False, 'len': 8, 'name': 'eps1_electricload', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|120]', 'physical_unit': 'A', 'precision': 0.5, 'type': 'double'}
double Vectorindependentsigmsg0::eps1_electricload(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.500000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The signal indicates the status of APA function error', 'enum': {0: 'EPS1_APAERRORSTATUS_NO_ERROR', 1: 'EPS1_APAERRORSTATUS_ERROR'}, 'is_signed_var': False, 'len': 1, 'name': 'eps1_apaerrorstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Eps1_apaerrorstatusType Vectorindependentsigmsg0::eps1_apaerrorstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Vector__independent_sig_msg_0::Eps1_apaerrorstatusType ret =  static_cast<Vector__independent_sig_msg_0::Eps1_apaerrorstatusType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'EPS APA Request Feedback', 'enum': {0: 'EPS1_APAREQUESTFEEDBACK_DISABLE', 1: 'EPS1_APAREQUESTFEEDBACK_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'eps1_aparequestfeedback', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Eps1_aparequestfeedbackType Vectorindependentsigmsg0::eps1_aparequestfeedback(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  Vector__independent_sig_msg_0::Eps1_aparequestfeedbackType ret =  static_cast<Vector__independent_sig_msg_0::Eps1_aparequestfeedbackType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'EPS APA Abort Feedback', 'enum': {0: 'EPS1_APAABORTFEEDBACK_NO_DRIVING_INTERUPTION', 1: 'EPS1_APAABORTFEEDBACK_RECOVERABLE_INTERRUPTION', 2: 'EPS1_APAABORTFEEDBACK_VEHICLE_SPEED_INVALID_OR_TIMEOUT', 3: 'EPS1_APAABORTFEEDBACK_STEERING_WHEEL_ANGLE_REQ_EXCEEDS_LIMITS', 4: 'EPS1_APAABORTFEEDBACK_STEERING_WHEEL_ANGLE_SPEED_REQ_EXCEEDS_LIMITS', 5: 'EPS1_APAABORTFEEDBACK_STEERING_WHEEL_ANGLE_INVALID_OR_TIMEOUT', 6: 'EPS1_APAABORTFEEDBACK_HAD_CONTROL_SIGNAL_INVALID_OR_TIMEOUT', 7: 'EPS1_APAABORTFEEDBACK_CAN_BUS_OFF', 8: 'EPS1_APAABORTFEEDBACK_STEERING_WHEEL_ANGLE_SPEED_EXCEEDS_LIMITS_WHEN_IN_CONTROL', 9: 'EPS1_APAABORTFEEDBACK_EPS_INTERNAL_FAILURE_WITH_LIMITED_STEERING_ASSISTANCE', 10: 'EPS1_APAABORTFEEDBACK_GEAR_SIGNAL_INVALID_OR_TIMEOUT', 11: 'EPS1_APAABORTFEEDBACK_EPS_CONTROL_REQ_RECEIVED_WHEN_IN_CONTOL', 12: 'EPS1_APAABORTFEEDBACK_DIFFERENCE_OF_THE_TWO_NEIGHBORING_STEERING_WHEEL_ANGLE_REQ_SIGNALS_EXCEEDS_LIMITS', 13: 'EPS1_APAABORTFEEDBACK_DIFFERENCE_OF_STEERING_WHEEL_ANGLE_REQ_AND_STEERING_WHEEL_ANGLE_EXCEEDS_LIMITS', 14: 'EPS1_APAABORTFEEDBACK_VEHICLE_SPEED_EXCEEDS_LIMITS_WHEN_IN_CONTROL', 15: 'EPS1_APAABORTFEEDBACK_EPS_SYSTEM_CRITICAL_FAILURE_NO_STEERING_ASSISTANCE', 16: 'EPS1_APAABORTFEEDBACK_EPS_CONTROL_ACTIVE_RECEIVED_WITHOUT_HANDSHAKING', 17: 'EPS1_APAABORTFEEDBACK_HANDSHAKING_TIMEOUT', 18: 'EPS1_APAABORTFEEDBACK_DIFFERENCE_OF_THE_FIRST_STEERING_WHEEL_ANGLE_REQ_SIGNAL_AND_STEERING_WHEEL_ANGLE_EXCEEDS_LIMITS', 19: 'EPS1_APAABORTFEEDBACK_RESERVED', 20: 'EPS1_APAABORTFEEDBACK_RESERVED', 21: 'EPS1_APAABORTFEEDBACK_RESERVED', 22: 'EPS1_APAABORTFEEDBACK_RESERVED', 23: 'EPS1_APAABORTFEEDBACK_RESERVED', 24: 'EPS1_APAABORTFEEDBACK_RESERVED', 25: 'EPS1_APAABORTFEEDBACK_RESERVED', 26: 'EPS1_APAABORTFEEDBACK_RESERVED', 27: 'EPS1_APAABORTFEEDBACK_RESERVED', 28: 'EPS1_APAABORTFEEDBACK_RESERVED', 29: 'EPS1_APAABORTFEEDBACK_RESERVED', 30: 'EPS1_APAABORTFEEDBACK_RESERVED', 31: 'EPS1_APAABORTFEEDBACK_RESERVED'}, 'is_signed_var': False, 'len': 5, 'name': 'eps1_apaabortfeedback', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|31]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Vector__independent_sig_msg_0::Eps1_apaabortfeedbackType Vectorindependentsigmsg0::eps1_apaabortfeedback(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 5);

  Vector__independent_sig_msg_0::Eps1_apaabortfeedbackType ret =  static_cast<Vector__independent_sig_msg_0::Eps1_apaabortfeedbackType>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': 'The signal indicates the actual applied overlay toque in EPS.', 'is_signed_var': False, 'len': 11, 'name': 'eps1_overlayinputtorque', 'offset': -10.0, 'order': 'intel', 'physical_range': '[-10|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::eps1_overlayinputtorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -10.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'eps1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::eps1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The signal indicates the torque measured by the torque sensor at the steering wheel', 'is_signed_var': False, 'len': 11, 'name': 'eps1_handsteeringtorque', 'offset': -10.0, 'order': 'intel', 'physical_range': '[-10|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
double Vectorindependentsigmsg0::eps1_handsteeringtorque(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 3);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000 + -10.000000;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'eps1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::eps1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'bdrr_winbuttonrr_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bdrr_winbuttonrr_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'bdrl_winbuttonrl_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bdrl_winbuttonrl_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'bdfr_winbuttonfr_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bdfr_winbuttonfr_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': True, 'len': 32, 'name': 'a_test_data', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::a_test_data(const std::uint8_t* bytes, int32_t length) const {
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

  x <<= 0;
  x >>= 0;

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_mirrightbutton_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_mirrightbutton_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_mirleftbutton_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_mirleftbutton_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_mirbuttonup_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_mirbuttonup_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_mirbuttonright_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_mirbuttonright_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_mirbuttonleft_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_mirbuttonleft_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_mirbuttondown_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_mirbuttondown_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_unlockbutton_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_unlockbutton_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_lockbutton_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_lockbutton_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'bdfl_bootbuttonfl_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vectorindependentsigmsg0::bdfl_bootbuttonfl_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'bdfl_winbuttonrr_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bdfl_winbuttonrr_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'bdfl_winbuttonrl_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bdfl_winbuttonrl_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'bdfl_winbuttonfr_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bdfl_winbuttonfr_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'bdfl_winbuttonfl_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vectorindependentsigmsg0::bdfl_winbuttonfl_st(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
