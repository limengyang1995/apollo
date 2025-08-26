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

#include "modules/canbus_vehicle/middlecar/middlecar_controller.h"

#include <string>

#include "modules/common_msgs/basic_msgs/vehicle_signal.pb.h"

#include "cyber/common/log.h"
#include "cyber/time/time.h"
#include "modules/canbus/vehicle/vehicle_controller.h"
#include "modules/canbus_vehicle/middlecar/middlecar_message_manager.h"
#include "modules/drivers/canbus/can_comm/can_sender.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace middlecar {
using ::apollo::common::ErrorCode;
using ::apollo::common::VehicleSignal;
using ::apollo::control::ControlCommand;
using ::apollo::drivers::canbus::ProtocolData;

namespace {
const int32_t kMaxFailAttempt = 10;
const int32_t CHECK_RESPONSE_STEER_UNIT_FLAG = 1;
const int32_t CHECK_RESPONSE_SPEED_UNIT_FLAG = 2;

}  // namespace

void MiddlecarController::AddSendMessage() {
    can_sender_->AddMessage(Fsdvcucmd16a0::ID, fsd_vcu_cmd1_6a0_, false);
    can_sender_->AddMessage(Fsdvcucmd26a2::ID, fsd_vcu_cmd2_6a2_, false);
}

ErrorCode MiddlecarController::Init(
        const VehicleParameter& params,
        CanSender<::apollo::canbus::Middlecar>* const can_sender,
        MessageManager<::apollo::canbus::Middlecar>* const message_manager) {
    if (is_initialized_) {
        AINFO << "MiddlecarController has already been initiated.";
        return ErrorCode::CANBUS_ERROR;
    }

    vehicle_params_.CopyFrom(common::VehicleConfigHelper::Instance()->GetConfig().vehicle_param());
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
    fsd_vcu_cmd1_6a0_ = dynamic_cast<Fsdvcucmd16a0*>(message_manager_->GetMutableProtocolDataById(Fsdvcucmd16a0::ID));
    if (fsd_vcu_cmd1_6a0_ == nullptr) {
        AERROR << "Fsdvcucmd16a0 does not exist in the MiddlecarMessageManager!";
        return ErrorCode::CANBUS_ERROR;
    }

    fsd_vcu_cmd2_6a2_ = dynamic_cast<Fsdvcucmd26a2*>(message_manager_->GetMutableProtocolDataById(Fsdvcucmd26a2::ID));
    if (fsd_vcu_cmd2_6a2_ == nullptr) {
        AERROR << "Fsdvcucmd26a2 does not exist in the MiddlecarMessageManager!";
        return ErrorCode::CANBUS_ERROR;
    }

    AddSendMessage();

    AINFO << "MiddlecarController is initialized.";

    is_initialized_ = true;
    return ErrorCode::OK;
}

MiddlecarController::~MiddlecarController() {}

bool MiddlecarController::Start() {
    if (!is_initialized_) {
        AERROR << "MiddlecarController has NOT been initiated.";
        return false;
    }
    const auto& update_func = [this] { SecurityDogThreadFunc(); };
    thread_.reset(new std::thread(update_func));

    return true;
}

void MiddlecarController::Stop() {
    if (!is_initialized_) {
        AERROR << "MiddlecarController stops or starts improperly!";
        return;
    }

    if (thread_ != nullptr && thread_->joinable()) {
        thread_->join();
        thread_.reset();
        AINFO << "MiddlecarController stopped.";
    }
}

