#!/bin/bash
source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"

rm "/home/wav/Documents/fmSpin/WavRos/wav_ros_packages/ros_wav/src/wavnodes/Maps/hector_map/hector_map.pgm"
rm "/home/wav/Documents/fmSpin/WavRos/wav_ros_packages/ros_wav/src/wavnodes/Maps/hector_map/hector_map.yaml"

rosrun map_server map_saver -f "/home/wav/Documents/fmSpin/WavRos/wav_ros_packages/ros_wav/src/wavnodes/Maps/hector_map/hector_map"
