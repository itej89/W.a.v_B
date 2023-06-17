#!/bin/bash
source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

rm "~/Documents/fmSpin/W.a.v_B/RosPackages/ros_wav/src/wavnodes/Maps/hector_map/hector_map.pgm"
rm "~/Documents/fmSpin/W.a.v_B/RosPackages/ros_wav/src/wavnodes/Maps/hector_map/hector_map.yaml"

rosrun map_server map_saver -f "~/Documents/fmSpin/W.a.v_B/RosPackages/ros_wav/src/wavnodes/Maps/hector_map/hector_map"
