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

class Eps01cff272d : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;

  Eps01cff272d();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'EPSSteerAngReq', 'offset': -40.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  Eps01cff272d* set_epssteerangreq(double epssteerangreq);

  // config detail: {'bit': 16, 'enum': {0: 'EPSCTRLREQ_', 1: 'EPSCTRLREQ_'}, 'is_signed_var': False, 'len': 2, 'name': 'EPSCtrlReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Eps01cff272d* set_epsctrlreq(Eps_01_cff272d::EpsctrlreqType epsctrlreq);

 private:

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'EPSSteerAngReq', 'offset': -40.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  void set_p_epssteerangreq(uint8_t* data, double epssteerangreq);

  // config detail: {'bit': 16, 'enum': {0: 'EPSCTRLREQ_', 1: 'EPSCTRLREQ_'}, 'is_signed_var': False, 'len': 2, 'name': 'EPSCtrlReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_epsctrlreq(uint8_t* data, Eps_01_cff272d::EpsctrlreqType epsctrlreq);

  double epssteerangreq(const std::uint8_t* bytes, const int32_t length) const;

  Eps_01_cff272d::EpsctrlreqType epsctrlreq(const std::uint8_t* bytes, const int32_t length) const;

 private:
  double epssteerangreq_;
  Eps_01_cff272d::EpsctrlreqType epsctrlreq_;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


