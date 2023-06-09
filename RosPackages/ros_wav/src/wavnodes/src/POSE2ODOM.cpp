#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Quaternion.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>
#include <mutex>
#include <thread> 
#include <iostream>


using namespace std;



ros::Publisher laser_odom_pub;

bool pub_odom = false;
bool pub_odom_tf = false;

void PoseStamped_callback(const geometry_msgs::PoseStamped& posestamped)
{ 

tf::TransformBroadcaster tf_br;

   std::cout << "Recived Data" <<std::endl;
                 
      //first, we'll publish the transform over tf
      geometry_msgs::TransformStamped odom_trans;
      odom_trans.header.stamp = posestamped.header.stamp;
      odom_trans.header.frame_id = "odom";
      odom_trans.child_frame_id = posestamped.header.frame_id;
  
      odom_trans.transform.translation.x = posestamped.pose.position.x;
      odom_trans.transform.translation.y = posestamped.pose.position.y;
      odom_trans.transform.translation.z = 0.0;
      odom_trans.transform.rotation = posestamped.pose.orientation;
  
      //next, we'll publish the odometry message over ROS
      nav_msgs::Odometry odom;
      odom.header.stamp = posestamped.header.stamp;
      odom.header.frame_id = "odom";
  
  
      //set the position
      odom.pose.pose.position.x = posestamped.pose.position.x;
      odom.pose.pose.position.y = posestamped.pose.position.y;
      odom.pose.pose.position.z = 0.0;
      odom.pose.pose.orientation = posestamped.pose.orientation;
  
      //set the velocity
      odom.child_frame_id = posestamped.header.frame_id;
      odom.twist.twist.linear.x = 0;
      odom.twist.twist.linear.y = 0;
      odom.twist.twist.angular.z = 0;

      if(pub_odom)
      {
        laser_odom_pub.publish(odom);
      }

      if(pub_odom_tf)
      {
        tf_br.sendTransform(odom_trans);
      }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "POSE2ODOM");

  ros::NodeHandle private_node_handle("~");
  
  private_node_handle.param<bool>("pub_odom", pub_odom, true);
  private_node_handle.param<bool>("pub_odom_tf", pub_odom_tf, true);


  ros::NodeHandle nPCL;
  laser_odom_pub = nPCL.advertise<nav_msgs::Odometry>("/wav_laser_odom", 50);


  ros::NodeHandle nPose;
  ros::Subscriber nPose_Sub = nPose.subscribe("/slam_out_pose", 1000, PoseStamped_callback);

  ros::Rate r(5); //5hz

  ros::Time lastOdOTime = ros::Time::now();
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
