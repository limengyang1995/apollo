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

#include "modules/canbus_vehicle/venus/venus_controller.h"

#include <string>

#include "modules/common_msgs/basic_msgs/vehicle_signal.pb.h"

#include "cyber/common/log.h"
#include "cyber/time/time.h"
#include "modules/canbus/vehicle/vehicle_controller.h"
#include "modules/canbus_vehicle/venus/venus_message_manager.h"
#include "modules/canbus_vehicle/venus/protocol/acu1_529.h"
#include "modules/canbus_vehicle/venus/protocol/acu2_532.h"
#include "modules/canbus_vehicle/venus/protocol/acu3_534.h"
#include "modules/canbus_vehicle/venus/protocol/vcu1_56f.h"
#include "modules/canbus_vehicle/venus/protocol/vcu3_2_56d.h"
#include "modules/canbus_vehicle/venus/protocol/vcu5_56a.h"
#include "modules/canbus_vehicle/venus/protocol/vcu6_56c.h"
#include "modules/canbus_vehicle/venus/protocol/vcu7_569.h"
#include "modules/drivers/canbus/can_comm/can_sender.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace venus {
using ::apollo::common::ErrorCode;
using ::apollo::common::VehicleSignal;
using ::apollo::control::ControlCommand;
using ::apollo::drivers::canbus::ProtocolData;

namespace {
const int32_t kMaxFailAttempt = 10;
const int32_t CHECK_RESPONSE_STEER_UNIT_FLAG = 1;
const int32_t CHECK_RESPONSE_SPEED_UNIT_FLAG = 2;

}  // namespace

