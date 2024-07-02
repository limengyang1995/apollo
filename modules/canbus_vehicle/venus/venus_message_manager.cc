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

#include "modules/canbus_vehicle/venus/venus_message_manager.h"

#include "modules/canbus_vehicle/venus/protocol/acu1_529.h"
#include "modules/canbus_vehicle/venus/protocol/acu2_532.h"
#include "modules/canbus_vehicle/venus/protocol/acu3_534.h"
#include "modules/canbus_vehicle/venus/protocol/vcu1_56f.h"
#include "modules/canbus_vehicle/venus/protocol/vcu3_2_56d.h"
#include "modules/canbus_vehicle/venus/protocol/vcu5_56a.h"
#include "modules/canbus_vehicle/venus/protocol/vcu6_56c.h"
#include "modules/canbus_vehicle/venus/protocol/vcu7_569.h"
#include "modules/canbus_vehicle/venus/protocol/vector__independent_sig_msg_0.h"

namespace apollo {
namespace canbus {
namespace venus {

VenusMessageManager::VenusMessageManager() {
  // Control Messages
  AddSendProtocolData<Acu1529, true>();
  AddSendProtocolData<Acu2532, true>();
  AddSendProtocolData<Acu3534, true>();

  // Report Messages
  AddRecvProtocolData<Vcu156f, true>();
  AddRecvProtocolData<Vcu3256d, true>();
  AddRecvProtocolData<Vcu556a, true>();
  AddRecvProtocolData<Vcu656c, true>();
  AddRecvProtocolData<Vcu7569, true>();
  AddRecvProtocolData<Vectorindependentsigmsg0, true>();
}

VenusMessageManager::~VenusMessageManager() {}

}  // namespace venus
}  // namespace canbus
}  // namespace apollo
