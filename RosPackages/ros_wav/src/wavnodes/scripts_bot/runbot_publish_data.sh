#!/bin/bash
source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

rm /home/tej/Documents/fmSpin/W.a.v_B/RosPackages/ros_wav/src/wavnodes/Maps/rtab_map/TejRoom.db

trap "exit" INT TERM ERR
trap "kill 0" EXIT
rosclean purge -y
roslaunch wavnodes wavnodes.launch &
wait
