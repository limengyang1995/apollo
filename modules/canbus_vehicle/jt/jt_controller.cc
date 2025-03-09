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

#include "modules/canbus_vehicle/jt/jt_controller.h"

#include <string>

#include "modules/common_msgs/basic_msgs/vehicle_signal.pb.h"

#include "cyber/common/log.h"
#include "cyber/time/time.h"
#include "modules/canbus/vehicle/vehicle_controller.h"
#include "modules/canbus_vehicle/jt/jt_message_manager.h"
#include "modules/drivers/canbus/can_comm/can_sender.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace jt {
using ::apollo::common::ErrorCode;
using ::apollo::common::VehicleSignal;
using ::apollo::control::ControlCommand;
using ::apollo::drivers::canbus::ProtocolData;

namespace {
const int32_t kMaxFailAttempt = 10;
const int32_t CHECK_RESPONSE_STEER_UNIT_FLAG = 1;
const int32_t CHECK_RESPONSE_SPEED_UNIT_FLAG = 2;

}  // namespace

ErrorCode JtController::Init(
	const VehicleParameter& params,
	CanSender<::apollo::canbus::Jt> *const can_sender,
  MessageManager<::apollo::canbus::Jt> *const message_manager) {
  if (is_initialized_) {
    AINFO << "JtController has already been initiated.";
    return ErrorCode::CANBUS_ERROR;
  }

  vehicle_params_.CopyFrom(
      common::VehicleConfigHelper::Instance()->GetConfig().vehicle_param());
  params_.CopyFrom(params);
  if (!params_.has_driving_mode()) {
    AERROR << "Vehicle conf pb not set driving_mode.";
    return ErrorCode::CANBUS_ERROR;
  }

  if (can_sender == nullptr) {
    AERROR << "Canbus sender is null.";
    return ErrorCode::CANBUS_ERROR;
  }
  can_sender_ = can_sender;

  if (message_manager == nullptr) {
    AERROR << "protocol manager is null.";
    return ErrorCode::CANBUS_ERROR;
  }
  message_manager_ = message_manager;

  // sender part
  acu1_151_ = dynamic_cast<Acu1151*>
          (message_manager_->GetMutableProtocolDataById(Acu1151::ID));
  if (acu1_151_ == nullptr) {
     AERROR << "Acu1151 does not exist in the JtMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  acu2_152_ = dynamic_cast<Acu2152*>
          (message_manager_->GetMutableProtocolDataById(Acu2152::ID));
  if (acu2_152_ == nullptr) {
     AERROR << "Acu2152 does not exist in the JtMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  acu3_153_ = dynamic_cast<Acu3153*>
          (message_manager_->GetMutableProtocolDataById(Acu3153::ID));
  if (acu3_153_ == nullptr) {
     AERROR << "Acu3153 does not exist in the JtMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  acu4_154_ = dynamic_cast<Acu4154*>
          (message_manager_->GetMutableProtocolDataById(Acu4154::ID));
  if (acu4_154_ == nullptr) {
     AERROR << "Acu4154 does not exist in the JtMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  can_sender_->AddMessage(Acu1151::ID, acu1_151_, false);
  can_sender_->AddMessage(Acu2152::ID, acu2_152_, false);
  can_sender_->AddMessage(Acu3153::ID, acu3_153_, false);
  can_sender_->AddMessage(Acu4154::ID, acu4_154_, false);

  former_gear_position = Chassis::GEAR_NEUTRAL;
  AINFO << "JtController is initialized.";

  is_initialized_ = true;
  return ErrorCode::OK;
}

JtController::~JtController() {}

bool JtController::Start() {
  if (!is_initialized_) {
    AERROR << "JtController has NOT been initiated.";
    return false;
  }
  const auto& update_func = [this] { SecurityDogThreadFunc(); };
  thread_.reset(new std::thread(update_func));

  return true;
}

void JtController::Stop() {
  if (!is_initialized_) {
    AERROR << "JtController stops or starts improperly!";
    return;
  }

  if (thread_ != nullptr && thread_->joinable()) {
    thread_->join();
    thread_.reset();
    AINFO << "JtController stopped.";
  }
}

Chassis JtController::chassis() {
  chassis_.Clear();
  Jt chassis_detail;
  message_manager_->GetSensorData(&chassis_detail);
  // 21, 22, previously 1, 2
  if (driving_mode() == Chassis::EMERGENCY_MODE) {
  set_chassis_error_code(Chassis::NO_ERROR);
  }

  chassis_.set_driving_mode(driving_mode());
  chassis_.set_error_code(chassis_error_code());

  // 3
  chassis_.set_engine_started(true);


  // 4 chassis spd
  if (chassis_detail.has_vcu2_211() &&
      chassis_detail.vcu2_211().has_vcu2_vehiclespeed()) {
    chassis_.set_speed_mps(
        static_cast<float>(chassis_detail.vcu2_211().vcu2_vehiclespeed() / 3.6 ));
  } else {
    chassis_.set_speed_mps(0);
  }


  // check chassis error
  if (CheckChassisError()) {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "Chassis has some fault, please check the chassis_detail.");
  }else{
    chassis_.mutable_engage_advice()->set_advice(
          apollo::common::EngageAdvice::READY_TO_ENGAGE);
  }

  /* ADD YOUR OWN CAR CHASSIS OPERATION HERE */

  // 5 gear location
  if (chassis_detail.has_vcu3_212() &&
      chassis_detail.vcu3_212().has_vcu3_leverinfo()) {
    switch (chassis_detail.vcu3_212().vcu3_leverinfo()) {
      case Vcu3_212::VCU3_LEVERINFO_D: {
        chassis_.set_gear_location(Chassis::GEAR_DRIVE);
      } break;
      case Vcu3_212::VCU3_LEVERINFO_N: {
        chassis_.set_gear_location(Chassis::GEAR_NEUTRAL);
      } break;
      case Vcu3_212::VCU3_LEVERINFO_R: {
        chassis_.set_gear_location(Chassis::GEAR_REVERSE);
      } break;
      case Vcu3_212::VCU3_LEVERINFO_P: {
        chassis_.set_gear_location(Chassis::GEAR_PARKING);
      } break;
      default:
        chassis_.set_gear_location(Chassis::GEAR_INVALID);
        break;
    }
  } else {
    chassis_.set_gear_location(Chassis::GEAR_INVALID);
  }


  // 6 epb status
  if (chassis_detail.has_vcu3_212() &&
      chassis_detail.vcu3_212().has_vcu3_epbstatus()) {
    chassis_.set_parking_brake(
      chassis_detail.vcu3_212().vcu3_epbstatus() != 0);
  } else {
    chassis_.set_parking_brake(false);
  }

  // 7 throttle pct
  if (chassis_detail.has_vcu2_211() && 
      chassis_detail.vcu2_211().has_vcu2_accelpedalposition()) {
    chassis_.set_throttle_percentage(chassis_detail.vcu2_211().vcu2_accelpedalposition());
  } else {
    chassis_.set_throttle_percentage(0);
  }

  // 8 brake  state  0: no act  1: act
  if (chassis_detail.has_vcu2_211() && 
      chassis_detail.vcu2_211().has_vcu2_brakepedalst()) {
    chassis_.set_brake_percentage(
      chassis_detail.vcu2_211().vcu2_brakepedalst()); //revise
  } else {
    chassis_.set_brake_percentage(0);
  }

  // 10 steering pct
  if (chassis_detail.has_vcu1_210() && 
      chassis_detail.vcu1_210().has_vcu1_steeringangle()) {
    chassis_.set_steering_percentage(
      - chassis_detail.vcu1_210().vcu1_steeringangle() * 100 / (vehicle_params_.max_steer_angle() / M_PI * 180) );
  } else {
    chassis_.set_steering_percentage(0);
  }

  // 11 hand steering torque
  if (chassis_detail.has_vcu1_210() && 
      chassis_detail.vcu1_210().has_vcu1_handsteeringtorque()) {
    chassis_.set_steering_torque_nm(
      chassis_detail.vcu1_210().vcu1_handsteeringtorque());
  } else {
    chassis_.set_steering_torque_nm(0);
  }

  

  // 13 chassis error
  if (chassis_error_mask_) {
    chassis_.set_chassis_error_mask(chassis_error_mask_);
  }

  // Give engage_advice based on error_code and canbus feedback
  if (chassis_error_mask_) {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason("Chassis error!");
  } else if (chassis_.parking_brake()) {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "Vehicle is not in a safe state to engage!");
  } else {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::READY_TO_ENGAGE);
  }

  return chassis_;
}

void JtController::Emergency() {
  set_driving_mode(Chassis::EMERGENCY_MODE);
  ResetProtocol();
  acu4_154_->set_acu4_hazardlamprequest(Acu4_154::ACU4_HAZARDLAMPREQUEST_ON);
}

ErrorCode JtController::EnableAutoMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE) {
    AINFO << "already in COMPLETE_AUTO_DRIVE mode";
    return ErrorCode::OK;
  }
  // set enable
  acu3_153_->set_acu3_gearcontrolflag(Acu3_153::ACU3_GEARCONTROLFLAG_REQUEST);
  acu1_151_->set_acu1_steeringcontrolflag(Acu1_151::ACU1_STEERINGCONTROLFLAG_REQUEST);
  // acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_REQUESTTHROTTLE);  //throttle
  acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_RESERVEDSPEED);  //speed
  // acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_POSITION);  //brakepedal
  acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_DEC);  //deceleration


  can_sender_->Update();
  const int32_t flag =
      CHECK_RESPONSE_STEER_UNIT_FLAG | CHECK_RESPONSE_SPEED_UNIT_FLAG;
  if (!CheckResponse(flag, true)) {
    AERROR << "Failed to switch to COMPLETE_AUTO_DRIVE mode. Please check the "
              "emergency button or chassis.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  }
  set_driving_mode(Chassis::COMPLETE_AUTO_DRIVE);
  AINFO << "Switch to COMPLETE_AUTO_DRIVE mode ok.";
  acu4_154_->set_acu4_hazardlamprequest(Acu4_154::ACU4_HAZARDLAMPREQUEST_OFF);
  return ErrorCode::OK;
}

