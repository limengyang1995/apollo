/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/localization/msf/local_pyramid_map/ndt_map/ndt_map.h"

namespace apollo {
namespace localization {
namespace msf {
namespace pyramid_map {

NdtMap::NdtMap(NdtMapConfig* config) : BaseMap(config) {}

NdtMap::~NdtMap() {}

/**
 * @brief 将地图节点数据保存为文本文件
 *
 * @param path 目录路径
 */
void NdtMap::SaveNodeText(const std::string& path) {
    std::vector<MapNodeIndex> index_list;
    map_node_cache_lvl1_->GetAllKey(index_list);

    if (index_list.empty()) {
        std::cout << "[NdtMap::SaveNodeText] index_list size = 0, illegal!\n";
        return;
    }
    std::cout << "[NdtMap::SaveNodeText] get index_list form L1-Cache, size = " << index_list.size() << "\n";

    // 从L1缓存中获取地图节点数据
    for (auto& idx : index_list) {
        BaseMapNode* node = nullptr;
        bool success = map_node_cache_lvl1_->Get(idx, &node);
        if (success) {
            std::cout << "[NdtMap::SaveNodeText] get node index: (" << node->GetMapNodeIndex().m_ << ", "
                      << node->GetMapNodeIndex().n_ << ")\n";
            NdtMapNode* ndt_node = dynamic_cast<NdtMapNode*>(node);

            // 保存地图节点数据为文本文件
            ndt_node->SaveText(path);
        } else {
            std::cout << "[NdtMap::SaveNodeText] get node index failed: (" << idx.m_ << ", " << idx.n_ << ")\n";
        }
    }
}

}  // namespace pyramid_map
}  // namespace msf
}  // namespace localization
}  // namespace apollo
