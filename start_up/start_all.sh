#! /bin/bash

source /opt/apollo/neo/setup.sh
if [ -e /opt/apollo/neo/packages/env-manager-dev/latest/scripts/auto_complete.bash ]; then . /opt/apollo/neo/packages/env-manager-dev/latest/scripts/auto_complete.bash; fi
[[ -e /opt/apollo/neo/setup.sh ]] && source /opt/apollo/neo/setup.sh

RTC_PATH=/opt/apollo/neo/src/modules/external_command/external_driver/rtc/lib
# ROCKCHIP_PATH=/opt/apollo/neo/src/modules/external_command/external_driver/multimedia/rockchip/lib/lib64
# echo $RTC_PATH
source /apollo_workspace/start_up/carid.sh
# echo $LD_LIBRARY_PATH``
echo "start launch"
bash /apollo_workspace/kill_all.sh
nohup taskset -c 3,4,5 cyber_launch start /apollo_workspace/start_up/lidar_gnss_camera.launch > /apollo_workspace/start_up/start.log 2>&1 &
sleep 1
nohup taskset -c 0,1,2 cyber_launch start /apollo_workspace/start_up/perception.launch > /apollo_workspace/start_up/start.log 2>&1 &
sleep 1 
nohup taskset -c 6,7 cyber_launch start /apollo_workspace/start_up/localization_pnc.launch > /apollo_workspace/start_up/start.log 2>&1 &

echo "start sucess!!"