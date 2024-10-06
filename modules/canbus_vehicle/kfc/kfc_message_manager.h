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
 * @file kfc_message_manager.h
 * @brief the class of KfcMessageManager
 */

#pragma once

#include "modules/canbus_vehicle/kfc/proto/kfc.pb.h"
#include "modules/drivers/canbus/can_comm/message_manager.h"

namespace apollo {
namespace canbus {
namespace kfc {

using ::apollo::drivers::canbus::MessageManager;

class KfcMessageManager
    : public MessageManager<::apollo::canbus::Kfc> {
 public:
  KfcMessageManager();
  virtual ~KfcMessageManager();
};

}  // namespace kfc
}  // namespace canbus
}  // namespace apollo
