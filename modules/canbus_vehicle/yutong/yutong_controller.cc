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

#include "modules/canbus_vehicle/yutong/yutong_controller.h"

#include <string>

#include "modules/common_msgs/basic_msgs/vehicle_signal.pb.h"

#include "cyber/common/log.h"
#include "cyber/time/time.h"
#include "modules/canbus/vehicle/vehicle_controller.h"
#include "modules/canbus_vehicle/yutong/yutong_message_manager.h"
#include "modules/canbus_vehicle/yutong/protocol/gw_16_8fe6e0b.h"
#include "modules/drivers/canbus/can_comm/can_sender.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace yutong {
using ::apollo::common::ErrorCode;
using ::apollo::common::VehicleSignal;
using ::apollo::control::ControlCommand;
using ::apollo::drivers::canbus::ProtocolData;

namespace {
const int32_t kMaxFailAttempt = 10;
const int32_t CHECK_RESPONSE_STEER_UNIT_FLAG = 1;
const int32_t CHECK_RESPONSE_SPEED_UNIT_FLAG = 2;

}  // namespace

ErrorCode YutongController::Init(
	const VehicleParameter& params,
	CanSender<::apollo::canbus::Yutong> *const can_sender,
    MessageManager<::apollo::canbus::Yutong> *const message_manager) {
  if (is_initialized_) {
    AINFO << "YutongController has already been initiated.";
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
  eps_01_cff272d_ = dynamic_cast<Eps01cff272d*>
          (message_manager_->GetMutableProtocolDataById(Eps01cff272d::ID));
  if (eps_01_cff272d_ == nullptr) {
     AERROR << "Eps01cff272d does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  vcu_01_cffd12a_ = dynamic_cast<Vcu01cffd12a*>
          (message_manager_->GetMutableProtocolDataById(Vcu01cffd12a::ID));
  if (vcu_01_cffd12a_ == nullptr) {
     AERROR << "Vcu01cffd12a does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  vcu_02_18ffda2a_ = dynamic_cast<Vcu0218ffda2a*>
          (message_manager_->GetMutableProtocolDataById(Vcu0218ffda2a::ID));
  if (vcu_02_18ffda2a_ == nullptr) {
     AERROR << "Vcu0218ffda2a does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  vcu_03_18fefa2d_ = dynamic_cast<Vcu0318fefa2d*>
          (message_manager_->GetMutableProtocolDataById(Vcu0318fefa2d::ID));
  if (vcu_03_18fefa2d_ == nullptr) {
     AERROR << "Vcu0318fefa2d does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  vcu_04_18fdcd2a_ = dynamic_cast<Vcu0418fdcd2a*>
          (message_manager_->GetMutableProtocolDataById(Vcu0418fdcd2a::ID));
  if (vcu_04_18fdcd2a_ == nullptr) {
     AERROR << "Vcu0418fdcd2a does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  vcu_05_18ff422a_ = dynamic_cast<Vcu0518ff422a*>
          (message_manager_->GetMutableProtocolDataById(Vcu0518ff422a::ID));
  if (vcu_05_18ff422a_ == nullptr) {
     AERROR << "Vcu0518ff422a does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  vcu_06_18fe412a_ = dynamic_cast<Vcu0618fe412a*>
          (message_manager_->GetMutableProtocolDataById(Vcu0618fe412a::ID));
  if (vcu_06_18fe412a_ == nullptr) {
     AERROR << "Vcu0618fe412a does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  vcu_07_df205f6_ = dynamic_cast<Vcu07df205f6*>
          (message_manager_->GetMutableProtocolDataById(Vcu07df205f6::ID));
  if (vcu_07_df205f6_ == nullptr) {
     AERROR << "Vcu07df205f6 does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  vcu_08_18ff452a_ = dynamic_cast<Vcu0818ff452a*>
          (message_manager_->GetMutableProtocolDataById(Vcu0818ff452a::ID));
  if (vcu_08_18ff452a_ == nullptr) {
     AERROR << "Vcu0818ff452a does not exist in the YutongMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  can_sender_->AddMessage(Eps01cff272d::ID, eps_01_cff272d_, false);
  can_sender_->AddMessage(Vcu01cffd12a::ID, vcu_01_cffd12a_, false);
  can_sender_->AddMessage(Vcu0218ffda2a::ID, vcu_02_18ffda2a_, false);
  can_sender_->AddMessage(Vcu0318fefa2d::ID, vcu_03_18fefa2d_, false);
  can_sender_->AddMessage(Vcu0418fdcd2a::ID, vcu_04_18fdcd2a_, false);
  can_sender_->AddMessage(Vcu0518ff422a::ID, vcu_05_18ff422a_, false);
  can_sender_->AddMessage(Vcu0618fe412a::ID, vcu_06_18fe412a_, false);
  can_sender_->AddMessage(Vcu07df205f6::ID, vcu_07_df205f6_, false);
  can_sender_->AddMessage(Vcu0818ff452a::ID, vcu_08_18ff452a_, false);

  // need sleep to ensure all messages received
  AINFO << "YutongController is initialized.";

  is_initialized_ = true;
  return ErrorCode::OK;
}

YutongController::~YutongController() {}

bool YutongController::Start() {
  if (!is_initialized_) {
    AERROR << "YutongController has NOT been initiated.";
    return false;
  }
  const auto& update_func = [this] { SecurityDogThreadFunc(); };
  thread_.reset(new std::thread(update_func));

  return true;
}

void YutongController::Stop() {
  if (!is_initialized_) {
    AERROR << "YutongController stops or starts improperly!";
    return;
  }

  if (thread_ != nullptr && thread_->joinable()) {
    thread_->join();
    thread_.reset();
    AINFO << "YutongController stopped.";
  }
}

Chassis YutongController::chassis() {
  chassis_.Clear();

  Yutong chassis_detail;
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

  /* ADD YOUR OWN CAR CHASSIS OPERATION */
  // 4 speed mps
  if (chassis_detail.has_gw_01_18ffdc24() &&
      chassis_detail.gw_01_18ffdc24().has_vehicle_speed()) {
    chassis_.set_speed_mps(
        static_cast<float>(chassis_detail.gw_01_18ffdc24().vehicle_speed() / 3.6 ));
  } else {
    chassis_.set_speed_mps(0);
  }

  // 5 gear location
  if (chassis_detail.has_gw_01_18ffdc24() &&
      chassis_detail.gw_01_18ffdc24().has_current_gear()) {
    switch (chassis_detail.gw_01_18ffdc24().current_gear()) {
      case Gw_01_18ffdc24::CURRENT_GEAR_D: {
        chassis_.set_gear_location(Chassis::GEAR_DRIVE);
      } break;
      case Gw_01_18ffdc24::CURRENT_GEAR_N: {
        chassis_.set_gear_location(Chassis::GEAR_NEUTRAL);
      } break;
      case Gw_01_18ffdc24::CURRENT_GEAR_R: {
        chassis_.set_gear_location(Chassis::GEAR_REVERSE);
      } break;
      default:
        chassis_.set_gear_location(Chassis::GEAR_INVALID);
        break;
    }
  } else {
    chassis_.set_gear_location(Chassis::GEAR_INVALID);
  }


  // 6 epb status
  if (chassis_detail.has_gw_08_18ff1424() &&
      chassis_detail.gw_08_18ff1424().has_electronic_parking_state()) {
    chassis_.set_parking_brake(
      chassis_detail.gw_08_18ff1424().electronic_parking_state() != 0);
  } else {
    chassis_.set_parking_brake(false);
  }

  // 7 throttle pct
  if (chassis_detail.has_gw_01_18ffdc24() && 
      chassis_detail.gw_01_18ffdc24().has_responds_accepedalpos()) {
    chassis_.set_throttle_percentage(chassis_detail.gw_01_18ffdc24().responds_accepedalpos());
  } else {
    chassis_.set_throttle_percentage(0);
  }

  // 8 brake  state  actual pedal by driver
  if (chassis_detail.has_gw_01_18ffdc24() && 
      chassis_detail.gw_01_18ffdc24().has_pedal_opening()) {
    chassis_.set_brake_percentage(
      chassis_detail.gw_01_18ffdc24().pedal_opening()); //revise
  } else {
    chassis_.set_brake_percentage(0);
  }

  // 9  wheel speed
  if (chassis_detail.has_gw_16_8fe6e0b()) {
    Gw_16_8fe6e0b gw_16_8fe6e0b = chassis_detail.gw_16_8fe6e0b();
    if (gw_16_8fe6e0b.has_rr_wheelspeed()) {
      chassis_.mutable_wheel_speed()->set_is_wheel_spd_rr_valid(true);
      chassis_.mutable_wheel_speed()->set_wheel_spd_rr(
          gw_16_8fe6e0b.rr_wheelspeed());
    }

    if (gw_16_8fe6e0b.has_rl_wheelspeed()) {
      chassis_.mutable_wheel_speed()->set_is_wheel_spd_rl_valid(true);
      chassis_.mutable_wheel_speed()->set_wheel_spd_rl(
          gw_16_8fe6e0b.rl_wheelspeed());
    }

    if (gw_16_8fe6e0b.has_fr_wheelspeed()) {
      chassis_.mutable_wheel_speed()->set_is_wheel_spd_fr_valid(true);
      chassis_.mutable_wheel_speed()->set_wheel_spd_fr(
          gw_16_8fe6e0b.fr_wheelspeed());
    }

    if (gw_16_8fe6e0b.has_fl_wheelspeed()) {
      chassis_.mutable_wheel_speed()->set_is_wheel_spd_fl_valid(true);
      chassis_.mutable_wheel_speed()->set_wheel_spd_fl(
          gw_16_8fe6e0b.fl_wheelspeed());
    }
  }
  /*// 10 steering pct   wheel voltage feedback   need to revise to steering wheel*/
  if (chassis_detail.has_gw_25_cff12fa() && 
      chassis_detail.gw_25_cff12fa().has_wheel_steering_angle()) {
    chassis_.set_steering_percentage(
      - (chassis_detail.gw_25_cff12fa().wheel_steering_angle() * 0.1 - 240) * 100 / (vehicle_params_.max_steer_angle() / M_PI * 180) );
  } else {
    chassis_.set_steering_percentage(0);
  } 
  

  return chassis_;
}

void YutongController::Emergency() {
  set_driving_mode(Chassis::EMERGENCY_MODE);
  ResetProtocol();
  vcu_06_18fe412a_->set_double_flash_lights(Vcu_06_18fe412a::DOUBLE_FLASH_LIGHTS_ON);
}

ErrorCode YutongController::EnableAutoMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE) {
    AINFO << "already in COMPLETE_AUTO_DRIVE mode";
    return ErrorCode::OK;
  }
  // set enable
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  vcu_02_18ffda2a_->set_adcontrolmode(Vcu_02_18ffda2a::ADCONTROLMODE_AUTO);
  vcu_01_cffd12a_->set_accactivests(Vcu_01_cffd12a::ACCACTIVESTS_ON);

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
  
  return ErrorCode::OK;
}

ErrorCode YutongController::EnableCloudMode() {
  if (driving_mode() == Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "Already in REMOTE_CLOUD_DRIVE mode";
    return ErrorCode::OK;
  }
  /*
  acu1_529_->set_acu1_steeringautocontrol(Acu1_529::ACU1_STEERINGAUTOCONTROL_REQUEST);
  acu1_529_->set_acu1_gearautocontrol(Acu1_529::ACU1_GEARAUTOCONTROL_REQUEST);
  acu2_532_->set_acu2_axialautocontrol(Acu2_532::ACU2_AXIALAUTOCONTROL_REQUEST);*/

  can_sender_->Update();
  set_driving_mode(Chassis::REMOTE_CLOUD_DRIVE);
  AINFO << "Switch to REMOTE_CLOUD_DRIVE mode ok.";
  return ErrorCode::OK;
}

ErrorCode YutongController::DisableAutoMode() {
  ResetProtocol();
  can_sender_->Update();
  set_driving_mode(Chassis::COMPLETE_MANUAL);
  set_chassis_error_code(Chassis::NO_ERROR);
  AINFO << "Switch to COMPLETE_MANUAL ok.";
  return ErrorCode::OK;
}

ErrorCode YutongController::EnableSteeringOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_STEER_ONLY) {
    set_driving_mode(Chassis::AUTO_STEER_ONLY);
    AINFO << "Already in AUTO_STEER_ONLY mode.";
    return ErrorCode::OK;
  }
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS MODE OR NOT
  // set enable
  /* ADD YOUR OWN CAR CHASSIS OPERATION

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
  */
  return ErrorCode::OK;
}

ErrorCode YutongController::EnableSpeedOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_SPEED_ONLY) {
    set_driving_mode(Chassis::AUTO_SPEED_ONLY);
    AINFO << "Already in AUTO_SPEED_ONLY mode";
    return ErrorCode::OK;
  }
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS MODE OR NOT
  // set enable
  /* ADD YOUR OWN CAR CHASSIS OPERATION

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
  */
  return ErrorCode::OK;
}

// NEUTRAL, REVERSE, DRIVE
void YutongController::Gear(Chassis::GearPosition gear_position) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    AINFO << "This drive mode no need to set gear.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
}

// brake with pedal
// pedal:0.00~99.99, unit:percentage
void YutongController::Brake(double pedal) {
  // double real_value = vehicle_params_.max_acceleration() * acceleration / 100;
  // TODO(All) :  Update brake value based on mode
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    AINFO << "The current drive mode does not need to set brake pedal.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
}

// drive with pedal
// pedal:0.0~99.9 unit:percentage
void YutongController::Throttle(double pedal) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    AINFO << "The current drive mode does not need to set throttle pedal.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
}

// confirm the car is driven by acceleration command instead of
// throttle/brake pedal drive with acceleration/deceleration acc:-7.0 ~ 5.0,
// unit:m/s^2
void YutongController::Acceleration(double acc) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    AINFO << "The current drive mode does not need to set acceleration.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
  */
}

// yutong default, +470 ~ -470 or other, left:+, right:-
// need to be compatible with control module, so reverse
// steering with steering angle
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
void YutongController::Steer(double angle) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
}

