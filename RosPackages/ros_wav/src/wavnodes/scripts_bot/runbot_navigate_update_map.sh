#!/bin/bash
source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

rm /home/tej/Documents/fmSpin/W.a.v_B/RosPackages/ros_wav/src/wavnodes/Maps/TejRoom.db

trap "exit" INT TERM ERR
trap "kill 0" EXIT
rosclean purge -y
roslaunch wavnodes wavnodes.launch &
until rostopic list | grep -m 1 "/rtabmap/rgbd_image/compressed"; do sleep 1; done
roslaunch wavnodes rtabmap_kinect.launch &
roslaunch wavnodes wav_mapping.launch &
roslaunch wavnodes move_base_Trajectory_Planner.launch &
# roslaunch wavnodes explore.launch &
wait