ErrorCode JtController::EnableCloudMode() {
  if (driving_mode() == Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "Already in REMOTE_CLOUD_DRIVE mode";
    return ErrorCode::OK;
  }
  // set enable
  acu3_153_->set_acu3_gearcontrolflag(Acu3_153::ACU3_GEARCONTROLFLAG_REQUEST);
  acu1_151_->set_acu1_steeringcontrolflag(Acu1_151::ACU1_STEERINGCONTROLFLAG_REQUEST);
  acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_REQUESTTHROTTLE);  //throttle
  // acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_RESERVEDSPEED);  //speed
  acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_POSITION);  //brakepedal
  // acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_DEC);  //deceleration


  can_sender_->Update();
  set_driving_mode(Chassis::REMOTE_CLOUD_DRIVE);
  AINFO << "Switch to REMOTE_CLOUD_DRIVE mode ok.";
  acu4_154_->set_acu4_hazardlamprequest(Acu4_154::ACU4_HAZARDLAMPREQUEST_OFF);
  return ErrorCode::OK;
}

ErrorCode JtController::DisableAutoMode() {
  ResetProtocol();
  can_sender_->Update();
  set_driving_mode(Chassis::COMPLETE_MANUAL);
  set_chassis_error_code(Chassis::NO_ERROR);
  AINFO << "Switch to COMPLETE_MANUAL ok.";
  return ErrorCode::OK;
}

