/*
 *  Created by wkx 2025.8.20
*/
#include "eskf.h"
#include "third_party/sophus/Sophus/sophus/so3.hpp"
// #include <g2o/types/slam2d/vertex_se2.h>
// #include <sophus/so3.hpp>

ErrorStateKalmanFilter::ErrorStateKalmanFilter(const ConfigParameters &config_parameters) :
        config_parameters_(config_parameters) {
    earth_rotation_speed_ = config_parameters_.earth_rotation_speed_;
    g_ = Eigen::Vector3d(0.0, 0.0, -config_parameters_.earth_gravity_);

    SetCovarianceP(
            config_parameters_.position_error_prior_std_,
            config_parameters_.velocity_error_prior_std_,
            config_parameters_.rotation_error_prior_std_,
            config_parameters_.gyro_bias_error_prior_std_,
            config_parameters_.accelerometer_bias_error_prior_std_);

    SetCovarianceR(
            config_parameters_.gps_position_x_std_,
            config_parameters_.gps_position_y_std_,
            config_parameters_.gps_position_z_std_);

    SetCovarianceVel(
            config_parameters_.vel_x_std_,
            config_parameters_.vel_y_std_,
            config_parameters_.vel_z_std_

    );       
    SetCovariancePoseQ(
        config_parameters_.vel_x_std_,
        config_parameters_.vel_y_std_,
        config_parameters_.vel_z_std_,
        config_parameters_.vel_x_std_,
        config_parameters_.vel_y_std_,
        config_parameters_.vel_z_std_
    ); 
    SetCovariancePoseQVel(config_parameters_.gps_position_x_std_,
                        config_parameters_.gps_position_x_std_,
                        config_parameters_.gps_position_x_std_,
                        config_parameters_.gnss_q_x_std_,
                        config_parameters_.gnss_q_y_std_,
                        config_parameters_.gnss_q_z_std_,
                        config_parameters_.gnss_vel_x_std_,
                        config_parameters_.gnss_vel_y_std_,
                        config_parameters_.gnss_vel_z_std_
                        );

    SetCovarianceQ(config_parameters_.gyro_noise_std_, config_parameters_.accelerometer_noise_std_);

    X_.setZero();
    F_.setZero();
    C_.setIdentity();

    //位置观测方程
    G_.block<3, 3>(INDEX_MEASUREMENT_POSI, INDEX_MEASUREMENT_POSI) = Eigen::Matrix3d::Identity();

    // 速度观测方程
    GVel_.block<3, 3>(INDEX_MEASUREMENT_POSI, INDEX_STATE_VEL) = Eigen::Matrix3d::Identity();

    // 位置 旋转的观测方程
    GPoseQ_.block<3, 3>(INDEX_MEASUREMENT_POSI, INDEX_MEASUREMENT_POSI) = Eigen::Matrix3d::Identity();
    GPoseQ_.block<3, 3>(3, INDEX_STATE_ORI) = Eigen::Matrix3d::Identity();

    // 位置 速度 旋转的观测方程
    GPoseVel_.block<3, 3>(0, INDEX_MEASUREMENT_POSI) = Eigen::Matrix3d::Identity();
    GPoseVel_.block<3, 3>(3, INDEX_STATE_VEL) = Eigen::Matrix3d::Identity();
    GPoseVel_.block<3, 3>(6, INDEX_STATE_ORI) = Eigen::Matrix3d::Identity();

    Eigen::Vector3d f_n(1.0, 2.0, 3.0);
    Eigen::Matrix3d f_n_hat = Sophus::SO3<double>::hat(f_n).matrix();
    
    std::cout << "Original vector f_n:\n" << f_n << "\n\n";
    std::cout << "Hat operation result (as matrix):\n" << f_n_hat << "\n\n";

}

void ErrorStateKalmanFilter::SetCovarianceQ(double gyro_noise, double accel_noise) {
    Q_.setZero();
    Q_.block<3, 3>(0, 0) = Eigen::Matrix3d::Identity() * gyro_noise * gyro_noise;
    Q_.block<3, 3>(3, 3) = Eigen::Matrix3d::Identity() * accel_noise * accel_noise;
}

