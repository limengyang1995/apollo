#pragma once

#include <string>
#include <cstring>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <fstream>

#include "common_utils.h"
#include "concurrent_deque.h"

// 判断文件夹是否存在
bool folder_exist(const std::string &folderPath, DIR **dir, bool is_return_dir = false);

// 写文件
bool write_string_list_to_file(const std::string &filePath, ConcurrentDeque<std::string> &infos);
