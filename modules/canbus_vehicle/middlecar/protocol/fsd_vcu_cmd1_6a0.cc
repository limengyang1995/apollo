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

#include "modules/canbus_vehicle/middlecar/protocol/fsd_vcu_cmd1_6a0.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace middlecar {

using ::apollo::drivers::canbus::Byte;

const int32_t Fsdvcucmd16a0::ID = 0x6A0;

// public
Fsdvcucmd16a0::Fsdvcucmd16a0() {
    Reset();
}

uint32_t Fsdvcucmd16a0::GetPeriod() const {
    // TODO(All) : modify every protocol's period manually
    static const uint32_t PERIOD = 20 * 1000;
    return PERIOD;
}

void Fsdvcucmd16a0::Parse(const std::uint8_t* bytes, int32_t length, Middlecar* chassis) const {
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_tarvehrearangle(fsd_vcu_tarvehrearangle(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_brakepec(fsd_vcu_brakepec(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_cmdsource(fsd_vcu_cmdsource(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_specialmode(fsd_vcu_specialmode(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_steermode(fsd_vcu_steermode(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_tarvehspeed(fsd_vcu_tarvehspeed(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_tarvehfrontangle(fsd_vcu_tarvehfrontangle(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_maxvehspeedlmt(fsd_vcu_maxvehspeedlmt(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_emergstop(fsd_vcu_emergstop(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_targear(fsd_vcu_targear(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_park(fsd_vcu_park(bytes, length));
    chassis->mutable_fsd_vcu_cmd1_6a0()->set_fsd_vcu_roulingcounter(fsd_vcu_roulingcounter(bytes, length));
}

void Fsdvcucmd16a0::UpdateData_Heartbeat(uint8_t* data) {
    // TODO(All) : you should add the heartbeat manually
}

void Fsdvcucmd16a0::UpdateData(uint8_t* data) {
    set_p_fsd_vcu_tarvehrearangle(data, fsd_vcu_tarvehrearangle_);
    set_p_fsd_vcu_brakepec(data, fsd_vcu_brakepec_);
    set_p_fsd_vcu_cmdsource(data, fsd_vcu_cmdsource_);
    set_p_fsd_vcu_specialmode(data, fsd_vcu_specialmode_);
    set_p_fsd_vcu_steermode(data, fsd_vcu_steermode_);
    set_p_fsd_vcu_tarvehspeed(data, fsd_vcu_tarvehspeed_);
    set_p_fsd_vcu_tarvehfrontangle(data, fsd_vcu_tarvehfrontangle_);
    set_p_fsd_vcu_maxvehspeedlmt(data, fsd_vcu_maxvehspeedlmt_);
    set_p_fsd_vcu_emergstop(data, fsd_vcu_emergstop_);
    set_p_fsd_vcu_targear(data, fsd_vcu_targear_);
    set_p_fsd_vcu_park(data, fsd_vcu_park_);
    set_p_fsd_vcu_roulingcounter(data, fsd_vcu_roulingcounter_);
}

void Fsdvcucmd16a0::Reset() {
    // TODO(All) :  you should check this manually
    fsd_vcu_tarvehrearangle_ = 0;
    fsd_vcu_brakepec_ = 0;
    fsd_vcu_cmdsource_ = Fsd_vcu_cmd1_6a0::FSD_VCU_CMDSOURCE_NOT_SELECTED;
    fsd_vcu_specialmode_ = Fsd_vcu_cmd1_6a0::FSD_VCU_SPECIALMODE_BENCH_MODE;
    fsd_vcu_steermode_ = Fsd_vcu_cmd1_6a0::FSD_VCU_STEERMODE_FRONT_AXLE_STEERING;
    fsd_vcu_tarvehspeed_ = 0.0;
    fsd_vcu_tarvehfrontangle_ = 0;
    fsd_vcu_maxvehspeedlmt_ = 0;
    fsd_vcu_emergstop_ = Fsd_vcu_cmd1_6a0::FSD_VCU_EMERGSTOP_NO_EMERGENCY_STOP;
    fsd_vcu_targear_ = Fsd_vcu_cmd1_6a0::FSD_VCU_TARGEAR_N;
    fsd_vcu_park_ = Fsd_vcu_cmd1_6a0::FSD_VCU_PARK_PARKING;
    fsd_vcu_roulingcounter_ = 0;
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_tarvehrearangle(int fsd_vcu_tarvehrearangle) {
    fsd_vcu_tarvehrearangle_ = fsd_vcu_tarvehrearangle;
    return this;
}

// config detail: {'bit': 41, 'description': 'Rear_axle_virtual_steering_wheel_angle', 'is_signed_var': False, 'len':
// 11, 'name': 'FSD_VCU_TarVehRearAngle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]',
// 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Fsdvcucmd16a0::set_p_fsd_vcu_tarvehrearangle(uint8_t* data, int fsd_vcu_tarvehrearangle) {
    fsd_vcu_tarvehrearangle = ProtocolData::BoundedValue(-800, 1247, fsd_vcu_tarvehrearangle);
    int x = (fsd_vcu_tarvehrearangle - -800.000000);
    uint8_t t = 0;

    t = x & 0x7F;
    Byte to_set0(data + 5);
    to_set0.set_value(t, 1, 7);
    x >>= 7;

    t = x & 0xF;
    Byte to_set1(data + 6);
    to_set1.set_value(t, 0, 4);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_brakepec(int fsd_vcu_brakepec) {
    fsd_vcu_brakepec_ = fsd_vcu_brakepec;
    return this;
}

// config detail: {'bit': 52, 'description': 'Brake_opening_degree', 'is_signed_var': False, 'len': 8, 'name':
// 'FSD_VCU_BrakePec', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '',
// 'precision': 1.0, 'type': 'int'}
void Fsdvcucmd16a0::set_p_fsd_vcu_brakepec(uint8_t* data, int fsd_vcu_brakepec) {
    fsd_vcu_brakepec = ProtocolData::BoundedValue(0, 100, fsd_vcu_brakepec);
    int x = fsd_vcu_brakepec;
    uint8_t t = 0;

    t = x & 0xF;
    Byte to_set0(data + 6);
    to_set0.set_value(t, 4, 4);
    x >>= 4;

    t = x & 0xF;
    Byte to_set1(data + 7);
    to_set1.set_value(t, 0, 4);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_cmdsource(Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType fsd_vcu_cmdsource) {
    fsd_vcu_cmdsource_ = fsd_vcu_cmdsource;
    return this;
}

// config detail: {'bit': 0, 'description': 'CmdSource', 'enum': {0: 'FSD_VCU_CMDSOURCE_NOT_SELECTED', 1:
// 'FSD_VCU_CMDSOURCE_FSD', 2: 'FSD_VCU_CMDSOURCE_CLOSE_RANGE_REMOTE_CONTROL'}, 'is_signed_var': False, 'len': 2,
// 'name': 'FSD_VCU_CmdSource', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '',
// 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd16a0::set_p_fsd_vcu_cmdsource(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType fsd_vcu_cmdsource) {
    int x = fsd_vcu_cmdsource;

    Byte to_set(data + 0);
    to_set.set_value(x, 0, 2);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_specialmode(Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType fsd_vcu_specialmode) {
    fsd_vcu_specialmode_ = fsd_vcu_specialmode;
    return this;
}

// config detail: {'bit': 2, 'description': 'Special_Mode', 'enum': {0: 'FSD_VCU_SPECIALMODE_BENCH_MODE', 1:
// 'FSD_VCU_SPECIALMODE_ECONOMIC_MODEL', 2: 'FSD_VCU_SPECIALMODE_STANDARD_MODE', 3: 'FSD_VCU_SPECIALMODE_SAND_MODE', 4:
// 'FSD_VCU_SPECIALMODE_RAMP_MODE', 5: 'FSD_VCU_SPECIALMODE_MUD_MODE'}, 'is_signed_var': False, 'len': 4, 'name':
// 'FSD_VCU_SpecialMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '',
// 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd16a0::set_p_fsd_vcu_specialmode(
        uint8_t* data,
        Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType fsd_vcu_specialmode) {
    int x = fsd_vcu_specialmode;

    Byte to_set(data + 0);
    to_set.set_value(x, 2, 4);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_steermode(Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType fsd_vcu_steermode) {
    fsd_vcu_steermode_ = fsd_vcu_steermode;
    return this;
}

// config detail: {'bit': 6, 'description': 'steering_mode', 'enum': {0: 'FSD_VCU_STEERMODE_FRONT_AXLE_STEERING', 1:
// 'FSD_VCU_STEERMODE_FULL_BRIDGE_STEERING', 2: 'FSD_VCU_STEERMODE_REAR_AXLE_STEERING'}, 'is_signed_var': False, 'len':
// 2, 'name': 'FSD_VCU_SteerMode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '',
// 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd16a0::set_p_fsd_vcu_steermode(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType fsd_vcu_steermode) {
    int x = fsd_vcu_steermode;

    Byte to_set(data + 0);
    to_set.set_value(x, 6, 2);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_tarvehspeed(double fsd_vcu_tarvehspeed) {
    fsd_vcu_tarvehspeed_ = fsd_vcu_tarvehspeed;
    return this;
}

// config detail: {'bit': 13, 'description': 'Target_speed', 'is_signed_var': False, 'len': 10, 'name':
// 'FSD_VCU_TarVehSpeed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision':
// 0.1, 'signal_type': 'speed', 'type': 'double'}
void Fsdvcucmd16a0::set_p_fsd_vcu_tarvehspeed(uint8_t* data, double fsd_vcu_tarvehspeed) {
    fsd_vcu_tarvehspeed = ProtocolData::BoundedValue(0.0, 40.0, fsd_vcu_tarvehspeed);
    int x = fsd_vcu_tarvehspeed / 0.100000;
    uint8_t t = 0;

    t = x & 0x7;
    Byte to_set0(data + 1);
    to_set0.set_value(t, 5, 3);
    x >>= 3;

    t = x & 0x7F;
    Byte to_set1(data + 2);
    to_set1.set_value(t, 0, 7);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_tarvehfrontangle(int fsd_vcu_tarvehfrontangle) {
    fsd_vcu_tarvehfrontangle_ = fsd_vcu_tarvehfrontangle;
    return this;
}

// config detail: {'bit': 30, 'description': 'Front_axle_virtual_steering_wheel_angle', 'is_signed_var': False, 'len':
// 11, 'name': 'FSD_VCU_TarVehFrontAngle', 'offset': -800.0, 'order': 'intel', 'physical_range': '[-800|1247]',
// 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Fsdvcucmd16a0::set_p_fsd_vcu_tarvehfrontangle(uint8_t* data, int fsd_vcu_tarvehfrontangle) {
    fsd_vcu_tarvehfrontangle = ProtocolData::BoundedValue(-800, 1247, fsd_vcu_tarvehfrontangle);
    int x = (fsd_vcu_tarvehfrontangle - -800.000000);
    uint8_t t = 0;

    t = x & 0x3;
    Byte to_set0(data + 3);
    to_set0.set_value(t, 6, 2);
    x >>= 2;

    t = x & 0xFF;
    Byte to_set1(data + 4);
    to_set1.set_value(t, 0, 8);
    x >>= 8;

    t = x & 0x1;
    Byte to_set2(data + 5);
    to_set2.set_value(t, 0, 1);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_maxvehspeedlmt(int fsd_vcu_maxvehspeedlmt) {
    fsd_vcu_maxvehspeedlmt_ = fsd_vcu_maxvehspeedlmt;
    return this;
}

// config detail: {'bit': 23, 'description': 'Maximum_speed_limit', 'is_signed_var': False, 'len': 7, 'name':
// 'FSD_VCU_MaxVehSpeedLmt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|127]', 'physical_unit': '',
// 'precision': 1.0, 'signal_type': 'speed', 'type': 'int'}
void Fsdvcucmd16a0::set_p_fsd_vcu_maxvehspeedlmt(uint8_t* data, int fsd_vcu_maxvehspeedlmt) {
    fsd_vcu_maxvehspeedlmt = ProtocolData::BoundedValue(0, 127, fsd_vcu_maxvehspeedlmt);
    int x = fsd_vcu_maxvehspeedlmt;
    uint8_t t = 0;

    t = x & 0x1;
    Byte to_set0(data + 2);
    to_set0.set_value(t, 7, 1);
    x >>= 1;

    t = x & 0x3F;
    Byte to_set1(data + 3);
    to_set1.set_value(t, 0, 6);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_emergstop(Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType fsd_vcu_emergstop) {
    fsd_vcu_emergstop_ = fsd_vcu_emergstop;
    return this;
}

// config detail: {'bit': 8, 'description': 'Emergency_stop', 'enum': {0: 'FSD_VCU_EMERGSTOP_NO_EMERGENCY_STOP', 1:
// 'FSD_VCU_EMERGSTOP_EMERGENCY_STOP'}, 'is_signed_var': False, 'len': 1, 'name': 'FSD_VCU_EmergStop', 'offset': 0.0,
// 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd16a0::set_p_fsd_vcu_emergstop(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType fsd_vcu_emergstop) {
    int x = fsd_vcu_emergstop;

    Byte to_set(data + 1);
    to_set.set_value(x, 0, 1);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_targear(Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType fsd_vcu_targear) {
    fsd_vcu_targear_ = fsd_vcu_targear;
    return this;
}

// config detail: {'bit': 9, 'description': 'Target_gear', 'enum': {0: 'FSD_VCU_TARGEAR_N', 1: 'FSD_VCU_TARGEAR_D', 2:
// 'FSD_VCU_TARGEAR_R'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_TarGear', 'offset': 0.0, 'order': 'intel',
// 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd16a0::set_p_fsd_vcu_targear(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType fsd_vcu_targear) {
    int x = fsd_vcu_targear;

    Byte to_set(data + 1);
    to_set.set_value(x, 1, 2);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_park(Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType fsd_vcu_park) {
    fsd_vcu_park_ = fsd_vcu_park;
    return this;
}

// config detail: {'bit': 11, 'description': 'parking', 'enum': {0: 'FSD_VCU_PARK_PARKING', 1:
// 'FSD_VCU_PARK_RELEASE_PARKING'}, 'is_signed_var': False, 'len': 2, 'name': 'FSD_VCU_Park', 'offset': 0.0, 'order':
// 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Fsdvcucmd16a0::set_p_fsd_vcu_park(uint8_t* data, Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType fsd_vcu_park) {
    int x = fsd_vcu_park;

    Byte to_set(data + 1);
    to_set.set_value(x, 3, 2);
}

Fsdvcucmd16a0* Fsdvcucmd16a0::set_fsd_vcu_roulingcounter(int fsd_vcu_roulingcounter) {
    fsd_vcu_roulingcounter_ = fsd_vcu_roulingcounter;
    return this;
}

// config detail: {'bit': 60, 'description': 'Life_signals', 'is_signed_var': False, 'len': 4, 'name':
// 'FSD_VCU_RoulingCounter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '',
// 'precision': 1.0, 'type': 'int'}
void Fsdvcucmd16a0::set_p_fsd_vcu_roulingcounter(uint8_t* data, int fsd_vcu_roulingcounter) {
    fsd_vcu_roulingcounter = ProtocolData::BoundedValue(0, 15, fsd_vcu_roulingcounter);
    int x = fsd_vcu_roulingcounter;

    Byte to_set(data + 7);
    to_set.set_value(x, 4, 4);
}

int Fsdvcucmd16a0::fsd_vcu_tarvehrearangle(const std::uint8_t* bytes, int32_t length) const {
    Byte t0(bytes + 6);
    int32_t x = t0.get_byte(0, 4);

    Byte t1(bytes + 5);
    int32_t t = t1.get_byte(1, 7);
    x <<= 7;
    x |= t;

    int ret = x + -800.000000;
    return ret;
}

int Fsdvcucmd16a0::fsd_vcu_brakepec(const std::uint8_t* bytes, int32_t length) const {
    Byte t0(bytes + 7);
    int32_t x = t0.get_byte(0, 4);

    Byte t1(bytes + 6);
    int32_t t = t1.get_byte(4, 4);
    x <<= 4;
    x |= t;

    int ret = x;
    return ret;
}

Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType Fsdvcucmd16a0::fsd_vcu_cmdsource(const std::uint8_t* bytes, int32_t length)
        const {
    Byte t0(bytes + 0);
    int32_t x = t0.get_byte(0, 2);

    Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType ret = static_cast<Fsd_vcu_cmd1_6a0::Fsd_vcu_cmdsourceType>(x);
    return ret;
}

Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType Fsdvcucmd16a0::fsd_vcu_specialmode(const std::uint8_t* bytes, int32_t length)
        const {
    Byte t0(bytes + 0);
    int32_t x = t0.get_byte(2, 4);

    Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType ret = static_cast<Fsd_vcu_cmd1_6a0::Fsd_vcu_specialmodeType>(x);
    return ret;
}

Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType Fsdvcucmd16a0::fsd_vcu_steermode(const std::uint8_t* bytes, int32_t length)
        const {
    Byte t0(bytes + 0);
    int32_t x = t0.get_byte(6, 2);

    Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType ret = static_cast<Fsd_vcu_cmd1_6a0::Fsd_vcu_steermodeType>(x);
    return ret;
}

double Fsdvcucmd16a0::fsd_vcu_tarvehspeed(const std::uint8_t* bytes, int32_t length) const {
    Byte t0(bytes + 2);
    int32_t x = t0.get_byte(0, 7);

    Byte t1(bytes + 1);
    int32_t t = t1.get_byte(5, 3);
    x <<= 3;
    x |= t;

    double ret = x * 0.100000;
    return ret;
}

int Fsdvcucmd16a0::fsd_vcu_tarvehfrontangle(const std::uint8_t* bytes, int32_t length) const {
    Byte t0(bytes + 5);
    int32_t x = t0.get_byte(0, 1);

    Byte t1(bytes + 4);
    int32_t t = t1.get_byte(0, 8);
    x <<= 8;
    x |= t;

    Byte t2(bytes + 3);
    t = t2.get_byte(6, 2);
    x <<= 2;
    x |= t;

    int ret = x + -800.000000;
    return ret;
}

int Fsdvcucmd16a0::fsd_vcu_maxvehspeedlmt(const std::uint8_t* bytes, int32_t length) const {
    Byte t0(bytes + 3);
    int32_t x = t0.get_byte(0, 6);

    Byte t1(bytes + 2);
    int32_t t = t1.get_byte(7, 1);
    x <<= 1;
    x |= t;

    int ret = x;
    return ret;
}

Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType Fsdvcucmd16a0::fsd_vcu_emergstop(const std::uint8_t* bytes, int32_t length)
        const {
    Byte t0(bytes + 1);
    int32_t x = t0.get_byte(0, 1);

    Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType ret = static_cast<Fsd_vcu_cmd1_6a0::Fsd_vcu_emergstopType>(x);
    return ret;
}

Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType Fsdvcucmd16a0::fsd_vcu_targear(const std::uint8_t* bytes, int32_t length) const {
    Byte t0(bytes + 1);
    int32_t x = t0.get_byte(1, 2);

    Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType ret = static_cast<Fsd_vcu_cmd1_6a0::Fsd_vcu_targearType>(x);
    return ret;
}

Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType Fsdvcucmd16a0::fsd_vcu_park(const std::uint8_t* bytes, int32_t length) const {
    Byte t0(bytes + 1);
    int32_t x = t0.get_byte(3, 2);

    Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType ret = static_cast<Fsd_vcu_cmd1_6a0::Fsd_vcu_parkType>(x);
    return ret;
}

int Fsdvcucmd16a0::fsd_vcu_roulingcounter(const std::uint8_t* bytes, int32_t length) const {
    Byte t0(bytes + 7);
    int32_t x = t0.get_byte(4, 4);

    int ret = x;
    return ret;
}
}  // namespace middlecar
}  // namespace canbus
}  // namespace apollo
