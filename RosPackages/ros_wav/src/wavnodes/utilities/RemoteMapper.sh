export ROS_IP=192.168.1.135
export ROS_MASTER_URI=http://192.168.1.126:11311


roslaunch rtabmap_ros rtabmap.launch  database_path:="/home/tej/Documents/WavRos/Maps/TejRoom_N.db"  subscribe_rgbd:=true rgbd_topic:=/rtabmap/rgbd_image compressed:=true 



# export ROS_NAMESPACE=rtabmap
# rosrun rtabmap_ros rtabmapviz _frame_id:=base_link

# source /home/tej/Documents/WavRos/rtabmap/devel/setup.bash


roslaunch rtabmap_ros rtabmap.launch  database_path:="/home/tej/Documents/WavRos/Maps/House.db" localization:=true  subscribe_rgbd:=true  publish_tf:=true rgbd_topic:=/rtabmap/rgbd_image compressed:=true  frame_id:=base_link

roslaunch rtabmap_ros rtabmap.launch  database_path:="/home/tej/Documents/WavRos/Maps/House.db"  subscribe_rgbd:=true rgbd_topic:=/rtabmap/rgbd_image compressed:=true  frame_id:=base_link



roslaunch rtabmap_ros rtabmap.launch  database_path:="/home/tej/Documents/WavRos/Maps/House.db" localization:=true  subscribe_rgbd:=true  publish_tf:=true rgbd_topic:=/rtabmap/rgbd_image_relay visual_odometry:=false odom_topic:="/odometry/filtered" frame_id:=base_link

roslaunch rtabmap_ros rtabmap.launch  database_path:="/home/tej/Documents/WavRos/Maps/House.db" localization:=true  subscribe_rgbd:=true  publish_tf:=true rgbd_topic:=/rtabmap/rgbd_image compressed:=true  frame_id:=base_link



roslaunch wavnodes rtabmap_kinect.launch 

roslaunch wavnodes wav_localization.launch 

source ~/Documents/WavRos/wav_move_base/devel/setup.bash 
roslaunch wavnodes move_base_Trajectory_Planner.launch 

rosrun rviz rviz

<node pkg="tf" type="static_transform_publisher" name="tf_broadcaster_cam" args="0 0 0.63 0 0 0 1 base_link camera_link 100" />

<node pkg="tf" type="static_transform_publisher" name="tf_broadcaster" args="0 0 0 0 0 -0.707107 0.707107 base_link base_imu_link 200" />


roslaunch rtabmap_ros rtabmap.launch  database_path:="/home/tej/Documents/WavRos/Maps/TejRoom.db"  subscribe_rgbd:=true  publish_tf:=true rgbd_topic:=/rtabmap/rgbd_image compressed:=true  frame_id:=base_link
