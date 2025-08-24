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

#include "modules/canbus_vehicle/middlecar/middlecar_message_manager.h"

#include "modules/canbus_vehicle/middlecar/protocol/fsd_vcu_cmd1_6a0.h"
#include "modules/canbus_vehicle/middlecar/protocol/fsd_vcu_cmd2_6a2.h"
#include "modules/canbus_vehicle/middlecar/protocol/vcu_errormsg1_681.h"
#include "modules/canbus_vehicle/middlecar/protocol/vcu_errormsg2_682.h"
#include "modules/canbus_vehicle/middlecar/protocol/vcu_fsd_status1_685.h"
#include "modules/canbus_vehicle/middlecar/protocol/vcu_fsd_status2_686.h"

namespace apollo {
namespace canbus {
namespace middlecar {

MiddlecarMessageManager::MiddlecarMessageManager() {
  // Control Messages
  AddSendProtocolData<Fsdvcucmd16a0, true>();
  AddSendProtocolData<Fsdvcucmd26a2, true>();

  // Report Messages
  AddRecvProtocolData<Vcuerrormsg1681, true>();
  AddRecvProtocolData<Vcuerrormsg2682, true>();
  AddRecvProtocolData<Vcufsdstatus1685, true>();
  AddRecvProtocolData<Vcufsdstatus2686, true>();
}

MiddlecarMessageManager::~MiddlecarMessageManager() {}

}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo
