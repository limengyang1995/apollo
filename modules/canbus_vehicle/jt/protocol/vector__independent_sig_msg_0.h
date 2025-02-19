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

#include "modules/canbus_vehicle/jt/proto/jt.pb.h"

#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace jt {

class Vectorindependentsigmsg0 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Vectorindependentsigmsg0();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'EPB1_Checksum_Copy_4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int epb1_checksum_copy_4(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACS3_Data7', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs3_data7(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACS3_Data6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs3_data6(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACS3_Data5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs3_data5(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACS3_Data4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs3_data4(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACS3_Data3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs3_data3(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACS3_Data2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs3_data2(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACS3_Data1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs3_data1(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'ACS3_Data0', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int acs3_data0(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'DCDC1_Temperature', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|210]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int dcdc1_temperature(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 2, 'name': 'DCDC1_Status', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int dcdc1_status(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'DCDC1_OutputVoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
    double dcdc1_outputvoltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 10, 'name': 'DCDC1_OutputCurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
    int dcdc1_outputcurrent(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'DCDC1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int dcdc1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 10, 'name': 'DCDC1_InputVoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
    int dcdc1_inputvoltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'DCDC1_InputCurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25]', 'physical_unit': 'A', 'precision': 0.1, 'type': 'double'}
    double dcdc1_inputcurrent(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'DCDC1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int dcdc1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 12, 'name': 'MCU1_TMTorque', 'offset': -500.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'Nm', 'precision': 0.25, 'type': 'double'}
    double mcu1_tmtorque(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'MCU1_TMTemperature', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|210]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int mcu1_tmtemperature(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 16, 'name': 'MCU1_TMSpeed', 'offset': -30000.0, 'order': 'intel', 'physical_range': '[-30000|30000]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
    int mcu1_tmspeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 9, 'name': 'MCU1_TMCapacitanceVoltage', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
    int mcu1_tmcapacitancevoltage(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'MCU1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int mcu1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'MCU1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int mcu1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ESC1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int esc1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ESC1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int esc1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'This signal indicates the yaw rate data (real data; sign depends on mounting position).anticlockwise=positive, clockwise=negative', 'is_signed_var': False, 'len': 12, 'name': 'ESC1_YawRate', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|100]', 'physical_unit': 'deg/s', 'precision': 0.05, 'type': 'double'}
    double esc1_yawrate(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The signal is LongitudinalAcceleration(exact value).Positive value represents  forward,  negative value represents backward.', 'is_signed_var': False, 'len': 12, 'name': 'ESC1_AccelerationX', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
    double esc1_accelerationx(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The signal is Lateral Acceleration(exact value).Positive value represents right side of vehicle, negative value represents  left side of vehicle.', 'is_signed_var': False, 'len': 12, 'name': 'ESC1_AccelerationY', 'offset': -20.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
    double esc1_accelerationy(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'ENV1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int env1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'ENV1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int env1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Indicates the GPS year', 'is_signed_var': False, 'len': 6, 'name': 'ENV1_TimeYear', 'offset': 2000.0, 'order': 'intel', 'physical_range': '[2000|2063]', 'physical_unit': 'Year', 'precision': 1.0, 'type': 'int'}
    int env1_timeyear(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Indicates the GPS second ', 'is_signed_var': False, 'len': 6, 'name': 'ENV1_TimeSecond', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|59]', 'physical_unit': 'Second', 'precision': 1.0, 'type': 'int'}
    int env1_timesecond(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Indicates the GPS month', 'is_signed_var': False, 'len': 4, 'name': 'ENV1_TimeMonth', 'offset': 1.0, 'order': 'intel', 'physical_range': '[1|12]', 'physical_unit': 'Month', 'precision': 1.0, 'type': 'int'}
    int env1_timemonth(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Indicates the GPS minute  ', 'is_signed_var': False, 'len': 6, 'name': 'ENV1_TimeMinute', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|59]', 'physical_unit': 'Minute', 'precision': 1.0, 'type': 'int'}
    int env1_timeminute(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Indicates the GPS hour', 'is_signed_var': False, 'len': 5, 'name': 'ENV1_TimeHour', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|23]', 'physical_unit': 'Hour', 'precision': 1.0, 'type': 'int'}
    int env1_timehour(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'Indicates the GPS day', 'is_signed_var': False, 'len': 5, 'name': 'ENV1_TimeDay', 'offset': 1.0, 'order': 'intel', 'physical_range': '[1|31]', 'physical_unit': 'Day', 'precision': 1.0, 'type': 'int'}
    int env1_timeday(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'This signal delivers information about rain intensity: from 0% (no rain) to 100% (very heavy rain).', 'is_signed_var': False, 'len': 4, 'name': 'ENV1_RainIntensity', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|150]', 'physical_unit': '%', 'precision': 10.0, 'type': 'double'}
    double env1_rainintensity(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'This signal  indicate the high precision light intensity expressed in 10 Bit.', 'is_signed_var': False, 'len': 10, 'name': 'ENV1_BrightnessH', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|6138]', 'physical_unit': 'LUX', 'precision': 6.0, 'type': 'double'}
    double env1_brightnessh(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The signal indicates the status of LKA function', 'enum': {0: 'EPS1_LKASTATUS_TEMPORARY_INHIBIT', 1: 'EPS1_LKASTATUS_AVAILABLE_FOR_CONTROL', 2: 'EPS1_LKASTATUS_ACTIVE', 3: 'EPS1_LKASTATUS_PERMANENTLY_FAIL', 4: 'EPS1_LKASTATUS_NOT_CONFIGURED', 5: 'EPS1_LKASTATUS_RESERVED', 6: 'EPS1_LKASTATUS_RESERVED', 7: 'EPS1_LKASTATUS_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'EPS1_LKAStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Eps1_lkastatusType eps1_lkastatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The signal indicates the load of the electric steering motor. If the load could not be measured or an error is detected on the motor, the invalid value of the signal is set', 'is_signed_var': False, 'len': 8, 'name': 'EPS1_ElectricLoad', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|120]', 'physical_unit': 'A', 'precision': 0.5, 'type': 'double'}
    double eps1_electricload(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The signal indicates the status of APA function error', 'enum': {0: 'EPS1_APAERRORSTATUS_NO_ERROR', 1: 'EPS1_APAERRORSTATUS_ERROR'}, 'is_signed_var': False, 'len': 1, 'name': 'EPS1_APAErrorStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Eps1_apaerrorstatusType eps1_apaerrorstatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'EPS APA Request Feedback', 'enum': {0: 'EPS1_APAREQUESTFEEDBACK_DISABLE', 1: 'EPS1_APAREQUESTFEEDBACK_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'EPS1_APARequestFeedback', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Eps1_aparequestfeedbackType eps1_aparequestfeedback(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'EPS APA Abort Feedback', 'enum': {0: 'EPS1_APAABORTFEEDBACK_NO_DRIVING_INTERUPTION', 1: 'EPS1_APAABORTFEEDBACK_RECOVERABLE_INTERRUPTION', 2: 'EPS1_APAABORTFEEDBACK_VEHICLE_SPEED_INVALID_OR_TIMEOUT', 3: 'EPS1_APAABORTFEEDBACK_STEERING_WHEEL_ANGLE_REQ_EXCEEDS_LIMITS', 4: 'EPS1_APAABORTFEEDBACK_STEERING_WHEEL_ANGLE_SPEED_REQ_EXCEEDS_LIMITS', 5: 'EPS1_APAABORTFEEDBACK_STEERING_WHEEL_ANGLE_INVALID_OR_TIMEOUT', 6: 'EPS1_APAABORTFEEDBACK_HAD_CONTROL_SIGNAL_INVALID_OR_TIMEOUT', 7: 'EPS1_APAABORTFEEDBACK_CAN_BUS_OFF', 8: 'EPS1_APAABORTFEEDBACK_STEERING_WHEEL_ANGLE_SPEED_EXCEEDS_LIMITS_WHEN_IN_CONTROL', 9: 'EPS1_APAABORTFEEDBACK_EPS_INTERNAL_FAILURE_WITH_LIMITED_STEERING_ASSISTANCE', 10: 'EPS1_APAABORTFEEDBACK_GEAR_SIGNAL_INVALID_OR_TIMEOUT', 11: 'EPS1_APAABORTFEEDBACK_EPS_CONTROL_REQ_RECEIVED_WHEN_IN_CONTOL', 12: 'EPS1_APAABORTFEEDBACK_DIFFERENCE_OF_THE_TWO_NEIGHBORING_STEERING_WHEEL_ANGLE_REQ_SIGNALS_EXCEEDS_LIMITS', 13: 'EPS1_APAABORTFEEDBACK_DIFFERENCE_OF_STEERING_WHEEL_ANGLE_REQ_AND_STEERING_WHEEL_ANGLE_EXCEEDS_LIMITS', 14: 'EPS1_APAABORTFEEDBACK_VEHICLE_SPEED_EXCEEDS_LIMITS_WHEN_IN_CONTROL', 15: 'EPS1_APAABORTFEEDBACK_EPS_SYSTEM_CRITICAL_FAILURE_NO_STEERING_ASSISTANCE', 16: 'EPS1_APAABORTFEEDBACK_EPS_CONTROL_ACTIVE_RECEIVED_WITHOUT_HANDSHAKING', 17: 'EPS1_APAABORTFEEDBACK_HANDSHAKING_TIMEOUT', 18: 'EPS1_APAABORTFEEDBACK_DIFFERENCE_OF_THE_FIRST_STEERING_WHEEL_ANGLE_REQ_SIGNAL_AND_STEERING_WHEEL_ANGLE_EXCEEDS_LIMITS', 19: 'EPS1_APAABORTFEEDBACK_RESERVED', 20: 'EPS1_APAABORTFEEDBACK_RESERVED', 21: 'EPS1_APAABORTFEEDBACK_RESERVED', 22: 'EPS1_APAABORTFEEDBACK_RESERVED', 23: 'EPS1_APAABORTFEEDBACK_RESERVED', 24: 'EPS1_APAABORTFEEDBACK_RESERVED', 25: 'EPS1_APAABORTFEEDBACK_RESERVED', 26: 'EPS1_APAABORTFEEDBACK_RESERVED', 27: 'EPS1_APAABORTFEEDBACK_RESERVED', 28: 'EPS1_APAABORTFEEDBACK_RESERVED', 29: 'EPS1_APAABORTFEEDBACK_RESERVED', 30: 'EPS1_APAABORTFEEDBACK_RESERVED', 31: 'EPS1_APAABORTFEEDBACK_RESERVED'}, 'is_signed_var': False, 'len': 5, 'name': 'EPS1_APAAbortFeedback', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|31]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Vector__independent_sig_msg_0::Eps1_apaabortfeedbackType eps1_apaabortfeedback(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The signal indicates the actual applied overlay toque in EPS.', 'is_signed_var': False, 'len': 11, 'name': 'EPS1_OverlayInputTorque', 'offset': -10.0, 'order': 'intel', 'physical_range': '[-10|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
    double eps1_overlayinputtorque(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'EPS1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int eps1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The signal indicates the torque measured by the torque sensor at the steering wheel', 'is_signed_var': False, 'len': 11, 'name': 'EPS1_HandSteeringTorque', 'offset': -10.0, 'order': 'intel', 'physical_range': '[-10|10]', 'physical_unit': 'Nm', 'precision': 0.01, 'type': 'double'}
    double eps1_handsteeringtorque(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'EPS1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int eps1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'BDRR_WinButtonRR_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bdrr_winbuttonrr_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'BDRL_WinButtonRL_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bdrl_winbuttonrl_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'BDFR_WinButtonFR_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bdfr_winbuttonfr_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': True, 'len': 32, 'name': 'A_Test_Data', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int a_test_data(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_MirRightButton_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_mirrightbutton_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_MirLeftButton_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_mirleftbutton_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_MirButtonUP_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_mirbuttonup_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_MirButtonRight_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_mirbuttonright_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_MirButtonLeft_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_mirbuttonleft_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_MirButtonDown_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_mirbuttondown_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_UnLockButton_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_unlockbutton_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_LockButton_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_lockbutton_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'BDFL_BootButtonFL_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
    bool bdfl_bootbuttonfl_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'BDFL_WinButtonRR_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bdfl_winbuttonrr_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'BDFL_WinButtonRL_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bdfl_winbuttonrl_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'BDFL_WinButtonFR_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bdfl_winbuttonfr_st(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'BDFL_WinButtonFL_ST', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
    int bdfl_winbuttonfl_st(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


