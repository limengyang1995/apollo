#include <chrono>
#include <omp.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/registration/gicp.h>

#include "modules/localization/msf/cereal/include/cereal/types/unordered_map.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/memory.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/vector.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/binary.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/json.hpp"
#include "modules/localization/multisf/fastgicp/calculate_covariances.h"
#include <fstream>

#include "modules/localization/msf/cereal/eigen_cereal.hpp"

#include "fast_gicp.h"
#include "fast_vgicp.h"
#include "gicp_settings.h"
using namespace fast_gicp;
int k_correspondences_ = 20;
int num_threads_ = 15;
int grid_size_ = 150;
RegularizationMethod regularization_method_ = RegularizationMethod::PLANE;

struct pcd_xyz_grid
{
    std::string filename;
    std::string name;
    bool usegrid = false;
    int grid_id;
    int grid_id_x;
    int grid_id_y;
    int lower_bound_x;
    int lower_bound_y;
    int upper_bound_x;
    int upper_bound_y;
    pcl::PointCloud<pcl::PointXYZ> cloud;
    std::vector<int>pose_index_;       // 存储该grid下的pose的索引
};
struct Covariances{

  int point_index;
  Eigen::Matrix4d cov;

  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( point_index,cov);
  }
};

std::vector<std::vector<double>> Read_Pose(const std::string &path);
bool GetFileList(const std::string filepath, std::vector<std::string>&filenames);
bool Get_calculate_covariances(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
                                std::vector<Eigen::Matrix4d, Eigen::aligned_allocator<Eigen::Matrix4d>>& covariances) ;
void Find_Boundaries(const std::vector<std::vector<double>>& map, double &min_x, double &max_x, double &min_y,
                                 double &max_y);
std::vector<pcd_xyz_grid> Get_Map_Grid(const std::vector<std::vector<double>> &data,const std::string &path, 
                                       const std::string savepath,pcl::PointCloud<pcl::PointXYZ>& map);  
void GetCovariances(const std::vector<pcd_xyz_grid>&map_grid,std::vector<Eigen::Matrix4d, Eigen::aligned_allocator<Eigen::Matrix4d>>&covariances);                        