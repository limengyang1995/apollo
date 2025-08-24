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

#include "modules/canbus_vehicle/middlecar/proto/middlecar.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace middlecar {

class Vcuerrormsg1681 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Middlecar> {
 public:
  static const int32_t ID;
  Vcuerrormsg1681();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Middlecar* chassis) const override;

 private:

    // config detail: {'bit': 34, 'description': 'DCDC_24V_fault_level', 'enum': {0: 'VCU_DC24ERRORLEVEL_NO_FAULT', 1: 'VCU_DC24ERRORLEVEL_MINOR_FAULT', 2: 'VCU_DC24ERRORLEVEL_GENERAL_FAULT', 3: 'VCU_DC24ERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_DC24ErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_dc24errorlevelType vcu_dc24errorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 36, 'description': 'Fault_level_of_low-voltage_distribution_box', 'enum': {0: 'VCU_LOWVOLTAGEBOXERRORLEVEL_NO_FAULT', 1: 'VCU_LOWVOLTAGEBOXERRORLEVEL_MINOR_FAULT', 2: 'VCU_LOWVOLTAGEBOXERRORLEVEL_GENERAL_FAULT', 3: 'VCU_LOWVOLTAGEBOXERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_LowVoltageBoxErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_lowvoltageboxerrorlevelType vcu_lowvoltageboxerrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 38, 'description': 'IMU_fault_level', 'enum': {0: 'VCU_IMUERRORLEVEL_NO_FAULT', 1: 'VCU_IMUERRORLEVEL_MINOR_FAULT', 2: 'VCU_IMUERRORLEVEL_GENERAL_FAULT', 3: 'VCU_IMUERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_IMUErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_imuerrorlevelType vcu_imuerrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 42, 'description': 'CAN_bus_fault', 'enum': {0: 'VCU_CANBUSERROR_FCANBUS_FAULT', 1: 'VCU_CANBUSERROR_RCANBUS_FAULT', 2: 'VCU_CANBUSERROR_FRCANBUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_CANbusError', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_canbuserrorType vcu_canbuserror(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Vehicle_fault_level', 'enum': {0: 'VCU_VEHICLEERRORLEVEL_NO_FAULT', 1: 'VCU_VEHICLEERRORLEVEL_MINOR_FAULT', 2: 'VCU_VEHICLEERRORLEVEL_GENERAL_FAULT', 3: 'VCU_VEHICLEERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_VehicleErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_vehicleerrorlevelType vcu_vehicleerrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 14, 'description': 'Fault_level_of_front_drive_motor', 'enum': {0: 'VCU_FRONTMOTORERRORLEVEL_NO_FAULT', 1: 'VCU_FRONTMOTORERRORLEVEL_MINOR_FAULT', 2: 'VCU_FRONTMOTORERRORLEVEL_GENERAL_FAULT', 3: 'VCU_FRONTMOTORERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_FrontMotorErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_frontmotorerrorlevelType vcu_frontmotorerrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'Fault_level_of_rear_drive_motor', 'enum': {0: 'VCU_REARMOTORERRORLEVEL_NO_FAULT', 1: 'VCU_REARMOTORERRORLEVEL_MINOR_FAULT', 2: 'VCU_REARMOTORERRORLEVEL_GENERAL_FAULT', 3: 'VCU_REARMOTORERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_RearMotorErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_rearmotorerrorlevelType vcu_rearmotorerrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 20, 'description': 'Right_battery_pack_fault_level', 'enum': {0: 'VCU_RIGHTBATTERYERRORLEVEL_NO_FAULT', 1: 'VCU_RIGHTBATTERYERRORLEVEL_MINOR_FAULT', 2: 'VCU_RIGHTBATTERYERRORLEVEL_GENERAL_FAULT', 3: 'VCU_RIGHTBATTERYERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_RightBatteryErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_rightbatteryerrorlevelType vcu_rightbatteryerrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'description': '1200w_DCDC_12V_fault_level', 'enum': {0: 'VCU_DC12_1200WERRORLEVEL_NO_FAULT', 1: 'VCU_DC12_1200WERRORLEVEL_MINOR_FAULT', 2: 'VCU_DC12_1200WERRORLEVEL_GENERAL_FAULT', 3: 'VCU_DC12_1200WERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_DC12_1200wErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_dc12_1200werrorlevelType vcu_dc12_1200werrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 12, 'description': 'Fault_level_of_right_battery_box', 'enum': {0: 'VCU_RIGHTPOWERERRORLEVEL_NO_FAULT', 1: 'VCU_RIGHTPOWERERRORLEVEL_MINOR_FAULT', 2: 'VCU_RIGHTPOWERERRORLEVEL_GENERAL_FAULT', 3: 'VCU_RIGHTPOWERERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_RightPowerErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_rightpowererrorlevelType vcu_rightpowererrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 10, 'description': 'Left_battery_box_fault_level', 'enum': {0: 'VCU_LEFTPOWERERRORLEVEL_NO_FAULT', 1: 'VCU_LEFTPOWERERRORLEVEL_MINOR_FAULT', 2: 'VCU_LEFTPOWERERRORLEVEL_GENERAL_FAULT', 3: 'VCU_LEFTPOWERERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_LeftPowerErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_leftpowererrorlevelType vcu_leftpowererrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'FSD_module_fault_level', 'enum': {0: 'VCU_FSDERRORLEVEL_FCANBUS_FAULT', 1: 'VCU_FSDERRORLEVEL_RCANBUS_FAULT', 2: 'VCU_FSDERRORLEVEL_FRCANBUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_FSDErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_fsderrorlevelType vcu_fsderrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 2, 'description': 'Front_axle_fault_level', 'enum': {0: 'VCU_FRONTAXLEERRORLEVEL_NO_FAULT', 1: 'VCU_FRONTAXLEERRORLEVEL_MINOR_FAULT', 2: 'VCU_FRONTAXLEERRORLEVEL_GENERAL_FAULT', 3: 'VCU_FRONTAXLEERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_FrontAxleErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_frontaxleerrorlevelType vcu_frontaxleerrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 6, 'description': 'Fault_level_of_chassis_control_box', 'enum': {0: 'VCU_CHASSISCONTROLBOXLEVEL_NO_FAULT', 1: 'VCU_CHASSISCONTROLBOXLEVEL_MINOR_FAULT', 2: 'VCU_CHASSISCONTROLBOXLEVEL_GENERAL_FAULT', 3: 'VCU_CHASSISCONTROLBOXLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_ChassisControlBoxLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_chassiscontrolboxlevelType vcu_chassiscontrolboxlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 4, 'description': 'Rear_axle_fault_level', 'enum': {0: 'VCU_REARAXLEERRORLEVEL_NO_FAULT', 1: 'VCU_REARAXLEERRORLEVEL_MINOR_FAULT', 2: 'VCU_REARAXLEERRORLEVEL_GENERAL_FAULT', 3: 'VCU_REARAXLEERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_RearAxleErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_rearaxleerrorlevelType vcu_rearaxleerrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'description': 'Left_battery_pack_fault_level', 'enum': {0: 'VCU_LEFTBATTERYLEVEL_NO_FAULT', 1: 'VCU_LEFTBATTERYLEVEL_MINOR_FAULT', 2: 'VCU_LEFTBATTERYLEVEL_GENERAL_FAULT', 3: 'VCU_LEFTBATTERYLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_LeftBatteryLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_leftbatterylevelType vcu_leftbatterylevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 30, 'description': '600W_DCDC_12V_fault_level', 'enum': {0: 'VCU_DC12_600WLEVEL_NO_FAULT', 1: 'VCU_DC12_600WLEVEL_MINOR_FAULT', 2: 'VCU_DC12_600WLEVEL_GENERAL_FAULT', 3: 'VCU_DC12_600WLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_DC12_600wLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_dc12_600wlevelType vcu_dc12_600wlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 26, 'description': 'Front_EPS_fault_level', 'enum': {0: 'VCU_FRONTEPSLEVEL_NO_FAULT', 1: 'VCU_FRONTEPSLEVEL_MINOR_FAULT', 2: 'VCU_FRONTEPSLEVEL_GENERAL_FAULT', 3: 'VCU_FRONTEPSLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_FrontEPSLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_frontepslevelType vcu_frontepslevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'description': 'rear_EPS_fault_level', 'enum': {0: 'VCU_REAREPSLEVEL_NO_FAULT', 1: 'VCU_REAREPSLEVEL_MINOR_FAULT', 2: 'VCU_REAREPSLEVEL_GENERAL_FAULT', 3: 'VCU_REAREPSLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_RearEPSLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_rearepslevelType vcu_rearepslevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 22, 'description': 'Front_brake_fault_level', 'enum': {0: 'VCU_FRONTBRAKELEVEL_NO_FAULT', 1: 'VCU_FRONTBRAKELEVEL_MINOR_FAULT', 2: 'VCU_FRONTBRAKELEVEL_GENERAL_FAULT', 3: 'VCU_FRONTBRAKELEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_FrontBrakeLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_frontbrakelevelType vcu_frontbrakelevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'description': 'Rear_brake_fault_level', 'enum': {0: 'VCU_REARBRAKELEVEL_NO_FAULT', 1: 'VCU_REARBRAKELEVEL_MINOR_FAULT', 2: 'VCU_REARBRAKELEVEL_GENERAL_FAULT', 3: 'VCU_REARBRAKELEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_RearBrakeLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_rearbrakelevelType vcu_rearbrakelevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 40, 'description': 'Load_fault_level', 'enum': {0: 'VCU_LOADERRORLEVEL_NO_FAULT', 1: 'VCU_LOADERRORLEVEL_MINOR_FAULT', 2: 'VCU_LOADERRORLEVEL_GENERAL_FAULT', 3: 'VCU_LOADERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_LoadErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_loaderrorlevelType vcu_loaderrorlevel(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 44, 'description': 'Remote_control_fault_level', 'enum': {0: 'VCU_REMOTEERRORLEVEL_NO_FAULT', 1: 'VCU_REMOTEERRORLEVEL_MINOR_FAULT', 2: 'VCU_REMOTEERRORLEVEL_GENERAL_FAULT', 3: 'VCU_REMOTEERRORLEVEL_SERIOUS_FAULT'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_RemoteErrorLevel', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vcu_errormsg1_681::Vcu_remoteerrorlevelType vcu_remoteerrorlevel(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo


