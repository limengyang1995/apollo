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

#include "modules/canbus_vehicle/jt/protocol/acu4_154.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

const int32_t Acu4154::ID = 0x154;

// public
Acu4154::Acu4154() { Reset(); }

uint32_t Acu4154::GetPeriod() const {
  // TODO(All) : modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Acu4154::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_acu4_154()->set_acu4_powerrequest(acu4_powerrequest(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_rrwindow_request(acu4_rrwindow_request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_rlwindow_request(acu4_rlwindow_request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_lock_request(acu4_lock_request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_frwindow_request(acu4_frwindow_request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_flwindow_request(acu4_flwindow_request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_boot_request(acu4_boot_request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_rearwiperrequest(acu4_rearwiperrequest(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_led4request(acu4_led4request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_led3request(acu4_led3request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_led2request(acu4_led2request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_led1request(acu4_led1request(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_lamphorn(acu4_lamphorn(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_whistlerequest(acu4_whistlerequest(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_frontwiperrequest(acu4_frontwiperrequest(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_beamlamprequest(acu4_beamlamprequest(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_livecounter(acu4_livecounter(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_checksum(acu4_checksum(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_steeringlamprequest(acu4_steeringlamprequest(bytes, length));
  chassis->mutable_acu4_154()->set_acu4_hazardlamprequest(acu4_hazardlamprequest(bytes, length));
}

void Acu4154::UpdateData_Heartbeat(uint8_t* data) {
   // TODO(All) : you should add the heartbeat manually
}

void Acu4154::UpdateData(uint8_t* data) {
  set_p_acu4_powerrequest(data, acu4_powerrequest_);
  set_p_acu4_rrwindow_request(data, acu4_rrwindow_request_);
  set_p_acu4_rlwindow_request(data, acu4_rlwindow_request_);
  set_p_acu4_lock_request(data, acu4_lock_request_);
  set_p_acu4_frwindow_request(data, acu4_frwindow_request_);
  set_p_acu4_flwindow_request(data, acu4_flwindow_request_);
  set_p_acu4_boot_request(data, acu4_boot_request_);
  set_p_acu4_rearwiperrequest(data, acu4_rearwiperrequest_);
  set_p_acu4_led4request(data, acu4_led4request_);
  set_p_acu4_led3request(data, acu4_led3request_);
  set_p_acu4_led2request(data, acu4_led2request_);
  set_p_acu4_led1request(data, acu4_led1request_);
  set_p_acu4_lamphorn(data, acu4_lamphorn_);
  set_p_acu4_whistlerequest(data, acu4_whistlerequest_);
  set_p_acu4_frontwiperrequest(data, acu4_frontwiperrequest_);
  set_p_acu4_beamlamprequest(data, acu4_beamlamprequest_);
  set_p_acu4_livecounter(data, acu4_livecounter_);
  set_p_acu4_checksum(data, acu4_checksum_);
  set_p_acu4_steeringlamprequest(data, acu4_steeringlamprequest_);
  set_p_acu4_hazardlamprequest(data, acu4_hazardlamprequest_);
}

void Acu4154::Reset() {
  // TODO(All) :  you should check this manually
  acu4_powerrequest_ = 0;
  acu4_rrwindow_request_ = 0;
  acu4_rlwindow_request_ = 0;
  acu4_lock_request_ = 0;
  acu4_frwindow_request_ = 0;
  acu4_flwindow_request_ = 0;
  acu4_boot_request_ = 0;
  acu4_rearwiperrequest_ = 0;
  acu4_led4request_ = false;
  acu4_led3request_ = false;
  acu4_led2request_ = false;
  acu4_led1request_ = false;
  acu4_lamphorn_ = false;
  acu4_whistlerequest_ = 0;
  acu4_frontwiperrequest_ = 0;
  acu4_beamlamprequest_ = 0;
  acu4_livecounter_ = 0;
  acu4_checksum_ = 0;
  acu4_steeringlamprequest_ = Acu4_154::ACU4_STEERINGLAMPREQUEST_OFF;
  acu4_hazardlamprequest_ = Acu4_154::ACU4_HAZARDLAMPREQUEST_OFF;
}

