#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>

// 曲线拟合顶点：表示曲线参数（例如二次曲线 y = a*x^2 + b*x + c 的参数 [a, b, c]）
class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d> {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    
    // 重置顶点到初始状态
    virtual void setToOriginImpl() override {
        _estimate << 0, 0, 0; // 初始化为零向量 [a, b, c] = [0, 0, 0]
    }
    
    // 更新顶点状态
    virtual void oplusImpl(const double* update) override {
        _estimate += Eigen::Vector3d(update); // 简单的加法更新
    }
    
    // 读取顶点数据（可选）
    virtual bool read(std::istream& is) override {
        for (int i = 0; i < 3; ++i) {
            is >> _estimate[i];
        }
        return true;
    }
    
    // 写入顶点数据（可选）
    virtual bool write(std::ostream& os) const override {
        for (int i = 0; i < 3; ++i) {
            os << _estimate[i] << " ";
        }
        return os.good();
    }
};

// 曲线拟合边：定义观测数据点与曲线预测值之间的误差
class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex> {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    
    CurveFittingEdge(double x) : _x(x) {}
    
    // 计算误差
    virtual void computeError() override {
        const CurveFittingVertex* v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector3d& abc = v->estimate();
        
        // 二次曲线模型: y = a*x^2 + b*x + c
        double predicted = abc[0] * _x * _x + abc[1] * _x + abc[2];
        _error[0] = _measurement - predicted; // 误差 = 观测值 - 预测值
    }
    
    // 线性化函数（计算雅可比矩阵）
    virtual void linearizeOplus() override {
        const CurveFittingVertex* v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector3d& abc = v->estimate();
        
        // 雅可比矩阵: [∂error/∂a, ∂error/∂b, ∂error/∂c]
        _jacobianOplusXi[0] = -_x * _x; // ∂error/∂a = -x²
        _jacobianOplusXi[1] = -_x;      // ∂error/∂b = -x
        _jacobianOplusXi[2] = -1;       // ∂error/∂c = -1
    }
    
    virtual bool read(std::istream& is) override { return true; }
    virtual bool write(std::ostream& os) const override { return true; }
    
private:
    double _x; // x 坐标值
};

int main() {
    // 创建优化器
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;
    typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType;
    
    auto solver = new g2o::OptimizationAlgorithmLevenberg(
        std::make_unique<BlockSolverType>(std::make_unique<LinearSolverType>()));
    
    g2o::SparseOptimizer optimizer;
    optimizer.setAlgorithm(solver);
    optimizer.setVerbose(true);
    
    // 添加顶点 - 现在可以正确实例化 CurveFittingVertex
    CurveFittingVertex* v = new CurveFittingVertex();
    v->setId(0);
    v->setEstimate(Eigen::Vector3d(0, 0, 0)); // 初始参数估计
    optimizer.addVertex(v);
    
    // 添加边 - 创建一些模拟数据点
    std::vector<std::pair<double, double>> data_points = {
        {0.0, 1.0}, {1.0, 2.0}, {2.0, 5.0}, 
        {3.0, 10.0}, {4.0, 17.0}, {5.0, 26.0} // y = x² + 1
    };
    
    for (size_t i = 0; i < data_points.size(); ++i) {
        CurveFittingEdge* edge = new CurveFittingEdge(data_points[i].first);
        edge->setId(i);
        edge->setVertex(0, v);
        edge->setMeasurement(data_points[i].second);
        edge->setInformation(Eigen::Matrix<double, 1, 1>::Identity()); // 信息矩阵
        optimizer.addEdge(edge);
    }
    
    // 执行优化
    optimizer.initializeOptimization();
    optimizer.optimize(10);
    
    // 输出结果
    std::cout << "优化后的参数: " << v->estimate().transpose() << std::endl;
    std::cout << "真实参数应为: [1, 0, 1] (y = x² + 1)" << std::endl;
    
    return 0;
}