#pragma once

#include "gflags/gflags.h"

DECLARE_bool(debug);
DECLARE_bool(location_mode);
DECLARE_string(fusion_mode);
DECLARE_string(calibration_config_path);
DECLARE_double(optimization_rtk_noise);
DECLARE_double(fusion_rtk_lidar_pose_time_diff_threshold_s);
DECLARE_string(output_map_dir_path);
DECLARE_string(map_dir_path);
DECLARE_string(loc_map_dir);

DECLARE_int32(auto_save_map_idle_threshold);
DECLARE_bool(use_rtk_prior);
DECLARE_uint32(rtk_hardware_version);
DECLARE_uint32(localization_acc_acquired_from);

// Scan Context
DECLARE_double(scan_context_max_radius);
DECLARE_double(scan_context_max_theta);
DECLARE_uint32(scan_context_num_rings);
DECLARE_uint32(scan_context_num_sectors);
DECLARE_uint32(scan_context_indexing_interval);
DECLARE_uint32(scan_context_min_key_frame_seq_distance);
DECLARE_uint32(scan_context_num_candidates);
DECLARE_double(scan_context_fast_alignment_search_ratio);
DECLARE_double(scan_context_scan_context_distance_thresh);
DECLARE_double(fusion_acc_noise);
DECLARE_double(fusion_acc_z_noise);
DECLARE_double(fusion_gyro_noise);
DECLARE_double(fusion_acc_bias_noise);
DECLARE_double(fusion_gyro_bias_noise);
DECLARE_double(fusion_laser_pose_noise);
DECLARE_double(fusion_laser_orient_noise);
DECLARE_double(fusion_laser_z_noise);
DECLARE_double(fusion_rtk_pose_noise);
DECLARE_double(fusion_rtk_orient_noise);
DECLARE_double(fusion_rtk_z_noise);
DECLARE_double(fusion_wheelspd_noise);
DECLARE_double(wheel_factor);
DECLARE_uint32(rtk_interval);

DECLARE_bool(playback_mode);
DECLARE_bool(output_evaluation_files);

DECLARE_bool(lidar_filter);
DECLARE_double(lidar_filter_cropbox_x_min);
DECLARE_double(lidar_filter_cropbox_x_max);
DECLARE_double(lidar_filter_cropbox_y_min);
DECLARE_double(lidar_filter_cropbox_y_max);
DECLARE_double(lidar_filter_cropbox_z_min);
DECLARE_double(lidar_filter_cropbox_z_max);

DECLARE_bool(lidar_range_filter);
DECLARE_double(lidar_range_filter_cropbox_x_min);
DECLARE_double(lidar_range_filter_cropbox_x_max);
DECLARE_double(lidar_range_filter_cropbox_y_min);
DECLARE_double(lidar_range_filter_cropbox_y_max);
DECLARE_double(lidar_range_filter_cropbox_z_min);
DECLARE_double(lidar_range_filter_cropbox_z_max);

DECLARE_double(lidar_map_matching_freq);  // Hz
DECLARE_double(lidar_desired_matching_point_number);

DECLARE_double(ndt_matching_epsilon);
DECLARE_double(ndt_matching_step_size);
DECLARE_double(ndt_matching_resolution);
DECLARE_uint32(ndt_matching_max_iterations);
DECLARE_double(ndt_matching_map_leaf_size);
DECLARE_double(ndt_matching_input_leaf_size);

DECLARE_double(ndt_matching_gpu_epsilon);
DECLARE_double(ndt_matching_gpu_step_size);
DECLARE_double(ndt_matching_gpu_resolution);
DECLARE_uint32(ndt_matching_gpu_max_iterations);
DECLARE_double(ndt_matching_gpu_map_leaf_size);
DECLARE_double(ndt_matching_gpu_input_leaf_size);
DECLARE_double(lidar_localization_fusion_loc_gap_threshold);

DECLARE_bool(fusion_use_rtk);
DECLARE_double(vs_threshold_static_judge);

DECLARE_bool(ndt_matching_use_gpu);
DECLARE_bool(offline_mode);
DECLARE_bool(use_compressed_map);

DECLARE_uint32(map_loader_count);
DECLARE_double(map_loader_margin);
DECLARE_double(ndt_matching_fitness_score_threshold);
DECLARE_double(inter_frame_diff_threshold);
DECLARE_double(lidar_diff_time_threshold);

DECLARE_double(global_shift_max_dist);
DECLARE_double(rtk_cpt_height_diff);

DECLARE_uint32(lidar_align_freq_divider_cnt);

DECLARE_bool(map_loader_check_rtk_status);
DECLARE_bool(loc_init_check_rtk_status);
// if true, initial pose from only fix status
DECLARE_bool(map_matching_init_with_only_rtk_fix);
DECLARE_bool(map_matching_init_with_rtk_mean);
// eskf
DECLARE_string(FUSION_METHOD);
DECLARE_double(GRAVITY_MAGNITUDE);
DECLARE_double(LATITUDE);
DECLARE_double(ROTATION_SPEED);
DECLARE_double(PRIOR_POSI);
DECLARE_double(PRIOR_VEL);
DECLARE_double(PRIOR_ORI);
DECLARE_double(PRIOR_EPSILON);
DECLARE_double(PRIOR_DELTA);
DECLARE_double(PROCESS_GYRO);
DECLARE_double(PROCESS_ACCEL);
DECLARE_double(PROCESS_ACCEL_Z);
DECLARE_double(MEASUREMENT_GPS_POSI);
DECLARE_double(MEASUREMENT_GPS_POSI_Z);
DECLARE_double(MEASUREMENT_GPS_ORI);
DECLARE_double(MEASUREMENT_GPS_VEL);
DECLARE_double(MEASUREMENT_LIDAR_POSI);
DECLARE_double(MEASUREMENT_LIDAR_ORI);
DECLARE_double(MEASUREMENT_LIDAR_VEL);
DECLARE_double(MEASUREMENT_VEHICLE_SPEED_POSI);
DECLARE_double(MEASUREMENT_VEHICLE_SPEED_ORI);
DECLARE_double(MEASUREMENT_VEHICLE_SPEED_VEL);
DECLARE_bool(MOTION_CONSTRAINT_ACTIVATED);
DECLARE_double(MOTION_CONSTRAINT_W_B_THRESH);
DECLARE_bool(static_switch);
DECLARE_bool(eskf_rtk_fusion);
DECLARE_bool(eskf_lidar_backup_rtk);

DECLARE_string(spot_name);
DECLARE_double(base_lat);
DECLARE_double(base_lon);
DECLARE_double(base_height);

DECLARE_bool(eskf_lidar_fusion);
DECLARE_uint32(eskf_rtk_interval);
DECLARE_uint32(eskf_rtk_recover_time);
DECLARE_string(eskf_rtk_fusion_mode);
DECLARE_string(eskf_lidar_fusion_mode);
DECLARE_bool(eskf_init_rtk);
DECLARE_bool(correct_point_cloud);

DECLARE_bool(eskf_speed_fusion);
DECLARE_bool(eskf_using_wheelspeed);

DECLARE_bool(eskf_state_bound_limit_mode);
DECLARE_double(eskf_bg_bound_limit_threshold);
DECLARE_double(eskf_ba_bound_limit_threshold);
DECLARE_double(eskf_wheel_factor_bound_limit_threshold);

DECLARE_bool(eskf_diagnose_by_topic_mode);