ErrorCode JtController::EnableSteeringOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_STEER_ONLY) {
    set_driving_mode(Chassis::AUTO_STEER_ONLY);
    AINFO << "Already in AUTO_STEER_ONLY mode.";
    acu4_154_->set_acu4_hazardlamprequest(Acu4_154::ACU4_HAZARDLAMPREQUEST_OFF);
    return ErrorCode::OK;
  }
  
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS MODE OR NOT
  // set enable
  acu1_151_->set_acu1_steeringcontrolflag(Acu1_151::ACU1_STEERINGCONTROLFLAG_REQUEST);

  can_sender_->Update();
  if (!CheckResponse(CHECK_RESPONSE_STEER_UNIT_FLAG, true)) {
    AERROR << "Failed to switch to AUTO_STEER_ONLY mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  }
  set_driving_mode(Chassis::AUTO_STEER_ONLY);
  AINFO << "Switch to AUTO_STEER_ONLY mode ok.";
  return ErrorCode::OK;
}

ErrorCode JtController::EnableSpeedOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_SPEED_ONLY) {
    set_driving_mode(Chassis::AUTO_SPEED_ONLY);
    AINFO << "Already in AUTO_SPEED_ONLY mode";
    return ErrorCode::OK;
  }
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS MODE OR NOT
  // set enable
  // acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_REQUESTTHROTTLE);  //throttle
  acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_RESERVEDSPEED);  //speed
  // acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_POSITION);  //brakepedal
  acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_DEC);  //deceleration

  can_sender_->Update();
  if (!CheckResponse(CHECK_RESPONSE_SPEED_UNIT_FLAG, true)) {
    AERROR << "Failed to switch to AUTO_SPEED_ONLY mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  }
  set_driving_mode(Chassis::AUTO_SPEED_ONLY);
  AINFO << "Switch to AUTO_SPEED_ONLY mode ok.";
  acu4_154_->set_acu4_hazardlamprequest(Acu4_154::ACU4_HAZARDLAMPREQUEST_OFF);
  return ErrorCode::OK;
}

