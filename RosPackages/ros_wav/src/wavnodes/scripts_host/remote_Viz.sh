#!/bin/bash


source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

trap "exit" INT TERM ERR
trap "kill 0" EXIT
# roslaunch wavnodes wav_visualization.launch &
rosrun rviz rviz -d ~/Documents/fmSpin/W.a.v_B/RosPackages/ros_wav/src/wavnodes/rviz/nav.rviz &
wait


