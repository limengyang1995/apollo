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

#include "modules/canbus_vehicle/kfc/kfc_message_manager.h"

#include "modules/canbus_vehicle/kfc/protocol/acu1_310.h"
#include "modules/canbus_vehicle/kfc/protocol/agv_321.h"
#include "modules/canbus_vehicle/kfc/protocol/vcu1_320.h"
#include "modules/canbus_vehicle/kfc/protocol/vector__independent_sig_msg_0.h"

namespace apollo {
namespace canbus {
namespace kfc {

KfcMessageManager::KfcMessageManager() {
  // Control Messages
  AddSendProtocolData<Acu1310, true>();

  // Report Messages
  AddRecvProtocolData<Agv321, true>();
  AddRecvProtocolData<Vcu1320, true>();
  AddRecvProtocolData<Vectorindependentsigmsg0, true>();
}

KfcMessageManager::~KfcMessageManager() {}

}  // namespace kfc
}  // namespace canbus
}  // namespace apollo