void ErrorStateKalmanFilter::SetCovarianceR(double position_x_std, double position_y_std, double position_z_std) {
    R_.setZero();
    R_(0, 0) = position_x_std * position_x_std;
    R_(1, 1) = position_y_std * position_y_std;
    R_(2, 2) = position_z_std * position_z_std;
}

void ErrorStateKalmanFilter::SetCovarianceVel(double vel_x_std, double vel_y_std, double vel_z_std) {
    RVel_.setZero();
    RVel_(0, 0) = vel_x_std * vel_x_std;
    RVel_(1, 1) = vel_y_std * vel_y_std;
    RVel_(2, 2) = vel_z_std * vel_z_std;
}

void ErrorStateKalmanFilter::SetCovariancePoseQ(double x_std, double y_std, double z_std, double q_x_std, double q_y_std, double q_z_std) {
    RPoseQ_.setZero();
    RPoseQ_(0, 0) = x_std * x_std;
    RPoseQ_(1, 1) = y_std * y_std;
    RPoseQ_(2, 2) = z_std * z_std;
    RPoseQ_(3, 3) = q_x_std * q_x_std;
    RPoseQ_(4, 4) = q_y_std * q_y_std;
    RPoseQ_(5, 5) = q_z_std * q_z_std;
}

void ErrorStateKalmanFilter::SetCovariancePoseQVel(double x_std, double y_std, double z_std, 
                                                double q_x_std, double q_y_std, double q_z_std,
                                                double x_vel, double y_vel, double z_vel) {
    RPoseQVel_.setZero();
    RPoseQVel_(0, 0) = x_std * x_std;
    RPoseQVel_(1, 1) = y_std * y_std;
    RPoseQVel_(2, 2) = z_std * z_std;
    RPoseQVel_(3, 3) = q_x_std * q_x_std;
    RPoseQVel_(4, 4) = q_y_std * q_y_std;
    RPoseQVel_(5, 5) = q_z_std * q_z_std;
    RPoseQVel_(6, 6) = x_vel * x_vel;
    RPoseQVel_(7, 7) = y_vel * y_vel;
    RPoseQVel_(8, 8) = z_vel * z_vel;
}

void ErrorStateKalmanFilter::SetCovarianceP(
        double posi_noise,
        double velocity_noise,
        double ori_noise,
        double gyro_noise,
        double accel_noise) {
    P_.setZero();
    P_.block<3, 3>(INDEX_STATE_POSI, INDEX_STATE_POSI) = Eigen::Matrix3d::Identity() * posi_noise * posi_noise;
    P_.block<3, 3>(INDEX_STATE_VEL, INDEX_STATE_VEL) = Eigen::Matrix3d::Identity() * velocity_noise * velocity_noise;
    P_.block<3, 3>(INDEX_STATE_ORI, INDEX_STATE_ORI) = Eigen::Matrix3d::Identity() * ori_noise * ori_noise;
    P_.block<3, 3>(INDEX_STATE_GYRO_BIAS, INDEX_STATE_GYRO_BIAS)
            = Eigen::Matrix3d::Identity() * gyro_noise * gyro_noise;
    P_.block<3, 3>(INDEX_STATE_ACC_BIAS, INDEX_STATE_ACC_BIAS)
            = Eigen::Matrix3d::Identity() * accel_noise * accel_noise;
}

bool ErrorStateKalmanFilter::Init(const GPSData &curr_gps_data, const IMUData &curr_imu_data,const Eigen::Quaterniond Q) {
    velocity_ = curr_gps_data.true_velocity;

    // Eigen::Quaterniond Q_init = Eigen::AngleAxisd(0 * kDegree2Radian, Eigen::Vector3d::UnitZ())
    //         * Eigen::AngleAxisd(0 * kDegree2Radian, Eigen::Vector3d::UnitY())
    //         * Eigen::AngleAxisd(0 * kDegree2Radian, Eigen::Vector3d::UnitX());

    pose_.block<3, 3>(0, 0) = Q.toRotationMatrix();
    pose_.block<3, 1>(0, 3) = curr_gps_data.local_position_ned;

    imu_data_buff_.clear();
    imu_data_buff_.push_back(curr_imu_data);

    curr_gps_data_ = curr_gps_data;

    return true;
}