ErrorCode VenusController::Init(
	const VehicleParameter& params,
	CanSender<::apollo::canbus::Venus> *const can_sender,
    MessageManager<::apollo::canbus::Venus> *const message_manager) {
  if (is_initialized_) {
    AINFO << "VenusController has already been initiated.";
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
  acu1_529_ = dynamic_cast<Acu1529*>(
      message_manager_->GetMutableProtocolDataById(Acu1529::ID));
  if (acu1_529_ == nullptr) {
    AERROR << "Acu1529 does not exist in the VenusMessageManager!";
    return ErrorCode::CANBUS_ERROR;
  }
  acu2_532_ = dynamic_cast<Acu2532*>(
      message_manager_->GetMutableProtocolDataById(Acu2532::ID));
  if (acu2_532_ == nullptr) {
    AERROR << "Acu2532 does not exist in the VenusMessageManager!";
    return ErrorCode::CANBUS_ERROR;
  }
  acu3_534_ = dynamic_cast<Acu3534*>(
      message_manager_->GetMutableProtocolDataById(Acu3534::ID));
  if (acu3_534_ == nullptr) {
    AERROR << "Acu3534 does not exist in the VenusMessageManager!";
    return ErrorCode::CANBUS_ERROR;
  }

  can_sender_->AddMessage(Acu1529::ID, acu1_529_, false);
  can_sender_->AddMessage(Acu2532::ID, acu2_532_, false);  
  can_sender_->AddMessage(Acu3534::ID, acu3_534_, false);


  // need sleep to ensure all messages received
  AINFO << "VenusController is initialized.";

  is_initialized_ = true;
  return ErrorCode::OK;
}

VenusController::~VenusController() {}

bool VenusController::Start() {
  if (!is_initialized_) {
    AERROR << "VenusController has NOT been initiated.";
    return false;
  }
  const auto& update_func = [this] { SecurityDogThreadFunc(); };
  thread_.reset(new std::thread(update_func));

  return true;
}

void VenusController::Stop() {
  if (!is_initialized_) {
    AERROR << "VenusController stops or starts improperly!";
    return;
  }

  if (thread_ != nullptr && thread_->joinable()) {
    thread_->join();
    thread_.reset();
    AINFO << "VenusController stopped.";
  }
}

Chassis VenusController::chassis() {
  chassis_.Clear();

  Venus chassis_detail;
  message_manager_->GetSensorData(&chassis_detail);

  // 21, 22, previously 1, 2
  if (driving_mode() == Chassis::EMERGENCY_MODE) {
    set_chassis_error_code(Chassis::NO_ERROR);
  }

  chassis_.set_driving_mode(driving_mode());
  chassis_.set_error_code(chassis_error_code());
  // 3
  chassis_.set_engine_started(true);
  if (CheckChassisError()) {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "Chassis has some fault, please check the chassis_detail.");
  }else{
    chassis_.mutable_engage_advice()->set_advice(
          apollo::common::EngageAdvice::READY_TO_ENGAGE);
  }
  // 5  wheel speed
  if (chassis_detail.has_vcu3_2_56d()) {
    Vcu3_2_56d vcu3_2_56d = chassis_detail.vcu3_2_56d();
    if (vcu3_2_56d.has_vcu3_wheelspeedrr()) {
      chassis_.mutable_wheel_speed()->set_is_wheel_spd_rr_valid(true);
      chassis_.mutable_wheel_speed()->set_wheel_spd_rr(
          vcu3_2_56d.vcu3_wheelspeedrr());
    }

    if (vcu3_2_56d.has_vcu3_wheelspeedrl()) {
      chassis_.mutable_wheel_speed()->set_is_wheel_spd_rl_valid(true);
      chassis_.mutable_wheel_speed()->set_wheel_spd_rl(
          vcu3_2_56d.vcu3_wheelspeedrl());
    }

    if (vcu3_2_56d.has_vcu3_wheelspeedfr()) {
      chassis_.mutable_wheel_speed()->set_is_wheel_spd_fr_valid(true);
      chassis_.mutable_wheel_speed()->set_wheel_spd_fr(
          vcu3_2_56d.vcu3_wheelspeedfr());
    }

    if (vcu3_2_56d.has_vcu3_wheelspeedfl()) {
      chassis_.mutable_wheel_speed()->set_is_wheel_spd_fl_valid(true);
      chassis_.mutable_wheel_speed()->set_wheel_spd_fl(
          vcu3_2_56d.vcu3_wheelspeedfl());
    }
  }
  //6 vehiclespeed  m/s
  if (chassis_detail.has_vcu1_56f() &&
      chassis_detail.vcu1_56f().has_vcu1_vehiclespeed()) {
    chassis_.set_speed_mps(
        static_cast<float>(chassis_detail.vcu1_56f().vcu1_vehiclespeed() / 3.6 ));
  } else {
    chassis_.set_speed_mps(0);
  }
  //7 battery soc && chassis throttle percentage and brake percentage
  if (chassis_detail.has_vcu6_56c()){
    if (chassis_detail.vcu6_56c().has_vcu6_batterysoc()) {
      chassis_.set_battery_soc_percentage(
          static_cast<int>(chassis_detail.vcu6_56c().vcu6_batterysoc()));
    }else {
      chassis_.set_battery_soc_percentage(0);
    }
    if (chassis_detail.vcu6_56c().has_vcu6_throttleposition()){
      chassis_.set_throttle_percentage(
          static_cast<float>(chassis_detail.vcu6_56c().vcu6_throttleposition()));
    }else {
      chassis_.set_throttle_percentage(0);
    }
    if (chassis_detail.vcu6_56c().has_vcu6_brakeposition()) {
      chassis_.set_brake_percentage(
          static_cast<float>(chassis_detail.vcu6_56c().vcu6_brakeposition()));
    }else {
      chassis_.set_brake_percentage(0);
    }
  }

  //gear location

  if (chassis_detail.has_vcu1_56f() &&
      chassis_detail.vcu1_56f().has_vcu1_gearinfo()) {
    switch (chassis_detail.vcu1_56f().vcu1_gearinfo()) {
      case Vcu1_56f::VCU1_GEARINFO_NOCONNECTION: {
        chassis_.set_gear_location(Chassis::GEAR_INVALID);
      } break;
      case Vcu1_56f::VCU1_GEARINFO_D: {
        chassis_.set_gear_location(Chassis::GEAR_DRIVE);
      } break;
      case Vcu1_56f::VCU1_GEARINFO_N: {
        chassis_.set_gear_location(Chassis::GEAR_NEUTRAL);
      } break;
      case Vcu1_56f::VCU1_GEARINFO_R: {
        chassis_.set_gear_location(Chassis::GEAR_REVERSE);
      } break;
      case Vcu1_56f::VCU1_GEARINFO_P: {
        chassis_.set_gear_location(Chassis::GEAR_PARKING);
      } break;
      default:
        chassis_.set_gear_location(Chassis::GEAR_INVALID);
        break;
    }
  } else {
    chassis_.set_gear_location(Chassis::GEAR_INVALID);
  }

  // 8 steering_percentage
  if (chassis_detail.has_vcu1_56f()){
    if (chassis_detail.vcu1_56f().has_vcu1_steeringangle_f()) {
      chassis_.set_steering_percentage(
        static_cast<float>((-1) * chassis_detail.vcu1_56f().vcu1_steeringangle_f() * 100.0 / (vehicle_params_.max_steer_angle() * 180 / M_PI)));
    } else {    
      chassis_.set_steering_percentage(0);
    }
    if (chassis_detail.vcu1_56f().has_vcu1_steeringangle_r()) {
      chassis_.set_rear_steering_percentage(
        static_cast<float>((-1) * chassis_detail.vcu1_56f().vcu1_steeringangle_r() * 100.0/ (vehicle_params_.max_steer_angle() * 180 / M_PI)));
    } else {    
      chassis_.set_rear_steering_percentage(0);
    }
  }
  //9  epb
  if (chassis_detail.has_vcu1_56f() &&
      chassis_detail.vcu1_56f().has_vcu1_parkingbrakeinfo()) {
    chassis_.set_parking_brake(chassis_detail.vcu1_56f().vcu1_parkingbrakeinfo() ==
                               Vcu1_56f::VCU1_PARKINGBRAKEINFO_LOCKED);
  } else {
    chassis_.set_parking_brake(false);
  }

  /* if (chassis_.error_code() != ErrorCode::NO_ERROR){
    if (chassis_.has_engage_advice()) {
      chassis_.mutable_engage_advice()->set_advice(
          apollo::common::EngageAdvice::DISALLOW_ENGAGE);
      chassis_.mutable_engage_advice()->set_reason("Chassis error!");
    }
  }else{
    if (chassis_.has_engage_advice()) {
      chassis_.mutable_engage_advice()->set_advice(
          apollo::common::EngageAdvice::READY_TO_ENGAGE);
    }
  } */
  return chassis_;
}

