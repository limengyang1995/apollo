#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <deque>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cfloat>
#include <iterator>
#include <sstream>
#include <string>
#include <limits>
#include <iomanip>
#include <array>
#include <thread>
#include <mutex>
#include <math.h>

#include "Eigen/Dense"
namespace apollo {
namespace multimsflocalization {

Eigen::Vector3d R2ypr(const Eigen::Matrix3d &R);  // 旋转矩阵转欧拉角
double normalize_angle(const double angle);       // 将角度限制在(-pi,pi]区间内
// check value是否位于[bound_low,
// bound_high]之间，超出范围则返回false，且为limit赋值为对应方向的边界值(bound_low或bound_high)
bool bound_check(const double value, const double bound_low, const double bound_high, double &limit);
// check value是否位于[-bound, bound]之间，超出范围则返回false，且为limit赋值为对应方向的边界值(-bound或bound)
bool bound_check(const double value, const double bound, double &limit);
}  // namespace multimsflocalization
}  // namespace apollo