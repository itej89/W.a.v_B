#include <ros/ros.h>

//imcluded to avoid compilation errors
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/buffer.h>
#include <tf2/transform_datatypes.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.h>

#include <sensor_msgs/PointCloud2.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/message_filter.h>
#include <message_filters/subscriber.h>
#include <geometry_msgs/PointStamped.h>
#include <ros/console.h>
#include "rtabmap_msgs/RGBDImage.h"

using namespace std;

class PCLTFCHECK
{
  private:
    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener tf2_;
    ros::NodeHandle g_nh;
    message_filters::Subscriber<sensor_msgs::PointCloud2> point_sub_;
    tf2_ros::MessageFilter<sensor_msgs::PointCloud2> tf2_filter_;

  public:
    void pointCloud2Callback(const sensor_msgs::PointCloud2ConstPtr& message);
    PCLTFCHECK();
    ~PCLTFCHECK();
};

void PCLTFCHECK::pointCloud2Callback(const sensor_msgs::PointCloud2ConstPtr& message)
{

    geometry_msgs::PointStamped global_origin;

    geometry_msgs::PointStamped local_origin;
    local_origin.header.stamp = (*message).header.stamp;
    local_origin.header.frame_id = "camera_link";
    local_origin.point.x = 0;
    local_origin.point.y = 0;
    local_origin.point.z = 0;

    sensor_msgs::PointCloud2 global_frame_cloud;

  try
  {
    buffer_.transform(local_origin, global_origin, "odom");
  }
   catch (tf2::TransformException &ex) 
  {
    ROS_ERROR("TF Exception that should never happen for sensor frame: %s, cloud frame: %s, %s", "camera_link",
              (*message).header.frame_id.c_str(), ex.what());
  std::cout << "Exception 1" << std::endl;
  }

  try
  {
    buffer_.transform((*message), global_frame_cloud, "odom");
  }
   catch (tf2::TransformException &ex)
  {
    ROS_ERROR("TF Exception that should never happen for sensor frame: %s, cloud frame: %s, %s", "camera_link",
              (*message).header.frame_id.c_str(), ex.what());
    std::cout << "Exception 2" << std::endl;
  }

  std::cout << (*message).header << "\n\n\n" << std::endl;

}

PCLTFCHECK::PCLTFCHECK() : 
tf2_(buffer_), tf2_filter_(point_sub_, buffer_, "odom", 50, 0)
{
  point_sub_.subscribe(g_nh, "wav_pcl", 50);
  tf2_filter_.registerCallback( boost::bind(&PCLTFCHECK::pointCloud2Callback, this, _1) );

  std::cout << "Subscribed!!" << std::endl;
}

PCLTFCHECK::~PCLTFCHECK()
{

}

int main(int argc, char **argv)
{
  bool PARAM;

  ros::init(argc, argv, "PCLTFCHECK");

  PCLTFCHECK pclCheck;
  
  ros::Rate r(1000); //5hz

  while(ros::ok())
  {
    ros::spinOnce();
    r.sleep();
  }


}