// NEUTRAL, REVERSE, DRIVE
void JtController::Gear(Chassis::GearPosition gear_position) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "This drive mode no need to set gear.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  if (gear_position != former_gear_position ){
    //switch gear need a brake pedal 10%
    acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_POSITION);  //brakepedal
    // wait for brake pedal or acceleration command
    acu3_153_->set_acu3_brakingtargetposition(20);
    ++gear_count;
  }else{
    if (gear_count < 50 && gear_count > 0 ){
      //switch gear need a brake pedal 10%
      acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_POSITION);  //brakepedal
      // wait for brake pedal or acceleration command
      acu3_153_->set_acu3_brakingtargetposition(20);
      ++gear_count;
    }else if(gear_count != 0){
      acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_NO_REQUEST);  //brakepedal
      gear_count = 0;
    }
  }
  
 acu3_153_->set_acu3_gearcontrolflag(Acu3_153::ACU3_GEARCONTROLFLAG_REQUEST);
 switch (gear_position) {
  case Chassis::GEAR_NEUTRAL: {
    acu3_153_->set_acu3_geartarget(Acu3_153::ACU3_GEARTARGET_N);
    break;
  }
  case Chassis::GEAR_REVERSE: {
    acu3_153_->set_acu3_geartarget(Acu3_153::ACU3_GEARTARGET_R);
    break;
  }
  case Chassis::GEAR_DRIVE: {
    acu3_153_->set_acu3_geartarget(Acu3_153::ACU3_GEARTARGET_D);
    break;
  }
  case Chassis::GEAR_PARKING: {
    acu3_153_->set_acu3_geartarget(Acu3_153::ACU3_GEARTARGET_P);
    break;
  }
  case Chassis::GEAR_NONE: {
    acu3_153_->set_acu3_gearcontrolflag(Acu3_153::ACU3_GEARCONTROLFLAG_NO_REQUEST);
    break;
  }
  case Chassis::GEAR_INVALID: {
    AERROR << "Gear command is invalid!";
    acu3_153_->set_acu3_gearcontrolflag(Acu3_153::ACU3_GEARCONTROLFLAG_NO_REQUEST);
    break;
  }
  default: {
    acu3_153_->set_acu3_gearcontrolflag(Acu3_153::ACU3_GEARCONTROLFLAG_NO_REQUEST);
    break;
  }
}
former_gear_position = gear_position;
}

