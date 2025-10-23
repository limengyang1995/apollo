#include "multilocalization_gflags.h"

DEFINE_bool(debug, false, "debug eskf");
DEFINE_bool(location_mode, true, "");
DEFINE_string(fusion_mode, "eskf", "");
DEFINE_string(calibration_config_path, "/home/ubuntu/haomo/HiDelivery/data/hw.prototxt", "");
DEFINE_double(optimization_rtk_noise, 0.5, "");
DEFINE_double(fusion_rtk_lidar_pose_time_diff_threshold_s, 0.5, "");
DEFINE_string(output_map_dir_path, "/localization/data/output_map", "");
DEFINE_string(map_dir_path, "/localization/data/map", "");
DEFINE_string(loc_map_dir, "/etc/data/map/ShunShiJiaYe.pcd", "");

DEFINE_int32(auto_save_map_idle_threshold, 10, "Auto save map if lidar odom pool is empty for 10s");
DEFINE_bool(use_rtk_prior, true, "");
DEFINE_uint32(rtk_hardware_version, 2, "");
DEFINE_uint32(localization_acc_acquired_from, 0, "");

DEFINE_double(scan_context_max_radius, 80, "");
DEFINE_double(scan_context_max_theta, 360, "");
DEFINE_uint32(scan_context_num_rings, 20, "");
DEFINE_uint32(scan_context_num_sectors, 60, "");
DEFINE_uint32(scan_context_indexing_interval, 1, "");
DEFINE_uint32(scan_context_min_key_frame_seq_distance, 100, "");
DEFINE_uint32(scan_context_num_candidates, 5, "");
DEFINE_double(scan_context_fast_alignment_search_ratio, 0.1, "");
DEFINE_double(scan_context_scan_context_distance_thresh, 0.20, "");
DEFINE_bool(playback_mode, false, "");
DEFINE_bool(output_evaluation_files, false, "");
DEFINE_double(fusion_acc_noise, 0.01, "");
DEFINE_double(fusion_acc_z_noise, 1, "");
DEFINE_double(fusion_gyro_noise, 1, "");
DEFINE_double(fusion_acc_bias_noise, 1e-6, "");
DEFINE_double(fusion_gyro_bias_noise, 1e-8, "");
DEFINE_double(fusion_laser_pose_noise, 0.3, "");
DEFINE_double(fusion_laser_orient_noise, 0.01, "");
DEFINE_double(fusion_laser_z_noise, 1e-10, "");
DEFINE_double(fusion_rtk_pose_noise, 0.8, "");
DEFINE_double(fusion_rtk_orient_noise, 1e20, "");
DEFINE_double(fusion_wheelspd_noise, 0.1, "");
DEFINE_double(wheel_factor, 1.005, "");
DEFINE_uint32(rtk_interval, 6, "");
DEFINE_double(fusion_rtk_z_noise, 1e20, "");

DEFINE_bool(lidar_filter, true, "");
DEFINE_double(lidar_filter_cropbox_x_min, -0.6, "");
DEFINE_double(lidar_filter_cropbox_x_max, 1.8, "");
DEFINE_double(lidar_filter_cropbox_y_min, -0.8, "");
DEFINE_double(lidar_filter_cropbox_y_max, 0.8, "");
DEFINE_double(lidar_filter_cropbox_z_min, -0.5, "");
DEFINE_double(lidar_filter_cropbox_z_max, 1.5, "");

DEFINE_bool(lidar_range_filter, true, "");
DEFINE_double(lidar_range_filter_cropbox_x_min, -60, "");
DEFINE_double(lidar_range_filter_cropbox_x_max, 60, "");
DEFINE_double(lidar_range_filter_cropbox_y_min, -50, "");
DEFINE_double(lidar_range_filter_cropbox_y_max, 50, "");
DEFINE_double(lidar_range_filter_cropbox_z_min, 0, "");
DEFINE_double(lidar_range_filter_cropbox_z_max, 10, "");

DEFINE_double(lidar_map_matching_freq, 2, "");  // Hz
DEFINE_double(lidar_desired_matching_point_number, 5000, "");

DEFINE_double(ndt_matching_epsilon, 0.01, "");
DEFINE_double(ndt_matching_step_size, 0.1, "");
DEFINE_double(ndt_matching_resolution, 1, "");
DEFINE_uint32(ndt_matching_max_iterations, 30, "");
DEFINE_double(ndt_matching_map_leaf_size, 0.8, "");
DEFINE_double(ndt_matching_input_leaf_size, 1.5, "");

DEFINE_double(ndt_matching_gpu_epsilon, 0.01, "");
DEFINE_double(ndt_matching_gpu_step_size, 0.1, "");
DEFINE_double(ndt_matching_gpu_resolution, 1, "");
DEFINE_uint32(ndt_matching_gpu_max_iterations, 30, "");
DEFINE_double(ndt_matching_gpu_map_leaf_size, 0.1, "");
DEFINE_double(ndt_matching_gpu_input_leaf_size, 0.2, "");
DEFINE_double(lidar_localization_fusion_loc_gap_threshold, 100000, "in us");

