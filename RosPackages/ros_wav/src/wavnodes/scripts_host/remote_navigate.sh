#!/bin/bash

source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"


printf "%s" "waiting for Wav B ..."
while ! timeout 0.2 ping -c 1 -n 10.42.0.1 &> /dev/null
do
    printf "%c" "."
done
printf "\n%s\n"  "Wav B is online"


ssh wav@10.42.0.1 'bash /home/wav/Documents/fmSpin/WavRos/wav_ros_packages/ros_wav/src/wavnodes/scripts_bot/runbot_navigate.sh' &





until rostopic list | grep -m 1 "/rtabmap/rgbd_image/compressed"; do sleep 1; done

scriptname="$0"
# scriptname = /home/tej/Documents/fmSpin/WavRos/wav_ros_packages/ros_wav/src/wavnodes/scripts_host/${scriptname} &


until rostopic list | grep -m 1 "/map"; do sleep 1; done


# rostopic pub /initialpose geometry_msgs/PoseWithCovarianceStamped "header:
#   seq: 0
#   stamp:
#     secs: 0
#     nsecs: 0
#   frame_id: 'map'
# pose:
#   pose:
#     position: {x: 0.715760970116, y: 0.709349298477, z: 0.0}
#     orientation: {x: 0.0, y: 0.0, z: -0.0110906715094, w: 0.999938496611}
#   covariance: [0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0,
#   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
#   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.06853892326654787]" --once &



until rostopic list | grep -m 1 "/rtabmap/grid_map"; do sleep 1; done


# rostopic pub /initialpose geometry_msgs/PoseWithCovariance -f  initialpose.yaml


#   rostopic pub /initialpose geometry_msgs/PoseWithCovarianceStamped "header:
#   seq: 0
#   stamp:
#     secs: 0
#     nsecs: 0
#   frame_id: 'map'
# pose:
#   pose:
#     position: {x: 0.815760970116, y: 0.809349298477, z: 0.0}
#     orientation: {x: 0.0, y: 0.0, z: -0.02568027411394, w: 0.999670207379}
#   covariance: [0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0,
#   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
#   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.06853892326654787]" --once &



read -p "Press any key to continue... " -n1 -s




botKillID=$(ssh wav@10.42.0.1   ps aux | grep -e "[r]unbot_navigate.sh" | awk -F" " '{print $2}')

echo "BotID : ${botKillID}"

ssh wav@10.42.0.1 kill -SIGTERM ${botKillID}



serverKillID=$(ps aux | grep -e "${scriptname}" | awk -F" " '{print $2}')

echo "serverID : ${serverKillID}"

kill -SIGTERM ${serverKillID}