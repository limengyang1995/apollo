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

#pragma once

#include "modules/canbus_vehicle/jt/proto/jt.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace jt {

class Acu4154 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;

  Acu4154();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 32, 'description': '1power on 3power off', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_PowerRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_powerrequest(int acu4_powerrequest);

  // config detail: {'bit': 30, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RRWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_rrwindow_request(int acu4_rrwindow_request);

  // config detail: {'bit': 28, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RLWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_rlwindow_request(int acu4_rlwindow_request);

  // config detail: {'bit': 16, 'description': '1lock 2unlock', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_Lock_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_lock_request(int acu4_lock_request);

  // config detail: {'bit': 26, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FRWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_frwindow_request(int acu4_frwindow_request);

  // config detail: {'bit': 24, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FLWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_flwindow_request(int acu4_flwindow_request);

  // config detail: {'bit': 18, 'description': '1on 2 off 3stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_Boot_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_boot_request(int acu4_boot_request);

  // config detail: {'bit': 22, 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RearWiperRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_rearwiperrequest(int acu4_rearwiperrequest);

  // config detail: {'bit': 59, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED4Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  Acu4154* set_acu4_led4request(bool acu4_led4request);

  // config detail: {'bit': 58, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED3Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  Acu4154* set_acu4_led3request(bool acu4_led3request);

  // config detail: {'bit': 57, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED2Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  Acu4154* set_acu4_led2request(bool acu4_led2request);

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED1Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  Acu4154* set_acu4_led1request(bool acu4_led1request);

  // config detail: {'bit': 11, 'description': 'This signal is the the horn lamp or request', 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LampHorn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  Acu4154* set_acu4_lamphorn(bool acu4_lamphorn);

  // config detail: {'bit': 14, 'description': '0off  1:on', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_WhistleRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_whistlerequest(int acu4_whistlerequest);

  // config detail: {'bit': 20, 'description': '0stop 1inject water 2slow 3fast', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FrontWiperRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_frontwiperrequest(int acu4_frontwiperrequest);

  // config detail: {'bit': 12, 'description': '0:OFF 1:LOW 2£ºHIGH', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_BeamLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_beamlamprequest(int acu4_beamlamprequest);

  // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU4_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_livecounter(int acu4_livecounter);

  // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU4_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  Acu4154* set_acu4_checksum(int acu4_checksum);

  // config detail: {'bit': 8, 'description': 'This signal is steering light request', 'enum': {0: 'ACU4_STEERINGLAMPREQUEST_OFF', 1: 'ACU4_STEERINGLAMPREQUEST_LEFT_ON', 2: 'ACU4_STEERINGLAMPREQUEST_RIGHT_ON', 3: 'ACU4_STEERINGLAMPREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU4_SteeringLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu4154* set_acu4_steeringlamprequest(Acu4_154::Acu4_steeringlamprequestType acu4_steeringlamprequest);

  // config detail: {'bit': 10, 'description': 'This signal is hazard light request', 'enum': {0: 'ACU4_HAZARDLAMPREQUEST_OFF', 1: 'ACU4_HAZARDLAMPREQUEST_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_HazardLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Acu4154* set_acu4_hazardlamprequest(Acu4_154::Acu4_hazardlamprequestType acu4_hazardlamprequest);

 private:

  // config detail: {'bit': 32, 'description': '1power on 3power off', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_PowerRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_powerrequest(uint8_t* data, int acu4_powerrequest);

  // config detail: {'bit': 30, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RRWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_rrwindow_request(uint8_t* data, int acu4_rrwindow_request);

  // config detail: {'bit': 28, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RLWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_rlwindow_request(uint8_t* data, int acu4_rlwindow_request);

  // config detail: {'bit': 16, 'description': '1lock 2unlock', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_Lock_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_lock_request(uint8_t* data, int acu4_lock_request);

  // config detail: {'bit': 26, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FRWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_frwindow_request(uint8_t* data, int acu4_frwindow_request);

  // config detail: {'bit': 24, 'description': '1fall  2 rise 3 stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FLWindow_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_flwindow_request(uint8_t* data, int acu4_flwindow_request);

  // config detail: {'bit': 18, 'description': '1on 2 off 3stop', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_Boot_Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_boot_request(uint8_t* data, int acu4_boot_request);

  // config detail: {'bit': 22, 'is_signed_var': False, 'len': 2, 'name': 'ACU4_RearWiperRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_rearwiperrequest(uint8_t* data, int acu4_rearwiperrequest);

  // config detail: {'bit': 59, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED4Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_acu4_led4request(uint8_t* data, bool acu4_led4request);

  // config detail: {'bit': 58, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED3Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_acu4_led3request(uint8_t* data, bool acu4_led3request);

  // config detail: {'bit': 57, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED2Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_acu4_led2request(uint8_t* data, bool acu4_led2request);

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LED1Request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_acu4_led1request(uint8_t* data, bool acu4_led1request);

  // config detail: {'bit': 11, 'description': 'This signal is the the horn lamp or request', 'is_signed_var': False, 'len': 1, 'name': 'ACU4_LampHorn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_acu4_lamphorn(uint8_t* data, bool acu4_lamphorn);

  // config detail: {'bit': 14, 'description': '0off  1:on', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_WhistleRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_whistlerequest(uint8_t* data, int acu4_whistlerequest);

  // config detail: {'bit': 20, 'description': '0stop 1inject water 2slow 3fast', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_FrontWiperRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_frontwiperrequest(uint8_t* data, int acu4_frontwiperrequest);

  // config detail: {'bit': 12, 'description': '0:OFF 1:LOW 2£ºHIGH', 'is_signed_var': False, 'len': 2, 'name': 'ACU4_BeamLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_beamlamprequest(uint8_t* data, int acu4_beamlamprequest);

  // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ACU4_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_livecounter(uint8_t* data, int acu4_livecounter);

  // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ACU4_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
  void set_p_acu4_checksum(uint8_t* data, int acu4_checksum);

  // config detail: {'bit': 8, 'description': 'This signal is steering light request', 'enum': {0: 'ACU4_STEERINGLAMPREQUEST_OFF', 1: 'ACU4_STEERINGLAMPREQUEST_LEFT_ON', 2: 'ACU4_STEERINGLAMPREQUEST_RIGHT_ON', 3: 'ACU4_STEERINGLAMPREQUEST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU4_SteeringLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu4_steeringlamprequest(uint8_t* data, Acu4_154::Acu4_steeringlamprequestType acu4_steeringlamprequest);

  // config detail: {'bit': 10, 'description': 'This signal is hazard light request', 'enum': {0: 'ACU4_HAZARDLAMPREQUEST_OFF', 1: 'ACU4_HAZARDLAMPREQUEST_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU4_HazardLampRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu4_hazardlamprequest(uint8_t* data, Acu4_154::Acu4_hazardlamprequestType acu4_hazardlamprequest);

  int acu4_powerrequest(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_rrwindow_request(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_rlwindow_request(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_lock_request(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_frwindow_request(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_flwindow_request(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_boot_request(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_rearwiperrequest(const std::uint8_t* bytes, const int32_t length) const;

  bool acu4_led4request(const std::uint8_t* bytes, const int32_t length) const;

  bool acu4_led3request(const std::uint8_t* bytes, const int32_t length) const;

  bool acu4_led2request(const std::uint8_t* bytes, const int32_t length) const;

  bool acu4_led1request(const std::uint8_t* bytes, const int32_t length) const;

  bool acu4_lamphorn(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_whistlerequest(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_frontwiperrequest(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_beamlamprequest(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_livecounter(const std::uint8_t* bytes, const int32_t length) const;

  int acu4_checksum(const std::uint8_t* bytes, const int32_t length) const;

  Acu4_154::Acu4_steeringlamprequestType acu4_steeringlamprequest(const std::uint8_t* bytes, const int32_t length) const;

  Acu4_154::Acu4_hazardlamprequestType acu4_hazardlamprequest(const std::uint8_t* bytes, const int32_t length) const;

 private:
  int acu4_powerrequest_;
  int acu4_rrwindow_request_;
  int acu4_rlwindow_request_;
  int acu4_lock_request_;
  int acu4_frwindow_request_;
  int acu4_flwindow_request_;
  int acu4_boot_request_;
  int acu4_rearwiperrequest_;
  bool acu4_led4request_;
  bool acu4_led3request_;
  bool acu4_led2request_;
  bool acu4_led1request_;
  bool acu4_lamphorn_;
  int acu4_whistlerequest_;
  int acu4_frontwiperrequest_;
  int acu4_beamlamprequest_;
  int acu4_livecounter_;
  int acu4_checksum_;
  Acu4_154::Acu4_steeringlamprequestType acu4_steeringlamprequest_;
  Acu4_154::Acu4_hazardlamprequestType acu4_hazardlamprequest_;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