void VenusController::Emergency() {
  set_driving_mode(Chassis::EMERGENCY_MODE);
  ResetProtocol();
  acu3_534_->set_acu3_hazardlight(Acu3_534::ACU3_HAZARDLIGHT_ON);
}

ErrorCode VenusController::EnableAutoMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE) {
    AINFO << "already in COMPLETE_AUTO_DRIVE mode";
    return ErrorCode::OK;
  }
  acu1_529_->set_acu1_steeringautocontrol(Acu1_529::ACU1_STEERINGAUTOCONTROL_REQUEST);
  acu1_529_->set_acu1_gearautocontrol(Acu1_529::ACU1_GEARAUTOCONTROL_REQUEST);
  acu2_532_->set_acu2_axialautocontrol(Acu2_532::ACU2_AXIALAUTOCONTROL_REQUEST);

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
  return ErrorCode::OK;
}

ErrorCode VenusController::EnableCloudMode() {
  if (driving_mode() == Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "Already in REMOTE_CLOUD_DRIVE mode";
    return ErrorCode::OK;
  }

  acu1_529_->set_acu1_steeringautocontrol(Acu1_529::ACU1_STEERINGAUTOCONTROL_REQUEST);
  acu1_529_->set_acu1_gearautocontrol(Acu1_529::ACU1_GEARAUTOCONTROL_REQUEST);
  acu2_532_->set_acu2_axialautocontrol(Acu2_532::ACU2_AXIALAUTOCONTROL_REQUEST);

  can_sender_->Update();
  set_driving_mode(Chassis::REMOTE_CLOUD_DRIVE);
  AINFO << "Switch to REMOTE_CLOUD_DRIVE mode ok.";
  return ErrorCode::OK;
}

ErrorCode VenusController::DisableAutoMode() {
  ResetProtocol();
  can_sender_->Update();
  set_driving_mode(Chassis::COMPLETE_MANUAL);
  set_chassis_error_code(Chassis::NO_ERROR);
  AINFO << "Switch to COMPLETE_MANUAL ok.";
  return ErrorCode::OK;
}

ErrorCode VenusController::EnableSteeringOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_STEER_ONLY) {
    set_driving_mode(Chassis::AUTO_STEER_ONLY);
    AINFO << "Already in AUTO_STEER_ONLY mode.";
    return ErrorCode::OK;
  }
  acu1_529_->set_acu1_steeringautocontrol(Acu1_529::ACU1_STEERINGAUTOCONTROL_REQUEST);
  acu1_529_->set_acu1_gearautocontrol(Acu1_529::ACU1_GEARAUTOCONTROL_NOREQUEST);
  acu2_532_->set_acu2_axialautocontrol(Acu2_532::ACU2_AXIALAUTOCONTROL_NOREQUET);
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

