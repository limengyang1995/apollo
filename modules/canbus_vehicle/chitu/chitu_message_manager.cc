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

#include "modules/canbus_vehicle/chitu/chitu_message_manager.h"

#include "modules/canbus_vehicle/chitu/protocol/adas_angle_cmd_112.h"
#include "modules/canbus_vehicle/chitu/protocol/adas_emergency_spot_2a0.h"
#include "modules/canbus_vehicle/chitu/protocol/adas_speed_cmd_113.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_adas_soc_4a0.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_braking_state_200.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_charge_discharge_4a2.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_diversion_angle_100.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_max_temp_4a1.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_mileage_info_111.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_remote_date1_4a3.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_remote_date2_4a4.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_remote_date3_4a5.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_remote_date4_4a6.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_speed_message_110.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_sw_state_130.h"
#include "modules/canbus_vehicle/chitu/protocol/vcu_voltage_state_201.h"

namespace apollo {
namespace canbus {
namespace chitu {

ChituMessageManager::ChituMessageManager() {
  // Control Messages
  AddSendProtocolData<Adasanglecmd112, true>();
  AddSendProtocolData<Adasemergencyspot2a0, true>();
  AddSendProtocolData<Adasspeedcmd113, true>();

  // Report Messages
  AddRecvProtocolData<Vcuadassoc4a0, true>();
  AddRecvProtocolData<Vcubrakingstate200, true>();
  AddRecvProtocolData<Vcuchargedischarge4a2, true>();
  AddRecvProtocolData<Vcudiversionangle100, true>();
  AddRecvProtocolData<Vcumaxtemp4a1, true>();
  AddRecvProtocolData<Vcumileageinfo111, true>();
  AddRecvProtocolData<Vcuremotedate14a3, true>();
  AddRecvProtocolData<Vcuremotedate24a4, true>();
  AddRecvProtocolData<Vcuremotedate34a5, true>();
  AddRecvProtocolData<Vcuremotedate44a6, true>();
  AddRecvProtocolData<Vcuspeedmessage110, true>();
  AddRecvProtocolData<Vcuswstate130, true>();
  AddRecvProtocolData<Vcuvoltagestate201, true>();
}

ChituMessageManager::~ChituMessageManager() {}

}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
