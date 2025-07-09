#! /bin/bash

source /opt/apollo/neo/setup.sh
if [ -e /opt/apollo/neo/packages/env-manager-dev/latest/scripts/auto_complete.bash ]; then . /opt/apollo/neo/packages/env-manager-dev/latest/scripts/auto_complete.bash; fi
[[ -e /opt/apollo/neo/setup.sh ]] && source /opt/apollo/neo/setup.sh

RTC_PATH=/opt/apollo/neo/src/modules/external_command/external_driver/rtc/lib
ROCKCHIP_PATH=/opt/apollo/neo/src/modules/external_command/external_driver/multimedia/rockchip/lib/lib64
# echo $RTC_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$RTC_PATH:$ROCKCHIP_PATH
source /apollo_workspace/start_up/carid.sh
# echo $LD_LIBRARY_PATH``

log_dir=/apollo_workspace/data/log/
log_file_suffix=$(date +%y%m%d-%H%M%S).log

echo "start launch"
bash /apollo_workspace/kill_all.sh
#rtc_publisher_server > ${log_dir}/rtc_publisher_server_${log_file_suffix} &
cyber_launch start /apollo_workspace/start_up/start.launch