void ErrorStateKalmanFilter::GetFGY(TypeMatrixF &F, TypeMatrixG &G, TypeVectorY &Y) {
    F = Ft_;
    G = G_;
    Y = Y_;
}

// 这块需要写一个速度 correct 函数
bool ErrorStateKalmanFilter::CorrectVel(const Eigen::Vector3d &vel_data) {
    YVel_ = velocity_ - pose_.block<3, 3>(0, 0)*vel_data;
    K_ = P_ * GVel_.transpose() * (GVel_ * P_ * GVel_.transpose() + RVel_).inverse();
    P_ = (TypeMatrixP::Identity() - K_ * GVel_) * P_;
    X_ = X_ + K_ * (YVel_ - GVel_ * X_);
    EliminateErrorVel();
    ResetState();

    return true;

}

// 暂时没时间写旋转的eskf更新
bool ErrorStateKalmanFilter::Correct(const GPSData &curr_gps_data,const Eigen::Quaterniond Q) {
    curr_gps_data_ = curr_gps_data;
    std::cout<<"start Correct!"<<std::endl;
    //旋转直接赋值
    // pose_.block<3, 3>(0, 0) = Q.toRotationMatrix();

    Y_ = curr_gps_data.local_position_ned - pose_.block<3, 1>(0, 3);

    // std::cout << "Y_:" << Y_ << std::endl;
    Rlio_.setZero();
    Rlio_(0, 0) = 0.1 * 0.1;
    Rlio_(1, 1) = 0.1 * 0.1;
    Rlio_(2, 2) = 0.1 * 0.1;

    K_ = P_ * G_.transpose() * (G_ * P_ * G_.transpose() + C_ * Rlio_ * C_.transpose()).inverse();
    // std::cout << "K_:" << K_ << std::endl;

    P_ = (TypeMatrixP::Identity() - K_ * G_) * P_;
    // std::cout << "P_:" << P_ << std::endl;

    X_ = X_ + K_ * (Y_ - G_ * X_);
    // std::cout << "X_:" << X_ << std::endl;

    EliminateError();

    ResetState();

    return true;
}
// 位置加旋转的correct
bool ErrorStateKalmanFilter::CorrectPoseQ(const GPSData &curr_gps_data,const Eigen::Quaterniond Q) {
    curr_gps_data_ = curr_gps_data;
    std::cout<<"start CorrectPoseQ!"<<std::endl;
    Eigen::Matrix3d C_nn_obs = pose_.block<3, 3>(0,0) * Q.toRotationMatrix().transpose();
    YPQ_.block<3, 1>(0,0) = curr_gps_data.local_position_ned - pose_.block<3, 1>(0, 3);
    YPQ_.block<3, 1>(3,0) = Sophus::SO3<double>::vee(Eigen::Matrix3d::Identity() - C_nn_obs);

    // std::cout << "Y_:" << Y_ << std::endl;

    Eigen::MatrixXd K = P_ * GPoseQ_.transpose() * (GPoseQ_ * P_ * GPoseQ_.transpose() + RPoseQ_).inverse();
    // std::cout << "K_:" << K_ << std::endl;

    P_ = (TypeMatrixP::Identity() - K * GPoseQ_) * P_;
    // std::cout << "P_:" << P_ << std::endl;

    X_ = X_ + K * (YPQ_ - GPoseQ_ * X_);
    // std::cout << "X_:" << X_ << std::endl;

    EliminateError();

    ResetState();
    std::cout<<"done CorrectPoseQ!"<<std::endl;

    return true;
}


