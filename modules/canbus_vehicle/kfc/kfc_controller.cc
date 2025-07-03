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

#include "modules/canbus_vehicle/kfc/kfc_controller.h"

#include <string>

#include "modules/common_msgs/basic_msgs/vehicle_signal.pb.h"

#include "cyber/common/log.h"
#include "cyber/time/time.h"
#include "modules/canbus/vehicle/vehicle_controller.h"
#include "modules/canbus_vehicle/kfc/kfc_message_manager.h"
#include "modules/drivers/canbus/can_comm/can_sender.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace kfc {
using ::apollo::common::ErrorCode;
using ::apollo::common::VehicleSignal;
using ::apollo::control::ControlCommand;
using ::apollo::drivers::canbus::ProtocolData;

namespace {
const int32_t kMaxFailAttempt = 10;
const int32_t CHECK_RESPONSE_STEER_UNIT_FLAG = 1;
const int32_t CHECK_RESPONSE_SPEED_UNIT_FLAG = 2;

}  // namespace

ErrorCode KfcController::Init(
	const VehicleParameter& params,
	CanSender<::apollo::canbus::Kfc> *const can_sender,
    MessageManager<::apollo::canbus::Kfc> *const message_manager) {
  if (is_initialized_) {
    AINFO << "KfcController has already been initiated.";
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
  acu1_310_ = dynamic_cast<Acu1310*>
          (message_manager_->GetMutableProtocolDataById(Acu1310::ID));
  if (acu1_310_ == nullptr) {
     AERROR << "Acu1310 does not exist in the KfcMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  can_sender_->AddMessage(Acu1310::ID, acu1_310_, false);

  // need sleep to ensure all messages received
  AINFO << "KfcController is initialized.";

  is_initialized_ = true;
  return ErrorCode::OK;
}

KfcController::~KfcController() {}

bool KfcController::Start() {
  if (!is_initialized_) {
    AERROR << "KfcController has NOT been initiated.";
    return false;
  }
  const auto& update_func = [this] { SecurityDogThreadFunc(); };
  thread_.reset(new std::thread(update_func));

  return true;
}

void KfcController::Stop() {
  if (!is_initialized_) {
    AERROR << "KfcController stops or starts improperly!";
    return;
  }

  if (thread_ != nullptr && thread_->joinable()) {
    thread_->join();
    thread_.reset();
    AINFO << "KfcController stopped.";
  }
}

Chassis KfcController::chassis() {
  chassis_.Clear();

  Kfc chassis_detail;
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

  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // 10 battery soc
  // 11 vin
  // 12 bumper event
  */

  //6 vehiclespeed  m/s
  if (chassis_detail.has_vcu1_320() &&
      chassis_detail.vcu1_320().has_vcu1_vehiclespeed()) {
    chassis_.set_speed_mps(
        static_cast<float>(chassis_detail.vcu1_320().vcu1_vehiclespeed() / 3.6 ));
  } else {
    chassis_.set_speed_mps(0);
  }
  //gear location

  if (chassis_detail.has_vcu1_320() &&
      chassis_detail.vcu1_320().has_vcu1_gearinfo()) {
    switch (chassis_detail.vcu1_320().vcu1_gearinfo()) {
      case Vcu1_320::VCU1_GEARINFO_D: {
        chassis_.set_gear_location(Chassis::GEAR_DRIVE);
      } break;
      case Vcu1_320::VCU1_GEARINFO_N: {
        chassis_.set_gear_location(Chassis::GEAR_NEUTRAL);
      } break;
      case Vcu1_320::VCU1_GEARINFO_R: {
        chassis_.set_gear_location(Chassis::GEAR_REVERSE);
      } break;
      case Vcu1_320::VCU1_GEARINFO_P: {
        chassis_.set_gear_location(Chassis::GEAR_PARKING);
      } break;
      default:
        chassis_.set_gear_location(Chassis::GEAR_INVALID);
        break;
    }
  } else {
    chassis_.set_gear_location(Chassis::GEAR_INVALID);
  }

  



  return chassis_;
}

void KfcController::Emergency() {
  set_driving_mode(Chassis::EMERGENCY_MODE);
  ResetProtocol();
}

ErrorCode KfcController::EnableAutoMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE) {
    AINFO << "already in COMPLETE_AUTO_DRIVE mode";
    return ErrorCode::OK;
  }
  acu1_310_->set_acu1_drivingcontrolrequest(Acu1_310::ACU1_DRIVINGCONTROLREQUEST_REQUEST);
  acu1_310_->set_acu1_steeringcontrolrequest(Acu1_310::ACU1_STEERINGCONTROLREQUEST_REQUEST);
  
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
ErrorCode KfcController::EnableCloudMode() {
  if (driving_mode() == Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "Already in REMOTE_CLOUD_DRIVE mode";
    return ErrorCode::OK;
  }

  acu1_310_->set_acu1_drivingcontrolrequest(Acu1_310::ACU1_DRIVINGCONTROLREQUEST_REQUEST);
  acu1_310_->set_acu1_steeringcontrolrequest(Acu1_310::ACU1_STEERINGCONTROLREQUEST_REQUEST);

  can_sender_->Update();
  set_driving_mode(Chassis::REMOTE_CLOUD_DRIVE);
  AINFO << "Switch to REMOTE_CLOUD_DRIVE mode ok.";
  return ErrorCode::OK;
}

ErrorCode KfcController::DisableAutoMode() {
  ResetProtocol();
  can_sender_->Update();
  set_driving_mode(Chassis::COMPLETE_MANUAL);
  set_chassis_error_code(Chassis::NO_ERROR);
  AINFO << "Switch to COMPLETE_MANUAL ok.";
  return ErrorCode::OK;
}

ErrorCode KfcController::EnableSteeringOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_STEER_ONLY) {
    set_driving_mode(Chassis::AUTO_STEER_ONLY);
    AINFO << "Already in AUTO_STEER_ONLY mode.";
    return ErrorCode::OK;
  }
  acu1_310_->set_acu1_drivingcontrolrequest(Acu1_310::ACU1_DRIVINGCONTROLREQUEST_NO_REQUET);
  acu1_310_->set_acu1_steeringcontrolrequest(Acu1_310::ACU1_STEERINGCONTROLREQUEST_REQUEST);
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