// yutong default, steering with new angle speed
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
// angle_spd:0.00~99.99, unit:deg/s
void YutongController::Steer(double angle, double angle_spd) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
}

void YutongController::SetEpbBreak(const ControlCommand& command) {
  if (command.parking_brake()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  } else {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  }
}

void YutongController::SetBeam(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.high_beam()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  } else if (vehicle_signal.low_beam()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  } else {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  }
}

void YutongController::SetHorn(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.horn()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  } else {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  }
}

void YutongController::SetTurningSignal(const VehicleSignal& vehicle_signal) {
  // Set Turn Signal
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  auto signal = vehicle_signal.turn_signal();
  if (signal == common::VehicleSignal::TURN_LEFT) {

  } else if (signal == common::VehicleSignal::TURN_RIGHT) {

  } else {

  }
  */
}

ErrorCode YutongController::HandleCustomOperation(
    const external_command::ChassisCommand& command) {
  return ErrorCode::OK;
}

bool YutongController::VerifyID() {
  if (!CheckVin()) {
    AERROR << "Failed to get the vin. Get vin again.";
    GetVin();
    return false;
  } else {
    ResetVin();
    return true;
  }
}

bool YutongController::CheckVin() {
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

void YutongController::GetVin() {
  // Get vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_ENABLE);
  AINFO << "Get vin";
  can_sender_->Update();
  */
}

void YutongController::ResetVin() {
  // Reset vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_DISABLE);
  AINFO << "Reset vin";
  can_sender_->Update();
  */
}

void YutongController::ResetProtocol() {
  message_manager_->ResetSendMessages();
}

bool YutongController::CheckChassisError() {
  Yutong chassis_detail;
  if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
    AERROR_EVERY(100) << "Get chassis detail failed.";
  }
  if (!chassis_.has_check_response()) {
    AERROR_EVERY(100) << "ChassisDetail has no yutong vehicle info.";
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "ChassisDetail has no yutong vehicle info.");
    return false;
  } else {
    chassis_.clear_engage_advice();
  }

  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // steer fault
  // drive fault
  // brake fault
  */
  return false;
}