bool ErrorStateKalmanFilter::CorrectPoseQVel(const GPSData &curr_gps_data,const Eigen::Quaterniond Q){
    // set measurement:
    std::cout<<"start CorrectPoseQVel!"<<std::endl;
    YPQVel_.block<3, 1>(0, 0) = curr_gps_data.local_position_ned - pose_.block<3, 1>(0,3);
    Eigen::Matrix3d C_nn_obs = pose_.block<3, 3>(0,0) * Q.toRotationMatrix().transpose();
    Eigen::Vector3d v_nn_obs = curr_gps_data.velocity - velocity_; 

    YPQVel_.block<3, 1>(3, 0) = v_nn_obs;
    YPQVel_.block<3, 1>(6, 0) = Sophus::SO3<double>::vee(Eigen::Matrix3d::Identity() - C_nn_obs);

    Eigen::MatrixXd K = P_ * GPoseVel_.transpose() * (GPoseVel_ * P_ * GPoseVel_.transpose() + RPoseQVel_).inverse();
    // std::cout << "K_:" << K_ << std::endl;

    P_ = (TypeMatrixP::Identity() - K * GPoseVel_) * P_;
    // std::cout << "P_:" << P_ << std::endl;

    X_ = X_ + K * (YPQVel_ - GPoseVel_ * X_);
    // std::cout << "X_:" << X_ << std::endl;
    EliminateError();
    ResetState();
    return true;

}

bool ErrorStateKalmanFilter::Predict(const IMUData &curr_imu_data) {
    imu_data_buff_.push_back(curr_imu_data);

    Eigen::Vector3d w_in = Eigen::Vector3d::Zero();

    if (config_parameters_.use_earth_model_) {
        w_in = ComputeNavigationFrameAngularVelocity();  // 时刻 m-1 -> m 地球转动引起的导航系转动角速度
    }
    UpdateOdomEstimation(w_in);

    double delta_t = curr_imu_data.time - imu_data_buff_.front().time;
    // std::cout << "delta_t:" << delta_t << std::endl;

    Eigen::Vector3d curr_accel = pose_.block<3, 3>(0, 0) * curr_imu_data.linear_accel;

    UpdateErrorState(delta_t, curr_accel, w_in);

    imu_data_buff_.pop_front();

    return true;
}

void ErrorStateKalmanFilter::UpdateErrorState(double t, const Eigen::Vector3d &accel, const Eigen::Vector3d &w_in_n) {
    Eigen::Matrix3d F_23 = BuildSkewSymmetricMatrix(accel);  // 创建反对称矩阵
    Eigen::Matrix3d F_33 = -BuildSkewSymmetricMatrix(w_in_n);

    F_.block<3, 3>(INDEX_STATE_POSI, INDEX_STATE_VEL) = Eigen::Matrix3d::Identity();
    F_.block<3, 3>(INDEX_STATE_VEL, INDEX_STATE_ORI) = F_23;
    F_.block<3, 3>(INDEX_STATE_ORI, INDEX_STATE_ORI) = F_33;
    F_.block<3, 3>(INDEX_STATE_VEL, INDEX_STATE_ACC_BIAS) = pose_.block<3, 3>(0, 0);
    F_.block<3, 3>(INDEX_STATE_ORI, INDEX_STATE_GYRO_BIAS) = -pose_.block<3, 3>(0, 0);
    B_.block<3, 3>(INDEX_STATE_VEL, 3) = pose_.block<3, 3>(0, 0);
    B_.block<3, 3>(INDEX_STATE_ORI, 0) = -pose_.block<3, 3>(0, 0);

    TypeMatrixF Fk = TypeMatrixF::Identity() + F_ * t;
    TypeMatrixB Bk = B_ * t;

    // 用于可观测性分析
    Ft_ = F_ * t;

    X_ = Fk * X_;
    P_ = Fk * P_ * Fk.transpose() + Bk * Q_ * Bk.transpose();
}

