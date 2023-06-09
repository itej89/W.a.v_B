#!/bin/bash

source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

rostopic pub /planner/move_base_simple/goal geometry_msgs/PoseStamped "header:
  seq: 0
  stamp:
    secs: 0
    nsecs: 0
  frame_id: 'map'
pose:
    position: {x: -3.9924733638, y: -3.99992442131, z: 0.0}
    orientation: {x: 0.0, y: 0.0, z: -0.71428777494, w: 0.699852109064}"