Acu4154* Acu4154::set_acu4_powerrequest(
    int acu4_powerrequest) {
  acu4_powerrequest_ = acu4_powerrequest;
  return this;
 }

// config detail: {'bit': 32, 'description': '1power on 3power off', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_PowerRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_powerrequest(uint8_t* data,
    int acu4_powerrequest) {
  acu4_powerrequest = ProtocolData::BoundedValue(0, 3, acu4_powerrequest);
  int x = acu4_powerrequest;

  Byte to_set(data + 4);
  to_set.set_value(x, 0, 2);
}


Acu4154* Acu4154::set_acu4_rrwindow_request(
    int acu4_rrwindow_request) {
  acu4_rrwindow_request_ = acu4_rrwindow_request;
  return this;
 }

// config detail: {'bit': 30, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RRWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_rrwindow_request(uint8_t* data,
    int acu4_rrwindow_request) {
  acu4_rrwindow_request = ProtocolData::BoundedValue(0, 0, acu4_rrwindow_request);
  int x = acu4_rrwindow_request;

  Byte to_set(data + 3);
  to_set.set_value(x, 6, 2);
}


Acu4154* Acu4154::set_acu4_rlwindow_request(
    int acu4_rlwindow_request) {
  acu4_rlwindow_request_ = acu4_rlwindow_request;
  return this;
 }

// config detail: {'bit': 28, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RLWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_rlwindow_request(uint8_t* data,
    int acu4_rlwindow_request) {
  acu4_rlwindow_request = ProtocolData::BoundedValue(0, 0, acu4_rlwindow_request);
  int x = acu4_rlwindow_request;

  Byte to_set(data + 3);
  to_set.set_value(x, 4, 2);
}


Acu4154* Acu4154::set_acu4_lock_request(
    int acu4_lock_request) {
  acu4_lock_request_ = acu4_lock_request;
  return this;
 }

// config detail: {'bit': 16, 'description': '1lock 2unlock', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_Lock_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_lock_request(uint8_t* data,
    int acu4_lock_request) {
  acu4_lock_request = ProtocolData::BoundedValue(0, 0, acu4_lock_request);
  int x = acu4_lock_request;

  Byte to_set(data + 2);
  to_set.set_value(x, 0, 2);
}


Acu4154* Acu4154::set_acu4_frwindow_request(
    int acu4_frwindow_request) {
  acu4_frwindow_request_ = acu4_frwindow_request;
  return this;
 }

// config detail: {'bit': 26, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FRWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_frwindow_request(uint8_t* data,
    int acu4_frwindow_request) {
  acu4_frwindow_request = ProtocolData::BoundedValue(0, 0, acu4_frwindow_request);
  int x = acu4_frwindow_request;

  Byte to_set(data + 3);
  to_set.set_value(x, 2, 2);
}


Acu4154* Acu4154::set_acu4_flwindow_request(
    int acu4_flwindow_request) {
  acu4_flwindow_request_ = acu4_flwindow_request;
  return this;
 }

// config detail: {'bit': 24, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FLWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_flwindow_request(uint8_t* data,
    int acu4_flwindow_request) {
  acu4_flwindow_request = ProtocolData::BoundedValue(0, 0, acu4_flwindow_request);
  int x = acu4_flwindow_request;

  Byte to_set(data + 3);
  to_set.set_value(x, 0, 2);
}


Acu4154* Acu4154::set_acu4_boot_request(
    int acu4_boot_request) {
  acu4_boot_request_ = acu4_boot_request;
  return this;
 }

// config detail: {'bit': 18, 'description': '1on 2 off 3stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_Boot_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_boot_request(uint8_t* data,
    int acu4_boot_request) {
  acu4_boot_request = ProtocolData::BoundedValue(0, 0, acu4_boot_request);
  int x = acu4_boot_request;

  Byte to_set(data + 2);
  to_set.set_value(x, 2, 2);
}


Acu4154* Acu4154::set_acu4_rearwiperrequest(
    int acu4_rearwiperrequest) {
  acu4_rearwiperrequest_ = acu4_rearwiperrequest;
  return this;
 }