void ErrorStateKalmanFilter::UpdateOdomEstimation(const Eigen::Vector3d &w_in) {
    const auto &last_imu_data = imu_data_buff_.at(0);
    const auto &curr_imu_data = imu_data_buff_.at(1);
    const double delta_t = curr_imu_data.time - last_imu_data.time;

    Eigen::Vector3d delta_rotation = ComputeDeltaRotation(last_imu_data, curr_imu_data);

    const Eigen::Vector3d phi_in = w_in * delta_t;
    const Eigen::AngleAxisd angle_axisd(phi_in.norm(), phi_in.normalized());
    const Eigen::Matrix3d R_nm_nm_1 = angle_axisd.toRotationMatrix().transpose();

    Eigen::Matrix3d curr_R;  // R_n_m m时刻的旋转
    Eigen::Matrix3d last_R;  // C_n_m_1 m-1时刻的旋转
    ComputeOrientation(delta_rotation, R_nm_nm_1, curr_R, last_R);

    Eigen::Vector3d curr_vel;  // 当前时刻导航系下的速度
    Eigen::Vector3d last_vel;  // 上一时刻导航系下的速度
    ComputeVelocity(last_R, curr_R, last_imu_data, curr_imu_data, last_vel, curr_vel);

    ComputePosition(last_R, curr_R, last_vel, curr_vel, last_imu_data, curr_imu_data);
}

Eigen::Vector3d ErrorStateKalmanFilter::ComputeDeltaRotation(const IMUData &imu_data_0, const IMUData &imu_data_1) {
    const double delta_t = imu_data_1.time - imu_data_0.time;

    CHECK_GT(delta_t, 0.0) << "IMU timestamp error";

    const Eigen::Vector3d &unbias_gyro_0 = ComputeUnbiasGyro(imu_data_0.angle_velocity);
    const Eigen::Vector3d &unbias_gyro_1 = ComputeUnbiasGyro(imu_data_1.angle_velocity);

    Eigen::Vector3d delta_theta = 0.5 * (unbias_gyro_0 + unbias_gyro_1) * delta_t;

    return delta_theta;
}

Eigen::Vector3d ErrorStateKalmanFilter::ComputeNavigationFrameAngularVelocity() {
    const double latitude = curr_gps_data_.position_lla.y() * kDegree2Radian;
    const double height = curr_gps_data_.position_lla.z();

    constexpr double f = 1.0 / 298.257223563;  // 椭球扁率

    constexpr double Re = 6378137.0;                     // 椭圆长半轴
    constexpr double Rp = (1.0 - f) * Re;                // 椭圆短半轴
    const double e = std::sqrt(Re * Re - Rp * Rp) / Re;  // 椭圆的偏心率

    const double Rn = Re / std::sqrt(1.0 - e * e * std::sin(latitude) * std::sin(latitude));  // 子午圈主曲率半径
    const double Rm = Re * (1.0 - e * e)
            / std::pow(1.0 - e * e * std::sin(latitude) * std::sin(latitude), 3.0 / 2.0);  // 卯酉圈主曲率半径

    // 由于载体在地球表面运动造成的导航系姿态变化。在导航系下表示
    Eigen::Vector3d w_en_n;
    w_en_n << velocity_[1] / (Rm + height), -velocity_[0] / (Rn + height),
            -velocity_[1] / (Rn + height) * std::tan(latitude);

    Eigen::Vector3d w_ie_n;
    w_ie_n << earth_rotation_speed_ * std::cos(latitude), 0.0, -earth_rotation_speed_ * std::sin(latitude);

    Eigen::Vector3d w_in_n = w_en_n + w_ie_n;

    return w_in_n;
}

void ErrorStateKalmanFilter::ComputeOrientation(
        const Eigen::Vector3d &angular_delta,
        const Eigen::Matrix3d &R_nm_nm_1,
        Eigen::Matrix3d &curr_R,
        Eigen::Matrix3d &last_R) {
    Eigen::AngleAxisd angle_axisd(angular_delta.norm(), angular_delta.normalized());

    last_R = pose_.block<3, 3>(0, 0);
    curr_R = R_nm_nm_1.transpose() * pose_.block<3, 3>(0, 0) * angle_axisd.toRotationMatrix();
    pose_.block<3, 3>(0, 0) = curr_R;
}

