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
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/gicp.h>

#include "modules/localization/msf/cereal/include/cereal/types/unordered_map.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/memory.hpp"
#include "modules/localization/msf/cereal/include/cereal/types/vector.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/binary.hpp"
#include "modules/localization/msf/cereal/include/cereal/archives/json.hpp"
#include <fstream>

#include "modules/localization/msf/cereal/eigen_cereal.hpp"

#include "fast_gicp.h"
#include "fast_vgicp.h"
#include "gicp_settings.h"
using namespace fast_gicp;
int k_correspondences_ = 20;
int num_threads_ = 9;
int grid_size_ = 90;
int div_x;
int div_y;
double strat_pointx = 695389.443486;
double strat_pointy = 4850524.026700;
double strat_pointz = 243.524253;
// 设置体素大小
float voxel_size = 0.5f;
std::unordered_map<int,std::vector<double>> umap;

RegularizationMethod regularization_method_ = RegularizationMethod::PLANE;
// num_threads_ = omp_get_max_threads();

struct pcd_xyz_grid
{
    std::string filename;
    std::string name;
    std::string name1;
    bool usegrid = false;
    int grid_id;
    int grid_id_x;
    int grid_id_y;
    int lower_bound_x;
    int lower_bound_y;
    int upper_bound_x;
    int upper_bound_y;
    pcl::PointCloud<pcl::PointXYZ>cloud;
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


std::vector<std::vector<double>> Read_Pose(const std::string &path){
    // 打开文件
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "无法打开文件!" << std::endl;
    }
    std::string line;
    // 用于存储每一行的数字
    std::vector<std::vector<double>> data;
    // 逐行读取
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double number;
        std::vector<double> row;
        // 逐个读取每一行中的数字
        while (iss >> number) {
            row.push_back(number);
        }
        row[2] = row[2] - strat_pointx;
        row[3] = row[3] - strat_pointy;
        row[4] = row[4] - strat_pointz;
        // std::cout<<std::setprecision(18)<<"row0 :"<<row[1]<<" row1 :"<<row[2]<<" row2:"<<row[3]<<std::endl;
        data.push_back(row);  // 将每行的数字加入到数据中
    }
    // 关闭文件
    file.close();
    return data;
}

bool GetFileList(const std::string filepath, std::vector<std::string>&filenames){
  std::cout<<"读取的pcd路径为: "<<filepath<<std::endl;
  const char* path = filepath.c_str(); // 修改为你的目录路径
    DIR* dir = opendir(path);
    if (dir == nullptr) {
        std::cerr << "无法打开目录: " << path << std::endl;
        return false;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        // 排除 "." 和 ".."
        if (entry->d_name[0] != '.') {
          // std::cout << entry->d_name << std::endl;
          filenames.push_back(entry->d_name);
        }
    }
    closedir(dir);
    // // 打印排序后的文件名
    // for (const auto& name : filenames) {
    //     std::cout << name << std::endl;
    // }
    return true;
}