Chassis MiddlecarController::chassis() {
    chassis_.Clear();
    Middlecar chassis_detail = GetNewRecvChassisDetail();
    ;

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
        chassis_.mutable_engage_advice()->set_advice(apollo::common::EngageAdvice::DISALLOW_ENGAGE);
        chassis_.mutable_engage_advice()->set_reason("Chassis has some fault, please check the chassis_detail.");
    }

    // check the chassis detail lost
    if (is_chassis_communication_error_) {
        chassis_.mutable_engage_advice()->set_advice(apollo::common::EngageAdvice::DISALLOW_ENGAGE);
        chassis_.mutable_engage_advice()->set_reason(
                "middlecar chassis detail is lost! Please check the communication error.");
        set_chassis_error_code(Chassis::CHASSIS_CAN_LOST);
        set_driving_mode(Chassis::EMERGENCY_MODE);
    }

    /* ADD YOUR OWN CAR CHASSIS OPERATION
    // 5 wheel spd
    // 6 speed_mps
    // 9 throttle
    // 10 brake
    // 11 gear
    // 12 steering
    // 13 parking brake
    // 14 battery soc
    // 16 sonor list
    // 17 set vin
    // 18,19 bumper event
    // 20 add checkresponse signal
    */

    // 4 speed_mps
    if (chassis_detail.has_vcu_fsd_status2_686() && chassis_detail.vcu_fsd_status2_686().has_vcu_fsd_vehspeed()) {
        chassis_.set_speed_mps(static_cast<float>(chassis_detail.vcu_fsd_status2_686().vcu_fsd_vehspeed()) / 3.6);
    } else {
        chassis_.set_speed_mps(0);
    }
    // 5 driving_mode
    if (chassis_detail.has_vcu_fsd_status1_685() && chassis_detail.vcu_fsd_status1_685().has_vcu_fsd_cmdsource()) {
        if (chassis_detail.vcu_fsd_status1_685().vcu_fsd_cmdsource() == Vcu_fsd_status1_685::VCU_FSD_CMDSOURCE_FSD) {
            chassis_.set_driving_mode(Chassis::COMPLETE_AUTO_DRIVE);
        } else {
            chassis_.set_driving_mode(Chassis::COMPLETE_MANUAL);
        }
    } else {
        chassis_.set_driving_mode(Chassis::COMPLETE_MANUAL);
    }

    // 6 soc
    if (chassis_detail.has_vcu_fsd_status1_685()) {
        if (chassis_detail.vcu_fsd_status1_685().has_vcu_fsd_vehsoc()) {
            chassis_.set_battery_soc_percentage(
                    static_cast<int>(chassis_detail.vcu_fsd_status1_685().vcu_fsd_vehsoc()));
        } else {
            chassis_.set_battery_soc_percentage(0);
        }

        if (chassis_detail.vcu_fsd_status1_685().has_vcu_fsd_touchborder()) {
            if (chassis_detail.vcu_fsd_status1_685().vcu_fsd_touchborder()
                == Vcu_fsd_status1_685::VCU_FSD_TOUCHBORDER_CONTACT) {
                chassis_.set_front_bumper_event(Chassis::BUMPER_PRESSED);
            } else {
                chassis_.set_front_bumper_event(Chassis::BUMPER_NORMAL);
            }
        } else {
            chassis_.set_front_bumper_event(Chassis::BUMPER_INVALID);
        }

        if (chassis_detail.vcu_fsd_status1_685().has_vcu_fsd_parkingstatus()) {
            if (chassis_detail.vcu_fsd_status1_685().vcu_fsd_parkingstatus()
                == Vcu_fsd_status1_685::VCU_FSD_PARKINGSTATUS_PARKING) {
                chassis_.set_parking_brake(true);
            } else {
                chassis_.set_parking_brake(false);
            }
        } else {
            chassis_.set_parking_brake(false);
        }

        if (chassis_detail.vcu_fsd_status1_685().has_vcu_fsd_gear_position()) {
            switch (chassis_detail.vcu_fsd_status1_685().vcu_fsd_gear_position()) {
            case Vcu_fsd_status1_685::VCU_FSD_GEAR_POSITION_D: {
                chassis_.set_gear_location(Chassis::GEAR_DRIVE);
            } break;
            case Vcu_fsd_status1_685::VCU_FSD_GEAR_POSITION_N: {
                chassis_.set_gear_location(Chassis::GEAR_NEUTRAL);
            } break;
            case Vcu_fsd_status1_685::VCU_FSD_GEAR_POSITION_R: {
                chassis_.set_gear_location(Chassis::GEAR_REVERSE);
            } break;
            default:
                chassis_.set_gear_location(Chassis::GEAR_INVALID);
                break;
            }
        } else {
            chassis_.set_gear_location(Chassis::GEAR_INVALID);
        }

        if (chassis_detail.vcu_fsd_status1_685().has_vcu_fsd_steermode()) {
            if (chassis_detail.vcu_fsd_status1_685().vcu_fsd_steermode()
                == Vcu_fsd_status1_685::VCU_FSD_STEERMODE_FRONT_AXLE_STEERING) {
                chassis_.set_steer_mode(Chassis::FRONT_AXLE);
            } else if (
                    chassis_detail.vcu_fsd_status1_685().vcu_fsd_steermode()
                    == Vcu_fsd_status1_685::VCU_FSD_STEERMODE_FULL_BRIDGE_STEERING) {
                chassis_.set_steer_mode(Chassis::FULL_BRIDGE);
            } else {
                chassis_.set_steer_mode(Chassis::REAR_AXLE);
            }
        } else {
            chassis_.set_steer_mode(Chassis::STEER_MODE_INVALID);
        }

    } else {
        chassis_.set_battery_soc_percentage(0);
        chassis_.set_front_bumper_event(Chassis::BUMPER_INVALID);
        chassis_.set_parking_brake(false);
        chassis_.set_gear_location(Chassis::GEAR_INVALID);
        chassis_.set_steer_mode(Chassis::STEER_MODE_INVALID);
    }

    if (chassis_detail.has_vcu_fsd_status2_686()) {
        if (chassis_detail.vcu_fsd_status2_686().has_vcu_fsd_vehroll()) {
            chassis_.mutable_chassis_gps()->set_roll(chassis_detail.vcu_fsd_status2_686().vcu_fsd_vehroll());
        } else {
            chassis_.mutable_chassis_gps()->set_roll(0);
        }

        if (chassis_detail.vcu_fsd_status2_686().has_vcu_fsd_vehpitch()) {
            chassis_.mutable_chassis_gps()->set_pitch(chassis_detail.vcu_fsd_status2_686().vcu_fsd_vehpitch());
        } else {
            chassis_.mutable_chassis_gps()->set_pitch(0);
        }

        if (chassis_detail.vcu_fsd_status2_686().has_vcu_fsd_vehfrontangle()) {
            chassis_.set_steering_percentage(
                    static_cast<float>(
                            chassis_detail.vcu_fsd_status2_686().vcu_fsd_vehfrontangle() * 100.0
                            / (vehicle_params_.max_steer_angle() * 180 / M_PI)));
        } else {
            chassis_.set_steering_percentage(0);
        }

        if (chassis_detail.vcu_fsd_status2_686().has_vcu_fsd_vehrearangle()) {
            chassis_.set_rear_steering_percentage(
                    static_cast<float>(
                            -chassis_detail.vcu_fsd_status2_686().vcu_fsd_vehrearangle() * 100.0
                            / (vehicle_params_.max_steer_angle() * 180 / M_PI)));
        } else {
            chassis_.set_steering_percentage(0);
            chassis_.set_rear_steering_percentage(0);
        }

    } else {
        chassis_.mutable_chassis_gps()->set_roll(0);
        chassis_.mutable_chassis_gps()->set_pitch(0);
        chassis_.set_steering_percentage(0);
        chassis_.set_rear_steering_percentage(0);
    }

    // 13 chassis error
    if (chassis_error_mask_) {
        chassis_.set_chassis_error_mask(chassis_error_mask_);
    }

    // Give engage_advice based on error_code and canbus feedback
    if (chassis_error_mask_) {
        chassis_.mutable_engage_advice()->set_advice(apollo::common::EngageAdvice::DISALLOW_ENGAGE);
        chassis_.mutable_engage_advice()->set_reason("Chassis error!");
    } else if (chassis_.parking_brake()) {
        chassis_.mutable_engage_advice()->set_advice(apollo::common::EngageAdvice::DISALLOW_ENGAGE);
        chassis_.mutable_engage_advice()->set_reason("Vehicle is not in a safe state to engage!");
    } else {
        chassis_.mutable_engage_advice()->set_advice(apollo::common::EngageAdvice::READY_TO_ENGAGE);
    }

    return chassis_;
}