// brake with pedal
// pedal:0.00~99.99, unit:percentage
void JtController::Brake(double pedal) {
  // double real_value = vehicle_params_.max_acceleration() * acceleration / 100;
  // TODO(All) :  Update brake value based on mode
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current drive mode does not need to set brake pedal.";
    return;
  }
/* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  AINFO << "break COMMAND 1 IS "<< pedal;
  acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_POSITION);  //brakepedal
  // wait for brake pedal or acceleration command
  acu3_153_->set_acu3_brakingtargetposition(std::abs(int(pedal)));
  
}

// drive with pedal
// pedal:0.0~99.9 unit:percentage
void JtController::Throttle(double pedal) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current drive mode does not need to set throttle pedal.";
    return;
  }
/* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  AINFO << "PEDAL COMMAND 1 IS "<< pedal;
  if (pedal >= 0){
    acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_REQUESTTHROTTLE);  //throttle
    acu2_152_->set_acu2_drivingtargetthrottle(int(pedal));
  }
  else{
    acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_NO_REQUEST);  //throttle
  }
}

// confirm the car is driven by acceleration command instead of
// throttle/brake pedal drive with acceleration/deceleration acc:-7.0 ~ 5.0,
// unit:m/s^2
void JtController::Acceleration(double acc) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    AINFO << "The current drive mode does not need to set acceleration.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
  */
  if (acc < 0){
    acu3_153_->set_acu3_brakingcontrolflag(Acu3_153::ACU3_BRAKINGCONTROLFLAG_REQUEST_DEC);  //deceleration
    acu3_153_->set_acu3_brakingtargetdeceleration(acc);
  }
}

// confirm the car is driven by speed command
// speed:-xx.0~xx.0, unit:m/s
void JtController::Speed(double speed) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY ) {
    AINFO << "The current drive mode does not need to set speed.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
  */  
  if (speed >= 0){
    acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_RESERVEDSPEED);  //speed
    acu2_152_->set_acu2_drivingtargetspeed(speed);
  }
  else{
    acu2_152_->set_acu2_drivingcontrolflag(Acu2_152::ACU2_DRIVINGCONTROLFLAG_NO_REQUEST);  //speed
  }
}

// jt default, +470 ~ -470 or other, left:+, right:-
// need to be compatible with control module, so reverse
// steering with steering angle
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
void JtController::Steer(double angle) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  acu1_151_->set_acu1_steeringcontrolflag(Acu1_151::ACU1_STEERINGCONTROLFLAG_REQUEST);
  acu1_151_->set_acu1_steeringtargetangle(- vehicle_params_.max_steer_angle() /M_PI * 180.0 * angle / 100.0);
  //acu1_310_->set_acu1_steeringcontrolrequest(Acu1_310::ACU1_STEERINGCONTROLREQUEST_REQUEST);
  //acu1_310_->set_acu1_targetsteeringangle( - vehicle_params_.max_steer_angle() /M_PI * 180.0 * angle / 100.0);
}

