#pragma once
#include "modules/localization/msf/cereal/include/cereal/cereal.hpp"
#include <Eigen/Dense>

namespace cereal {

/* save函数 */
template <class Archive, typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline typename std::enable_if<(_Rows != Eigen::Dynamic) && (_Cols != Eigen::Dynamic), void>::type
CEREAL_SAVE_FUNCTION_NAME( Archive & ar, Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> const & matrix )
{
    // 固定大小矩阵直接序列化数据
    for(int i = 0; i < _Rows; ++i) {
        for(int j = 0; j < _Cols; ++j) {
            ar(matrix(i,j));
        }
    }
}

/* load函数 */
template <class Archive, typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline typename std::enable_if<(_Rows != Eigen::Dynamic) && (_Cols != Eigen::Dynamic), void>::type
CEREAL_LOAD_FUNCTION_NAME( Archive & ar, Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> & matrix )
{
    // 固定大小矩阵直接序列化数据
    for(int i = 0; i < _Rows; ++i) {
        for(int j = 0; j < _Cols; ++j) {
            ar(matrix(i,j));
        }
    }
}

} // namespace cereal