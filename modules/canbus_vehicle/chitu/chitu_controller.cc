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

#include "modules/canbus_vehicle/chitu/chitu_controller.h"

#include <string>

#include "modules/common_msgs/basic_msgs/vehicle_signal.pb.h"

#include "cyber/common/log.h"
#include "cyber/time/time.h"
#include "modules/canbus/vehicle/vehicle_controller.h"
#include "modules/canbus_vehicle/chitu/chitu_message_manager.h"
#include "modules/drivers/canbus/can_comm/can_sender.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace chitu {
using ::apollo::common::ErrorCode;
using ::apollo::common::VehicleSignal;
using ::apollo::control::ControlCommand;
using ::apollo::drivers::canbus::ProtocolData;

namespace {
const int32_t kMaxFailAttempt = 10;
const int32_t CHECK_RESPONSE_STEER_UNIT_FLAG = 1;
const int32_t CHECK_RESPONSE_SPEED_UNIT_FLAG = 2;

}  // namespace

void ChituController::AddSendMessage() {
  can_sender_->AddMessage(Adasanglecmd112::ID, adas_angle_cmd_112_, false);
  can_sender_->AddMessage(Adasemergencyspot2a0::ID, adas_emergency_spot_2a0_, false);
  can_sender_->AddMessage(Adasspeedcmd113::ID, adas_speed_cmd_113_, false);
}