// config detail: {'bit': 22, 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RearWiperRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_rearwiperrequest(uint8_t* data,
    int acu4_rearwiperrequest) {
  acu4_rearwiperrequest = ProtocolData::BoundedValue(0, 3, acu4_rearwiperrequest);
  int x = acu4_rearwiperrequest;

  Byte to_set(data + 2);
  to_set.set_value(x, 6, 2);
}


Acu4154* Acu4154::set_acu4_led4request(
    bool acu4_led4request) {
  acu4_led4request_ = acu4_led4request;
  return this;
 }

// config detail: {'bit': 59, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED4Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void Acu4154::set_p_acu4_led4request(uint8_t* data,
    bool acu4_led4request) {
  int x = acu4_led4request;

  Byte to_set(data + 7);
  to_set.set_value(x, 3, 1);
}


Acu4154* Acu4154::set_acu4_led3request(
    bool acu4_led3request) {
  acu4_led3request_ = acu4_led3request;
  return this;
 }

// config detail: {'bit': 58, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED3Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void Acu4154::set_p_acu4_led3request(uint8_t* data,
    bool acu4_led3request) {
  int x = acu4_led3request;

  Byte to_set(data + 7);
  to_set.set_value(x, 2, 1);
}


Acu4154* Acu4154::set_acu4_led2request(
    bool acu4_led2request) {
  acu4_led2request_ = acu4_led2request;
  return this;
 }

// config detail: {'bit': 57, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED2Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void Acu4154::set_p_acu4_led2request(uint8_t* data,
    bool acu4_led2request) {
  int x = acu4_led2request;

  Byte to_set(data + 7);
  to_set.set_value(x, 1, 1);
}


Acu4154* Acu4154::set_acu4_led1request(
    bool acu4_led1request) {
  acu4_led1request_ = acu4_led1request;
  return this;
 }

// config detail: {'bit': 56, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED1Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void Acu4154::set_p_acu4_led1request(uint8_t* data,
    bool acu4_led1request) {
  int x = acu4_led1request;

  Byte to_set(data + 7);
  to_set.set_value(x, 0, 1);
}


Acu4154* Acu4154::set_acu4_lamphorn(
    bool acu4_lamphorn) {
  acu4_lamphorn_ = acu4_lamphorn;
  return this;
 }

// config detail: {'bit': 11, 'description': 'This signal is the the horn lamp or request', 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LampHorn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void Acu4154::set_p_acu4_lamphorn(uint8_t* data,
    bool acu4_lamphorn) {
  int x = acu4_lamphorn;

  Byte to_set(data + 1);
  to_set.set_value(x, 3, 1);
}


Acu4154* Acu4154::set_acu4_whistlerequest(
    int acu4_whistlerequest) {
  acu4_whistlerequest_ = acu4_whistlerequest;
  return this;
 }

// config detail: {'bit': 14, 'description': '0off  1:on', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_WhistleRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_whistlerequest(uint8_t* data,
    int acu4_whistlerequest) {
  acu4_whistlerequest = ProtocolData::BoundedValue(0, 3, acu4_whistlerequest);
  int x = acu4_whistlerequest;

  Byte to_set(data + 1);
  to_set.set_value(x, 6, 2);
}


Acu4154* Acu4154::set_acu4_frontwiperrequest(
    int acu4_frontwiperrequest) {
  acu4_frontwiperrequest_ = acu4_frontwiperrequest;
  return this;
 }

// config detail: {'bit': 20, 'description': '0stop 1inject water 2slow 3fast', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FrontWiperRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_frontwiperrequest(uint8_t* data,
    int acu4_frontwiperrequest) {
  acu4_frontwiperrequest = ProtocolData::BoundedValue(0, 3, acu4_frontwiperrequest);
  int x = acu4_frontwiperrequest;

  Byte to_set(data + 2);
  to_set.set_value(x, 4, 2);
}


Acu4154* Acu4154::set_acu4_beamlamprequest(
    int acu4_beamlamprequest) {
  acu4_beamlamprequest_ = acu4_beamlamprequest;
  return this;
 }

// config detail: {'bit': 12, 'description': '0:OFF 1:LOW 2£ºHIGH', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_BeamLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_beamlamprequest(uint8_t* data,
    int acu4_beamlamprequest) {
  acu4_beamlamprequest = ProtocolData::BoundedValue(0, 3, acu4_beamlamprequest);
  int x = acu4_beamlamprequest;

  Byte to_set(data + 1);
  to_set.set_value(x, 4, 2);
}