ErrorCode KfcController::EnableSpeedOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_SPEED_ONLY) {
    set_driving_mode(Chassis::AUTO_SPEED_ONLY);
    AINFO << "Already in AUTO_SPEED_ONLY mode";
    return ErrorCode::OK;
  }
  acu1_310_->set_acu1_drivingcontrolrequest(Acu1_310::ACU1_DRIVINGCONTROLREQUEST_REQUEST);
  acu1_310_->set_acu1_steeringcontrolrequest(Acu1_310::ACU1_STEERINGCONTROLREQUEST_NO_REQUET);
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
void KfcController::Gear(Chassis::GearPosition gear_position) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "This drive mode no need to set gear.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
 switch (gear_position) {
  case Chassis::GEAR_NEUTRAL: {
    acu1_310_->set_acu1_targetgear(Acu1_310::ACU1_TARGETGEAR_N);
    break;
  }
  case Chassis::GEAR_REVERSE: {
    acu1_310_->set_acu1_targetgear(Acu1_310::ACU1_TARGETGEAR_R);
    break;
  }
  case Chassis::GEAR_DRIVE: {
    acu1_310_->set_acu1_targetgear(Acu1_310::ACU1_TARGETGEAR_D);
    break;
  }
  case Chassis::GEAR_PARKING: {
    acu1_310_->set_acu1_targetgear(Acu1_310::ACU1_TARGETGEAR_P);
    break;
  }
  case Chassis::GEAR_NONE: {
    acu1_310_->set_acu1_targetgear(Acu1_310::ACU1_TARGETGEAR_NO_REQUEST);
    break;
  }
  case Chassis::GEAR_INVALID: {
    AERROR << "Gear command is invalid!";
    acu1_310_->set_acu1_targetgear(Acu1_310::ACU1_TARGETGEAR_NO_REQUEST);
    break;
  }
  default: {
    acu1_310_->set_acu1_targetgear(Acu1_310::ACU1_TARGETGEAR_NO_REQUEST);
    break;
  }
}
}

