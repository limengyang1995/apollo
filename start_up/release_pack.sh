#! /bin/bash

bash -c "buildtool release -p modules/drivers/camera modules/drivers/canbus modules/external_command/external_driver modules/canbus modules/canbus_vehicle/venus modules/control/control_component modules/control/controllers/lat_based_lqr_controller modules/control/controllers/lon_based_pid_controller modules/control/controllers/mpc_controller"
