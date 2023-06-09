#!/bin/bash


source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

trap "exit" INT TERM ERR
trap "kill 0" EXIT
# roslaunch wavnodes wav_visualization.launch &
rosrun rviz rviz -d /home/tej/Documents/fmSpin/WavRos/wav_ros_packages/nav.rviz &
wait


