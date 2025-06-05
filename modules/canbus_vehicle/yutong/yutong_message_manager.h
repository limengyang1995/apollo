/******************************************************************************
 * Copyright 2023 The Apollo Authors. All Rights Reserved.
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

/**
 * @file yutong_message_manager.h
 * @brief the class of YutongMessageManager
 */

#pragma once

#include "modules/canbus_vehicle/yutong/proto/yutong.pb.h"
#include "modules/drivers/canbus/can_comm/message_manager.h"

namespace apollo {
namespace canbus {
namespace yutong {

using ::apollo::drivers::canbus::MessageManager;

class YutongMessageManager
    : public MessageManager<::apollo::canbus::Yutong> {
 public:
  YutongMessageManager();
  virtual ~YutongMessageManager();
};

}  // namespace yutong
}  // namespace canbus
}  // namespace apollo
