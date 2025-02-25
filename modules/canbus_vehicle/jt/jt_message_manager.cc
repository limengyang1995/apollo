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

#include "modules/canbus_vehicle/jt/jt_message_manager.h"

#include "modules/canbus_vehicle/jt/protocol/acu1_151.h"
#include "modules/canbus_vehicle/jt/protocol/acu2_152.h"
#include "modules/canbus_vehicle/jt/protocol/acu3_153.h"
#include "modules/canbus_vehicle/jt/protocol/acu4_154.h"
#include "modules/canbus_vehicle/jt/protocol/acs1_20c.h"
#include "modules/canbus_vehicle/jt/protocol/acs2_20d.h"
#include "modules/canbus_vehicle/jt/protocol/acs3_20e.h"
#include "modules/canbus_vehicle/jt/protocol/epb1_2a1.h"
#include "modules/canbus_vehicle/jt/protocol/vcu1_210.h"
#include "modules/canbus_vehicle/jt/protocol/vcu2_211.h"
#include "modules/canbus_vehicle/jt/protocol/vcu3_212.h"

namespace apollo {
namespace canbus {
namespace jt {

JtMessageManager::JtMessageManager() {
  // Control Messages
  AddSendProtocolData<Acu1151, true>();
  AddSendProtocolData<Acu2152, true>();
  AddSendProtocolData<Acu3153, true>();
  AddSendProtocolData<Acu4154, true>();

  // Report Messages
  AddRecvProtocolData<Acs120c, true>();
  AddRecvProtocolData<Acs220d, true>();
  AddRecvProtocolData<Acs320e, true>();
  AddRecvProtocolData<Epb12a1, true>();
  AddRecvProtocolData<Vcu1210, true>();
  AddRecvProtocolData<Vcu2211, true>();
  AddRecvProtocolData<Vcu3212, true>();
}

JtMessageManager::~JtMessageManager() {}

}  // namespace jt
}  // namespace canbus
}  // namespace apollo