bool Get_calculate_covariances(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,std::vector<Eigen::Matrix4d, Eigen::aligned_allocator<Eigen::Matrix4d>>& covariances) {
  covariances.resize(cloud->size());
  std::cout<<" cloud size: "<<cloud->size()<<std::endl;
  pcl::search::KdTree<pcl::PointXYZ> kdtree;
  kdtree.setInputCloud(cloud);
  #pragma omp parallel for num_threads(num_threads_) schedule(guided, 8)
  for (int i = 0; i < cloud->size(); i++) {
    std::vector<int> k_indices;
    std::vector<float> k_sq_distances;
    kdtree.nearestKSearch(cloud->at(i), k_correspondences_, k_indices, k_sq_distances);
    // std::cout<<" cloud->at(i): "<<cloud->at(i).x<<" "<<cloud->at(i).y<<std::endl;
    Eigen::Matrix<double, 4, -1> neighbors(4, k_correspondences_);
    for (int j = 0; j < k_indices.size(); j++) {
      neighbors.col(j) = cloud->at(k_indices[j]).getVector4fMap().template cast<double>();
    }

    neighbors.colwise() -= neighbors.rowwise().mean().eval();
    Eigen::Matrix4d cov = neighbors * neighbors.transpose() / k_correspondences_;

    if (regularization_method_ == RegularizationMethod::NONE) {
      covariances[i] = cov;
    } else if (regularization_method_ == RegularizationMethod::FROBENIUS) {
      double lambda = 1e-3;
      Eigen::Matrix3d C = cov.block<3, 3>(0, 0).cast<double>() + lambda * Eigen::Matrix3d::Identity();
      Eigen::Matrix3d C_inv = C.inverse();
      covariances[i].setZero();
      covariances[i].template block<3, 3>(0, 0) = (C_inv / C_inv.norm()).inverse();
    } else {
      Eigen::JacobiSVD<Eigen::Matrix3d> svd(cov.block<3, 3>(0, 0), Eigen::ComputeFullU | Eigen::ComputeFullV);
      Eigen::Vector3d values;

      switch (regularization_method_) {
        default:
          std::cerr << "here must not be reached" << std::endl;
          abort();
        case RegularizationMethod::PLANE:
          values = Eigen::Vector3d(1, 1, 1e-3);
          break;
        case RegularizationMethod::MIN_EIG:
          values = svd.singularValues().array().max(1e-3);
          break;
        case RegularizationMethod::NORMALIZED_MIN_EIG:
          values = svd.singularValues() / svd.singularValues().maxCoeff();
          values = values.array().max(1e-3);
          break;
      }

      covariances[i].setZero();
      covariances[i].template block<3, 3>(0, 0) = svd.matrixU() * values.asDiagonal() * svd.matrixV().transpose();
      // std::cout<<"covariances:"<<i<<":"<<std::endl;
      // std::cout<<"covariances:"<<covariances[i]<<std::endl;
    }
  }
  std::cout<<"covariances done, covariances size: "<<covariances.size()<<std::endl;
  return true;
}
void Find_Boundaries(const std::vector<std::vector<double>>& map, double &min_x, double &max_x, double &min_y,
                                 double &max_y)
{
    for (auto p : map)
    {
        // std::cout<<"p1"<<p[2]<<" p2"<<p[3]<<std::endl;
        if (p[2] < min_x)
        {
            min_x = p[2];
        }
        if (p[2] > max_x)
        {
            max_x = p[2];
        }
        if (p[3] < min_y)
        {
            min_y = p[3];
        }
        if (p[3] > max_y)
        {
            max_y = p[3];
        }
    }
}
void GetCovariances(const std::vector<pcd_xyz_grid>&map_grid){
    
    for(int i = 0; i < map_grid.size(); i++){
      if(map_grid[i].cloud.size() > 8){
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloudgrid(new pcl::PointCloud<pcl::PointXYZ>(map_grid[i].cloud));
        // 找到 i 附近周围的相邻id的块加在一起
        std::vector<int>index_id;
        int id_left = i - 1;
        if(id_left < map_grid.size() && id_left >= 0){
          index_id.push_back(id_left);
        }
        int id_right = i + 1;
        if(id_right < map_grid.size() && id_right >= 0){
          index_id.push_back(id_right);
        }
        int u_id_up = i - div_x;
        if(u_id_up < map_grid.size() && u_id_up >= 0){
          index_id.push_back(u_id_up);
        }
        int u_id_up_left = u_id_up - 1;
        if(u_id_up_left < map_grid.size() && u_id_up_left >= 0){
          index_id.push_back(u_id_up_left);
        }
        int u_id_up_right = u_id_up + 1;
        if(u_id_up_right < map_grid.size() && u_id_up_right >= 0){
          index_id.push_back(u_id_up_right);
        }

        int u_id_down = i + div_x;
        if(u_id_down < map_grid.size() && u_id_down >= 0){
          index_id.push_back(u_id_down);
        }
        int u_id_down_left = u_id_down - 1;
                if(u_id_down_left < map_grid.size() && u_id_down_left >= 0){
          index_id.push_back(u_id_down_left);
        }
        int u_id_down_right = u_id_down + 1;
                if(u_id_down_right < map_grid.size() && u_id_down_right >= 0){
          index_id.push_back(u_id_down_right);
        }
        for(int j = 0; j < index_id.size(); j++){
            if(map_grid[index_id[j]].cloud.size() > 8){
              pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPtr(new pcl::PointCloud<pcl::PointXYZ>(map_grid[index_id[j]].cloud));
              *cloudgrid += *cloudPtr;
            }
        }
        std::vector<Eigen::Matrix4d, Eigen::aligned_allocator<Eigen::Matrix4d>>covariances;
        std::cout<<" cloudgrid size: "<<cloudgrid->size()<<std::endl;
        // 创建体素滤波器对象
        pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
        voxel_filter.setInputCloud(cloudgrid);
        voxel_filter.setLeafSize(voxel_size, voxel_size, voxel_size);
        // 输出下采样后的点云
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
        voxel_filter.filter(*cloud_filtered);
        pcl::io::savePCDFileBinary(map_grid[i].name,*cloud_filtered);

        // // 创建体素滤波器对象
        // pcl::PointCloud<pcl::PointXYZ>::Ptr cloudgrid1(new pcl::PointCloud<pcl::PointXYZ>(map_grid[i].cloud));
        // pcl::VoxelGrid<pcl::PointXYZ> voxel_filter1;
        // voxel_filter1.setInputCloud(cloudgrid1);
        // voxel_filter1.setLeafSize(voxel_size, voxel_size, voxel_size);
        // // 输出下采样后的点云
        // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered1(new pcl::PointCloud<pcl::PointXYZ>);
        // voxel_filter1.filter(*cloud_filtered1);
        // pcl::io::savePCDFileBinary(map_grid[i].name1,*cloud_filtered1);

        Get_calculate_covariances(cloud_filtered,covariances);
        // 保存对grid的点云及对应的协方差
        // 序列化到文件
        {
          std::cout<<"grid covariances save path:"<<map_grid[i].filename<<std::endl;
          std::string path = map_grid[i].filename;
          std::ofstream os(path,std::ios::binary);
          cereal::BinaryOutputArchive archive(os);
          archive(covariances);
        }

      }
      else{
        std::cout<<"改grid下没有点云点: "<<i<<std::endl;
      }
    }
}
void Get_Map_Grid(const std::string& path_pose,const std::string &path, 
                                       const std::string savepath,pcl::PointCloud<pcl::PointXYZ>& map){

  std::vector<std::string>filenames;
  if(GetFileList(path,filenames)){
    std::cout<<"get pcd name all!"<<std::endl;
  }
  // 加载所有点云文件
  for (int l = 0; l < filenames.size(); l++)
  {
    // std::cout << "filenames path : " << filenames[l] << std::endl;
    pcl::PointCloud<pcl::PointXYZ>::Ptr map_sub(new pcl::PointCloud<pcl::PointXYZ>);
    std::string sub_map_path = path + filenames[l];
    if (pcl::io::loadPCDFile(sub_map_path, *map_sub) < 0)
    {
        std::cout<<" 该index : "<<l<<" 下没有对应点云帧！"<<std::endl;
    }
    map += *map_sub;
  }
  std::cout << "Total points num: " << map.points.size() << " points." << std::endl; 

  double min_x = 10000000000.0;
  double max_x = -10000000000.0;
  double min_y = 10000000000.0;
  double max_y = -10000000000.0;
  std::vector<std::vector<double>>data = Read_Pose(path_pose);
  Find_Boundaries(data,min_x,max_x,min_y,max_y);
  min_x = min_x - 300;
  max_x = max_x + 300;
  min_y = min_y - 300;
  max_y = max_y + 300;
  std::cout<<std::setprecision(19)<<"min_x : "<<min_x<<" max_x : "<<max_x<<" min_y : "<<min_y<<" max_y : "<<max_y<<std::endl;
  int min_x_b = grid_size_ * static_cast<int>(floor(min_x / grid_size_));
  // int max_x_b = grid_size_ * static_cast<int>(floor(max_x / grid_size_) + 1);
  int min_y_b = grid_size_ * static_cast<int>(floor(min_y / grid_size_));
  // int max_y_b = grid_size_ * static_cast<int>(floor(max_y / grid_size_) + 1);
  div_x = (max_x - min_x_b) / grid_size_ + 1;
  div_y = (max_y - min_y_b) / grid_size_ + 1;
  umap[-1] = {strat_pointx,strat_pointy,strat_pointz};
  umap[-2] = {div_x,div_y};
  umap[-3] = {min_x,max_x,min_y,max_y};
  int grid_num = div_x * div_y;
  std::vector<pcd_xyz_grid> grids_(grid_num);
  for (int y = 0; y < div_y; y++)
  {
      for (int x = 0; x < div_x; x++)
      {
          int id = div_x * y + x;
          std::cout<<"id:"<<id<<std::endl;
          grids_[id].grid_id = id;
          grids_[id].grid_id_x = x;
          grids_[id].grid_id_y = y;
          grids_[id].lower_bound_x = min_x_b + grid_size_ * x;
          grids_[id].lower_bound_y = min_y_b + grid_size_ * y;
          grids_[id].upper_bound_x = min_x_b + grid_size_ * (x + 1);
          grids_[id].upper_bound_y = min_y_b + grid_size_ * (y + 1);
          std::vector<double>boundpoint{grids_[id].lower_bound_x,grids_[id].lower_bound_y,grids_[id].upper_bound_x,grids_[id].upper_bound_y};
          // 检查元素是否存在
          if (umap.find(id) != umap.end()) {
              std::cout << "Orange is found!" << std::endl;
          } else {
              umap[id] = boundpoint;
          }
          // 遍历pose，查看属于该id下的pose 索引
          for(int i = 0; i < data.size(); i++){
              if(data[i][1] > grids_[id].lower_bound_x && data[i][1] <= grids_[id].upper_bound_x && 
                  data[i][2] > grids_[id].lower_bound_y && data[i][2] <= grids_[id].upper_bound_y){
                grids_[id].pose_index_.push_back(i);
              }
          }

          // grids_[id].filename = savepath + "/" + std::to_string(id) + "_" +
          //                       std::to_string(grids_[id].lower_bound_x) + "_" +
          //                       std::to_string(grids_[id].lower_bound_y) + ".json";
          grids_[id].filename = savepath + "/" + std::to_string(id) +".bin";
          // grids_[id].name =  savepath + "/" +std::to_string(id) + "_" + std::to_string(grids_[id].lower_bound_x) + "_" +
          //                   std::to_string(grids_[id].lower_bound_y) + ".pcd";
          grids_[id].name =  savepath + "/" + std::to_string(id) + ".pcd";
          grids_[id].name1 =  savepath + "/" + std::to_string(id) + "_1.pcd";
          grids_[id].cloud = pcl::PointCloud<pcl::PointXYZ>();
      }
  }
  std::cout<<"开始对点云进行划分，grid!"<<std::endl;
  // 遍历地图点，计算grid id并将其push_back到对应grid的点云中
  for (auto p = map.points.begin(); p != map.points.end(); p++)
  {
      int idx = static_cast<int>(floor((p->x - static_cast<float>(min_x_b)) / grid_size_));
      int idy = static_cast<int>(floor((p->y - static_cast<float>(min_y_b)) / grid_size_));
      int id = idy * div_x + idx;
      // std::cout<<"grid id:"<<id<<std::endl;
      if(0 <= id && id < grids_.size()){
        const pcl::PointXYZ &tmp = *p;
        grids_[id].cloud.points.push_back(tmp);
      }
      else{
        std::cout<<"id :"<<id<<std::endl;
        std::cout<<"p: "<<p->x<<" "<<p->y<<std::endl;
      }
      
  }
  // 保存grid索引及其边界
  std::string path_config = savepath + "/config.json";
  std::ofstream os(path_config);
  cereal::JSONOutputArchive archive(os);
  archive(umap);

  // 获得协方差
  GetCovariances(grids_);
}


int main(int argc,char **argv){
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    // if (pcl::io::loadPCDFile(argv[1], *cloud)) {
    //     std::cerr << "failed to open " << argv[1] << std::endl;
    //     return 1;
    // }
    // auto t1 = std::chrono::high_resolution_clock::now();
    // auto t2 = std::chrono::high_resolution_clock::now();
    // double multi = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e6;
    // std::cout << "1times:" << multi << "[msec] " << std::flush;
    // // for(int i = 0; i < covariances.size(); i++){
    // //     std::cout<<"***************** covariances: "<<i<<"***********************"<<std::endl;
    // //     std::cout<<covariances[i]<<std::endl;
    // // }

    //根据pose，对地图进行分割,argv[2]poses.txt路径
    //获得分割结果并读取文件夹下所有的pose对应pcd文件
    pcl::PointCloud<pcl::PointXYZ> map;
    //argv[1]pcd path argv[3]协方差保存路径
    Get_Map_Grid(argv[2],argv[1],argv[3],map);

    return 0;
}