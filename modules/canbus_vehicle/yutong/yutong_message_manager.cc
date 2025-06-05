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

#include "modules/canbus_vehicle/yutong/yutong_message_manager.h"

#include "modules/canbus_vehicle/yutong/protocol/eps_01_cff272d.h"
#include "modules/canbus_vehicle/yutong/protocol/vcu_01_cffd12a.h"
#include "modules/canbus_vehicle/yutong/protocol/vcu_02_18ffda2a.h"
#include "modules/canbus_vehicle/yutong/protocol/vcu_03_18fefa2d.h"
#include "modules/canbus_vehicle/yutong/protocol/vcu_04_18fdcd2a.h"
#include "modules/canbus_vehicle/yutong/protocol/vcu_05_18ff422a.h"
#include "modules/canbus_vehicle/yutong/protocol/vcu_06_18fe412a.h"
#include "modules/canbus_vehicle/yutong/protocol/vcu_07_df205f6.h"
#include "modules/canbus_vehicle/yutong/protocol/vcu_08_18ff452a.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_01_18ffdc24.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_02_19ffcb24.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_03_19ffca24.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_04_18ff0824.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_05_18ff1924.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_06_18ff1724.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_07_18ff0f24.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_08_18ff1424.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_09_cff5182.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_10_cff5183.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_11_18ff2df3.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_12_18ff30f4.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_13_18ff32f4.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_14_18fead0b.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_15_18febf0b.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_16_8fe6e0b.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_17_18f0090b.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_18_19fff103.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_19_18ffcc17.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_20_18fec117.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_21_19ff5417.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_22_18ffe117.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_23_18ffc017.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_24_18a70017.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_25_cff12fa.h"

namespace apollo {
namespace canbus {
namespace yutong {

YutongMessageManager::YutongMessageManager() {
  // Control Messages
  AddSendProtocolData<Eps01cff272d, true>();
  AddSendProtocolData<Vcu01cffd12a, true>();
  AddSendProtocolData<Vcu0218ffda2a, true>();
  AddSendProtocolData<Vcu0318fefa2d, true>();
  AddSendProtocolData<Vcu0418fdcd2a, true>();
  AddSendProtocolData<Vcu0518ff422a, true>();
  AddSendProtocolData<Vcu0618fe412a, true>();
  AddSendProtocolData<Vcu07df205f6, true>();
  AddSendProtocolData<Vcu0818ff452a, true>();

  // Report Messages
  AddRecvProtocolData<Gw0118ffdc24, true>();
  AddRecvProtocolData<Gw0219ffcb24, true>();
  AddRecvProtocolData<Gw0319ffca24, true>();
  AddRecvProtocolData<Gw0418ff0824, true>();
  AddRecvProtocolData<Gw0518ff1924, true>();
  AddRecvProtocolData<Gw0618ff1724, true>();
  AddRecvProtocolData<Gw0718ff0f24, true>();
  AddRecvProtocolData<Gw0818ff1424, true>();
  AddRecvProtocolData<Gw09cff5182, true>();
  AddRecvProtocolData<Gw10cff5183, true>();
  AddRecvProtocolData<Gw1118ff2df3, true>();
  AddRecvProtocolData<Gw1218ff30f4, true>();
  AddRecvProtocolData<Gw1318ff32f4, true>();
  AddRecvProtocolData<Gw1418fead0b, true>();
  AddRecvProtocolData<Gw1518febf0b, true>();
  AddRecvProtocolData<Gw168fe6e0b, true>();
  AddRecvProtocolData<Gw1718f0090b, true>();
  AddRecvProtocolData<Gw1819fff103, true>();
  AddRecvProtocolData<Gw1918ffcc17, true>();
  AddRecvProtocolData<Gw2018fec117, true>();
  AddRecvProtocolData<Gw2119ff5417, true>();
  AddRecvProtocolData<Gw2218ffe117, true>();
  AddRecvProtocolData<Gw2318ffc017, true>();
  AddRecvProtocolData<Gw2418a70017, true>();
  AddRecvProtocolData<Gw25cff12fa, true>();
}

YutongMessageManager::~YutongMessageManager() {}

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