void MiddlecarController::Emergency() {
    set_driving_mode(Chassis::EMERGENCY_MODE);
    ResetProtocol();
}

ErrorCode MiddlecarController::EnableAutoMode() {
    if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE) {
        AINFO << "already in COMPLETE_AUTO_DRIVE mode";
        return ErrorCode::OK;
    }
    // set enable
    /* ADD YOUR OWN CAR CHASSIS OPERATION*/
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_cmdsource(Fsd_vcu_cmd1_6a0::FSD_VCU_CMDSOURCE_FSD);
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_specialmode(Fsd_vcu_cmd1_6a0::FSD_VCU_SPECIALMODE_STANDARD_MODE);
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_steermode(Fsd_vcu_cmd1_6a0::FSD_VCU_STEERMODE_FRONT_AXLE_STEERING);

    can_sender_->Update();
    const int32_t flag = CHECK_RESPONSE_STEER_UNIT_FLAG | CHECK_RESPONSE_SPEED_UNIT_FLAG;
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

ErrorCode MiddlecarController::EnableCloudMode() {
    if (driving_mode() == Chassis::REMOTE_CLOUD_DRIVE) {
        ADEBUG << "Already in REMOTE_CLOUD_DRIVE mode";
        return ErrorCode::OK;
    }
    // set enable
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_cmdsource(Fsd_vcu_cmd1_6a0::FSD_VCU_CMDSOURCE_FSD);
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_specialmode(Fsd_vcu_cmd1_6a0::FSD_VCU_SPECIALMODE_STANDARD_MODE);
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_steermode(Fsd_vcu_cmd1_6a0::FSD_VCU_STEERMODE_FRONT_AXLE_STEERING);

    can_sender_->Update();
    set_driving_mode(Chassis::REMOTE_CLOUD_DRIVE);
    ADEBUG << "Switch to REMOTE_CLOUD_DRIVE mode ok.";
    return ErrorCode::OK;
}