ErrorCode ChituController::Init(
	const VehicleParameter& params,
	CanSender<::apollo::canbus::Chitu> *const can_sender,
  MessageManager<::apollo::canbus::Chitu> *const message_manager) {
  if (is_initialized_) {
    ADEBUG << "ChituController has already been initiated.";
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
  adas_angle_cmd_112_ = dynamic_cast<Adasanglecmd112*>
          (message_manager_->GetMutableProtocolDataById(Adasanglecmd112::ID));
  if (adas_angle_cmd_112_ == nullptr) {
     AERROR << "Adasanglecmd112 does not exist in the ChituMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  adas_emergency_spot_2a0_ = dynamic_cast<Adasemergencyspot2a0*>
          (message_manager_->GetMutableProtocolDataById(Adasemergencyspot2a0::ID));
  if (adas_emergency_spot_2a0_ == nullptr) {
     AERROR << "Adasemergencyspot2a0 does not exist in the ChituMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  adas_speed_cmd_113_ = dynamic_cast<Adasspeedcmd113*>
          (message_manager_->GetMutableProtocolDataById(Adasspeedcmd113::ID));
  if (adas_speed_cmd_113_ == nullptr) {
     AERROR << "Adasspeedcmd113 does not exist in the ChituMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  AddSendMessage();

  ADEBUG << "ChituController is initialized.";

  is_initialized_ = true;
  return ErrorCode::OK;
}

ChituController::~ChituController() {}

bool ChituController::Start() {
  if (!is_initialized_) {
    AERROR << "ChituController has NOT been initiated.";
    return false;
  }
  const auto& update_func = [this] { SecurityDogThreadFunc(); };
  thread_.reset(new std::thread(update_func));

  return true;
}

void ChituController::Stop() {
  if (!is_initialized_) {
    AERROR << "ChituController stops or starts improperly!";
    return;
  }

  if (thread_ != nullptr && thread_->joinable()) {
    thread_->join();
    thread_.reset();
    ADEBUG << "ChituController stopped.";
  }
}

Chassis ChituController::chassis() {
  chassis_.Clear();
  Chitu chassis_detail = GetNewRecvChassisDetail();;

  // 1, 2
  // if (driving_mode() == Chassis::EMERGENCY_MODE) {
  //   set_chassis_error_code(Chassis::NO_ERROR);
  // }

  chassis_.set_driving_mode(driving_mode());
  chassis_.set_error_code(chassis_error_code());

  // 3
  chassis_.set_engine_started(true);

  

  // check chassis error
  if (CheckChassisError()) {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "Chassis has some fault, please check the chassis_detail.");
  }

  // check the chassis detail lost
  if (is_chassis_communication_error_) {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "chitu chassis detail is lost! Please check the communication error.");
    set_chassis_error_code(Chassis::CHASSIS_CAN_LOST);
    set_driving_mode(Chassis::EMERGENCY_MODE);
  }
  // 4 speed
  if (chassis_detail.has_vcu_speed_message_110() &&
      chassis_detail.vcu_speed_message_110().has_actual_speed()) {
    chassis_.set_speed_mps(
        static_cast<float>(chassis_detail.vcu_speed_message_110().actual_speed()));
  } else {
    chassis_.set_speed_mps(0);
  }

  //5 driving_mode
  if (chassis_detail.has_vcu_sw_state_130() &&
      chassis_detail.vcu_sw_state_130().has_vcu_mode()) {
    if(chassis_detail.vcu_sw_state_130().vcu_mode() == Vcu_sw_state_130 :: VCU_MODE_AUTOMODE){
      chassis_.set_driving_mode(Chassis::COMPLETE_AUTO_DRIVE);
    }
    else{
      chassis_.set_driving_mode(Chassis::COMPLETE_MANUAL);
    }
  }else{
      chassis_.set_driving_mode(Chassis::COMPLETE_MANUAL);
  }

  //6 soc
  if (chassis_detail.has_vcu_adas_soc_4a0()){
    if (chassis_detail.vcu_adas_soc_4a0().has_soc()) {
      chassis_.set_battery_soc_percentage(
          static_cast<int>(chassis_detail.vcu_adas_soc_4a0().soc()));
    }else {
      chassis_.set_battery_soc_percentage(0);
    }
  }else {
      chassis_.set_battery_soc_percentage(0);
  }

  //7 steer
  if (chassis_detail.has_vcu_diversion_angle_100()){
    if (chassis_detail.vcu_diversion_angle_100().has_actual_steering_radian()) {
      chassis_.set_steering_percentage(
        static_cast<float>(chassis_detail.vcu_diversion_angle_100().actual_steering_radian() 
        * vehicle_params_.steer_ratio() * 100.0 / (vehicle_params_.max_steer_angle() * 180 / M_PI)));
    } else {    
      chassis_.set_steering_percentage(0);
    }
  }else {    
      chassis_.set_steering_percentage(0);
  }

  return chassis_;
}

void ChituController::Emergency() {
  set_driving_mode(Chassis::EMERGENCY_MODE);
  ResetProtocol();
}

ErrorCode ChituController::EnableAutoMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE) {
    ADEBUG << "already in COMPLETE_AUTO_DRIVE mode";
    return ErrorCode::OK;
  }
  // set enable
  

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
  ADEBUG << "Switch to COMPLETE_AUTO_DRIVE mode ok.";
  return ErrorCode::OK;
}

ErrorCode ChituController::EnableCloudMode() {
  if (driving_mode() == Chassis::REMOTE_CLOUD_DRIVE) {
    ADEBUG << "Already in REMOTE_CLOUD_DRIVE mode";
    return ErrorCode::OK;
  }

  can_sender_->Update();
  set_driving_mode(Chassis::REMOTE_CLOUD_DRIVE);
  ADEBUG << "Switch to REMOTE_CLOUD_DRIVE mode ok.";
  return ErrorCode::OK;
}

ErrorCode ChituController::DisableAutoMode() {
  ResetProtocol();
  can_sender_->Update();
  set_driving_mode(Chassis::COMPLETE_MANUAL);
  set_chassis_error_code(Chassis::NO_ERROR);
  ADEBUG << "Switch to COMPLETE_MANUAL ok.";
  return ErrorCode::OK;
}

ErrorCode ChituController::EnableSteeringOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_STEER_ONLY) {
    set_driving_mode(Chassis::AUTO_STEER_ONLY);
    ADEBUG << "Already in AUTO_STEER_ONLY mode.";
    return ErrorCode::OK;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS MODE OR NOT
  // set enable
  

  can_sender_->Update();
  if (!CheckResponse(CHECK_RESPONSE_STEER_UNIT_FLAG, true)) {
    AERROR << "Failed to switch to AUTO_STEER_ONLY mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  }
  set_driving_mode(Chassis::AUTO_STEER_ONLY);
  ADEBUG << "Switch to AUTO_STEER_ONLY mode ok.";
  return ErrorCode::OK;
  */
  return ErrorCode::OK;
}

ErrorCode ChituController::EnableSpeedOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_SPEED_ONLY) {
    set_driving_mode(Chassis::AUTO_SPEED_ONLY);
    ADEBUG << "Already in AUTO_SPEED_ONLY mode";
    return ErrorCode::OK;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS MODE OR NOT
  // set enable
  

  can_sender_->Update();
  if (!CheckResponse(CHECK_RESPONSE_SPEED_UNIT_FLAG, true)) {
    AERROR << "Failed to switch to AUTO_SPEED_ONLY mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  }
  set_driving_mode(Chassis::AUTO_SPEED_ONLY);
  ADEBUG << "Switch to AUTO_SPEED_ONLY mode ok.";
  return ErrorCode::OK;
  */
  return ErrorCode::OK;
}

// NEUTRAL, REVERSE, DRIVE
void ChituController::Gear(Chassis::GearPosition gear_position) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    ADEBUG << "This drive mode no need to set gear.";
    return;
  }
  
}

// brake with pedal
// pedal:0.00~99.99, unit:percentage
void ChituController::Brake(double pedal) {
  // double real_value = vehicle_params_.max_acceleration() * acceleration / 100;
  // TODO(All) :  Update brake value based on mode
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    ADEBUG << "The current drive mode does not need to set brake pedal.";
    return;
  }
  
}

// drive with pedal
// pedal:0.0~99.9 unit:percentage
void ChituController::Throttle(double pedal) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    ADEBUG << "The current drive mode does not need to set throttle pedal.";
    return;
  }
  
}

// confirm the car is driven by acceleration command instead of
// throttle/brake pedal drive with acceleration/deceleration acc:-7.0 ~ 5.0,
// unit:m/s^2
void ChituController::Acceleration(double acc) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    ADEBUG << "The current drive mode does not need to set acceleration.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
  */
  adas_speed_cmd_113_->set_accelerated_speed(acc);
}

// confirm the car is driven by speed command
// speed:-xx.0~xx.0, unit:m/s
void ChituController::Speed(double speed) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    ADEBUG << "The current drive mode does not need to set speed.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
  */
  adas_speed_cmd_113_->set_vehicle_speed(speed);
  
}

// chitu default, +470 ~ -470 or other, left:+, right:-
// need to be compatible with control module, so reverse
// steering with steering angle
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
void ChituController::Steer(double angle) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY) {
    ADEBUG << "The current driving mode does not need to set steer.";
    return;
  }
  adas_angle_cmd_112_->set_steering_angle(vehicle_params_.max_steer_angle() / M_PI * 
    180.0 * angle / 100.0 / vehicle_params_.steer_ratio());
  adas_angle_cmd_112_->set_ac_steering_speed(14.4);
}

// chitu default, steering with new angle and angle speed
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
// angle_spd:0.00~99.99, unit:deg/s
void ChituController::Steer(double angle, double angle_spd) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY) {
    ADEBUG << "The current driving mode does not need to set steer.";
    return;
  }
  adas_angle_cmd_112_->set_steering_angle(vehicle_params_.max_steer_angle() / M_PI * 
    180.0 * angle / 100.0 / vehicle_params_.steer_ratio());
  adas_angle_cmd_112_->set_ac_steering_speed(14.4);
  
}

void ChituController::SetEpbBreak(const ControlCommand& command) {
  if (command.parking_brake()) {
    // None
  } else {
    // None
  }
}

void ChituController::SetBeam(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.high_beam()) {
    // None
  } else if (vehicle_signal.low_beam()) {
    // None
  } else {
    // None
  }
}

void ChituController::SetHorn(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.horn()) {
    // None
  } else {
    // None
  }
}

void ChituController::SetTurningSignal(const VehicleSignal& vehicle_signal) {
  // Set Turn Signal
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  auto signal = vehicle_signal.turn_signal();
  if (signal == common::VehicleSignal::TURN_LEFT) {

  } else if (signal == common::VehicleSignal::TURN_RIGHT) {

  } else {

  }
  */
}

ErrorCode ChituController::HandleCustomOperation(
    const external_command::ChassisCommand& command) {
  return ErrorCode::OK;
}

bool ChituController::VerifyID() {
  if (!CheckVin()) {
    AERROR << "Failed to get the vin. Get vin again.";
    GetVin();
    return false;
  } else {
    ResetVin();
    return true;
  }
}

bool ChituController::CheckVin() {
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  if (chassis_.vehicle_id().vin().size() >= 7) {
    ADEBUG << "Vin check success! Vehicel vin is "
          << chassis_.vehicle_id().vin();
    return true;
  } else {
    ADEBUG << "Vin check failed! Current vin size is "
          << chassis_.vehicle_id().vin().size();
    return false;
  }
  */
  return false;
}

void ChituController::GetVin() {
  // Get vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_ENABLE);
  ADEBUG << "Get vin";
  can_sender_->Update();
  */
}

void ChituController::ResetVin() {
  // Reset vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_DISABLE);
  ADEBUG << "Reset vin";
  can_sender_->Update();
  */
}

void ChituController::ResetProtocol() {
  message_manager_->ResetSendMessages();
}

bool ChituController::CheckChassisError() {
  if (is_chassis_communication_error_) {
    AERROR_EVERY(100) << "ChassisDetail has no chitu vehicle info.";
    return false;
  }

  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // steer fault
  // drive fault
  // brake fault
  */
  return false;
}

void ChituController::SecurityDogThreadFunc() {
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
         mode == Chassis::AUTO_STEER_ONLY) &&
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
         mode == Chassis::AUTO_SPEED_ONLY) &&
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
    // recove error code
    if (!emergency_mode && !is_chassis_communication_error_ &&
        mode == Chassis::EMERGENCY_MODE) {
      set_chassis_error_code(Chassis::NO_ERROR);
    }

    end = ::apollo::cyber::Time::Now().ToMicrosecond();
    std::chrono::duration<double, std::micro> elapsed{end - start};
    if (elapsed < default_period) {
      std::this_thread::sleep_for(default_period - elapsed);
    } else {
      AERROR << "Too much time consumption in ChituController looping process:"
             << elapsed.count();
    }
  }
}

bool ChituController::CheckResponse(const int32_t flags, bool need_wait) {
  int32_t retry_num = 20;
  bool is_eps_online = false;
  bool is_vcu_online = false;
  bool is_esp_online = false;
  Chitu chassis_detail;

  do {
    if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
      AERROR_EVERY(100) << "Get chassis detail failed.";
      return false;
    }
    bool check_ok = true;
    
    if (flags & CHECK_RESPONSE_SPEED_UNIT_FLAG) {
      is_vcu_online = chassis_detail.has_vcu_braking_state_200() &&
                      chassis_detail.vcu_braking_state_200().has_brake_state() &&
                      !chassis_detail.vcu_braking_state_200().brake_state();
      
      check_ok = check_ok && is_vcu_online;
    }
    if (check_ok) {
      return true;
    } else {
      ADEBUG << "Need to check response again.";
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
    AERROR << "speed check_response fail: " << "is_vcu_online:" << is_vcu_online;
  }

  return false;
}

void ChituController::set_chassis_error_mask(const int32_t mask) {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  chassis_error_mask_ = mask;
}

int32_t ChituController::chassis_error_mask() {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  return chassis_error_mask_;
}

Chassis::ErrorCode ChituController::chassis_error_code() {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  return chassis_error_code_;
}

void ChituController::set_chassis_error_code(
    const Chassis::ErrorCode& error_code) {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  chassis_error_code_ = error_code;
}

}  // namespace chitu
}  // namespace canbus
}  // namespace apollo
