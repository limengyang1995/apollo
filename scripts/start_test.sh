#!/bin/sh
#_______________________________________________sync_start_______________________________________________________#
gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-cpld-test -d /dev/ttyTHS1 -t 3 -l 232 -b 115200;exec bash" '
sleep 1s

#_______________________________________________camera_trigger___________________________________________________#
gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-cpld-test -d /dev/ttyTHS1 -t 4 -c 8 -f 30 -w 1000 -o 0;exec bash" '
sleep 5s

#_______________________________________________sync_check_______________________________________________________#
gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S service chrony restart;exec bash" '
sleep 1s
gnome-terminal --window -e 'bash -c "watch chronyc sources -v;exec bash" '
sleep 1s

#_______________________________________________camera_show 0&1__________________________________________________#
#gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-camera-show-cuda /dev/video0 1920 1080;exec bash" '
#sleep 1s
#gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-camera-show-cuda /dev/video1 1920 1080;exec bash" '
#sleep 1s
#gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-camera-show-cuda /dev/video4 1920 1080;exec bash" '
#sleep 1s
#gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-camera-show-cuda /dev/video5 1920 1080;exec bash" '
#sleep 1s
#gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-camera-show-cuda /dev/video6 1920 1080;exec bash" '
#sleep 1s
#gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-camera-show-cuda /dev/video7 1920 1080;exec bash" '
#sleep 1s
#gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S tztek-jetson-tool-camera-show-cuda /dev/video2 3840 2160;exec bash" '
#sleep 1s

#_______________________________________________sync_lidar_______________________________________________________#
gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S ptp4l -m -S -E -2 -i eth0;exec bash" '
sleep 10s

#_______________________________________________can0_init________________________________________________________#
gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S ip link set can0 type can bitrate 500000;exec bash" '
sleep 1s
gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S ip link set up can0;exec bash" '
sleep 1s

#_______________________________________________can0 rx message show_____________________________________________#
gnome-terminal --window -e 'bash -c "candump can0;exec bash" '
sleep 1s

#_______________________________________________RS232 init_______________________________________________________#
gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S chmod 777 /dev/ttysWK1;exec bash" '
sleep 1s

# #_______________________________________________ros start imu____________________________________________________#
# gnome-terminal --window -e 'bash -c "roslaunch ins demo.launch;exec bash" '
# sleep 1s
# #gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S ip link set can1 type can bitrate 500000;exec bash" '
# #sleep 1s
# #gnome-terminal --window -e 'bash -c "echo nvidia | sudo -S ip link set up can1;exec bash" '
# #sleep 1s

# #_______________________________________________ros start lidar 40P______________________________________________#
# gnome-terminal --window -e 'bash -c "roslaunch hesai_lidar hesai_lidar.launch;exec bash" '
# sleep 5s

# #_______________________________________________rostopic check____________________________________________________#
# gnome-terminal --window -e 'bash -c "rostopic echo /INS/ASENSING_INS/header;exec bash" '
# sleep 5s
# gnome-terminal --window -e 'bash -c "rostopic echo /lidar/main/header;exec bash" '
# sleep 5s