ErrorCode MiddlecarController::DisableAutoMode() {
    ResetProtocol();
    can_sender_->Update();
    set_driving_mode(Chassis::COMPLETE_MANUAL);
    set_chassis_error_code(Chassis::NO_ERROR);
    AINFO << "Switch to COMPLETE_MANUAL ok.";
    return ErrorCode::OK;
}

ErrorCode MiddlecarController::EnableSteeringOnlyMode() {
    if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE || driving_mode() == Chassis::AUTO_STEER_ONLY) {
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

ErrorCode MiddlecarController::EnableSpeedOnlyMode() {
    if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE || driving_mode() == Chassis::AUTO_SPEED_ONLY) {
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
void MiddlecarController::Gear(Chassis::GearPosition gear_position) {
    if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE && driving_mode() != Chassis::AUTO_SPEED_ONLY
        && driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
        AINFO << "This drive mode no need to set gear.";
        return;
    }
    /* ADD YOUR OWN CAR CHASSIS OPERATION
     */
    switch (gear_position) {
    case Chassis::GEAR_NEUTRAL: {
        fsd_vcu_cmd1_6a0_->set_fsd_vcu_targear(Fsd_vcu_cmd1_6a0::FSD_VCU_TARGEAR_N);
        break;
    }
    case Chassis::GEAR_REVERSE: {
        fsd_vcu_cmd1_6a0_->set_fsd_vcu_targear(Fsd_vcu_cmd1_6a0::FSD_VCU_TARGEAR_R);
        break;
    }
    case Chassis::GEAR_DRIVE: {
        fsd_vcu_cmd1_6a0_->set_fsd_vcu_targear(Fsd_vcu_cmd1_6a0::FSD_VCU_TARGEAR_D);
        break;
    }
    default: {
        fsd_vcu_cmd1_6a0_->set_fsd_vcu_targear(Fsd_vcu_cmd1_6a0::FSD_VCU_TARGEAR_N);
        break;
    }
    }
}

// brake with pedal
// pedal:0.00~99.99, unit:percentage
void MiddlecarController::Brake(double pedal) {
    // double real_value = vehicle_params_.max_acceleration() * acceleration / 100;
    // TODO(All) :  Update brake value based on mode
    if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE && driving_mode() != Chassis::AUTO_SPEED_ONLY
        && driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
        AINFO << "The current drive mode does not need to set brake pedal.";
        return;
    }
    /* ADD YOUR OWN CAR CHASSIS OPERATION
     */
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_brakepec(std::abs(int(pedal)));
}

