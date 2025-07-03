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

#include "modules/canbus_vehicle/venus/proto/venus.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace venus {

class Vectorindependentsigmsg0 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Venus> {
 public:
  static const int32_t ID;
  Vectorindependentsigmsg0();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Venus* chassis) const override;

 private:

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'ACU4_ConditionerTemp', 'offset': 15.0, 'order': 'intel', 'physical_range': '[15|30]', 'physical_unit': '¡æ', 'precision': 1.0, 'type': 'int'}
    int acu4_conditionertemp(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 12, 'name': 'VCU2_YawRate', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|100]', 'physical_unit': 'deg/s', 'precision': 0.05, 'type': 'double'}
    double vcu2_yawrate(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 12, 'name': 'VCU2_LongitudinalAccel', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
    double vcu2_longitudinalaccel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'VCU2_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int vcu2_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 12, 'name': 'VCU2_LateraAccel', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
    double vcu2_lateraaccel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU2_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int vcu2_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'VCU4_VEHICLEMODEINDICATION_NORMAL', 1: 'VCU4_VEHICLEMODEINDICATION_ECO', 2: 'VCU4_VEHICLEMODEINDICATION_SPORT', 3: 'VCU4_VEHICLEMODEINDICATION_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU4_VehicleModeIndication', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Vcu4_vehiclemodeindicationType vcu4_vehiclemodeindication(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU4_OutputPowerPercent', 'offset': -50.0, 'order': 'intel', 'physical_range': '[-50|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
    int vcu4_outputpowerpercent(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'VCU4_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int vcu4_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'VCU4_INTERLOCKSYSTEMFAULT_NOFAULT', 1: 'VCU4_INTERLOCKSYSTEMFAULT_FAULT'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU4_InterlockSystemFault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Vcu4_interlocksystemfaultType vcu4_interlocksystemfault(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'VCU4_INSULATIONMONITORWARNING_NORMAL', 1: 'VCU4_INSULATIONMONITORWARNING_SECONDWARNING', 2: 'VCU4_INSULATIONMONITORWARNING_FIRSTWARNING', 3: 'VCU4_INSULATIONMONITORWARNING_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU4_InsulationMonitorWarning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Vcu4_insulationmonitorwarningType vcu4_insulationmonitorwarning(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'VCU4_DCDCSTATUS_NOTWORKING', 1: 'VCU4_DCDCSTATUS_WORKING', 2: 'VCU4_DCDCSTATUS_NORMALERROR', 3: 'VCU4_DCDCSTATUS_CRITICALERROR'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU4_DCDCStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Vcu4_dcdcstatusType vcu4_dcdcstatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU4_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int vcu4_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'VCU4_CHARGERSTATUS_NOTCHARGE', 1: 'VCU4_CHARGERSTATUS_CHARGING', 2: 'VCU4_CHARGERSTATUS_CHARGEFINISH', 3: 'VCU4_CHARGERSTATUS_CHARGEFAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU4_ChargerStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Vcu4_chargerstatusType vcu4_chargerstatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 9, 'name': 'VCU4_BatteryPackVoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
    int vcu4_batterypackvoltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU4_BatteryPackTemperature', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|210]', 'physical_unit': '¡ãC', 'precision': 1.0, 'type': 'int'}
    int vcu4_batterypacktemperature(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU4_BatteryPackSOC', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
    int vcu4_batterypacksoc(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 10, 'name': 'VCU4_BatteryPackCurrent', 'offset': -500.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
    int vcu4_batterypackcurrent(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'BYD_GearCMD', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int byd_gearcmd(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'GEAR_P', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool gear_p(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'Gear_Info', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int gear_info(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'ACU5_WheelSpeedRR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double acu5_wheelspeedrr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'ACU5_WheelSpeedRL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double acu5_wheelspeedrl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'ACU5_WheelSpeedFR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double acu5_wheelspeedfr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 15, 'name': 'ACU5_WheelSpeedFL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|180]', 'physical_unit': 'km/h', 'precision': 0.01, 'type': 'double'}
    double acu5_wheelspeedfl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 32, 'name': 'SIGNAL2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int signal2(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 32, 'name': 'pulse1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int pulse1(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'ACU3_Action6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acu3_action6(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'ACU3_Action5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acu3_action5(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_Action4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acu3_action4(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_Action3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acu3_action3(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_Action2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acu3_action2(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_Action1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acu3_action1(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'ACU3_WIPER_NOREQUEST', 1: 'ACU3_WIPER_SPEED1', 2: 'ACU3_WIPER_SPEED2', 3: 'ACU3_WIPER_SPEED3', 4: 'ACU3_WIPER_SPEED4', 5: 'ACU3_WIPER_AUTO', 6: 'ACU3_WIPER_WASH', 7: 'ACU3_WIPER_OFF'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU3_Wiper', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Acu3_wiperType acu3_wiper(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'ACU3_WIDTHLIGHT_NOREQUEST', 1: 'ACU3_WIDTHLIGHT_ON', 2: 'ACU3_WIDTHLIGHT_OFF', 3: 'ACU3_WIDTHLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_WidthLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Acu3_widthlightType acu3_widthlight(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 4, 'name': 'ACU3_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int acu3_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'ACU3_IGNITION_NOREQUEST', 1: 'ACU3_IGNITION_ON', 2: 'ACU3_IGNITION_START', 3: 'ACU3_IGNITION_OFF', 4: 'ACU3_IGNITION_IG1', 5: 'ACU3_IGNITION_IG2', 6: 'ACU3_IGNITION_RESERVED1', 7: 'ACU3_IGNITION_RESERVED2'}, 'is_signed_var': False, 'len': 3, 'name': 'ACU3_Ignition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Acu3_ignitionType acu3_ignition(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'ACU3_HORNLIGHT_NOREQUEST', 1: 'ACU3_HORNLIGHT_ON', 2: 'ACU3_HORNLIGHT_OFF', 3: 'ACU3_HORNLIGHT_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_HornLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Acu3_hornlightType acu3_hornlight(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'ACU3_HORN_NOREQUEST', 1: 'ACU3_HORN_ON', 2: 'ACU3_HORN_OFF', 3: 'ACU3_HORN_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_Horn', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Acu3_hornType acu3_horn(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'ACU3_DOORLOCK_NOREQUEST', 1: 'ACU3_DOORLOCK_LOCK', 2: 'ACU3_DOORLOCK_UNLOCK', 3: 'ACU3_DOORLOCK_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'ACU3_DoorLock', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Acu3_doorlockType acu3_doorlock(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'ACU3_ARTISTICLIGHT_NOREQUEST', 1: 'ACU3_ARTISTICLIGHT_EFFECT1', 2: 'ACU3_ARTISTICLIGHT_EFFECT2', 3: 'ACU3_ARTISTICLIGHT_EFFECT3', 4: 'ACU3_ARTISTICLIGHT_EFFECT4', 5: 'ACU3_ARTISTICLIGHT_EFFECT5', 6: 'ACU3_ARTISTICLIGHT_EFFECT6', 7: 'ACU3_ARTISTICLIGHT_EFFECT7', 8: 'ACU3_ARTISTICLIGHT_EFFECT8', 9: 'ACU3_ARTISTICLIGHT_EFFECT9', 10: 'ACU3_ARTISTICLIGHT_EFFECT10', 11: 'ACU3_ARTISTICLIGHT_EFFECT11', 12: 'ACU3_ARTISTICLIGHT_EFFECT12', 13: 'ACU3_ARTISTICLIGHT_EFFECT13', 14: 'ACU3_ARTISTICLIGHT_EFFECT14', 15: 'ACU3_ARTISTICLIGHT_OFF'}, 'is_signed_var': False, 'len': 4, 'name': 'ACU3_ArtisticLight', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Acu3_artisticlightType acu3_artisticlight(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'enum': {0: 'ACU1_STANDSTILLST_INACTIVE', 1: 'ACU1_STANDSTILLST_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'ACU1_StandStillSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Acu1_standstillstType acu1_standstillst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'EPS1_ModeR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int eps1_moder(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'EPS1_Mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int eps1_mode(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'EPS1_AutoControlR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool eps1_autocontrolr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'EPS1_AutoControlF', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool eps1_autocontrolf(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'EPS1_ErrorR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int eps1_errorr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'EPS1_ErrorF', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int eps1_errorf(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'EPS1_CurrentSpeedR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': '', 'precision': 4.0, 'type': 'double'}
    double eps1_currentspeedr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'EPS1_CurrentSpeedF', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': '', 'precision': 4.0, 'type': 'double'}
    double eps1_currentspeedf(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 14, 'name': 'EPS1_CurrentAngleR', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
    double eps1_currentangler(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 14, 'name': 'EPS1_CurrentAngleF', 'offset': -600.0, 'order': 'intel', 'physical_range': '[-600|600]', 'physical_unit': '', 'precision': 0.1, 'type': 'double'}
    double eps1_currentanglef(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BCM_EngStartST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bcm_engstartst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'BCM_LampST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bcm_lampst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'BCM_FuelRemain', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bcm_fuelremain(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BCM_DifLock', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bcm_diflock(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'BCM_EngineStartRequest', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bcm_enginestartrequest(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU3_ESPPresure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu3_esppresure(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'VCU3_ESPPosition', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int vcu3_espposition(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace venus
}  // namespace canbus
}  // namespace apollo


