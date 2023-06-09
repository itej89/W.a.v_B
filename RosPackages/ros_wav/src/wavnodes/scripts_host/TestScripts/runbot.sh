#!/bin/bash
source /opt/ros/melodic/setup.bash
source ~/Documents/WavRos/ros_wav/devel/setup.bash

export ROS_IP=10.42.0.1
export ROS_MASTER_URI=http://10.42.0.1:11311

trap "exit" INT TERM ERR
trap "kill 0" EXIT
rosclean purge -y
roslaunch wavnodes wavnodes.launch &
wait
