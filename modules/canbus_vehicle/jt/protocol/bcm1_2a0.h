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

class Bcm12a0 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::Jt> {
 public:
  static const int32_t ID;
  Bcm12a0();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     Jt* chassis) const override;

 private:

    // config detail: {'bit': 54, 'description': 'The signal is sent to indicate the Driver Seat Belt is buckled or Unbuckled.', 'enum': {0: 'BCM1_PASSENGERSIDEBUCKLE_UNBUCKLED', 1: 'BCM1_PASSENGERSIDEBUCKLE_BUCKLED', 2: 'BCM1_PASSENGERSIDEBUCKLE_RESERVED', 3: 'BCM1_PASSENGERSIDEBUCKLE_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_PassengerSideBuckle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_passengersidebuckleType bcm1_passengersidebuckle(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 37, 'description': 'This signal informs about the wiper speed requested by the Sensor according to rain intensity or other factors', 'enum': {0: 'BCM1_WIPERSPEED_NO_WIPE', 1: 'BCM1_WIPERSPEED_42_TIMES_MIN', 2: 'BCM1_WIPERSPEED_45_TIMES_MIN', 3: 'BCM1_WIPERSPEED_48_TIMES_MIN', 4: 'BCM1_WIPERSPEED_51_TIMES_MIN', 5: 'BCM1_WIPERSPEED_54_TIMES_MIN', 6: 'BCM1_WIPERSPEED_57_TIMES_MIN', 7: 'BCM1_WIPERSPEED_60_TIMES_MIN'}, 'is_signed_var': False, 'len': 3, 'name': 'BCM1_WiperSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
    Bcm1_2a0::Bcm1_wiperspeedType bcm1_wiperspeed(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 32, 'description': 'The signal indicates the status of position light.', 'enum': {0: 'BCM1_POSITIONLIGHTST_OFF', 1: 'BCM1_POSITIONLIGHTST_ON', 2: 'BCM1_POSITIONLIGHTST_RESERVED', 3: 'BCM1_POSITIONLIGHTST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_PositionLightSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_positionlightstType bcm1_positionlightst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 50, 'description': 'Fold status of right mirror', 'enum': {0: 'BCM1_MIRRORFOLDST_FR_UNFOLD', 1: 'BCM1_MIRRORFOLDST_FR_FOLD', 2: 'BCM1_MIRRORFOLDST_FR_RESERVED', 3: 'BCM1_MIRRORFOLDST_FR_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_MirrorFoldSt_FR', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_mirrorfoldst_frType bcm1_mirrorfoldst_fr(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 48, 'description': 'Fold status of left mirror', 'enum': {0: 'BCM1_MIRRORFOLDST_FL_UNFOLD', 1: 'BCM1_MIRRORFOLDST_FL_FOLD', 2: 'BCM1_MIRRORFOLDST_FL_RESERVED', 3: 'BCM1_MIRRORFOLDST_FL_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_MirrorFoldSt_FL', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_mirrorfoldst_flType bcm1_mirrorfoldst_fl(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 52, 'description': 'The signal is sent to indicate the Driver Seat Belt is buckled or Unbuckled.', 'enum': {0: 'BCM1_DRIVERSIDEBUCKLE_UNBUCKLED', 1: 'BCM1_DRIVERSIDEBUCKLE_BUCKLED', 2: 'BCM1_DRIVERSIDEBUCKLE_RESERVED', 3: 'BCM1_DRIVERSIDEBUCKLE_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_DriverSideBuckle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_driversidebuckleType bcm1_driversidebuckle(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 34, 'description': 'The signal indicates front wiper status.', 'enum': {0: 'BCM1_WIPERSTATUS_OFF', 1: 'BCM1_WIPERSTATUS_TIP', 2: 'BCM1_WIPERSTATUS_INTERVAL_OR_AUTO_LEVER', 3: 'BCM1_WIPERSTATUS_LOW_SPEED', 4: 'BCM1_WIPERSTATUS_HIGH_SPEED', 5: 'BCM1_WIPERSTATUS_RESERVED', 6: 'BCM1_WIPERSTATUS_RESERVED', 7: 'BCM1_WIPERSTATUS_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'BCM1_WiperStatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_wiperstatusType bcm1_wiperstatus(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 21, 'description': 'This signal indicates luggage door status', 'enum': {0: 'BCM1_LUGGAGEDOORST_CLOSE', 1: 'BCM1_LUGGAGEDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'BCM1_LuggageDoorSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_luggagedoorstType bcm1_luggagedoorst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 28, 'description': 'The signal  indicates the status of low beam indicator.', 'enum': {0: 'BCM1_LOWBEAMST_OFF', 1: 'BCM1_LOWBEAMST_ON', 2: 'BCM1_LOWBEAMST_RESERVED', 3: 'BCM1_LOWBEAMST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_LowBeamSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_lowbeamstType bcm1_lowbeamst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 30, 'description': 'The signal  indicates the status of high beam indicator.', 'enum': {0: 'BCM1_HIGHBEAMST_OFF', 1: 'BCM1_HIGHBEAMST_ON', 2: 'BCM1_HIGHBEAMST_RESERVED', 3: 'BCM1_HIGHBEAMST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_HighBeamSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_highbeamstType bcm1_highbeamst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 20, 'description': 'This signal shows engine hood status.', 'enum': {0: 'BCM1_ENGHOODST_CLOSE', 1: 'BCM1_ENGHOODST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'BCM1_EngHoodSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_enghoodstType bcm1_enghoodst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 14, 'description': 'This signal indicates the lock state of RR door.', 'enum': {0: 'BCM1_RRDOORLOCKST_LOCK', 1: 'BCM1_RRDOORLOCKST_UNLOCK', 2: 'BCM1_RRDOORLOCKST_RESERVED', 3: 'BCM1_RRDOORLOCKST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_RRDoorLockSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_rrdoorlockstType bcm1_rrdoorlockst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 19, 'description': 'This signal indicates the state of RR door.', 'enum': {0: 'BCM1_RRDOORST_CLOSE', 1: 'BCM1_RRDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'BCM1_RRDoorSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_rrdoorstType bcm1_rrdoorst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 12, 'description': 'This signal indicates the lock state of RL door.', 'enum': {0: 'BCM1_RLDOORLOCKST_LOCK', 1: 'BCM1_RLDOORLOCKST_UNLOCK', 2: 'BCM1_RLDOORLOCKST_RESERVED', 3: 'BCM1_RLDOORLOCKST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_RLDoorLockSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_rldoorlockstType bcm1_rldoorlockst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 18, 'description': 'This signal indicates the state of RL door.', 'enum': {0: 'BCM1_RLDOORST_CLOSE', 1: 'BCM1_RLDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'BCM1_RLDoorSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_rldoorstType bcm1_rldoorst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 10, 'description': 'This signal indicates the lock state of passenger door.', 'enum': {0: 'BCM1_PASSENGERDOORLOCKST_LOCK', 1: 'BCM1_PASSENGERDOORLOCKST_UNLOCK', 2: 'BCM1_PASSENGERDOORLOCKST_RESERVED', 3: 'BCM1_PASSENGERDOORLOCKST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_PassengerDoorLockSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_passengerdoorlockstType bcm1_passengerdoorlockst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 17, 'description': 'This signal indicates the state of passenger door.', 'enum': {0: 'BCM1_PASSENGERDOORST_CLOSE', 1: 'BCM1_PASSENGERDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'BCM1_PassengerDoorSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_passengerdoorstType bcm1_passengerdoorst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 8, 'description': 'This signal indicates the lock state of driver door.', 'enum': {0: 'BCM1_DRIVERDOORLOCKST_LOCK', 1: 'BCM1_DRIVERDOORLOCKST_UNLOCK', 2: 'BCM1_DRIVERDOORLOCKST_RESERVED', 3: 'BCM1_DRIVERDOORLOCKST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_DriverDoorLockSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_driverdoorlockstType bcm1_driverdoorlockst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 16, 'description': 'This signal indicates the state of driver door.', 'enum': {0: 'BCM1_DRIVERDOORST_CLOSE', 1: 'BCM1_DRIVERDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'BCM1_DriverDoorSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_driverdoorstType bcm1_driverdoorst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'BCM1_LiveCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
    int bcm1_livecounter(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'BCM1_Checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
    int bcm1_checksum(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 24, 'description': 'The signal indicates the driving status of the turn light.', 'enum': {0: 'BCM1_STEERINGLIGHTST_OFF', 1: 'BCM1_STEERINGLIGHTST_LEFT_ON', 2: 'BCM1_STEERINGLIGHTST_RIGHT_ON', 3: 'BCM1_STEERINGLIGHTST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_SteeringLightSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_steeringlightstType bcm1_steeringlightst(const std::uint8_t* bytes, const int32_t length) const;

    // config detail: {'bit': 26, 'description': 'The signal indicates Indicates the Hazard Warning is active or not', 'enum': {0: 'BCM1_HAZARDLIGHTST_OFF', 1: 'BCM1_HAZARDLIGHTST_ON', 2: 'BCM1_HAZARDLIGHTST_RESERVED', 3: 'BCM1_HAZARDLIGHTST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'BCM1_HazardLightSt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
    Bcm1_2a0::Bcm1_hazardlightstType bcm1_hazardlightst(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace jt
}  // namespace canbus
}  // namespace apollo


