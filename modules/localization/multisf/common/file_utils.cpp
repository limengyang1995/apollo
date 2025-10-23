#include "file_utils.h"

/**
 * @brief 判断文件夹是否存在
 *
 * @param [in] folderPath
 * @param [out] dir
 * @param [in] is_return_dir 是否返回dir
 * @return true
 * @return false
 */
bool folder_exist(const std::string &folderPath, DIR **dir, bool is_return_dir) {
    *dir = opendir(folderPath.c_str());  // 打开文件夹
    if (*dir) {
        // 如果不需要返回dir，则直接关闭dir
        if (!is_return_dir) {
            closedir(*dir);
        }
        return true;
    } else {
        std::cout << "[folder_exist] path = " << folderPath << " is not exist!\n";
        return false;
    }
    return true;
}

/**
 * @brief 写文件
 *
 * @param filePath
 * @param infos
 * @return true
 * @return false
 */
bool write_string_list_to_file(const std::string &filePath, ConcurrentDeque<std::string> &infos) {
    if (filePath == "") {
        std::cout << "[write_string_list_to_file] filePath is empty!\n";
        return false;
    }

    if (infos.size() == 0) {
        std::cout << "[write_string_list_to_file] infos is empty!\n";
        return false;
    }

    std::ofstream res_file(filePath, std::ios::out | std::ios::app);
    if (res_file.is_open()) {
        for (size_t i = 0; i < infos.size(); ++i) {
            res_file << infos[i] << std::endl;
        }

        res_file.close();
    } else {
        std::cout << "[write_string_list_to_file] file open error!" << std::endl;
    }
    return true;
}
