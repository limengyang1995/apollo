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

class Vcu0318fefa2d : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Yutong> {
 public:
  static const int32_t ID;

  Vcu0318fefa2d();

  uint32_t GetPeriod() const override;

  void Parse(const std::uint8_t* bytes, int32_t length,
                     Yutong* chassis) const override;

  void UpdateData_Heartbeat(uint8_t* data) override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'bit': 0, 'enum': {0: 'EPBREQ_', 1: 'EPBREQ_EPB', 2: 'EPBREQ_EPB'}, 'is_signed_var': False, 'len': 2, 'name': 'EPBReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0318fefa2d* set_epbreq(Vcu_03_18fefa2d::EpbreqType epbreq);

  // config detail: {'bit': 8, 'enum': {0: 'AUTOHOLDREQ_', 1: 'AUTOHOLDREQ_AUTO_HOLD', 2: 'AUTOHOLDREQ_AUTO_HOLD'}, 'is_signed_var': False, 'len': 2, 'name': 'AutoHoldReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  Vcu0318fefa2d* set_autoholdreq(Vcu_03_18fefa2d::AutoholdreqType autoholdreq);

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'LoadMass', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 't', 'precision': 0.01, 'type': 'double'}
  Vcu0318fefa2d* set_loadmass(double loadmass);

 private:

  // config detail: {'bit': 0, 'enum': {0: 'EPBREQ_', 1: 'EPBREQ_EPB', 2: 'EPBREQ_EPB'}, 'is_signed_var': False, 'len': 2, 'name': 'EPBReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_epbreq(uint8_t* data, Vcu_03_18fefa2d::EpbreqType epbreq);

  // config detail: {'bit': 8, 'enum': {0: 'AUTOHOLDREQ_', 1: 'AUTOHOLDREQ_AUTO_HOLD', 2: 'AUTOHOLDREQ_AUTO_HOLD'}, 'is_signed_var': False, 'len': 2, 'name': 'AutoHoldReq', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_autoholdreq(uint8_t* data, Vcu_03_18fefa2d::AutoholdreqType autoholdreq);

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 16, 'name': 'LoadMass', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 't', 'precision': 0.01, 'type': 'double'}
  void set_p_loadmass(uint8_t* data, double loadmass);

  Vcu_03_18fefa2d::EpbreqType epbreq(const std::uint8_t* bytes, const int32_t length) const;

  Vcu_03_18fefa2d::AutoholdreqType autoholdreq(const std::uint8_t* bytes, const int32_t length) const;

  double loadmass(const std::uint8_t* bytes, const int32_t length) const;

 private:
  Vcu_03_18fefa2d::EpbreqType epbreq_;
  Vcu_03_18fefa2d::AutoholdreqType autoholdreq_;
  double loadmass_;
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo


