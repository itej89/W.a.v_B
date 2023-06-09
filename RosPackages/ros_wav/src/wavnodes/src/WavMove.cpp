#include <iostream>
#include <fstream>
#include <cmath>

#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>

#include <tf/transform_datatypes.h>
#include <mutex>
#include <thread> 
#include <iostream>

#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include "nlohmann/json.hpp"

using namespace std;

//Amount of turn angle for Front wheel of inner rotation circle
//added abs for radius value lies in between middle circle and inner circle
// double cosPhi = abs(r-11.25)/(sqrt( (r*r) - (22.5*r) + 263.96));

//Amount of turn angle for Front wheel of outer rotation circle
// double cosAlpha = (r+11.25)/(sqrt( (r*r) + (22.5*r) + 263.96));



class WavMove
{
    private:
    ros::Publisher vel_pub;
    ros::Subscriber odom_sub;
    double max_vel_lin = 0.4;
    double min_vel_lin = 0.4;
    double max_vel_th = 0.3;
    double min_vel_th = 0.3;
    double min_in_place_vel_th = 0.68;
    double tolerance_trans_x = 0.15;
    double tolerance_trans_y = 0.15;
    double tolerance_rot = 30;
    double max_heading_diff_before_moving = 30;
    double footprint_data[4][2] = {{-0.18, -0.1775}, {-0.18, 0.1775}, {0.18, 0.1775}, {0.18, -0.1775}};
    geometry_msgs::Point footprint[4];

    nav_msgs::Odometry ROBOT_ODOMETRY;
    nav_msgs::Path NAV_PATH;
    int PoseIndex = 0;

        
    public:
    WavMove(ros::NodeHandle *nh)
    {
        nh->getParam("/WavMove/max_vel_lin", max_vel_lin);
        nh->getParam("/WavMove/min_vel_lin", min_vel_lin);
        nh->getParam("/WavMove/max_vel_th", max_vel_th);
        nh->getParam("/WavMove/min_vel_th", min_vel_th);
        nh->getParam("/WavMove/min_in_place_vel_th", min_in_place_vel_th);
        nh->getParam("/WavMove/tolerance_trans_x", tolerance_trans_x);
        nh->getParam("/WavMove/tolerance_trans_y", tolerance_trans_y);
        nh->getParam("/WavMove/tolerance_rot", tolerance_rot);
        nh->getParam("/WavMove/max_heading_diff_before_moving", max_heading_diff_before_moving);
        
        vel_pub = nh->advertise<geometry_msgs::Twist>("/cmd_vel", 50);
        odom_sub = nh->subscribe("/odom", 1000, &WavMove::odom_callback, this);

        std::cout << "max_vel_lin : " << max_vel_lin << std::endl;
        std::cout << "min_vel_lin : " << min_vel_lin << std::endl;
        std::cout << "max_vel_th : " << max_vel_th << std::endl;
        std::cout << "min_vel_th : " << min_vel_th << std::endl;
        std::cout << "tolerance_trans_x : " << tolerance_trans_x << std::endl;
        std::cout << "tolerance_trans_y : " << tolerance_trans_y << std::endl;
        std::cout << "tolerance_rot : " << tolerance_rot << std::endl;
        std::cout << "min_in_place_vel_th : " << min_in_place_vel_th << std::endl;
        std::cout << "max_heading_diff_before_moving : " << max_heading_diff_before_moving << std::endl;

        for(int i=0; i<4; i++)
        {
           footprint[i].x = footprint_data[i][0];
           footprint[i].y = footprint_data[i][1];
        }
    }



    void odom_callback(const nav_msgs::Odometry& odom)
    { 
       try
        {
          ROBOT_ODOMETRY.pose.pose.position.x = odom.pose.pose.position.x;
          ROBOT_ODOMETRY.pose.pose.position.y = odom.pose.pose.position.y;
          ROBOT_ODOMETRY.pose.pose.orientation.x = odom.pose.pose.orientation.x;
          ROBOT_ODOMETRY.pose.pose.orientation.y = odom.pose.pose.orientation.y;
          ROBOT_ODOMETRY.pose.pose.orientation.z = odom.pose.pose.orientation.z;
          ROBOT_ODOMETRY.pose.pose.orientation.w = odom.pose.pose.orientation.w;

          // tf::Quaternion q(odom.pose.pose.orientation.x, odom.pose.pose.orientation.y, odom.pose.pose.orientation.z, odom.pose.pose.orientation.w);
          // tf::Matrix3x3 m(q);
          // double roll, pitch, yaw;
          // m.getRPY(roll, pitch, yaw);

          // double yaw_degrees = yaw * 180.0 / M_PI; // conversion to degrees
          // if( yaw_degrees < 0 ) yaw_degrees += 360.0; // convert negative to positive angles

          // std::cout << "odom x : "<< odom.pose.pose.position.x <<std::endl;
          // std::cout << "odom y : "<< odom.pose.pose.position.x <<std::endl;
          // std::cout << "odom z : "<< yaw_degrees <<std::endl;
        }
        catch (exception& e)
        {
           std::cout << "error : "<< e.what() <<std::endl;
        }
    }

