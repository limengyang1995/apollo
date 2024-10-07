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

/**
 * @file
 **/

#include "modules/planning/scenarios/narrow_uturn/narrow_uturn_scenario.h"

#include "cyber/common/log.h"
#include "modules/map/hdmap/hdmap_util.h"
#include "modules/planning/scenarios/pull_over/stage_reverse.h"


namespace apollo {
namespace planning {

using apollo::hdmap::HDMapUtil;

bool NarrowUturnScenario::Init(std::shared_ptr<DependencyInjector> injector,
                            const std::string& name) {
  if (init_) {
    return true;
  }

  if (!Scenario::Init(injector, name)) {
    AERROR << "failed to init scenario" << Name();
    return false;
  }

  if (!Scenario::LoadConfig<ScenarioNarrowUturnConfig>(
          &context_.scenario_config)) {
    AERROR << "fail to get config of scenario" << Name();
    return false;
  }

  init_ = true;
  return true;
}

bool NarrowUturnScenario::IsTransferable(const Scenario* const other_scenario,
                                      const Frame& frame) {
  if (!frame.local_view().planning_command->has_lane_follow_command()) {
    return false;
  }
  if (other_scenario == nullptr || frame.reference_line_info().empty()) {
    return false;
  }
  if (!FLAGS_enable_uturn_at_narrow_street) {
    return false;
  }
  const auto routing_end = frame.local_view().end_lane_way_point;
  if (nullptr == routing_end) {
    return false;
  }
  
  
  const auto& reference_line_info = frame.reference_line_info().front();
  const auto& reference_line = reference_line_info.reference_line();
  
  const double adc_front_edge_s = reference_line_info.AdcSlBoundary().end_s();
  
  std::vector <ReferencePoint>  ref_points = GetReferencePoints(adc_front_edge_s - 10,  adc_front_edge_s + 10);
  if (std::abs(ref_points.begin()->heading() - ref_points.end()->heading()) < context_.scenario_config.uturn_heading_diff_threshold()){
    return false;
  }

  const auto& vehicle_param = common::VehicleConfigHelper::Instance()->GetConfig().vehicle_param();
  double max_kappa = 1.0 / vehicle_param.min_turn_radius();
  ReferencePoint* uturn_max_kappa_point = ref_points.data();
  for(auto ref_point = ref_points.begin(); ref_point != ref_points.end(); ++ref_point){
    if ref_point->kappa() > uturn_point->kappa(){
      uturn_max_kappa_point = ref_point;
    }
  }
  if (uturn_max_kappa_point->kappa() < max_kappa){
    return false;
  }

  common::SLPoint uturn_max_kappa_sl;
  common::math::Vec2d uturn_max_kappa_xy = {uturn_max_kappa_point->x(), uturn_max_kappa_point->y()}
  reference_line.XYToSL(uturn_max_kappa_xy, &uturn_max_kappa_sl);
  const double adc_dis_to_uturn_max_kappa = uturn_max_kappa_sl.s() - adc_front_edge_s;
  if (std::abs(adc_dis_to_uturn_max_kappa) > context_.scenario_config.dis_to_uturn_threshold()){
    return false;
  }  
  
  ADEBUG << "adc_dis_to_uturn_max_kappa[" << adc_dis_to_uturn_max_kappa
         << "] uturn_max_kappa_s[" << uturn_max_kappa_sl.s() << "] adc_front_edge_s["
         << adc_front_edge_s << "]";

  const double adc_speed = injector_->vehicle_state()->linear_velocity();
  if (adc_speed > context_.scenario_config.speed_uturn_threshold()){
    return false;
  }





  bool pull_over_scenario =
      (frame.reference_line_info().size() == 1 &&  // NO, while changing lane
       adc_distance_to_dest >=
           context_.scenario_config.pull_over_min_distance_buffer() &&
       adc_distance_to_dest <=
           context_.scenario_config.start_pull_over_scenario_distance());
  
  // too close to destination + not found pull-over position
  if (pull_over_scenario) {
    if (adc_distance_to_dest <
        context_.scenario_config.max_distance_stop_search()) {
      pull_over_scenario = false;
    }
  }
  // check around junction
  auto first_encountered_overlaps =
      frame.reference_line_info().front().FirstEncounteredOverlaps();
  if (pull_over_scenario) {
    static constexpr double kDistanceToAvoidJunction = 8.0;  // meter
    for (const auto& overlap : first_encountered_overlaps) {
      if (overlap.first == ReferenceLineInfo::PNC_JUNCTION ||
          overlap.first == ReferenceLineInfo::SIGNAL ||
          overlap.first == ReferenceLineInfo::STOP_SIGN ||
          overlap.first == ReferenceLineInfo::YIELD_SIGN) {
        const double distance_to = overlap.second.start_s - dest_sl.s();
        const double distance_passed = dest_sl.s() - overlap.second.end_s;
        if ((distance_to > 0.0 && distance_to < kDistanceToAvoidJunction) ||
            (distance_passed > 0.0 &&
             distance_passed < kDistanceToAvoidJunction)) {
          pull_over_scenario = false;
          break;
        }
      }
    }
  }

  // check rightmost driving lane along pull-over path
  if (pull_over_scenario) {
    double check_s = adc_front_edge_s;
    static constexpr double kDistanceUnit = 5.0;
    while (check_s < dest_sl.s()) {
      check_s += kDistanceUnit;

      std::vector<hdmap::LaneInfoConstPtr> lanes;
      reference_line.GetLaneFromS(check_s, &lanes);
      if (lanes.empty()) {
        ADEBUG << "check_s[" << check_s << "] can't find a lane";
        continue;
      }
      const hdmap::LaneInfoConstPtr lane = lanes[0];
      const std::string lane_id = lane->lane().id().id();
      ADEBUG << "check_s[" << check_s << "] lane[" << lane_id << "]";

      // check neighbor lanes type: NONE/CITY_DRIVING/BIKING/SIDEWALK/PARKING
      bool rightmost_driving_lane = true;
      for (const auto& neighbor_lane_id :
           lane->lane().right_neighbor_forward_lane_id()) {
        const auto hdmap_ptr = HDMapUtil::BaseMapPtr();
        CHECK_NOTNULL(hdmap_ptr);
        const auto neighbor_lane = hdmap_ptr->GetLaneById(neighbor_lane_id);
        if (neighbor_lane == nullptr) {
          AWARN << "Failed to find neighbor lane[" << neighbor_lane_id.id()
                << "]";
          continue;
        }
        const auto& lane_type = neighbor_lane->lane().type();
        if (lane_type == hdmap::Lane::CITY_DRIVING) {
          AWARN << "lane[" << lane_id << "]'s right neighbor forward lane["
                << neighbor_lane_id.id() << "] type["
                << Lane_LaneType_Name(lane_type) << "] can't pull over";
          rightmost_driving_lane = false;
          break;
        }
      }
      if (!rightmost_driving_lane) {
        pull_over_scenario = false;
        break;
      }
    }
  }
  return pull_over_scenario;
}

bool NarrowUturnScenario::Exit(Frame* frame) {
  injector_->planning_context()->mutable_planning_status()->clear_pull_over();
  return true;
}

bool NarrowUturnScenario::Enter(Frame* frame) {
  auto* pull_over = injector_->planning_context()
                        ->mutable_planning_status()
                        ->mutable_pull_over();
  pull_over->set_pull_over_type(PullOverStatus::PULL_OVER);
  pull_over->set_plan_pull_over_path(true);
  return true;
}

}  // namespace planning
}  // namespace apollo
