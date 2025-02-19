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

#include "modules/canbus_vehicle/jt/protocol/bcm1_2a0.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace jt {

using ::apollo::drivers::canbus::Byte;

Bcm12a0::Bcm12a0() {}
const int32_t Bcm12a0::ID = 0x2A0;

void Bcm12a0::Parse(const std::uint8_t* bytes, int32_t length,
                         Jt* chassis) const {
  chassis->mutable_bcm1_2a0()->set_bcm1_passengersidebuckle(bcm1_passengersidebuckle(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_wiperspeed(bcm1_wiperspeed(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_positionlightst(bcm1_positionlightst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_mirrorfoldst_fr(bcm1_mirrorfoldst_fr(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_mirrorfoldst_fl(bcm1_mirrorfoldst_fl(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_driversidebuckle(bcm1_driversidebuckle(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_wiperstatus(bcm1_wiperstatus(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_luggagedoorst(bcm1_luggagedoorst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_lowbeamst(bcm1_lowbeamst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_highbeamst(bcm1_highbeamst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_enghoodst(bcm1_enghoodst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_rrdoorlockst(bcm1_rrdoorlockst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_rrdoorst(bcm1_rrdoorst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_rldoorlockst(bcm1_rldoorlockst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_rldoorst(bcm1_rldoorst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_passengerdoorlockst(bcm1_passengerdoorlockst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_passengerdoorst(bcm1_passengerdoorst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_driverdoorlockst(bcm1_driverdoorlockst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_driverdoorst(bcm1_driverdoorst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_livecounter(bcm1_livecounter(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_checksum(bcm1_checksum(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_steeringlightst(bcm1_steeringlightst(bytes, length));
  chassis->mutable_bcm1_2a0()->set_bcm1_hazardlightst(bcm1_hazardlightst(bytes, length));
}

// config detail: {'bit': 54, 'description': 'The signal is sent to indicate the Driver Seat Belt is buckled or Unbuckled.', 'enum': {0: 'BCM1_PASSENGERSIDEBUCKLE_UNBUCKLED', 1: 'BCM1_PASSENGERSIDEBUCKLE_BUCKLED', 2: 'BCM1_PASSENGERSIDEBUCKLE_RESERVED', 3: 'BCM1_PASSENGERSIDEBUCKLE_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_passengersidebuckle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_passengersidebuckleType Bcm12a0::bcm1_passengersidebuckle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(6, 2);

  Bcm1_2a0::Bcm1_passengersidebuckleType ret =  static_cast<Bcm1_2a0::Bcm1_passengersidebuckleType>(x);
  return ret;
}

// config detail: {'bit': 37, 'description': 'This signal informs about the wiper speed requested by the Sensor according to rain intensity or other factors', 'enum': {0: 'BCM1_WIPERSPEED_NO_WIPE', 1: 'BCM1_WIPERSPEED_42_TIMES_MIN', 2: 'BCM1_WIPERSPEED_45_TIMES_MIN', 3: 'BCM1_WIPERSPEED_48_TIMES_MIN', 4: 'BCM1_WIPERSPEED_51_TIMES_MIN', 5: 'BCM1_WIPERSPEED_54_TIMES_MIN', 6: 'BCM1_WIPERSPEED_57_TIMES_MIN', 7: 'BCM1_WIPERSPEED_60_TIMES_MIN'}, 'is_signed_var': False, 'len': 3, 'name': 'bcm1_wiperspeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'signal_type': 'speed', 'type': 'enum'}
Bcm1_2a0::Bcm1_wiperspeedType Bcm12a0::bcm1_wiperspeed(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(5, 3);

  Bcm1_2a0::Bcm1_wiperspeedType ret =  static_cast<Bcm1_2a0::Bcm1_wiperspeedType>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': 'The signal indicates the status of position light.', 'enum': {0: 'BCM1_POSITIONLIGHTST_OFF', 1: 'BCM1_POSITIONLIGHTST_ON', 2: 'BCM1_POSITIONLIGHTST_RESERVED', 3: 'BCM1_POSITIONLIGHTST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_positionlightst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_positionlightstType Bcm12a0::bcm1_positionlightst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 2);

  Bcm1_2a0::Bcm1_positionlightstType ret =  static_cast<Bcm1_2a0::Bcm1_positionlightstType>(x);
  return ret;
}

// config detail: {'bit': 50, 'description': 'Fold status of right mirror', 'enum': {0: 'BCM1_MIRRORFOLDST_FR_UNFOLD', 1: 'BCM1_MIRRORFOLDST_FR_FOLD', 2: 'BCM1_MIRRORFOLDST_FR_RESERVED', 3: 'BCM1_MIRRORFOLDST_FR_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_mirrorfoldst_fr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_mirrorfoldst_frType Bcm12a0::bcm1_mirrorfoldst_fr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(2, 2);

  Bcm1_2a0::Bcm1_mirrorfoldst_frType ret =  static_cast<Bcm1_2a0::Bcm1_mirrorfoldst_frType>(x);
  return ret;
}

// config detail: {'bit': 48, 'description': 'Fold status of left mirror', 'enum': {0: 'BCM1_MIRRORFOLDST_FL_UNFOLD', 1: 'BCM1_MIRRORFOLDST_FL_FOLD', 2: 'BCM1_MIRRORFOLDST_FL_RESERVED', 3: 'BCM1_MIRRORFOLDST_FL_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_mirrorfoldst_fl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_mirrorfoldst_flType Bcm12a0::bcm1_mirrorfoldst_fl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 2);

  Bcm1_2a0::Bcm1_mirrorfoldst_flType ret =  static_cast<Bcm1_2a0::Bcm1_mirrorfoldst_flType>(x);
  return ret;
}

// config detail: {'bit': 52, 'description': 'The signal is sent to indicate the Driver Seat Belt is buckled or Unbuckled.', 'enum': {0: 'BCM1_DRIVERSIDEBUCKLE_UNBUCKLED', 1: 'BCM1_DRIVERSIDEBUCKLE_BUCKLED', 2: 'BCM1_DRIVERSIDEBUCKLE_RESERVED', 3: 'BCM1_DRIVERSIDEBUCKLE_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_driversidebuckle', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_driversidebuckleType Bcm12a0::bcm1_driversidebuckle(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(4, 2);

  Bcm1_2a0::Bcm1_driversidebuckleType ret =  static_cast<Bcm1_2a0::Bcm1_driversidebuckleType>(x);
  return ret;
}

// config detail: {'bit': 34, 'description': 'The signal indicates front wiper status.', 'enum': {0: 'BCM1_WIPERSTATUS_OFF', 1: 'BCM1_WIPERSTATUS_TIP', 2: 'BCM1_WIPERSTATUS_INTERVAL_OR_AUTO_LEVER', 3: 'BCM1_WIPERSTATUS_LOW_SPEED', 4: 'BCM1_WIPERSTATUS_HIGH_SPEED', 5: 'BCM1_WIPERSTATUS_RESERVED', 6: 'BCM1_WIPERSTATUS_RESERVED', 7: 'BCM1_WIPERSTATUS_RESERVED'}, 'is_signed_var': False, 'len': 3, 'name': 'bcm1_wiperstatus', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_wiperstatusType Bcm12a0::bcm1_wiperstatus(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(2, 3);

  Bcm1_2a0::Bcm1_wiperstatusType ret =  static_cast<Bcm1_2a0::Bcm1_wiperstatusType>(x);
  return ret;
}

// config detail: {'bit': 21, 'description': 'This signal indicates luggage door status', 'enum': {0: 'BCM1_LUGGAGEDOORST_CLOSE', 1: 'BCM1_LUGGAGEDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm1_luggagedoorst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_luggagedoorstType Bcm12a0::bcm1_luggagedoorst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(5, 1);

  Bcm1_2a0::Bcm1_luggagedoorstType ret =  static_cast<Bcm1_2a0::Bcm1_luggagedoorstType>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': 'The signal  indicates the status of low beam indicator.', 'enum': {0: 'BCM1_LOWBEAMST_OFF', 1: 'BCM1_LOWBEAMST_ON', 2: 'BCM1_LOWBEAMST_RESERVED', 3: 'BCM1_LOWBEAMST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_lowbeamst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_lowbeamstType Bcm12a0::bcm1_lowbeamst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(4, 2);

  Bcm1_2a0::Bcm1_lowbeamstType ret =  static_cast<Bcm1_2a0::Bcm1_lowbeamstType>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': 'The signal  indicates the status of high beam indicator.', 'enum': {0: 'BCM1_HIGHBEAMST_OFF', 1: 'BCM1_HIGHBEAMST_ON', 2: 'BCM1_HIGHBEAMST_RESERVED', 3: 'BCM1_HIGHBEAMST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_highbeamst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_highbeamstType Bcm12a0::bcm1_highbeamst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(6, 2);

  Bcm1_2a0::Bcm1_highbeamstType ret =  static_cast<Bcm1_2a0::Bcm1_highbeamstType>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': 'This signal shows engine hood status.', 'enum': {0: 'BCM1_ENGHOODST_CLOSE', 1: 'BCM1_ENGHOODST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm1_enghoodst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_enghoodstType Bcm12a0::bcm1_enghoodst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(4, 1);

  Bcm1_2a0::Bcm1_enghoodstType ret =  static_cast<Bcm1_2a0::Bcm1_enghoodstType>(x);
  return ret;
}

// config detail: {'bit': 14, 'description': 'This signal indicates the lock state of RR door.', 'enum': {0: 'BCM1_RRDOORLOCKST_LOCK', 1: 'BCM1_RRDOORLOCKST_UNLOCK', 2: 'BCM1_RRDOORLOCKST_RESERVED', 3: 'BCM1_RRDOORLOCKST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_rrdoorlockst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_rrdoorlockstType Bcm12a0::bcm1_rrdoorlockst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(6, 2);

  Bcm1_2a0::Bcm1_rrdoorlockstType ret =  static_cast<Bcm1_2a0::Bcm1_rrdoorlockstType>(x);
  return ret;
}

// config detail: {'bit': 19, 'description': 'This signal indicates the state of RR door.', 'enum': {0: 'BCM1_RRDOORST_CLOSE', 1: 'BCM1_RRDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm1_rrdoorst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_rrdoorstType Bcm12a0::bcm1_rrdoorst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(3, 1);

  Bcm1_2a0::Bcm1_rrdoorstType ret =  static_cast<Bcm1_2a0::Bcm1_rrdoorstType>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': 'This signal indicates the lock state of RL door.', 'enum': {0: 'BCM1_RLDOORLOCKST_LOCK', 1: 'BCM1_RLDOORLOCKST_UNLOCK', 2: 'BCM1_RLDOORLOCKST_RESERVED', 3: 'BCM1_RLDOORLOCKST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_rldoorlockst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_rldoorlockstType Bcm12a0::bcm1_rldoorlockst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(4, 2);

  Bcm1_2a0::Bcm1_rldoorlockstType ret =  static_cast<Bcm1_2a0::Bcm1_rldoorlockstType>(x);
  return ret;
}

// config detail: {'bit': 18, 'description': 'This signal indicates the state of RL door.', 'enum': {0: 'BCM1_RLDOORST_CLOSE', 1: 'BCM1_RLDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm1_rldoorst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_rldoorstType Bcm12a0::bcm1_rldoorst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(2, 1);

  Bcm1_2a0::Bcm1_rldoorstType ret =  static_cast<Bcm1_2a0::Bcm1_rldoorstType>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': 'This signal indicates the lock state of passenger door.', 'enum': {0: 'BCM1_PASSENGERDOORLOCKST_LOCK', 1: 'BCM1_PASSENGERDOORLOCKST_UNLOCK', 2: 'BCM1_PASSENGERDOORLOCKST_RESERVED', 3: 'BCM1_PASSENGERDOORLOCKST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_passengerdoorlockst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_passengerdoorlockstType Bcm12a0::bcm1_passengerdoorlockst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(2, 2);

  Bcm1_2a0::Bcm1_passengerdoorlockstType ret =  static_cast<Bcm1_2a0::Bcm1_passengerdoorlockstType>(x);
  return ret;
}

// config detail: {'bit': 17, 'description': 'This signal indicates the state of passenger door.', 'enum': {0: 'BCM1_PASSENGERDOORST_CLOSE', 1: 'BCM1_PASSENGERDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm1_passengerdoorst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_passengerdoorstType Bcm12a0::bcm1_passengerdoorst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(1, 1);

  Bcm1_2a0::Bcm1_passengerdoorstType ret =  static_cast<Bcm1_2a0::Bcm1_passengerdoorstType>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': 'This signal indicates the lock state of driver door.', 'enum': {0: 'BCM1_DRIVERDOORLOCKST_LOCK', 1: 'BCM1_DRIVERDOORLOCKST_UNLOCK', 2: 'BCM1_DRIVERDOORLOCKST_RESERVED', 3: 'BCM1_DRIVERDOORLOCKST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_driverdoorlockst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_driverdoorlockstType Bcm12a0::bcm1_driverdoorlockst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 2);

  Bcm1_2a0::Bcm1_driverdoorlockstType ret =  static_cast<Bcm1_2a0::Bcm1_driverdoorlockstType>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': 'This signal indicates the state of driver door.', 'enum': {0: 'BCM1_DRIVERDOORST_CLOSE', 1: 'BCM1_DRIVERDOORST_OPEN'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm1_driverdoorst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_driverdoorstType Bcm12a0::bcm1_driverdoorst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 1);

  Bcm1_2a0::Bcm1_driverdoorstType ret =  static_cast<Bcm1_2a0::Bcm1_driverdoorstType>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': 'The Livecounter is used to check the signal consistency of the messages', 'is_signed_var': False, 'len': 4, 'name': 'bcm1_livecounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': 'count', 'precision': 1.0, 'type': 'int'}
int Bcm12a0::bcm1_livecounter(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(4, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 0, 'description': 'The checksum is used to check whether the data transmission errors', 'is_signed_var': False, 'len': 8, 'name': 'bcm1_checksum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'check', 'precision': 1.0, 'type': 'int'}
int Bcm12a0::bcm1_checksum(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 24, 'description': 'The signal indicates the driving status of the turn light.', 'enum': {0: 'BCM1_STEERINGLIGHTST_OFF', 1: 'BCM1_STEERINGLIGHTST_LEFT_ON', 2: 'BCM1_STEERINGLIGHTST_RIGHT_ON', 3: 'BCM1_STEERINGLIGHTST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_steeringlightst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_steeringlightstType Bcm12a0::bcm1_steeringlightst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 2);

  Bcm1_2a0::Bcm1_steeringlightstType ret =  static_cast<Bcm1_2a0::Bcm1_steeringlightstType>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': 'The signal indicates Indicates the Hazard Warning is active or not', 'enum': {0: 'BCM1_HAZARDLIGHTST_OFF', 1: 'BCM1_HAZARDLIGHTST_ON', 2: 'BCM1_HAZARDLIGHTST_RESERVED', 3: 'BCM1_HAZARDLIGHTST_RESERVED'}, 'is_signed_var': False, 'len': 2, 'name': 'bcm1_hazardlightst', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
Bcm1_2a0::Bcm1_hazardlightstType Bcm12a0::bcm1_hazardlightst(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(2, 2);

  Bcm1_2a0::Bcm1_hazardlightstType ret =  static_cast<Bcm1_2a0::Bcm1_hazardlightstType>(x);
  return ret;
}
}  // namespace jt
}  // namespace canbus
}  // namespace apollo