// brake with pedal
// pedal:0.00~99.99, unit:percentage
void KfcController::Brake(double pedal) {
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
  acu1_310_->set_acu1_drivingcontrolrequest(Acu1_310::ACU1_DRIVINGCONTROLREQUEST_REQUEST);
  acu1_310_->set_acu1_targetbrakingposition(std::abs(int(pedal)));
 
}

// drive with pedal
// pedal:0.0~99.9 unit:percentage
void KfcController::Throttle(double pedal) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current drive mode does not need to set throttle pedal.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  AINFO << "PEDAL COMMAND 1 IS "<< pedal;
  acu1_310_->set_acu1_drivingcontrolrequest(Acu1_310::ACU1_DRIVINGCONTROLREQUEST_REQUEST);
  acu1_310_->set_acu1_targetthrottleposition(std::abs(int(pedal)));
 
}

// confirm the car is driven by acceleration command instead of
// throttle/brake pedal drive with acceleration/deceleration acc:-7.0 ~ 5.0,
// unit:m/s^2
void KfcController::Acceleration(double acc) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current drive mode does not need to set acceleration.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
  */
}

// kfc default, +470 ~ -470 or other, left:+, right:-
// need to be compatible with control module, so reverse
// steering with steering angle
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
void KfcController::Steer(double angle) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  acu1_310_->set_acu1_steeringcontrolrequest(Acu1_310::ACU1_STEERINGCONTROLREQUEST_REQUEST);
  acu1_310_->set_acu1_targetsteeringangle( - vehicle_params_.max_steer_angle() /M_PI * 180.0 * angle / 100.0);
}

// kfc default, steering with new angle speed
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
// angle_spd:0.00~99.99, unit:deg/s
void KfcController::Steer(double angle, double angle_spd) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_STEER_ONLY &&
      driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  acu1_310_->set_acu1_steeringcontrolrequest(Acu1_310::ACU1_STEERINGCONTROLREQUEST_REQUEST);
  acu1_310_->set_acu1_targetsteeringangle(-int(vehicle_params_.max_steer_angle() /M_PI * 180.0 * angle / 100.0));
  acu1_310_->set_acu1_targetsteeringspeed(int(vehicle_params_.max_steer_angle_rate() /M_PI * 180 * angle_spd / 100));
}

void KfcController::SetEpbBreak(const ControlCommand& command) {
  if (command.parking_brake()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
    acu1_310_->set_acu1_standstillst(Acu1_310::ACU1_STANDSTILLST_ACTIVE);
  } else {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
    acu1_310_->set_acu1_standstillst(Acu1_310::ACU1_STANDSTILLST_INACTIVE);
  }
}