void ErrorStateKalmanFilter::ComputeVelocity(
        const Eigen::Matrix3d &R_0,
        const Eigen::Matrix3d &R_1,
        const IMUData &imu_data_0,
        const IMUData &imu_data_1,
        Eigen::Vector3d &last_vel,
        Eigen::Vector3d &curr_vel) {
    double delta_t = imu_data_1.time - imu_data_0.time;

    CHECK_GT(delta_t, 0.0) << "IMU timestamp error";

    Eigen::Vector3d unbias_accel_0 = R_0 * ComputeUnbiasAccel(imu_data_0.linear_accel) - g_;
    Eigen::Vector3d unbias_accel_1 = R_1 * ComputeUnbiasAccel(imu_data_1.linear_accel) - g_;

    last_vel = velocity_;

    // 中值积分
    velocity_ += delta_t * 0.5 * (unbias_accel_0 + unbias_accel_1);

    curr_vel = velocity_;
}

Eigen::Vector3d ErrorStateKalmanFilter::ComputeUnbiasAccel(const Eigen::Vector3d &accel) {
    return accel - accel_bias_;
}

Eigen::Vector3d ErrorStateKalmanFilter::ComputeUnbiasGyro(const Eigen::Vector3d &gyro) {
    return gyro - gyro_bias_;
}

void ErrorStateKalmanFilter::ComputePosition(
        const Eigen::Matrix3d &R_0,
        const Eigen::Matrix3d &R_1,
        const Eigen::Vector3d &last_vel,
        const Eigen::Vector3d &curr_vel,
        const IMUData &imu_data_0,
        const IMUData &imu_data_1) {
    Eigen::Vector3d unbias_accel_0 = R_0 * ComputeUnbiasAccel(imu_data_0.linear_accel) - g_;
    Eigen::Vector3d unbias_accel_1 = R_1 * ComputeUnbiasAccel(imu_data_1.linear_accel) - g_;

    double delta_t = imu_data_1.time - imu_data_0.time;

    pose_.block<3, 1>(0, 3)
            += 0.5 * delta_t * (curr_vel + last_vel) + 0.25 * (unbias_accel_0 + unbias_accel_1) * delta_t * delta_t;
}

void ErrorStateKalmanFilter::ResetState() {
    X_.setZero();
}

void ErrorStateKalmanFilter::EliminateError() {
    // 更新位置pose
    pose_.block<3, 1>(0, 3) = pose_.block<3, 1>(0, 3) + X_.block<3, 1>(INDEX_STATE_POSI, 0);
    
    //kx 这一块需要再研究研究
    Eigen::Matrix3d C_nn = SO3Exp(X_.block<3, 1>(INDEX_STATE_ORI, 0));
    pose_.block<3, 3>(0, 0) = C_nn * pose_.block<3, 3>(0, 0);
    // 更新速度
    velocity_ = velocity_ + X_.block<3, 1>(INDEX_STATE_VEL, 0);

    // 更新角速度噪声
    gyro_bias_ = gyro_bias_ + X_.block<3, 1>(INDEX_STATE_GYRO_BIAS, 0);
    // 更新加速度噪声
    accel_bias_ = accel_bias_ + X_.block<3, 1>(INDEX_STATE_ACC_BIAS, 0);
}

// 该函数与EliminateError函数作用一致
void ErrorStateKalmanFilter::EliminateErrorVel() {
    // 更新位置pose
    pose_.block<3, 1>(0, 3) = pose_.block<3, 1>(0, 3) + X_.block<3, 1>(INDEX_STATE_POSI, 0);
    //kx 这一块需要再研究研究
    Eigen::Matrix3d C_nn = SO3Exp(X_.block<3, 1>(INDEX_STATE_ORI, 0));
    pose_.block<3, 3>(0, 0) = C_nn * pose_.block<3, 3>(0, 0);
    // 更新速度
    velocity_ = velocity_ + X_.block<3, 1>(INDEX_STATE_VEL, 0);
    // 更新角速度噪声
    gyro_bias_ = gyro_bias_ + X_.block<3, 1>(INDEX_STATE_GYRO_BIAS, 0);
    // 更新加速度噪声
    accel_bias_ = accel_bias_ + X_.block<3, 1>(INDEX_STATE_ACC_BIAS, 0);
}

Eigen::Matrix4d ErrorStateKalmanFilter::GetPose() {
    // std::cout << "pose_:" << pose_ << std::endl;
    return pose_;
}