// drive with pedal
// pedal:0.0~99.9 unit:percentage
void MiddlecarController::Throttle(double pedal) {
    if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE && driving_mode() != Chassis::AUTO_SPEED_ONLY
        && driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
        AINFO << "The current drive mode does not need to set throttle pedal.";
        return;
    }
    /* ADD YOUR OWN CAR CHASSIS OPERATION
     */
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_tarvehspeed(pedal * 0.5);
}

// confirm the car is driven by acceleration command instead of
// throttle/brake pedal drive with acceleration/deceleration acc:-7.0 ~ 5.0,
// unit:m/s^2
void MiddlecarController::Acceleration(double acc) {
    if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE && driving_mode() != Chassis::AUTO_SPEED_ONLY
        && driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
        AINFO << "The current drive mode does not need to set acceleration.";
        return;
    }
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
    */
    fsd_vcu_cmd2_6a2_->set_fsd_vcu_acceleration(acc);
}

// confirm the car is driven by speed command
// speed:-xx.0~xx.0, unit:m/s
void MiddlecarController::Speed(double speed) {
    if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE && driving_mode() != Chassis::AUTO_SPEED_ONLY
        && driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
        AINFO << "The current drive mode does not need to set speed.";
        return;
    }
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    // TODO(ALL): CHECK YOUR VEHICLE WHETHER SUPPORT THIS DRIVE MODE
    */
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_tarvehspeed(speed * 3.6);
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_maxvehspeedlmt(20);
}

// middlecar default, +470 ~ -470 or other, left:+, right:-
// need to be compatible with control module, so reverse
// steering with steering angle
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
void MiddlecarController::Steer(double angle) {
    if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE && driving_mode() != Chassis::AUTO_STEER_ONLY
        && driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
        AINFO << "The current driving mode does not need to set steer.";
        return;
    }
    /* ADD YOUR OWN CAR CHASSIS OPERATION
     */
    fsd_vcu_cmd1_6a0_->set_fsd_vcu_tarvehfrontangle(-vehicle_params_.max_steer_angle() / M_PI * 180.0 * angle / 100.0);
}

// middlecar default, steering with new angle and angle speed
// angle:99.99~0.00~-99.99, unit:deg, left:+, right:-
// angle_spd:0.00~99.99, unit:deg/s
void MiddlecarController::Steer(double angle, double angle_spd) {
    if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE && driving_mode() != Chassis::AUTO_STEER_ONLY
        && driving_mode() != Chassis::REMOTE_CLOUD_DRIVE) {
        AINFO << "The current driving mode does not need to set steer.";
        return;
    }
    /* ADD YOUR OWN CAR CHASSIS OPERATION
     */
}

void MiddlecarController::SetEpbBreak(const ControlCommand& command) {
    if (command.parking_brake()) {
        /* ADD YOUR OWN CAR CHASSIS OPERATION
         */
        fsd_vcu_cmd1_6a0_->set_fsd_vcu_park(Fsd_vcu_cmd1_6a0::FSD_VCU_PARK_PARKING);
    } else {
        /* ADD YOUR OWN CAR CHASSIS OPERATION
         */
        fsd_vcu_cmd1_6a0_->set_fsd_vcu_park(Fsd_vcu_cmd1_6a0::FSD_VCU_PARK_RELEASE_PARKING);
    }
}

void MiddlecarController::SetBeam(const VehicleSignal& vehicle_signal) {
    if (vehicle_signal.high_beam()) {
        /* ADD YOUR OWN CAR CHASSIS OPERATION
         */
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_headlamp(Fsd_vcu_cmd2_6a2::FSD_VCU_HEADLAMP_ENABLE);
    } else if (vehicle_signal.low_beam()) {
        /* ADD YOUR OWN CAR CHASSIS OPERATION
         */
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_nearlylamp(Fsd_vcu_cmd2_6a2::FSD_VCU_NEARLYLAMP_ENABLE);
    } else {
        /* ADD YOUR OWN CAR CHASSIS OPERATION
         */
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_nearlylamp(Fsd_vcu_cmd2_6a2::FSD_VCU_NEARLYLAMP_DISABLE);
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_headlamp(Fsd_vcu_cmd2_6a2::FSD_VCU_HEADLAMP_DISABLE);
    }
}