void KfcController::SetBeam(const VehicleSignal& vehicle_signal) {
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

void KfcController::SetHorn(const VehicleSignal& vehicle_signal) {
  if (vehicle_signal.horn()) {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  } else {
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    */
  }
}

void KfcController::SetTurningSignal(const VehicleSignal& vehicle_signal) {
  // Set Turn Signal
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  auto signal = vehicle_signal.turn_signal();
  if (signal == common::VehicleSignal::TURN_LEFT) {

  } else if (signal == common::VehicleSignal::TURN_RIGHT) {

  } else {

  }
  */
}

ErrorCode KfcController::HandleCustomOperation(
    const external_command::ChassisCommand& command) {
  return ErrorCode::OK;
}

bool KfcController::VerifyID() {
  if (!CheckVin()) {
    AERROR << "Failed to get the vin. Get vin again.";
    GetVin();
    return false;
  } else {
    ResetVin();
    return true;
  }
}

bool KfcController::CheckVin() {
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

void KfcController::GetVin() {
  // Get vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_ENABLE);
  AINFO << "Get vin";
  can_sender_->Update();
  */
}

void KfcController::ResetVin() {
  // Reset vin from vehicle if exist
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  vehicle_mode_command_116_->set_vin_req_cmd(
      Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_DISABLE);
  AINFO << "Reset vin";
  can_sender_->Update();
  */
}

void KfcController::ResetProtocol() {
  message_manager_->ResetSendMessages();
}

bool KfcController::CheckChassisError() {
  Kfc chassis_detail;
  if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
    AERROR_EVERY(100) << "Get chassis detail failed.";
  }
  /*
  if (!chassis_.has_check_response()) {
    AERROR_EVERY(100) << "ChassisDetail has no kfc vehicle info.";
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "ChassisDetail has no kfc vehicle info.");
    return false;
  } else {
    chassis_.clear_engage_advice();
  }
  */

  /* ADD YOUR OWN CAR CHASSIS OPERATION
  // steer fault
  // drive fault
  // brake fault
  */
 if (chassis_detail.has_vcu1_320()){
  if (chassis_detail.vcu1_320().has_vcu1_drivingfailurest()) {
    if(chassis_detail.vcu1_320().vcu1_drivingfailurest() != Vcu1_320::VCU1_DRIVINGFAILUREST_NO_FAIL){ 
      chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_THROTTLE);
      return true;
    }else{
      chassis_.set_error_code(Chassis::NO_ERROR);
    }
  }else{
    chassis_.set_error_code(Chassis::CHASSIS_ERROR_ON_THROTTLE);
    return true;
  }

  if (chassis_detail.vcu1_320().has_vcu1_steeringfailurest()) {
    if(chassis_detail.vcu1_320().vcu1_steeringfailurest() != Vcu1_320::VCU1_STEERINGFAILUREST_NO_FAIL){ 
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

void KfcController::SecurityDogThreadFunc() {
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
      AERROR << "Too much time consumption in KfcController looping process:"
             << elapsed.count();
    }
  }
}

bool KfcController::CheckResponse(const int32_t flags, bool need_wait) {
  int32_t retry_num = 20;
  bool is_eps_online = false;
  bool is_vcu_online = false;
  bool is_esp_online = false;
  Kfc chassis_detail;

  do {
    if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
      AERROR_EVERY(100) << "Get chassis detail failed.";
      return false;
    }
    bool check_ok = true;
    if (flags & CHECK_RESPONSE_STEER_UNIT_FLAG) {
      is_eps_online = chassis_detail.has_vcu1_320() &&
                      chassis_detail.vcu1_320().has_vcu1_steeringtakeoverst() &&
                      !chassis_detail.vcu1_320().vcu1_steeringtakeoverst();
      check_ok = check_ok && is_eps_online;
    }

    if (flags & CHECK_RESPONSE_SPEED_UNIT_FLAG) {
      is_vcu_online = chassis_detail.has_vcu1_320() &&
                      chassis_detail.vcu1_320().has_vcu1_drivingtakeoverst() &&
                      !chassis_detail.vcu1_320().vcu1_drivingtakeoverst();
      check_ok = check_ok && is_vcu_online;
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
         << ", is_vcu_online:" << is_vcu_online;

  return false;
}

void KfcController::set_chassis_error_mask(const int32_t mask) {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  chassis_error_mask_ = mask;
}

int32_t KfcController::chassis_error_mask() {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  return chassis_error_mask_;
}

Chassis::ErrorCode KfcController::chassis_error_code() {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  return chassis_error_code_;
}

void KfcController::set_chassis_error_code(
    const Chassis::ErrorCode& error_code) {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  chassis_error_code_ = error_code;
}

}  // namespace kfc
}  // namespace canbus
}  // namespace apollo
