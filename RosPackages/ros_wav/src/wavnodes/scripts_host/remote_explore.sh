#!/bin/bash

source "${BASH_SOURCE%/*}/.ros_profile"
source "${BASH_SOURCE%/*}/.remote_profile"


printf "%s" "waiting for Wav B ..."
while ! timeout 0.2 ping -c 1 -n 10.42.0.1 &> /dev/null
do
    printf "%c" "."
done
printf "\n%s\n"  "Wav B is online"


ssh wavb@10.42.0.1 'bash ~/Documents/fmSpin/W.a.v_B/RosPackages/ros_wav/src/wavnodes/scripts_bot/runbot_explore.sh' &

until rostopic list | grep -m 1 "/rtabmap/rgbd_image/compressed"; do sleep 1; done

scriptname="$0"
# /home/tej/Documents/fmSpin/WavRos/wav_ros_packages/ros_wav/src/wavnodes/scripts_host/${scriptname} &


until rostopic list | grep -m 1 "/rtabmap/grid_map"; do sleep 1; done



read -p "Press any key to continue... " -n1 -s


ssh wavb@10.42.0.1 'bash ~/Documents/fmSpin/W.a.v_B/RosPackages/ros_wav/src/wavnodes/scripts_bot/save_map.sh'


botKillID=$(ssh wavb@10.42.0.1   ps aux | grep -e "[r]unbot_explore.sh" | awk -F" " '{print $2}')

echo "BotID : ${botKillID}"

ssh tej@10.42.0.1 kill -SIGTERM ${botKillID}



serverKillID=$(ps aux | grep -e "${scriptname}" | awk -F" " '{print $2}')

echo "serverID : ${serverKillID}"

kill -SIGTERM ${serverKillID}