Acu4154* Acu4154::set_acu4_livecounter(
    int acu4_livecounter) {
  acu4_livecounter_ = acu4_livecounter;
  return this;
 }

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU4_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_livecounter(uint8_t* data,
    int acu4_livecounter) {
  acu4_livecounter = ProtocolData::BoundedValue(0, 15, acu4_livecounter);
  int x = acu4_livecounter;

  Byte to_set(data + 7);
  to_set.set_value(x, 4, 4);
}


Acu4154* Acu4154::set_acu4_checksum(
    int acu4_checksum) {
  acu4_checksum_ = acu4_checksum;
  return this;
 }

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU4_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
void Acu4154::set_p_acu4_checksum(uint8_t* data,
    int acu4_checksum) {
  acu4_checksum = ProtocolData::BoundedValue(0, 255, acu4_checksum);
  int x = acu4_checksum;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


Acu4154* Acu4154::set_acu4_steeringlamprequest(
    Acu4_154::Acu4_steeringlamprequestType acu4_steeringlamprequest) {
  acu4_steeringlamprequest_ = acu4_steeringlamprequest;
  return this;
 }

// config detail: {'bit': 8, 'description': 'This signal is steering light request', 'enum': {0: 'ACU4_STEERINGLAMPREQUEST_OFF', 1: 'ACU4_STEERINGLAMPREQUEST_LEFT_ON', 2: 'ACU4_STEERINGLAMPREQUEST_RIGHT_ON', 3: 'ACU4_STEERINGLAMPREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU4_SteeringLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu4154::set_p_acu4_steeringlamprequest(uint8_t* data,
    Acu4_154::Acu4_steeringlamprequestType acu4_steeringlamprequest) {
  int x = acu4_steeringlamprequest;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 2);
}


Acu4154* Acu4154::set_acu4_hazardlamprequest(
    Acu4_154::Acu4_hazardlamprequestType acu4_hazardlamprequest) {
  acu4_hazardlamprequest_ = acu4_hazardlamprequest;
  return this;
 }

// config detail: {'bit': 10, 'description': 'This signal is hazard light request', 'enum': {0: 'ACU4_HAZARDLAMPREQUEST_OFF', 1: 'ACU4_HAZARDLAMPREQUEST_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_HazardLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acu4154::set_p_acu4_hazardlamprequest(uint8_t* data,
    Acu4_154::Acu4_hazardlamprequestType acu4_hazardlamprequest) {
  int x = acu4_hazardlamprequest;

  Byte to_set(data + 1);
  to_set.set_value(x, 2, 1);
}


int Acu4154::acu4_powerrequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_rrwindow_request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(6, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_rlwindow_request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_lock_request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_frwindow_request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(2, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_flwindow_request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_boot_request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_rearwiperrequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(6, 2);

  int ret = x;
  return ret;
}

bool Acu4154::acu4_led4request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(3, 1);

  bool ret = x;
  return ret;
}

bool Acu4154::acu4_led3request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(2, 1);

  bool ret = x;
  return ret;
}

bool Acu4154::acu4_led2request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(1, 1);

  bool ret = x;
  return ret;
}

bool Acu4154::acu4_led1request(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

bool Acu4154::acu4_lamphorn(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(3, 1);

  bool ret = x;
  return ret;
}

int Acu4154::acu4_whistlerequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(6, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_frontwiperrequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_beamlamprequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  int ret = x;
  return ret;
}

int Acu4154::acu4_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

int Acu4154::acu4_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

Acu4_154::Acu4_steeringlamprequestType Acu4154::acu4_steeringlamprequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Acu4_154::Acu4_steeringlamprequestType ret =  static_cast<Acu4_154::Acu4_steeringlamprequestType>(x);
  return ret;
}

Acu4_154::Acu4_hazardlamprequestType Acu4154::acu4_hazardlamprequest(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 1);

  Acu4_154::Acu4_hazardlamprequestType ret =  static_cast<Acu4_154::Acu4_hazardlamprequestType>(x);
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
