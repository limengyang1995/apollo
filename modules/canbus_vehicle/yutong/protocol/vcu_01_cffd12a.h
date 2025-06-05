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

#include "modules/canbus_vehicle/yutong/proto/yutong.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace yutong {

class Vcu01cffd12a : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;

  Vcu01cffd12a();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACCpedalPosReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
  Vcu01cffd12a* set_accpedalposreq(double accpedalposreq);

  // config detail: {'bit': 8, 'enum': {0: 'GEARREQ_N', 32: 'GEARREQ_D', 64: 'GEARREQ_R', 96: 'GEARREQ_L'}, 'is_signed_var': False, 'len': 8, 'name': 'GearReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu01cffd12a* set_gearreq(Vcu_01_cffd12a::GearreqType gearreq);

  // config detail: {'bit': 16, 'enum': {0: 'BRAKEACTIVEREQ_', 1: 'BRAKEACTIVEREQ_'}, 'is_signed_var': False, 'len': 4, 'name': 'BrakeActiveReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu01cffd12a* set_brakeactivereq(Vcu_01_cffd12a::BrakeactivereqType brakeactivereq);

  // config detail: {'bit': 20, 'enum': {0: 'ACCACTIVESTS_', 1: 'ACCACTIVESTS_'}, 'is_signed_var': False, 'len': 4, 'name': 'ACCactiveSts', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu01cffd12a* set_accactivests(Vcu_01_cffd12a::AccactivestsType accactivests);

  // config detail: {'bit': 24, 'is_signed_var': False, 'len': 16, 'name': 'DecelerationReq', 'offset': -15.687, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'm/s2', 'precision': 0.000488281, 'type': 'double'}
  Vcu01cffd12a* set_decelerationreq(double decelerationreq);

  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'MsgCnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Vcu01cffd12a* set_msgcnt(int msgcnt);

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'Checkcum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  Vcu01cffd12a* set_checkcum(int checkcum);

 private:

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACCpedalPosReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '%', 'precision': 0.4, 'type': 'double'}
  void set_p_accpedalposreq(uint8_t* data, double accpedalposreq);

  // config detail: {'bit': 8, 'enum': {0: 'GEARREQ_N', 32: 'GEARREQ_D', 64: 'GEARREQ_R', 96: 'GEARREQ_L'}, 'is_signed_var': False, 'len': 8, 'name': 'GearReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_gearreq(uint8_t* data, Vcu_01_cffd12a::GearreqType gearreq);

  // config detail: {'bit': 16, 'enum': {0: 'BRAKEACTIVEREQ_', 1: 'BRAKEACTIVEREQ_'}, 'is_signed_var': False, 'len': 4, 'name': 'BrakeActiveReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_brakeactivereq(uint8_t* data, Vcu_01_cffd12a::BrakeactivereqType brakeactivereq);

  // config detail: {'bit': 20, 'enum': {0: 'ACCACTIVESTS_', 1: 'ACCACTIVESTS_'}, 'is_signed_var': False, 'len': 4, 'name': 'ACCactiveSts', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_accactivests(uint8_t* data, Vcu_01_cffd12a::AccactivestsType accactivests);

  // config detail: {'bit': 24, 'is_signed_var': False, 'len': 16, 'name': 'DecelerationReq', 'offset': -15.687, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'm/s2', 'precision': 0.000488281, 'type': 'double'}
  void set_p_decelerationreq(uint8_t* data, double decelerationreq);

  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'MsgCnt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_msgcnt(uint8_t* data, int msgcnt);

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'Checkcum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_checkcum(uint8_t* data, int checkcum);

  double accpedalposreq(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_01_cffd12a::GearreqType gearreq(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_01_cffd12a::BrakeactivereqType brakeactivereq(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_01_cffd12a::AccactivestsType accactivests(const std::uint8_t* bytes, const int32_t length) const;

  double decelerationreq(const std::uint8_t* bytes, const int32_t length) const;

  int msgcnt(const std::uint8_t* bytes, const int32_t length) const;

  int checkcum(const std::uint8_t* bytes, const int32_t length) const;

 private:
  double accpedalposreq_;
  Vcu_01_cffd12a::GearreqType gearreq_;
  Vcu_01_cffd12a::BrakeactivereqType brakeactivereq_;
  Vcu_01_cffd12a::AccactivestsType accactivests_;
  double decelerationreq_;
  int msgcnt_;
  int checkcum_;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