ErrorCode VenusController::EnableSpeedOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_SPEED_ONLY) {
    set_driving_mode(Chassis::AUTO_SPEED_ONLY);
    AINFO << "Already in AUTO_SPEED_ONLY mode";
    return ErrorCode::OK;
  }
  acu1_529_->set_acu1_steeringautocontrol(Acu1_529::ACU1_STEERINGAUTOCONTROL_NOREQUET);
  acu1_529_->set_acu1_gearautocontrol(Acu1_529::ACU1_GEARAUTOCONTROL_REQUEST);
  acu2_532_->set_acu2_axialautocontrol(Acu2_532::ACU2_AXIALAUTOCONTROL_REQUEST);

  can_sender_->Update();
  if (!CheckResponse(CHECK_RESPONSE_SPEED_UNIT_FLAG, true)) {
    AERROR << "Failed to switch to AUTO_SPEED_ONLY mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  }
  set_driving_mode(Chassis::AUTO_SPEED_ONLY);
  AINFO << "Switch to AUTO_SPEED_ONLY mode ok.";
  return ErrorCode::OK;
  
}

// NEUTRAL, REVERSE, DRIVE
void VenusController::Gear(Chassis::GearPosition gear_position) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "This drive mode no need to set gear.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  acu1_529_->set_acu1_gearautocontrol(Acu1_529::ACU1_GEARAUTOCONTROL_REQUEST);

  Venus chassis_detail;
  message_manager_->GetSensorData(&chassis_detail);
  // Need to request neutral gear first if current gear location is not neutral
  // or none
  /* if (gear_position != current_gear_position &&
      current_gear_position != Chassis::GEAR_NEUTRAL &&
      current_gear_position != Chassis::GEAR_NONE) {
    gear_tmp_ = Chassis::GEAR_NEUTRAL;
  } else if (current_gear_position == Chassis::GEAR_NEUTRAL) {
    gear_tmp_ = gear_position;
  } */
  
  if (chassis_detail.has_vcu5_56a() &&
      chassis_detail.vcu5_56a().has_vcu5_gearautocontrolst() &&
      chassis_detail.vcu5_56a().vcu5_gearautocontrolst() == Vcu5_56a::VCU5_GEARAUTOCONTROLST_ACTIVE){
    switch (gear_position) {
      case Chassis::GEAR_NEUTRAL: {
        acu1_529_->set_acu1_targetgear(Acu1_529::ACU1_TARGETGEAR_N);
        break;
      }
      case Chassis::GEAR_REVERSE: {
        acu1_529_->set_acu1_targetgear(Acu1_529::ACU1_TARGETGEAR_R);
        break;
      }
      case Chassis::GEAR_DRIVE: {
        acu1_529_->set_acu1_targetgear(Acu1_529::ACU1_TARGETGEAR_D);
        break;
      }
      case Chassis::GEAR_PARKING: {
        acu1_529_->set_acu1_targetgear(Acu1_529::ACU1_TARGETGEAR_P);
        break;
      }
      case Chassis::GEAR_NONE: {
        acu1_529_->set_acu1_targetgear(Acu1_529::ACU1_TARGETGEAR_NOREQUEST);
        break;
      }
      case Chassis::GEAR_INVALID: {
        AERROR << "Gear command is invalid!";
        acu1_529_->set_acu1_targetgear(Acu1_529::ACU1_TARGETGEAR_NOREQUEST);
        break;
      }
      default: {
        acu1_529_->set_acu1_targetgear(Acu1_529::ACU1_TARGETGEAR_NOREQUEST);
        break;
      }
    }
  }else{
    AERROR << "Gear status is not activated";
  }
  
}

// brake with pedal
// pedal:0.00~99.99, unit:percentage
void VenusController::Brake(double pedal) {
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
  acu2_532_->set_acu2_axialautocontrol(Acu2_532::ACU2_AXIALAUTOCONTROL_NOREQUET);
  acu2_532_->set_acu2_brakingcontrolmode(Acu2_532::ACU2_BRAKINGCONTROLMODE_POSITION);
  acu2_532_->set_acu2_targetbrakingposition(std::abs(int(pedal)));

}

// drive with pedal
// pedal:0.0~99.9 unit:percentage
void VenusController::Throttle(double pedal) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current drive mode does not need to set throttle pedal.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  acu2_532_->set_acu2_axialautocontrol(Acu2_532::ACU2_AXIALAUTOCONTROL_REQUEST);
  acu2_532_->set_acu2_acceleratorcontrolmode(Acu2_532::ACU2_ACCELERATORCONTROLMODE_POSITION);
  acu2_532_->set_acu2_targetacceleratorposition(std::abs(int(pedal)));
}