// jt default, steering with new angle and angle speed
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
// angle_spd:0.00~99.99, unit:deg/s
void JtController::Steer(double angle, double angle_spd) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  acu1_151_->set_acu1_steeringcontrolflag(Acu1_151::ACU1_STEERINGCONTROLFLAG_REQUEST);
  acu1_151_->set_acu1_steeringtargetangle(- vehicle_params_.max_steer_angle() /M_PI * 180.0 * angle / 100.0);
  acu1_151_->set_acu1_steeringtargetspeed(vehicle_params_.max_steer_angle_rate() /M_PI * 180 * angle_spd / 100);
  //acu1_310_->set_acu1_steeringcontrolrequest(Acu1_310::ACU1_STEERINGCONTROLREQUEST_REQUEST);
  //acu1_310_->set_acu1_targetsteeringangle(-int(vehicle_params_.max_steer_angle() /M_PI * 180.0 * angle / 100.0));
  //acu1_310_->set_acu1_targetsteeringspeed(int(vehicle_params_.max_steer_angle_rate() /M_PI * 180 * angle_spd / 100));
}

void JtController::SetEpbBreak(const ControlCommand& command) {
  if (command.parking_brake()) {
    if (former_parking_brake != command.parking_brake()){
      acu3_153_->set_acu3_epbcontrolflag(Acu3_153::ACU3_EPBCONTROLFLAG_LOCK);
    }else{
      acu3_153_->set_acu3_epbcontrolflag(Acu3_153::ACU3_EPBCONTROLFLAG_NO_REQUEST);
    }
  } else {
    if (former_parking_brake != command.parking_brake()){
      acu3_153_->set_acu3_epbcontrolflag(Acu3_153::ACU3_EPBCONTROLFLAG_RELEASE);
    }else{
      acu3_153_->set_acu3_epbcontrolflag(Acu3_153::ACU3_EPBCONTROLFLAG_NO_REQUEST);
    }
    
  }
  former_parking_brake = command.parking_brake();

}

void JtController::SetBeam(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.high_beam()) {
    acu4_154_->set_acu4_beamlamprequest(2);
  } else if (vehicle_signal.low_beam()) {
    acu4_154_->set_acu4_beamlamprequest(1);
  } else {
    acu4_154_->set_acu4_beamlamprequest(0);
  }
}

void JtController::SetHorn(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.horn()) {
    acu4_154_->set_acu4_whistlerequest(1);
  } else {
    acu4_154_->set_acu4_whistlerequest(0);
  }
}

void JtController::SetTurningSignal(const VehicleSignal& vehicle_signal) {
  // Set Turn Signal
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  auto signal = vehicle_signal.turn_signal();
  if (signal == common::VehicleSignal::TURN_LEFT) {
    acu4_154_->set_acu4_steeringlamprequest(Acu4_154::ACU4_STEERINGLAMPREQUEST_LEFT_ON);
  } else if (signal == common::VehicleSignal::TURN_RIGHT) {
    acu4_154_->set_acu4_steeringlamprequest(Acu4_154::ACU4_STEERINGLAMPREQUEST_RIGHT_ON);
  } else {
    acu4_154_->set_acu4_steeringlamprequest(Acu4_154::ACU4_STEERINGLAMPREQUEST_OFF);
  }
  
}

ErrorCode JtController::HandleCustomOperation(
    const external_command::ChassisCommand& command) {
  return ErrorCode::OK;
}

bool JtController::VerifyID() {
  if (!CheckVin()) {
    AERROR << "Failed to get the vin. Get vin again.";
    GetVin();
    return false;
  } else {
    ResetVin();
    return true;
  }
}

bool JtController::CheckVin() {
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  if (chassis_.vehicle_id().vin().size() >= 7) {
    AINFO << "Vin check success! Vehicel vin is "
          << chassis_.vehicle_id().vin();
    return true;
  } else {
    AINFO << "Vin check failed! Current vin size is "
          << chassis_.vehicle_id().vin().size();
    return false;
  }
  */
  return false;
}

void JtController::GetVin() {
  // Get vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_ENABLE);
  AINFO << "Get vin";
  can_sender_->Update();
  */
}

void JtController::ResetVin() {
  // Reset vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_DISABLE);
  AINFO << "Reset vin";
  can_sender_->Update();
  */
}

void JtController::ResetProtocol() {
  message_manager_->ResetSendMessages();
}

