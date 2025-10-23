#include "calculate_covariances.h"
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


    std::vector<std::vector<double>> data;
    //根据pose，对地图进行分割,argv[2]poses.txt路径
    data = Read_Pose(argv[2]);
    //获得分割结果并读取文件夹下所有的pose对应pcd文件
    pcl::PointCloud<pcl::PointXYZ> map;
    //argv[1]pcd path argv[3]协方差保存路径
    std::vector<pcd_xyz_grid>map_grid = Get_Map_Grid(data,argv[1],argv[3],map);

    // 获得协方差
    std::vector<Eigen::Matrix4d, Eigen::aligned_allocator<Eigen::Matrix4d>> covariances;
    GetCovariances(map_grid,covariances);

    return 0;
}