    void LoadPath(string Path)
    {

      std::cout<< "Loading path" << std::endl;

      std::ifstream ifs(Path);
      nlohmann::json jf = nlohmann::json::parse(ifs);
      nlohmann::json poseArray = jf["poses"];

      for (auto it = poseArray.begin(); it != poseArray.end(); ++it)
      {
        geometry_msgs::PoseStamped pose;

        pose.header.stamp = ros::Time::now();
        pose.header.frame_id = "base_link";
        pose.pose.position.x = (*it)["x"].get<float>();
        pose.pose.position.y = (*it)["y"].get<float>();
        float degree = (*it)["th"].get<float>();

        float radians = (M_PI/180)*degree;

        geometry_msgs::Quaternion orientation = tf::createQuaternionMsgFromYaw(radians);
        pose.pose.orientation = orientation;
      
        NAV_PATH.poses.push_back(pose);
      }
      
    }


    enum MOV_STATES {NA, GET_PATH_NEXT_POSE, DRIVE, CHECK_POSITION, FINISH} CURRENT_STATE=  NA;

    double GetPositiveYaw(tf::Quaternion q)
    {
         tf::Matrix3x3 m(q);
          double roll, pitch, yaw;
          m.getRPY(roll, pitch, yaw);

          double yaw_degrees = yaw * 180.0 / M_PI; // conversion to degrees
          if( yaw_degrees < 0 ) yaw_degrees += 360.0; // convert negative to positive angles

          return yaw_degrees;
    }

    void DO_PATH()
    {
      switch (CURRENT_STATE)
      {
        case GET_PATH_NEXT_POSE:
        {
          CURRENT_STATE = DRIVE;
          PoseIndex++;
          break;
        }
        case DRIVE:
        {
          break;
        }
        case CHECK_POSITION:
        {
          if(PoseIndex < NAV_PATH.poses.size())
          {
            tf::Quaternion robot_YAW(ROBOT_ODOMETRY.pose.pose.orientation.x, ROBOT_ODOMETRY.pose.pose.orientation.y, ROBOT_ODOMETRY.pose.pose.orientation.z, ROBOT_ODOMETRY.pose.pose.orientation.w);
            tf::Quaternion pose_YAW(NAV_PATH.poses[PoseIndex].pose.orientation.x, NAV_PATH.poses[PoseIndex].pose.orientation.y, NAV_PATH.poses[PoseIndex].pose.orientation.z, NAV_PATH.poses[PoseIndex].pose.orientation.w);
           
            double Bot_Yaw = GetPositiveYaw(robot_YAW);
            double Goal_Yaw = GetPositiveYaw(pose_YAW);

            if(abs(NAV_PATH.poses[PoseIndex].pose.position.x - ROBOT_ODOMETRY.pose.pose.position.x) < tolerance_trans_x &&
            abs(NAV_PATH.poses[PoseIndex].pose.position.y - ROBOT_ODOMETRY.pose.pose.position.y) < tolerance_trans_y &&
            abs(Bot_Yaw - Goal_Yaw) < tolerance_rot)
            {
              CURRENT_STATE = FINISH;
            }
            else
            {
              CURRENT_STATE = DRIVE;
            }
          }
          else
          {
            CURRENT_STATE = FINISH;
          }
          break;
        }
        case FINISH:
        {
          CURRENT_STATE = NA;
          break;
        }
        default:
          break;
      }
    }


};


int main(int argc, char **argv)
{

  ros::init(argc, argv, "WavMove");

  ros::NodeHandle nh;
 
  WavMove _WavMov = WavMove(&nh);

  _WavMov.LoadPath("/home/tej/Documents/WavRos/ros_wav/build/devel/lib/wavnodes/path_static/mapping.json");

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
