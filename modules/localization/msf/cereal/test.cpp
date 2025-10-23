#include "include/cereal/types/unordered_map.hpp"
#include "include/cereal/types/memory.hpp"
#include <cereal/types/vector.hpp>
#include "include/cereal/archives/binary.hpp"
#include "include/cereal/archives/json.hpp"
#include <fstream>

#include "eigen_cereal.hpp"
    
struct MyRecord
{
  uint8_t x, y;
  float z;

  MyRecord () = default;
  MyRecord (uint8_t _x, uint8_t _y, float _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
  }
  
  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( x, y, z );
  }
};
    
struct SomeData
{
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  int32_t id;
  std::shared_ptr<std::unordered_map<uint32_t, MyRecord>> data; // 哈希表
  std::unique_ptr<int> tmp1;

  int rows_ = 3;
  int cols_ = 3;
  std::unique_ptr<std::vector<int>> int_array; // 动态数组std::vector

  Eigen::Vector3f mean;
  // Eigen::Matrix3f cov;
  Eigen::Matrix<float, 3, 3> cov;

  void get_test_data() {
    id = 999;

    // 哈希表
    data = std::make_shared<std::unordered_map<uint32_t, MyRecord>>();
    for(int i = 0; i < 10; ++i) {
      MyRecord record(uint8_t(i), uint8_t(i+1), float(i) * 3.0f);
      data->insert(std::make_pair(i, record));
    }

    tmp1.reset(new int(88888));

    // 数组
    int size_array = rows_ * cols_;
    int_array.reset(new std::vector<int>(size_array));
    for(int i = 1; i <= rows_; ++i) {
      for(int j = 1; j <= cols_; ++j) {
        (*int_array)[(i - 1) * cols_ + j - 1] = (i + 0) * (j + 0);
      }
    }

    // Eigen::Matrix
    mean << 99, 88, 77;
    cov << 1, 3, 5,
           7, 9, 11,
           13, 15, 17;
  }

  /**
   * @brief 打印
   * 
   * @return std::string 
   */
  std::string to_msg () {
    std::stringstream ss;

    // id
    ss << "id: " << id << ", tmp1: " << *tmp1 << "\n";

    // 哈希表
    ss << "data:\n";
    for(auto &pair: *data) {
      ss << "key = " << pair.first << ", MyRecord = {" << int(pair.second.x) << ", " 
         << int(pair.second.y) << ", " << pair.second.z << "}\n";
    }

    // 数组 std::vector
    ss << "int_array: {";
    for(int i = 0; i < rows_; ++i) {
      for(int j = 0; j < cols_; ++j) {
        int idx = i * cols_ + j;
        if (idx != 0) {
          ss << ", ";
        }
        ss << (*int_array)[idx];
      }
    }
    ss << "}\n";

    // Eigen::Vector
    ss << "mean = [" << mean.transpose() << "]\n";

    // Eigen::Matrix
    ss << "cov:\n" << cov << "\n";

    return ss.str();
  }

  /**
   * @brief 序列化函数接口
   * 
   * @tparam Archive 
   * @param ar 
   */
  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( id, data, tmp1, int_array, mean, cov );
  }
};

/**
 * @brief 序列化并保存到json文件
 * 
 * @param filename 
 */
void test_save(std::string &filename)
{
  std::ofstream os(filename);
  cereal::JSONOutputArchive oarchive(os);

  SomeData myData;
  myData.get_test_data(); // 构造测试数据
  oarchive( myData );

  std::cout << "test_save succeed, save file: " << filename << "\n";
}

/**
 * @brief 读取json文件并反序列化
 * 
 * @param filename 
 */
void test_load(std::string &filename)
{
  std::ifstream is(filename);
  cereal::JSONInputArchive iarchive(is);

  SomeData myData;
  iarchive( myData );
  
  // 打印内存中的数据，验证是否解码成功
  std::cout << "test_load succeed, decode as follow ———— " << myData.to_msg() << "\n";
}

/**
 * @brief 
 * 
 * @return int 
 */
int main()
{
  std::string path = "cereal_out.json";
  test_save(path); // 序列化并保存到json文件

  test_load(path); // 读取json文件并反序列化

  return 0;
}