// confirm the car is driven by acceleration command instead of
// throttle/brake pedal drive with acceleration/deceleration acc:-7.0 ~ 5.0,
// unit:m/s^2
void VenusController::Acceleration(double acc) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current drive mode does not need to set acceleration.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
  */
  acu2_532_->set_acu2_axialautocontrol(Acu2_532::ACU2_AXIALAUTOCONTROL_REQUEST);
  acu2_532_->set_acu2_acceleratorcontrolmode(Acu2_532::ACU2_ACCELERATORCONTROLMODE_ACCEL);
  acu2_532_->set_acu2_brakingcontrolmode(Acu2_532::ACU2_BRAKINGCONTROLMODE_DECELACC);
  acu2_532_->set_acu2_targetaxialacceldecel(acc);
}

// venus default, +470 ~ -470 or other, left:+, right:-
// need to be compatible with control module, so reverse
// steering with steering angle
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
void VenusController::Steer(double angle) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  acu1_529_->set_acu1_steeringautocontrol(Acu1_529::ACU1_STEERINGAUTOCONTROL_REQUEST);
  acu1_529_->set_acu1_targetsteeringangle_f(double((-1) * vehicle_params_.max_steer_angle() /M_PI * 180.0 * angle / 100.0));
  acu1_529_->set_acu1_targetsteeringspeed(400);
}

// venus default, steering with new angle speed
// angle:99.99~0.00~-99.99, unit:deg, left:-, right:+
// angle_spd:0.00~500, unit:deg/s
void VenusController::Steer(double angle, double angle_spd) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  acu1_529_->set_acu1_steeringautocontrol(Acu1_529::ACU1_STEERINGAUTOCONTROL_REQUEST);
  acu1_529_->set_acu1_targetsteeringangle_f(double((-1) * vehicle_params_.max_steer_angle() /M_PI * 180.0 * angle / 100.0));
  acu1_529_->set_acu1_targetsteeringspeed(int(vehicle_params_.max_steer_angle_rate() /M_PI * 180 * angle_spd / 100));
}

void VenusController::SetEpbBreak(const ControlCommand& command) {
  if (command.parking_brake()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
    acu1_529_->set_acu1_targetepb(Acu1_529::ACU1_TARGETEPB_LOCK);
  } else {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
    acu1_529_->set_acu1_targetepb(Acu1_529::ACU1_TARGETEPB_RELEASE);
  }
}

void VenusController::SetBeam(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.high_beam()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
    acu3_534_->set_acu3_beamlight(Acu3_534::ACU3_BEAMLIGHT_HIGH);
  } else if (vehicle_signal.low_beam()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
    acu3_534_->set_acu3_beamlight(Acu3_534::ACU3_BEAMLIGHT_LOW);
  } else {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
    acu3_534_->set_acu3_beamlight(Acu3_534::ACU3_BEAMLIGHT_NOREQUEST);
  }
}

void VenusController::SetHorn(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.horn()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  } else {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  }
}

void VenusController::SetTurningSignal(const VehicleSignal& vehicle_signal) {
  // Set Turn Signal
  auto signal = vehicle_signal.turn_signal();
  if (signal == common::VehicleSignal::TURN_LEFT) {
    acu3_534_->set_acu3_steeringlight(Acu3_534::ACU3_STEERINGLIGHT_LEFT);
  } else if (signal == common::VehicleSignal::TURN_RIGHT) {
    acu3_534_->set_acu3_steeringlight(Acu3_534::ACU3_STEERINGLIGHT_RIGHT);
  } else {
    acu3_534_->set_acu3_steeringlight(Acu3_534::ACU3_STEERINGLIGHT_NOREQUEST);
  }
 
}

ErrorCode VenusController::HandleCustomOperation(
    const external_command::ChassisCommand& command) {
  return ErrorCode::OK;
}

bool VenusController::VerifyID() {
  if (!CheckVin()) {
    AERROR << "Failed to get the vin. Get vin again.";
    GetVin();
    return false;
  } else {
    ResetVin();
    return true;
  }
}