DEFINE_bool(fusion_use_rtk, false, "");
DEFINE_double(vs_threshold_static_judge, 0.1, "");

DEFINE_bool(ndt_matching_use_gpu, true, "");
DEFINE_bool(offline_mode, false, "");
DEFINE_bool(use_compressed_map, true, "");
DEFINE_uint32(map_loader_count, 200, "");
DEFINE_double(map_loader_margin, 80, "");
DEFINE_double(ndt_matching_fitness_score_threshold, 200, "");
DEFINE_double(inter_frame_diff_threshold, 10.0, "");
DEFINE_double(lidar_diff_time_threshold, 0.3, "unit: s");
DEFINE_double(global_shift_max_dist, 20000, "");
DEFINE_double(rtk_cpt_height_diff, 8.7, "");

DEFINE_uint32(lidar_align_freq_divider_cnt, 1, "");

DEFINE_bool(map_loader_check_rtk_status, false, "");
DEFINE_bool(loc_init_check_rtk_status, false, "");
DEFINE_bool(map_matching_init_with_only_rtk_fix, false, "");
DEFINE_bool(map_matching_init_with_rtk_mean, true, "");
// eskf
DEFINE_string(FUSION_METHOD, "error_state_kalman_filter", "");
DEFINE_double(GRAVITY_MAGNITUDE, 9.80157, "");
DEFINE_double(LATITUDE, 40, "");
DEFINE_double(ROTATION_SPEED, 7.292115e-5, "");
DEFINE_double(PRIOR_POSI, 1.0e-2, "");
DEFINE_double(PRIOR_VEL, 1.0e-2, "");
DEFINE_double(PRIOR_ORI, 1.0e-4, "");
DEFINE_double(PRIOR_EPSILON, 1.0e-3, "");
DEFINE_double(PRIOR_DELTA, 1.0e-3, "");
DEFINE_double(PROCESS_GYRO, 1e-8, "");
DEFINE_double(PROCESS_ACCEL, 4e-4, "");
DEFINE_double(PROCESS_ACCEL_Z, 4e-4, "");
DEFINE_double(MEASUREMENT_GPS_POSI, 5e-2, "");
DEFINE_double(MEASUREMENT_GPS_POSI_Z, 1e-2, "");
DEFINE_double(MEASUREMENT_GPS_ORI, 5e-5, "");
DEFINE_double(MEASUREMENT_GPS_VEL, 1e-2, "");
DEFINE_double(MEASUREMENT_LIDAR_POSI, 1.0e-2, "");
DEFINE_double(MEASUREMENT_LIDAR_ORI, 5e-4, "");
DEFINE_double(MEASUREMENT_LIDAR_VEL, 2.5e-5, "");
DEFINE_double(MEASUREMENT_VEHICLE_SPEED_POSI, 1.0e-2, "");
DEFINE_double(MEASUREMENT_VEHICLE_SPEED_ORI, 1.0e-3, "");
DEFINE_double(MEASUREMENT_VEHICLE_SPEED_VEL, 0.1, "");
DEFINE_bool(MOTION_CONSTRAINT_ACTIVATED, false, "");
DEFINE_double(MOTION_CONSTRAINT_W_B_THRESH, 0.13, "");
DEFINE_bool(static_switch, false, "");
DEFINE_bool(eskf_rtk_fusion, true, "");
DEFINE_bool(eskf_lidar_backup_rtk, false, "");
DEFINE_bool(eskf_lidar_fusion, true, "");
DEFINE_uint32(eskf_rtk_interval, 0, "");
DEFINE_uint32(eskf_rtk_recover_time, 0, "");
DEFINE_bool(eskf_init_rtk, true, "");
DEFINE_string(eskf_rtk_fusion_mode, "POSE_VEL", "");
DEFINE_bool(eskf_speed_fusion, true, "");
DEFINE_bool(eskf_using_wheelspeed, false, "");
DEFINE_string(eskf_lidar_fusion_mode, "POSE", "");

DEFINE_string(spot_name, "mapo", "");
DEFINE_double(base_lat, 40.1696614, "reference lat lon for conversion from latlon to local enu");
DEFINE_double(base_lon, 116.6567247, "");
DEFINE_double(base_height, 37.32699966430664, "");
DEFINE_bool(correct_point_cloud, false, "");

DEFINE_bool(eskf_state_bound_limit_mode, true, "");
DEFINE_double(eskf_bg_bound_limit_threshold, 0.15, "");
DEFINE_double(eskf_ba_bound_limit_threshold, 0.3, "");
DEFINE_double(eskf_wheel_factor_bound_limit_threshold, 0.05, "");

DEFINE_bool(eskf_diagnose_by_topic_mode, true, "");