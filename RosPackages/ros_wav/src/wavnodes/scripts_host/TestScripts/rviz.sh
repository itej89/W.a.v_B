#!/bin/bash


source "${BASH_SOURCE%/*}/.ros_profile"
# source "${BASH_SOURCE%/*}/.remote_profile"

trap "exit" INT TERM ERR
trap "kill 0" EXIT
rosrun rviz rviz &
wait


