#!/bin/bash


source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

trap "exit" INT TERM ERR
trap "kill 0" EXIT
# rosparam set /WavComms/joy_control true
roslaunch wavnodes rtabmap_kinect.launch &
roslaunch wavnodes wav_mapping.launch &
roslaunch wavnodes move_base_Trajectory_Planner.launch &
rosrun rviz rviz &
wait