void MiddlecarController::SetHorn(const VehicleSignal& vehicle_signal) {
    if (vehicle_signal.horn()) {
        /* ADD YOUR OWN CAR CHASSIS OPERATION
         */
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_horn(Fsd_vcu_cmd2_6a2::FSD_VCU_HORN_ENABLE);
    } else {
        /* ADD YOUR OWN CAR CHASSIS OPERATION
         */
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_horn(Fsd_vcu_cmd2_6a2::FSD_VCU_HORN_DISABLE);
    }
}

void MiddlecarController::SetTurningSignal(const VehicleSignal& vehicle_signal) {
    // Set Turn Signal
    /* ADD YOUR OWN CAR CHASSIS OPERATION*/
    auto signal = vehicle_signal.turn_signal();
    if (signal == common::VehicleSignal::TURN_LEFT) {
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_leftturnlamp(Fsd_vcu_cmd2_6a2::FSD_VCU_LEFTTURNLAMP_ENABLE);
    } else if (signal == common::VehicleSignal::TURN_RIGHT) {
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_rightturnlamp(Fsd_vcu_cmd2_6a2::FSD_VCU_RIGHTTURNLAMP_ENABLE);
    } else {
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_leftturnlamp(Fsd_vcu_cmd2_6a2::FSD_VCU_LEFTTURNLAMP_DISABLE);
        fsd_vcu_cmd2_6a2_->set_fsd_vcu_rightturnlamp(Fsd_vcu_cmd2_6a2::FSD_VCU_RIGHTTURNLAMP_DISABLE);
    }
}

ErrorCode MiddlecarController::HandleCustomOperation(const external_command::ChassisCommand& command) {
    return ErrorCode::OK;
}

bool MiddlecarController::VerifyID() {
    if (!CheckVin()) {
        AERROR << "Failed to get the vin. Get vin again.";
        GetVin();
        return false;
    } else {
        ResetVin();
        return true;
    }
}