void YutongController::SecurityDogThreadFunc() {
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
      AERROR << "Too much time consumption in YutongController looping process:"
             << elapsed.count();
    }
  }
}

bool YutongController::CheckResponse(const int32_t flags, bool need_wait) {
  int32_t retry_num = 20;
  bool is_eps_online = false;
  bool is_vcu_online = false;
  bool is_esp_online = false;

  do {
    bool check_ok = true;
    if (flags & CHECK_RESPONSE_STEER_UNIT_FLAG) {
      is_eps_online = chassis_.has_check_response() &&
                      chassis_.check_response().has_is_eps_online() &&
                      chassis_.check_response().is_eps_online();
      check_ok = check_ok && is_eps_online;
    }

    if (flags & CHECK_RESPONSE_SPEED_UNIT_FLAG) {
      is_vcu_online = chassis_.has_check_response() &&
                      chassis_.check_response().has_is_vcu_online() &&
                      chassis_.check_response().is_vcu_online();
      is_esp_online = chassis_.has_check_response() &&
                      chassis_.check_response().has_is_esp_online() &&
                      chassis_.check_response().is_esp_online();
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

void YutongController::set_chassis_error_mask(const int32_t mask) {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  chassis_error_mask_ = mask;
}

int32_t YutongController::chassis_error_mask() {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  return chassis_error_mask_;
}

Chassis::ErrorCode YutongController::chassis_error_code() {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  return chassis_error_code_;
}

void YutongController::set_chassis_error_code(
    const Chassis::ErrorCode& error_code) {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  chassis_error_code_ = error_code;
}

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
