#include <geometry_msgs/Quaternion.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>


#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/Temperature.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <mutex>
#include <thread>
#include <iostream>

#include "rtabmap_msgs/RGBDImage.h"

using namespace std;

class RGBD2PCL{
  private:
  bool PARAM;
  ros::Publisher camera_info_pub;
  ros::Publisher color_image_pub;
  ros::Publisher depth_image_pub;
  ros::Subscriber rgbd_Sub;

  public:
  RGBD2PCL(ros::NodeHandle *nh){
        nh->param<bool>("PARAM", PARAM, true);

        camera_info_pub = nh->advertise<sensor_msgs::CameraInfo>("/wav_camera_info", 50);
        color_image_pub = nh->advertise<sensor_msgs::Image>("/wav_image_color", 50);
        depth_image_pub = nh->advertise<sensor_msgs::Image>("/wav_depth_image", 50);

        rgbd_Sub = nh->subscribe("/rtabmap/rgbd_image_relay", 1000, &RGBD2PCL::RGBD_callback, this);
  }

  void RGBD_callback(const rtabmap_msgs::RGBDImage& rgbd)
  {
    std::cout << "Recived Data" <<std::endl;
    camera_info_pub.publish(rgbd.rgb_camera_info);
    color_image_pub.publish(rgbd.rgb);

    depth_image_pub.publish(rgbd.depth);
  }


};


int main(int argc, char **argv)
{

  ros::init(argc, argv, "RGBD2PCL");

  ros::NodeHandle nh;

  RGBD2PCL _RGBD2PCL = RGBD2PCL(&nh);

  ros::Rate r(5); //5hz

  while(ros::ok())
  {
        try
        {

        }
        catch (exception& e)
        {
          ROS_ERROR_STREAM("Error in process loop\n");
          ros::Duration(5).sleep();
        }
    ros::spinOnce();
    r.sleep();
  }

}