bool MiddlecarController::CheckVin() {
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

void MiddlecarController::GetVin() {
    // Get vin from vehicle if exist
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    vehicle_mode_command_116_->set_vin_req_cmd(
        Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_ENABLE);
    AINFO << "Get vin";
    can_sender_->Update();
    */
}

void MiddlecarController::ResetVin() {
    // Reset vin from vehicle if exist
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    vehicle_mode_command_116_->set_vin_req_cmd(
        Vehicle_mode_command_116::VIN_REQ_CMD_VIN_REQ_DISABLE);
    AINFO << "Reset vin";
    can_sender_->Update();
    */
}

void MiddlecarController::ResetProtocol() {
    message_manager_->ResetSendMessages();
}

bool MiddlecarController::CheckChassisError() {
    if (is_chassis_communication_error_) {
        AERROR_EVERY(100) << "ChassisDetail has no middlecar vehicle info.";
        return false;
    }
    Middlecar chassis_detail = GetNewRecvChassisDetail();
    /* ADD YOUR OWN CAR CHASSIS OPERATION
    // steer fault
    // drive fault
    // brake fault
    */
    if (chassis_detail.has_vcu_errormsg1_681()) {
        if (chassis_detail.vcu_errormsg1_681().has_vcu_vehicleerrorlevel()) {
            if (chassis_detail.vcu_errormsg1_681().vcu_vehicleerrorlevel()
                        == Vcu_errormsg1_681::VCU_VEHICLEERRORLEVEL_GENERAL_FAULT
                || chassis_detail.vcu_errormsg1_681().vcu_vehicleerrorlevel()
                        == Vcu_errormsg1_681::VCU_VEHICLEERRORLEVEL_SERIOUS_FAULT) {
                chassis_.set_error_code(Chassis::CHASSIS_ERROR);
                return true;
            } else {
                chassis_.set_error_code(Chassis::NO_ERROR);
            }
        } else {
            chassis_.set_error_code(Chassis::CHASSIS_CAN_LOST);
            return true;
        }
    } else {
        chassis_.set_error_code(Chassis::CHASSIS_CAN_LOST);
        return true;
    }
    return false;
}

void MiddlecarController::SecurityDogThreadFunc() {
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
        if (rolling_counter < 16) {
            ++rolling_counter;
        } else {
            rolling_counter = 0;
        }
        fsd_vcu_cmd1_6a0_->set_fsd_vcu_roulingcounter(rolling_counter);
        can_sender_->Update();
        start = ::apollo::cyber::Time::Now().ToMicrosecond();
        const Chassis::DrivingMode mode = driving_mode();
        bool emergency_mode = false;

        // 1. horizontal control check
        if ((mode == Chassis::COMPLETE_AUTO_DRIVE || mode == Chassis::AUTO_STEER_ONLY
             || mode == Chassis::REMOTE_CLOUD_DRIVE)
            && !CheckResponse(CHECK_RESPONSE_STEER_UNIT_FLAG, false)) {
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
        if ((mode == Chassis::COMPLETE_AUTO_DRIVE || mode == Chassis::AUTO_SPEED_ONLY
             || mode == Chassis::REMOTE_CLOUD_DRIVE)
            && !CheckResponse(CHECK_RESPONSE_SPEED_UNIT_FLAG, false)) {
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
        if (!emergency_mode && !is_chassis_communication_error_ && mode == Chassis::EMERGENCY_MODE) {
            set_chassis_error_code(Chassis::NO_ERROR);
        }

        end = ::apollo::cyber::Time::Now().ToMicrosecond();
        std::chrono::duration<double, std::micro> elapsed{end - start};
        if (elapsed < default_period) {
            std::this_thread::sleep_for(default_period - elapsed);
        } else {
            AERROR << "Too much time consumption in MiddlecarController looping process:" << elapsed.count();
        }
    }
}

bool MiddlecarController::CheckResponse(const int32_t flags, bool need_wait) {
    int32_t retry_num = 20;
    bool is_eps_online = false;
    bool is_vcu_online = false;
    bool is_esp_online = false;

    do {
        Middlecar chassis_detail = GetNewRecvChassisDetail();
        bool check_ok = true;
        if (flags & CHECK_RESPONSE_STEER_UNIT_FLAG) {
            is_eps_online = chassis_detail.has_vcu_errormsg2_682()
                    && chassis_detail.vcu_errormsg2_682().has_vcu_fronteps_online()
                    && chassis_detail.vcu_errormsg2_682().vcu_fronteps_online();
            check_ok = check_ok && is_eps_online;
        }

        if (flags & CHECK_RESPONSE_SPEED_UNIT_FLAG) {
            is_vcu_online = chassis_detail.has_vcu_errormsg2_682()
                    && chassis_detail.vcu_errormsg2_682().has_vcu_frontmotor_online()
                    && chassis_detail.vcu_errormsg2_682().vcu_frontmotor_online();
            is_esp_online = chassis_detail.has_vcu_errormsg2_682()
                    && chassis_detail.vcu_errormsg2_682().has_vcu_frontbrake_online()
                    && chassis_detail.vcu_errormsg2_682().vcu_frontbrake_online();
            check_ok = check_ok && is_vcu_online && is_esp_online;
        }
        if (check_ok) {
            return true;
        } else {
            AINFO << "Need to check response again.";
        }
        if (need_wait) {
            --retry_num;
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(20));
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

void MiddlecarController::set_chassis_error_mask(const int32_t mask) {
    std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
    chassis_error_mask_ = mask;
}

int32_t MiddlecarController::chassis_error_mask() {
    std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
    return chassis_error_mask_;
}

Chassis::ErrorCode MiddlecarController::chassis_error_code() {
    std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
    return chassis_error_code_;
}

void MiddlecarController::set_chassis_error_code(const Chassis::ErrorCode& error_code) {
    std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
    chassis_error_code_ = error_code;
}

}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo
