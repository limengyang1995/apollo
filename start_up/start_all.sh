#! /bin/bash

source /opt/apollo/neo/setup.sh
if [ -e /opt/apollo/neo/packages/env-manager-dev/latest/scripts/auto_complete.bash ]; then . /opt/apollo/neo/packages/env-manager-dev/latest/scripts/auto_complete.bash; fi
[[ -e /opt/apollo/neo/setup.sh ]] && source /opt/apollo/neo/setup.sh

RTC_PATH=/opt/apollo/neo/src/modules/external_command/external_driver/rtc/lib
# echo $RTC_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH$RTC_PATH
source /apollo_workspace/start_up/carid.sh
# echo $LD_LIBRARY_PATH
echo "start launch"
bash /apollo_workspace/kill_all.sh
cyber_launch start /apollo_workspace/start_up/start.launch
