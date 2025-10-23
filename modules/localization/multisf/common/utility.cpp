#include "utility.h"
namespace apollo {
namespace multimsflocalization {
Eigen::Vector3d R2ypr(const Eigen::Matrix3d &R) {
    Eigen::Vector3d n = R.col(0);
    Eigen::Vector3d o = R.col(1);
    Eigen::Vector3d a = R.col(2);

    Eigen::Vector3d ypr(3);
    double y = atan2(n(1), n(0));
    double p = atan2(-n(2), n(0) * cos(y) + n(1) * sin(y));
    double r = atan2(a(0) * sin(y) - a(1) * cos(y), -o(0) * sin(y) + o(1) * cos(y));
    ypr(0) = y;
    ypr(1) = p;
    ypr(2) = r;

    return ypr;
}

/**
 * @brief 将角度限制在(-pi,pi]区间内
 *
 * @return double
 */
double normalize_angle(const double angle) {
    if (angle <= -M_PI) {
        return normalize_angle(angle + 2. * M_PI);
    } else if (angle > M_PI) {
        return normalize_angle(angle - 2. * M_PI);
    } else {
        return angle;
    }
}

/**
 * @brief check value是否位于[bound_low,
 * bound_high]之间，超出范围则返回false，且为limit赋值为对应方向的边界值(bound_low或bound_high)
 *
 * @param value
 * @param bound_low
 * @param bound_high
 * @param limit
 * @return true
 * @return false
 */
bool bound_check(const double value, const double bound_low, const double bound_high, double &limit) {
    bool res = false;

    if (value < bound_low) {
        res = true;
        limit = bound_low;
    } else if (value > bound_high) {
        res = true;
        limit = bound_high;
    } else {
        // do nothing
    }

    return res;
}

/**
 * @brief check value是否位于[-bound, bound]之间，超出范围则返回false，且为limit赋值为对应方向的边界值(-bound或bound)
 *
 * @param [in] value
 * @param [in] bound
 * @param [out] limit
 * @return true
 * @return false
 */
bool bound_check(const double value, const double bound, double &limit) {
    return bound_check(value, -bound, bound, limit);
}
}  // namespace multimsflocalization
}  // namespace apollo