bool JtController::CheckChassisError() {
  Jt chassis_detail;
  if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
    AERROR_EVERY(100) << "Get chassis detail failed.";
  }

  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // steer fault
  // drive fault
  // brake fault
  */
if (chassis_detail.has_acs1_20c()){
  if (chassis_detail.acs1_20c().has_acs1_drivingfailurest()) {
    if(chassis_detail.acs1_20c().acs1_drivingfailurest() != Acs1_20c::ACS1_DRIVINGFAILUREST_NO_FAIL){ 
      chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_THROTTLE);
      return true;
    }else{
      chassis_.set_error_code(Chassis::NO_ERROR);
    }
  }else{
    chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_THROTTLE);
    return true;
  }
  if (chassis_detail.acs1_20c().has_acs1_brakingfailurest()) {
    if(chassis_detail.acs1_20c().acs1_brakingfailurest() != Acs1_20c::ACS1_BRAKINGFAILUREST_NO_FAIL){ 
      chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_BRAKE);
      return true;
    }else{
      chassis_.set_error_code(Chassis::NO_ERROR);
    }
  }else{
    chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_BRAKE);
    return true;
  }

  if (chassis_detail.acs1_20c().has_acs1_gearfailurest()) {
    if(chassis_detail.acs1_20c().acs1_gearfailurest() != Acs1_20c::ACS1_GEARFAILUREST_NO_FAIL){ 
      chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_GEAR);
      return true;
    }else{
      chassis_.set_error_code(Chassis::NO_ERROR);
    }
  }else{
    chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_GEAR);
    return true;
  }

  if (chassis_detail.acs1_20c().has_acs1_steeringfailurest()) {
    if(chassis_detail.acs1_20c().acs1_steeringfailurest() != Acs1_20c::ACS1_STEERINGFAILUREST_NO_FAIL){ 
      //std :: cout << "steer fail 1" << std :: endl;
      chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_STEER);
      return true;
    }else{
      chassis_.set_error_code(Chassis::NO_ERROR);
    }
  }else{
    //std :: cout << "steer fail 2" << std :: endl;
    chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_STEER);
    return true;
  }
}
  return false;
}
/* ADD YOUR OWN CAR CHASSIS OPERATION
  // steer fault
  // drive fault
  // brake fault
  */

void JtController::SecurityDogThreadFunc() {
  int32_t vertical_ctrl_fail = 0;
  int32_t horizontal_ctrl_fail = 0;

  if (can_sender_ == nullptr) {
    AERROR << "Failed to run SecurityDogThreadFunc() because can_sender_ is "
              "nullptr.";
    return;
  }
  while (!can_sender_->IsRunning()) {
    std::this_thread::yield();
  }

  std::chrono::duration<double, std::micro> default_period{50000};
  int64_t start = 0;
  int64_t end = 0;
  while (can_sender_->IsRunning()) {
    start = ::apollo::cyber::Time::Now().ToMicrosecond();
    const Chassis::DrivingMode mode = driving_mode();
    bool emergency_mode = false;

    // 1. horizontal control check
    if ((mode == Chassis::COMPLETE_AUTO_DRIVE ||
         mode == Chassis::AUTO_STEER_ONLY || 
         mode == Chassis::REMOTE_CLOUD_DRIVE) &&
        !CheckResponse(CHECK_RESPONSE_STEER_UNIT_FLAG, false)) {
      ++horizontal_ctrl_fail;
      if (horizontal_ctrl_fail >= kMaxFailAttempt) {
        emergency_mode = true;
        AERROR << "Driving_mode is into emergency by steer manual intervention";
        set_chassis_error_code(Chassis::MANUAL_INTERVENTION);
      }
    } else {
      horizontal_ctrl_fail = 0;
    }

    // 2. vertical control check
    if ((mode == Chassis::COMPLETE_AUTO_DRIVE ||
         mode == Chassis::AUTO_SPEED_ONLY || 
         mode == Chassis::REMOTE_CLOUD_DRIVE) &&
        !CheckResponse(CHECK_RESPONSE_SPEED_UNIT_FLAG, false)) {
      ++vertical_ctrl_fail;
      if (vertical_ctrl_fail >= kMaxFailAttempt) {
        emergency_mode = true;
        AERROR << "Driving_mode is into emergency by speed manual intervention";
        set_chassis_error_code(Chassis::MANUAL_INTERVENTION);
      }
    } else {
      vertical_ctrl_fail = 0;
    }

    // 3. chassis fault check
    if (CheckChassisError()) {
      set_chassis_error_code(Chassis::CHASSIS_ERROR);
      emergency_mode = true;
    }

    // process emergency_mode
    if (emergency_mode && mode != Chassis::EMERGENCY_MODE) {
      set_driving_mode(Chassis::EMERGENCY_MODE);
      message_manager_->ResetSendMessages();
      can_sender_->Update();
    }

    end = ::apollo::cyber::Time::Now().ToMicrosecond();
    std::chrono::duration<double, std::micro> elapsed{end - start};
    if (elapsed < default_period) {
      std::this_thread::sleep_for(default_period - elapsed);
    } else {
      AERROR << "Too much time consumption in JtController looping process:"
             << elapsed.count();
    }
  }
}

