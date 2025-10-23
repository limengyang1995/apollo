#include <chrono>
#include <iostream>
#include <omp.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/registration/gicp.h>

#include "fast_gicp.h"
#include "fast_vgicp.h"
#include "modules/localization/msf/cereal/include/cereal/types/unordered_map.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/memory.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/vector.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/binary.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/json.hpp"
#include <fstream>

#include "modules/localization/msf/cereal/eigen_cereal.hpp"


template <typename Registration>
void test(Registration& reg, const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& target, const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& source) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr aligned(new pcl::PointCloud<pcl::PointXYZ>);

  double fitness_score = 0.0;

  // single run
//   auto t1 = std::chrono::high_resolution_clock::now();
//   // fast_gicp reuses calculated covariances if an input cloud is the same as the previous one
//   // to prevent this for benchmarking, force clear source and target clouds
//   reg.clearTarget();
//   reg.clearSource();
//   reg.setInputTarget(target);
//   reg.setInputSource(source);
//   reg.align(*aligned);
//   auto t2 = std::chrono::high_resolution_clock::now();
//   fitness_score = reg.getFitnessScore();
//   double single = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e6;

//   std::cout << "single:" << single << "[msec] " << std::flush;

  // 100 times
  auto t1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 1; i++) {
    reg.clearTarget();
    reg.clearSource();
    reg.setInputTarget(target);
    reg.setInputSource(source);
    reg.align(*aligned);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  double multi = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e6;
  std::cout << "1times:" << multi << "[msec] " << std::flush;
  pcl::io::savePCDFile("/apollo_workspace/data/apollo_data/map/fvgicp.pcd",*aligned);

//   // for some tasks like odometry calculation,
//   // you can reuse the covariances of a source point cloud in the next registration
//   t1 = std::chrono::high_resolution_clock::now();
//   pcl::PointCloud<pcl::PointXYZ>::ConstPtr target_ = target;
//   pcl::PointCloud<pcl::PointXYZ>::ConstPtr source_ = source;
//   for (int i = 0; i < 10; i++) {
//     reg.swapSourceAndTarget();
//     reg.clearSource();

//     reg.setInputTarget(target_);
//     reg.setInputSource(source_);
//     reg.align(*aligned);

//     target_.swap(source_);
//   }
//   t2 = std::chrono::high_resolution_clock::now();
//   double reuse = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e6;

//   std::cout << "100times_reuse:" << reuse << "[msec] fitness_score:" << fitness_score << std::endl;
}

int main(int argc, char** argv) {

  std::ifstream is("/apollo_workspace/data/apollo_data/Covariances/150_0_-150.json");
  cereal::JSONInputArchive iarchive(is);
  std::vector<Eigen::Matrix4d, Eigen::aligned_allocator<Eigen::Matrix4d>>covariances;
  iarchive( covariances );
  for(int i = 0; i < covariances.size(); i++){
     std::cout<<"covariances:"<<covariances[i]<<std::endl;
  }
  std::cout<<"covariances size :"<<covariances.size()<<std::endl;

  pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud(new pcl::PointCloud<pcl::PointXYZ>());
  pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud(new pcl::PointCloud<pcl::PointXYZ>());

  if (pcl::io::loadPCDFile(argv[1], *target_cloud)) {
    std::cerr << "failed to open " << argv[1] << std::endl;
    return 1;
  }
  if (pcl::io::loadPCDFile(argv[2], *source_cloud)) {
    std::cerr << "failed to open " << argv[2] << std::endl;
    return 1;
  }

  // remove invalid points around origin
  source_cloud->erase(
    std::remove_if(source_cloud->begin(), source_cloud->end(), [=](const pcl::PointXYZ& pt) { return pt.getVector3fMap().squaredNorm() < 1e-3; }),
    source_cloud->end());
  target_cloud->erase(
    std::remove_if(target_cloud->begin(), target_cloud->end(), [=](const pcl::PointXYZ& pt) { return pt.getVector3fMap().squaredNorm() < 1e-3; }),
    target_cloud->end());

  // downsampling
  pcl::ApproximateVoxelGrid<pcl::PointXYZ> voxelgrid;
  voxelgrid.setLeafSize(0.2f, 0.2f, 0.2f);

  pcl::PointCloud<pcl::PointXYZ>::Ptr filtered(new pcl::PointCloud<pcl::PointXYZ>());
  voxelgrid.setInputCloud(target_cloud);
  voxelgrid.filter(*filtered);
  target_cloud = filtered;

  filtered.reset(new pcl::PointCloud<pcl::PointXYZ>());
  voxelgrid.setInputCloud(source_cloud);
  voxelgrid.filter(*filtered);
  source_cloud = filtered;

  std::cout << "target:" << target_cloud->size() << "[pts] source:" << source_cloud->size() << "[pts]" << std::endl;
//   std::cout << "--- vgicp_st ---" << std::endl;
    fast_gicp::FastVGICP<pcl::PointXYZ, pcl::PointXYZ> vgicp;;
    pcl::PointCloud<pcl::PointXYZ>::Ptr aligned(new pcl::PointCloud<pcl::PointXYZ>);
    vgicp.setResolution(1.0);
    vgicp.setNumThreads(1);
    vgicp.clearTarget();
    vgicp.clearSource();
    vgicp.setInputTarget(target_cloud);
    vgicp.setInputSource(source_cloud);
    vgicp.align(*aligned);
    test(vgicp, target_cloud, source_cloud);

//   std::cout << "--- vgicp_mt ---" << std::endl;
//   vgicp.setNumThreads(omp_get_max_threads());
//   test(vgicp, target_cloud, source_cloud);
  return 0;
}