bool VenusController::CheckVin() {
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

void VenusController::GetVin() {
  // Get vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_ENABLE);
  AINFO << "Get vin";
  can_sender_->Update();
  */
}

void VenusController::ResetVin() {
  // Reset vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_DISABLE);
  AINFO << "Reset vin";
  can_sender_->Update();
  */
}

void VenusController::ResetProtocol() {
  message_manager_->ResetSendMessages();
}

bool VenusController::CheckChassisError() {
  Venus chassis_detail;
  if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
    AERROR_EVERY(100) << "Get chassis detail failed.";
  }

  if (chassis_detail.has_vcu5_56a()){
    if (chassis_detail.vcu5_56a().has_vcu5_drivingfailurest()) {
      if(chassis_detail.vcu5_56a().vcu5_drivingfailurest() != Vcu5_56a::VCU5_DRIVINGFAILUREST_NOTFAIL){ 
        chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_THROTTLE);
        return true;
      }else{
        chassis_.set_error_code(Chassis::NO_ERROR);
      }
    }else{
      chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_THROTTLE);
      return true;
    }

    if (chassis_detail.vcu5_56a().has_vcu5_brakingfailurest()) {
      if(chassis_detail.vcu5_56a().vcu5_brakingfailurest() != Vcu5_56a::VCU5_BRAKINGFAILUREST_NOTFAIL){ 
        chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_BRAKE);
        return true;
      }else{
        chassis_.set_error_code(Chassis::NO_ERROR);
      }
    }else{
      chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_BRAKE);
      return true;
    }

    if (chassis_detail.vcu5_56a().has_vcu5_frontsteeringfailurest() && 
        chassis_detail.vcu5_56a().has_vcu5_rearsteeringfailurest()) {
      if(chassis_detail.vcu5_56a().vcu5_frontsteeringfailurest() != Vcu5_56a::VCU5_FRONTSTEERINGFAILUREST_NOTFAIL &&
         chassis_detail.vcu5_56a().vcu5_rearsteeringfailurest() != Vcu5_56a::VCU5_REARSTEERINGFAILUREST_NOTFAIL){ 
        chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_STEER);
        return true;
      }else{
        chassis_.set_error_code(Chassis::NO_ERROR);
      }
    }else{
      chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_STEER);
      return true;
    }
  }
  return false;
}

void VenusController::SecurityDogThreadFunc() {
  int32_t vertical_ctrl_fail = 0;
  int32_t horizontal_ctrl_fail = 0;

  if (can_sender_ == nullptr) {
    AERROR << "Failed to run SecurityDogThreadFunc() because can_sender_ is nullptr.";
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
      AERROR << "Too much time consumption in VenusController looping process:"
             << elapsed.count();
    }
  }
}

bool VenusController::CheckResponse(const int32_t flags, bool need_wait) {
  int32_t retry_num = 20;
  bool is_eps_online = false;
  bool is_vcu_online = false;
  bool is_esp_online = false;
  Venus chassis_detail;
  
  
  do {
    if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
      AERROR_EVERY(100) << "Get chassis detail failed.";
      return false;
    }
    bool check_ok = true;
    if (flags & CHECK_RESPONSE_STEER_UNIT_FLAG) {
      is_eps_online = chassis_detail.has_vcu5_56a() &&
                      chassis_detail.vcu5_56a().has_vcu5_frontsteeringtakeoverst() &&
                      !chassis_detail.vcu5_56a().vcu5_frontsteeringtakeoverst();
      check_ok = check_ok && is_eps_online;
    }

    if (flags & CHECK_RESPONSE_SPEED_UNIT_FLAG) {
      is_vcu_online = chassis_detail.has_vcu5_56a() &&
                      chassis_detail.vcu5_56a().has_vcu5_drivingtakeoverst() &&
                      !chassis_detail.vcu5_56a().vcu5_drivingtakeoverst();
      is_esp_online = chassis_detail.has_vcu5_56a() &&
                      chassis_detail.vcu5_56a().has_vcu5_brakingtakeoverst() &&
                      !chassis_detail.vcu5_56a().vcu5_brakingtakeoverst();
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

  AERROR << "check_response fail: is_eps_online:" << is_eps_online
         << ", is_vcu_online:" << is_vcu_online
         << ", is_esp_online:" << is_esp_online;

  return false;
}

void VenusController::set_chassis_error_mask(const int32_t mask) {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  chassis_error_mask_ = mask;
}

int32_t VenusController::chassis_error_mask() {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  return chassis_error_mask_;
}

Chassis::ErrorCode VenusController::chassis_error_code() {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  return chassis_error_code_;
}

void VenusController::set_chassis_error_code(
    const Chassis::ErrorCode& error_code) {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  chassis_error_code_ = error_code;
}

}  // namespace venus
}  // namespace canbus
}  // namespace apollo