bool JtController::CheckResponse(const int32_t flags, bool need_wait) {
  int32_t retry_num = 20;
  bool is_eps_online = false;
  bool is_vcu_online = false;
  bool is_esp_online = false;
  Jt chassis_detail;

  do {
    if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
      AERROR_EVERY(100) << "Get chassis detail failed.";
      return false;
    }
    bool check_ok = true;
    if (flags & CHECK_RESPONSE_STEER_UNIT_FLAG) {
      is_eps_online = chassis_detail.has_acs1_20c() &&
                      chassis_detail.acs1_20c().has_acs1_steeringtakeoverst() &&
                      !chassis_detail.acs1_20c().acs1_steeringtakeoverst();
      check_ok = check_ok && is_eps_online;
    }

    if (flags & CHECK_RESPONSE_SPEED_UNIT_FLAG) {
      is_vcu_online = chassis_detail.has_acs1_20c() &&
                      chassis_detail.acs1_20c().has_acs1_drivingtakeoverst() &&
                      !chassis_detail.acs1_20c().acs1_drivingtakeoverst();
      is_esp_online = chassis_detail.has_acs1_20c() &&
                      chassis_detail.acs1_20c().has_acs1_brakingtakeoverst() &&
                      !chassis_detail.acs1_20c().acs1_brakingtakeoverst();
      check_ok = check_ok && is_vcu_online && is_esp_online;
    }
    if (check_ok) {
      return true;
    } else {
      AINFO << "Need to check response again.";
    }
    if (need_wait) {
      --retry_num;
      std::this_thread::sleep_for(
          std::chrono::duration<double, std::milli>(20));
    }
  } while (need_wait && retry_num);

  if (flags & CHECK_RESPONSE_STEER_UNIT_FLAG) {
    AERROR << "steer check_response fail: is_eps_online:" << is_eps_online;
  }

  if (flags & CHECK_RESPONSE_SPEED_UNIT_FLAG) {
    AERROR << "speed check_response fail: " << "is_vcu_online:" << is_vcu_online
           << ", is_esp_online:" << is_esp_online;
  }

  return false;
}

void JtController::set_chassis_error_mask(const int32_t mask) {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  chassis_error_mask_ = mask;
}

int32_t JtController::chassis_error_mask() {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  return chassis_error_mask_;
}

Chassis::ErrorCode JtController::chassis_error_code() {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  return chassis_error_code_;
}

void JtController::set_chassis_error_code(
    const Chassis::ErrorCode& error_code) {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  chassis_error_code_ = error_code;
}

}  // namespace jt
}  // namespace canbus
}  // namespace apollo
