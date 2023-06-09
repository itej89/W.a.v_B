#!/bin/bash


source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

trap "exit" INT TERM ERR
trap "kill 0" EXIT
# rosparam set /WavComms/joy_control true
roslaunch wavnodes cartographer_kinect.launch &
roslaunch cartographer_ros my_robot_2d.launch &
roslaunch wavnodes move_base_Trajectory_Planner_Cartographer.launch &
rosrun rviz rviz &
wait


