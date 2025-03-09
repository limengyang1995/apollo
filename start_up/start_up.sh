!/bin/bash

#_______________________________________________sync_start_______________________________________________________#
#bash -c "echo nvidia | sudo -S tztek-jetson-tool-cpld-test -d /dev/ttyTHS1 -t 3 -l 232 -b 115200;exec bash" 

#_______________________________________________camera_trigger___________________________________________________#
bash -c "echo nvidia | sudo -S tztek-jetson-tool-cpld-test -d /dev/ttyTHS1 -t 4 -c 8 -f 30 -w 1000 -o 0;exec bash" 
#sleep 5s

#_______________________________________________sync_check_______________________________________________________#
#bash -c "echo nvidia | sudo -S service chrony restart;exec bash" 

