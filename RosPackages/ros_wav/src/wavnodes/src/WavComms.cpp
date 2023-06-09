#include <geometry_msgs/Quaternion.h>
#include <ros/ros.h>
#include "serial/serial.h"
#include <std_msgs/Byte.h>
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

using namespace std;


serial::Serial base_serial;
serial::Serial head_serial;

bool find_port(std::string port_name)
{
  std::vector<serial::PortInfo> port_list =  serial::list_ports();

  for(serial::PortInfo pInfo : port_list) 
  {
    if(pInfo.port == port_name) return true;
  }
  return false;
}


float Steering_Rmin  = 363.407; //in mm
float Vx_max  = 200.0; //in mm/sec


float Cache_Lx = 0;
float Cache_Ly = 0;
float Cache_Az = 0;
float Cache_Th = 0;

bool SteerMode = false;
uint8_t VelocityCommand[] = {0x00, 0x53, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x50, 0x00};
uint8_t SteerCommand[]    = {0x00, 0x53, 0x54, 0x00, 0x00, 0x00, 0x00, 0x53, 0x50, 0x00};

bool IsWaitingForAck  = false;
ros::Time LastVelCommandTrigger;
void SendVelCommand()
{

   if(!IsWaitingForAck || (ros::Time::now().toSec() - LastVelCommandTrigger.toSec() > 5))
  {
      std::cout<<"Sending Velocity Command"<<std::endl;
      uint16_t Vx = abs(Cache_Lx);
      uint16_t Vy = abs(Cache_Ly);
      uint16_t Wz = (abs(Cache_Az) * 10000.0);

      VelocityCommand[3] = (Vx >> 8) & 0x7F;
      VelocityCommand[4] =  (Vx) & 0xFF;
      if(Cache_Lx > 0) VelocityCommand[3] = VelocityCommand[3] | 0x80;

      VelocityCommand[5] = (abs(Wz) >> 8) & 0x7F;
      VelocityCommand[6] =  abs(Wz) & 0xFF;
      if(Cache_Az > 0) VelocityCommand[5] = VelocityCommand[5] | 0x80;

      VelocityCommand[7] = (Vy >> 8) & 0x7F;
      VelocityCommand[8] =  (Vy) & 0xFF;
      if(Cache_Ly > 0) VelocityCommand[7] = VelocityCommand[7] | 0x80;

      LastVelCommandTrigger = ros::Time::now();
      IsWaitingForAck = true;
      base_serial.write(VelocityCommand , 12);
  }
}

void SendAkrVelCommand()
{
  if(!IsWaitingForAck || (ros::Time::now().toSec() - LastVelCommandTrigger.toSec() > 5))
  {
            std::cout<<"Sending Akr Velocity Command"<<std::endl;
      uint16_t Vx = abs(Cache_Lx);
      uint16_t Wz = (abs(Cache_Th) * 10000.0);

      SteerCommand[3] = (Vx >> 8) & 0x7F;
      SteerCommand[4] =  (Vx) & 0xFF;
      if(Cache_Lx > 0) SteerCommand[3] = SteerCommand[3] | 0x80;

      SteerCommand[5] = (abs(Wz) >> 8) & 0x7F;
      SteerCommand[6] =  abs(Wz) & 0xFF;
      if(Cache_Th > 0) SteerCommand[5] = SteerCommand[5] | 0x80;

      IsWaitingForAck = true;
      LastVelCommandTrigger = ros::Time::now();
      base_serial.write(SteerCommand , 10);
  }
}


bool RunCmdLoop = false;
bool ISRunCmdLoopOn = false;
ros::Publisher joy_vel_pub;
ros::Publisher joy_akr_vel_pub;
void CmdVel_loop()
{ 
  RunCmdLoop = true;

  while(RunCmdLoop)
  {
    ISRunCmdLoopOn = true;
    if(base_serial.isOpen())
    {
      if(!SteerMode)
      {
      geometry_msgs::Twist joy_vel_cmd;
      joy_vel_cmd.linear.x = Cache_Lx/1000;
      joy_vel_cmd.linear.y = Cache_Ly/1000;
      joy_vel_cmd.angular.z = Cache_Az;
      joy_vel_pub.publish(joy_vel_cmd);
      }
      else
      {
        geometry_msgs::Twist joy_akr_vel_cmd;
        joy_akr_vel_cmd.linear.x = Cache_Lx/1000;
        joy_akr_vel_cmd.angular.z = Cache_Th;
        joy_akr_vel_pub.publish(joy_akr_vel_cmd);
      }
      
      usleep(300000);
    }
  }

  ISRunCmdLoopOn = false;
}



std::mutex joylock;


//............................................. Head Yaw....Head Pitch...............*//
uint8_t HeadPoseCommand[] = {0x00, 0x53, 0x53, 0x00, 0x00, 0x00, 0x00, 0x53, 0x50, 0x00};
ros::Time LastPoseTrigger;
float Roll_To_Degree = 0;
float Pitch_To_Degree = 0;
bool IsHeadCommandHandled = true;

void joy_head_callback(const sensor_msgs::Joy& joyStat)
{ 

  if(ISRunCmdLoopOn && head_serial.isOpen() && IsHeadCommandHandled && (ros::Time::now().toNSec() - LastPoseTrigger.toNSec()/1000000.0 > 50))
  {
      LastPoseTrigger = ros::Time::now();
    // float Roll_Scalled = joyStat.axes[3] * 1000;
    // float Pitch_Scalled = joyStat.axes[4] * 1000;

    //  if(joyStat.buttons[5] == 0)
    //  {
    //  Roll_To_Degree = Roll_Scalled * (31400/2000);
    //  }
    //  else
    //  if(joyStat.buttons[5] == 1)
    //  {
    //  Pitch_To_Degree = Pitch_Scalled * (31400/2000);
    //  }


    if( abs(joyStat.axes[3]) > 0.3)
    {
      if(joyStat.axes[3] > 0)
      {
        Roll_To_Degree ++;
        Roll_To_Degree = Roll_To_Degree > 90? 90 : Roll_To_Degree;
        Roll_To_Degree = Roll_To_Degree < -90? -90 : Roll_To_Degree;
      }
      else
      if(joyStat.axes[3] < 0)
      {
        Roll_To_Degree --;
        Roll_To_Degree = Roll_To_Degree > 90? 90 : Roll_To_Degree;
        Roll_To_Degree = Roll_To_Degree < -90? -90 : Roll_To_Degree;
      }
    }
    
    if(abs(joyStat.axes[4]) > 0.3)
    {
      if(joyStat.axes[4] > 0)
      {
        Pitch_To_Degree ++;
        Pitch_To_Degree = Pitch_To_Degree > 90? 90 : Pitch_To_Degree;
        Pitch_To_Degree = Pitch_To_Degree < -90? -90 : Pitch_To_Degree;
      }
      else
      if(joyStat.axes[4] < 0)
      {
        Pitch_To_Degree --;
        Pitch_To_Degree = Pitch_To_Degree > 90? 90 : Pitch_To_Degree;
        Pitch_To_Degree = Pitch_To_Degree < -90? -90 : Pitch_To_Degree;
      }
    }


    uint16_t HYaw = abs(Roll_To_Degree*31400/180);
    uint16_t HPitch = abs(Pitch_To_Degree*31400/180);


    HeadPoseCommand[3] = (HYaw >> 8) & 0x3F;
    HeadPoseCommand[4] = (HYaw) & 0xFF;
    if(Roll_To_Degree > 0) HeadPoseCommand[3] = HeadPoseCommand[3] | 0x40;
    else
    if(Roll_To_Degree < 0) HeadPoseCommand[3] = HeadPoseCommand[3] | 0x80;
    else
    if(Roll_To_Degree == 0) HeadPoseCommand[3] = HeadPoseCommand[3] | 0xC0;

    HeadPoseCommand[5] = (HPitch >> 8) & 0x3F;
    HeadPoseCommand[6] = (HPitch) & 0xFF;
    if(Pitch_To_Degree > 0) HeadPoseCommand[5] = HeadPoseCommand[5] | 0x40;
    else
    if(Pitch_To_Degree < 0) HeadPoseCommand[5] = HeadPoseCommand[5] | 0x80;
    else
    if(Pitch_To_Degree == 0) HeadPoseCommand[5] = HeadPoseCommand[5] | 0xC0;

    IsHeadCommandHandled = false;
    head_serial.write(HeadPoseCommand , 10);
  }
}




bool IsFirstCommand = true;
void joy_callback(const sensor_msgs::Joy& joyStat)
{
   std::cout << "\n\n\n joy ht  \n\n\n" << std::endl;
     
  if(ISRunCmdLoopOn)
  {

  std::cout << "\n\n\n joy run  \n\n\n" << std::endl;
  
  if(joyStat.buttons[5] == 1)
  {
    SteerMode = !SteerMode;
  }

  if(joyStat.buttons[4] == 0)
  {
    float left_Trigger = 1- joyStat.axes[2];
    float right_Trigger = 1- joyStat.axes[5];
    if(!SteerMode)
    {
        float angular_Range = joyStat.axes[0]*17.5/100; // for a Wz max of 0.550rad/sec

        left_Trigger = left_Trigger/2;
        right_Trigger = right_Trigger/2;

        if(joyStat.axes[0] < 0.3 && joyStat.axes[0] > -0.3)
        angular_Range = 0;

        float angular_vel = 3.14 * angular_Range;
        float Lx = 0;
        if(left_Trigger > 0.2)
        {
          left_Trigger = left_Trigger-0.2;
          Lx = Vx_max * left_Trigger;
          if(abs(angular_vel) > 0)
          {
            float radius = Lx/abs(angular_vel);
            if(radius < Steering_Rmin)
            {
              Lx = Steering_Rmin * abs(angular_vel);
            }
          }
        }
        else
        if(right_Trigger > 0.2)
        {
          right_Trigger = right_Trigger-0.2;
          Lx = -1 * Vx_max * right_Trigger;
          if(abs(angular_vel) > 0)
          {
            float radius = abs(Lx/angular_vel);
            if(radius < Steering_Rmin)
            {
              Lx = -1 * Steering_Rmin * abs(angular_vel);
            }
          }
        }

        float Ly = 0;
        float Az = angular_vel;

        if(Lx == 100 || Lx == -100) {
          Lx =0;
        }

      if(Lx == Cache_Lx && Ly == Cache_Ly && Az == Cache_Az)
      { 
          return;
      } 

        Cache_Lx = Lx;
        Cache_Ly = 0;
        Cache_Az = Az;
    }
    else
    {
      float Lx = 0;
      if(left_Trigger > 0.2)
      {
        left_Trigger = left_Trigger-0.2;
        Lx = Vx_max * left_Trigger;
      }
      else
      if(right_Trigger > 0.2)
      {
        right_Trigger = right_Trigger-0.2;
        Lx = -1 * Vx_max * right_Trigger;
      }


      if(Lx == 100 || Lx == -100) {
        Lx =0;
      }

      float steer_range = joyStat.axes[0] * 0.52;

      if(joyStat.axes[0] < 0.3 && joyStat.axes[0] > -0.3)
      {   
        steer_range = 0;
      }
      else
      {
        if(joyStat.axes[0] > 0.3)
        {
          steer_range = (joyStat.axes[0]-0.3) * 0.52;
        }
        else
        if(joyStat.axes[0] < -0.3)
        {
          steer_range = (joyStat.axes[0]+0.3) * 0.52;
        }
      }
          


      if(Lx == Cache_Lx && steer_range == Cache_Th)
      { 
          return;
      } 

      Cache_Lx = Lx;
      Cache_Th = steer_range;
    }

  }
  else
  {
    float Ly = Vx_max * joyStat.axes[0];

    if(joyStat.axes[0] < 0.3 && joyStat.axes[0] > -0.3) 
     Ly = 0;
   
    if(Ly == Cache_Ly)
    { 
      return;
    }

    Cache_Lx = 0;
    Cache_Ly = Ly;
    Cache_Az = 0;

  }
}
    // std::cout << "Cache_Lx :" << Cache_Lx << std::endl;
    // std::cout << "Cache_Ly :" << Cache_Ly << std::endl;
    // std::cout << "Cache_Az :" << Cache_Az << std::endl;
}



//Velocity Command fron move_base
void cmd_vel_callback(const geometry_msgs::Twist& vel_cmd)
{ 
 //if(!ISRunCmdLoopOn)
 {
    float Lx = vel_cmd.linear.x;
    float Ly = vel_cmd.linear.y;
    float Az = vel_cmd.angular.z;

    float Vx = (Lx*1000);
    float Vy = (Ly*1000);
    float Wz = ((Az));

    Cache_Lx = Vx;
    Cache_Ly = Vy;
    Cache_Az = Az;

    SendVelCommand();
 }
}


void akr_cmd_vel_callback(const geometry_msgs::Twist& akr_vel_cmd)
{ 
 //if(!ISRunCmdLoopOn)
 {
    float Lx = akr_vel_cmd.linear.x;
    float Az = akr_vel_cmd.angular.z;

    float Vx = (Lx*1000);
    float Wz = ((Az));

    Cache_Lx = Vx;
    Cache_Th = Az;

    SendAkrVelCommand();
 }
}


bool base_zero_orientation_set = false;

bool set_base_zero_orientation(std_srvs::Empty::Request&,
                          std_srvs::Empty::Response&)
{
  ROS_INFO("Base Zero Orientation Set.");
  base_zero_orientation_set = false;
  return true;
}



bool head_zero_orientation_set = false;

bool set_head_zero_orientation(std_srvs::Empty::Request&,
                          std_srvs::Empty::Response&)
{
  ROS_INFO("Head Zero Orientation Set.");
  head_zero_orientation_set = false;
  return true;
}

int main(int argc, char **argv)
{
  bool base_connected = false;
  bool head_connected = false;
  std::string base_port;
  std::string head_port;

  bool pub_odom;
  bool pub_odom_tf;
  bool pub_base_imu;

  bool pub_head_imu;
  bool pub_head_imu_tf;


  uint8_t base_comms_last_received_message_number;
  bool base_comms_received_message = false;
  int base_comms_data_packet_start;

  uint8_t head_comms_last_received_message_number;
  bool head_comms_received_message = false;
  int head_comms_data_packet_start;


  bool joy_control;

  double base_linear_acceleration_stddev;
  double base_angular_velocity_stddev;
  double base_orientation_stddev;

  double head_linear_acceleration_stddev;
  double head_angular_velocity_stddev;
  double head_orientation_stddev;

  tf::Quaternion base_diff_orientation;
  tf::Quaternion base_zero_orientation;

  tf::Quaternion head_diff_orientation;
  tf::Quaternion head_zero_orientation;


  ros::init(argc, argv, "WavComms");

  

  ros::NodeHandle WavComms_node_handle("WavComms_Param");
  WavComms_node_handle.param<bool>("joy_control", joy_control, true);

  WavComms_node_handle.param<bool>("base_connected", base_connected, false);
  WavComms_node_handle.param<std::string>("base_port", base_port, "/dev/ttyUSB3");
  WavComms_node_handle.param<bool>("pub_base_imu", pub_base_imu, true);
  WavComms_node_handle.param<bool>("pub_odom", pub_odom, true);
  WavComms_node_handle.param<bool>("pub_odom_tf", pub_odom_tf, true);
  WavComms_node_handle.param<double>("base_linear_acceleration_stddev", base_linear_acceleration_stddev, 0.0);
  WavComms_node_handle.param<double>("base_angular_velocity_stddev", base_angular_velocity_stddev, 0.0);
  WavComms_node_handle.param<double>("base_orientation_stddev", base_orientation_stddev, 0.0);


  WavComms_node_handle.param<bool>("head_connected", head_connected, false);
  WavComms_node_handle.param<std::string>("head_port", head_port, "/dev/ttyUSB2");
  WavComms_node_handle.param<bool>("pub_head_imu", pub_head_imu, true);
  WavComms_node_handle.param<bool>("pub_head_imu_tf", pub_head_imu_tf, true);
  WavComms_node_handle.param<double>("head_linear_acceleration_stddev", head_linear_acceleration_stddev, 0.0);
  WavComms_node_handle.param<double>("head_angular_velocity_stddev", head_angular_velocity_stddev, 0.0);
  WavComms_node_handle.param<double>("head_orientation_stddev", head_orientation_stddev, 0.0);


  thread* vel;
//  if(joy_control)
//     {
//   vel = new thread(CmdVel_loop);
//     }


  ros::NodeHandle nb("baseimu");
  ros::Publisher base_imu_pub = nb.advertise<sensor_msgs::Imu>("base_imu_data", 50);
  ros::Publisher base_imu_temperature_pub = nb.advertise<sensor_msgs::Temperature>("base_imu_temperature", 50);
  ros::ServiceServer base_service = nb.advertiseService("set_base_imu_zero_orientation", set_base_zero_orientation);

  ros::NodeHandle nh("headimu");
  ros::Publisher head_imu_pub = nh.advertise<sensor_msgs::Imu>("head_imu_data", 50);
  ros::Publisher head_imu_temperature_pub = nh.advertise<sensor_msgs::Temperature>("head_imu_temperature", 50);
  ros::ServiceServer head_service = nh.advertiseService("set_head_imu_zero_orientation", set_head_zero_orientation);



  std::cout<<"base port : " << base_port <<std::endl;
  std::cout<<"head port : " << head_port <<std::endl;


  ros::NodeHandle njoyvel;
  joy_vel_pub = njoyvel.advertise<geometry_msgs::Twist>("/cmd_vel", 50);

  ros::NodeHandle njoyakrvel;
  joy_akr_vel_pub = njoyakrvel.advertise<geometry_msgs::Twist>("/akr_cmd_vel", 50);

  ros::NodeHandle nodo;
  ros::Publisher odom_pub = nodo.advertise<nav_msgs::Odometry>("/odom", 50);

  ros::NodeHandle nVelACK;
  ros::Publisher velACK_pub = nVelACK.advertise<std_msgs::Byte>("/cmd_vel_ack", 50);

  ros::NodeHandle nvel;
  ros::Subscriber sub = nvel.subscribe("/cmd_vel", 1000, cmd_vel_callback);

  ros::NodeHandle nakrvel;
  ros::Subscriber akrsub = nakrvel.subscribe("/akr_cmd_vel", 1000, akr_cmd_vel_callback);

  ros::NodeHandle npose;
  ros::Subscriber joyBodySub = npose.subscribe("/joy", 1000, joy_callback);

  //ros::NodeHandle hpose;
  //ros::Subscriber joyHeadSub = hpose.subscribe("/joy", 1000, joy_head_callback);


 
  tf::TransformListener listener;
  tf::TransformBroadcaster tf_br;

  tf::Transform baseImu_transform;
  tf::Quaternion baseImu_Position;
  baseImu_Position.setRPY( 0, 0, -1*M_PI/2 );
  baseImu_transform.setRotation(baseImu_Position);
  baseImu_transform.setOrigin(tf::Vector3(0,0,0));

  tf::Transform headImu_transform;
  headImu_transform.setOrigin(tf::Vector3(0.06,0,0.713));


  ros::Rate r(200); // 200 hz


  sensor_msgs::Imu base_imu;

  base_imu.linear_acceleration_covariance[0] = base_linear_acceleration_stddev;
  base_imu.linear_acceleration_covariance[4] = base_linear_acceleration_stddev;
  base_imu.linear_acceleration_covariance[8] = base_linear_acceleration_stddev;

  base_imu.angular_velocity_covariance[0] = base_angular_velocity_stddev;
  base_imu.angular_velocity_covariance[4] = base_angular_velocity_stddev;
  base_imu.angular_velocity_covariance[8] = base_angular_velocity_stddev;

  base_imu.orientation_covariance[0] = base_orientation_stddev;
  base_imu.orientation_covariance[4] = base_orientation_stddev;
  base_imu.orientation_covariance[8] = base_orientation_stddev;

  sensor_msgs::Temperature base_imu_temperature_msg;
  base_imu_temperature_msg.variance = 0;



  sensor_msgs::Imu head_imu;

  head_imu.linear_acceleration_covariance[0] = head_linear_acceleration_stddev;
  head_imu.linear_acceleration_covariance[4] = head_linear_acceleration_stddev;
  head_imu.linear_acceleration_covariance[8] = head_linear_acceleration_stddev;

  head_imu.angular_velocity_covariance[0] = head_angular_velocity_stddev;
  head_imu.angular_velocity_covariance[4] = head_angular_velocity_stddev;
  head_imu.angular_velocity_covariance[8] = head_angular_velocity_stddev;

  head_imu.orientation_covariance[0] = head_orientation_stddev;
  head_imu.orientation_covariance[4] = head_orientation_stddev;
  head_imu.orientation_covariance[8] = head_orientation_stddev;

  sensor_msgs::Temperature head_imu_temperature_msg;
  head_imu_temperature_msg.variance = 0;



  std::string base_comms_input;
  std::string base_comms_read;

  std::string head_comms_input;
  std::string head_comms_read;

  double ODO_x = 0;
  double ODO_y = 0;
  double ODO_vx = 0;
  double ODO_vy = 0;
  double ODO_th = 0;
  double ODO_vth = 0;


 bool isJoyEnabled = false;

  ros::Time lastOdOTime = ros::Time::now();
  while(ros::ok())
  {
    WavComms_node_handle.getParam("/WavComms/joy_control",joy_control);
    WavComms_node_handle.getParam("/WavComms/base_connected",base_connected);
    WavComms_node_handle.getParam("/WavComms/base_port",base_port);
    WavComms_node_handle.getParam("/WavComms/pub_base_imu",pub_base_imu);
    WavComms_node_handle.getParam("/WavComms/pub_odom",pub_odom);
    WavComms_node_handle.getParam("/WavComms/pub_odom_tf",pub_odom_tf);
    WavComms_node_handle.getParam("/WavComms/base_linear_acceleration_stddev",base_linear_acceleration_stddev);
    WavComms_node_handle.getParam("/WavComms/base_angular_velocity_stddev",base_angular_velocity_stddev);
    WavComms_node_handle.getParam("/WavComms/base_orientation_stddev",base_orientation_stddev);

    WavComms_node_handle.getParam("/WavComms/head_connected",head_connected);
    WavComms_node_handle.getParam("/WavComms/head_port",head_port);
    WavComms_node_handle.getParam("/WavComms/pub_head_imu",pub_head_imu);
    WavComms_node_handle.getParam("/WavComms/pub_head_imu_tf",pub_head_imu_tf);
    WavComms_node_handle.getParam("/WavComms/head_linear_acceleration_stddev",head_linear_acceleration_stddev);
    WavComms_node_handle.getParam("/WavComms/head_angular_velocity_stddev",head_angular_velocity_stddev);
    WavComms_node_handle.getParam("/WavComms/head_orientation_stddev",head_orientation_stddev);


    if(joy_control)
    {
      if(!isJoyEnabled && !ISRunCmdLoopOn)
      {
         std::cout << "\n\n\n joy_control enabled \n\n\n" << std::endl;
     
        isJoyEnabled = true;
          vel = new thread(CmdVel_loop);
      }
    }
    else
    {
      if(isJoyEnabled)
      {
        std::cout << "\n\n\n joy_control enabled false \n\n\n" << std::endl;
      
       isJoyEnabled = false;
       RunCmdLoop = false;
      }
    }
      // calculate measurement time
      ros::Time current_time = ros::Time::now();

try
    {
      if (head_serial.isOpen())
      {
        // read string from serial device
        if(head_serial.available())
        {
          head_comms_read = head_serial.readString(head_serial.available());
          ROS_DEBUG("read %i new characters from serial port, adding to %i characters of old input.", (int)head_comms_read.size(), (int)head_comms_input.size());
          head_comms_input += head_comms_read;
          if (head_comms_input.length() >= 29) // while there might be a complete package in input
          {
            //parse for data packets
            head_comms_data_packet_start = head_comms_input.find("$\x03");
            if (head_comms_data_packet_start != std::string::npos)
            {

              head_comms_input = head_comms_input.substr(head_comms_data_packet_start);

              if(head_comms_input.length() >= 29)
              {
              head_comms_data_packet_start = head_comms_input.find("$\x03");
              ROS_DEBUG("found possible start of data packet at position %d", head_comms_data_packet_start);
              if ((head_comms_input.length() >= head_comms_data_packet_start + 29) && (head_comms_input.compare(head_comms_data_packet_start + 27, 2, "\r\n") == 0))  //check if positions 26,27 exist, then test values
              {
                ROS_DEBUG("seems to be a real data package: long enough and found end characters");

                if((0xff &(char)head_comms_input[head_comms_data_packet_start + 24]) == 0xCC)
                IsHeadCommandHandled = true;
                
                //get quaternion values
                int16_t w = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 2]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 3]);
                int16_t x = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 4]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 5]);
                int16_t y = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 6]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 7]);
                int16_t z = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 8]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 9]);

                double wf = w/16384.0;
                double xf = x/16384.0;
                double yf = y/16384.0;
                double zf = z/16384.0;

                tf::Quaternion orientation(xf, yf, zf, wf);

                if (!head_zero_orientation_set)
                {
                  head_zero_orientation = orientation;
                  head_zero_orientation_set = true;
                  head_diff_orientation = head_zero_orientation.inverse() * orientation;
                }

                //http://answers.ros.org/question/10124/relative-rotation-between-two-quaternions/
              
              
                // get gyro values
                int16_t gx = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 10]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 11]);
                int16_t gy = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 12]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 13]);
                int16_t gz = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 14]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 15]);
                // calculate rotational velocities in rad/s
                // without the last factor the velocities were too small
                // http://www.i2cdevlib.com/forums/topic/106-get-angular-velocity-from-mpu-6050/
                // FIFO frequency 100 Hz -> factor 10 ?
                // seems 25 is the right factor
                //TODO: check / test if rotational velocities are correct
                double gxf = gx * (4000.0/65536.0) * (M_PI/180.0) * 25.0;
                double gyf = gy * (4000.0/65536.0) * (M_PI/180.0) * 25.0;
                double gzf = gz * (4000.0/65536.0) * (M_PI/180.0) * 25.0;

                // get acelerometer values
                int16_t ax = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 16]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 17]);
                int16_t ay = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 18]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 19]);
                int16_t az = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 20]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 21]);
                // calculate accelerations in m/s²
                double axf = ax * (8.0 / 65536.0) * 9.81;
                double ayf = ay * (8.0 / 65536.0) * 9.81;
                double azf = az * (8.0 / 65536.0) * 9.81;

                // get temperature
                int16_t temperature = (((0xff &(char)head_comms_input[head_comms_data_packet_start + 22]) << 8) | 0xff &(char)head_comms_input[head_comms_data_packet_start + 23]);
                double temperature_in_C = (temperature / 340.0 ) + 36.53;
                ROS_DEBUG_STREAM("Temperature [in C] " << temperature_in_C);

           


   float sumsq = head_diff_orientation.getX() * head_diff_orientation.getX() +
                              head_diff_orientation.getY() * head_diff_orientation.getY() +
                              head_diff_orientation.getZ() * head_diff_orientation.getZ()+
                              head_diff_orientation.getW() * head_diff_orientation.getW() ;
               if(sumsq > 0.999 )
                {

                head_diff_orientation.normalize();
               
                // publish imu message
                head_imu.header.stamp = current_time;
                head_imu.header.frame_id = "camera_link";

                quaternionTFToMsg(head_diff_orientation, head_imu.orientation);

                head_imu.angular_velocity.x = gxf;
                head_imu.angular_velocity.y = gyf;
                head_imu.angular_velocity.z = gzf;

                head_imu.linear_acceleration.x = axf;
                head_imu.linear_acceleration.y = ayf;
                head_imu.linear_acceleration.z = azf;


                // publish temperature message
                head_imu_temperature_msg.header.stamp = current_time;
                head_imu_temperature_msg.header.frame_id = "camera_link";
                head_imu_temperature_msg.temperature = temperature_in_C;

                if (pub_head_imu_tf)
                {
                  headImu_transform.setOrigin(tf::Vector3(0.06,0,0.655));
                  headImu_transform.setRotation(head_diff_orientation);
                }
              
              }
                head_comms_input.erase(0, head_comms_data_packet_start + 29); // delete everything up to and including the processed packet
              }
              else
              {
                if (head_comms_input.length() >= head_comms_data_packet_start + 29)
                {
                  head_comms_input.erase(0, head_comms_data_packet_start + 1); // delete up to false head_comms_data_packet_start character so it is not found again
                }
                else
                {
                  // do not delete start character, maybe complete package has not arrived yet
                  head_comms_input.erase(0, head_comms_data_packet_start);
                }
              }
              }
            }
            else
            {
              // no start character found in input, so delete everything
              head_comms_input.clear();
            }
          }
        }
      }
      else
      {
        // try and open the serial port
        try
        {
          
          if(head_connected == true){
            if(find_port(head_port) == true){
            ROS_DEBUG_STREAM("try to Open Head Serial");
            head_serial.setPort(head_port);
            head_serial.setBaudrate(115200);
            serial::Timeout to = serial::Timeout::simpleTimeout(1000);
            head_serial.setTimeout(to);
            head_serial.open();
            ROS_DEBUG_STREAM("Head serial opened!");
            }
            else
            {

            ROS_WARN_STREAM("Head port not connected");
            }
          }

        }
        catch (serial::IOException& e)
        {
          ROS_ERROR_STREAM("Unable to open serial port " << head_serial.getPort() << ". Trying again in 5 seconds.");
          ros::Duration(5).sleep();
        }

        if(head_serial.isOpen())
        {
          ROS_DEBUG_STREAM("Serial port " << head_serial.getPort() << " initialized and opened.");
        }
      }
    }
    catch (serial::IOException& e)
    {
      ROS_ERROR_STREAM("Error reading from the serial port " << head_serial.getPort() << ". Closing connection.");
      head_serial.close();
    }




    try
    {
      if (base_serial.isOpen())
      {
        
           // std::cout<<"Base Serial Open"<<std::endl;
        // read string from serial device
        if(base_serial.available())
        {
        //  std::cout<<"available"<<std::endl;
          base_comms_read = base_serial.readString(base_serial.available());
          ROS_DEBUG("read %i new characters from serial port, adding to %i characters of old base_comms_input.", (int)base_comms_read.size(), (int)base_comms_input.size());
          base_comms_input += base_comms_read;
          if (base_comms_input.length() >= 54) // while there might be a complete package in base_comms_input
          {
           // std::cout<<"Base read"<<std::endl;
            //parse for data packets
            base_comms_data_packet_start = base_comms_input.find("$\x03");
            if (base_comms_data_packet_start != std::string::npos)
            {
              base_comms_input = base_comms_input.substr(base_comms_data_packet_start);

              if(base_comms_input.length() >= 54)
              {
                base_comms_data_packet_start = base_comms_input.find("$\x03");
              // else
              // {
              //   if(IsWaitingForAck && (ros::Time::now().toSec() - LastVelCommandTrigger.toSec() > 5))
              //   {
              //     IsWaitingForAck = false;
              //     std_msgs::Byte ack;
              //     ack.data = 0xCC;
              //     velACK_pub.publish(ack);
              //   }
              // }

              ROS_DEBUG("found possible start of data packet at position %d", base_comms_data_packet_start);
              if ((base_comms_input.length() >= base_comms_data_packet_start + 54) && (base_comms_input.compare(base_comms_data_packet_start + 52, 2, "\r\n") == 0))  //check if positions 26,27 exist, then test values
              {
                  
                  if( (0xFF & (char)base_comms_input[base_comms_data_packet_start+49]) == 0xCC && IsWaitingForAck)
                  {
                    std_msgs::Byte ack;
                    uint8_t flag = (0xFF & (char)base_comms_input[base_comms_data_packet_start+49]);
                    
                    
                      std::cout<<"Recieved ACK : "<< flag <<std::endl;
                      IsWaitingForAck = false;

                      ack.data = flag;
                      velACK_pub.publish(ack);
                  }
                  else
                  if(IsWaitingForAck && (ros::Time::now().toSec() - LastVelCommandTrigger.toSec() > 5))
                  {
                     std_msgs::Byte ack;
                      uint8_t flag = (0xFF & (char)base_comms_input[base_comms_data_packet_start+49]);
                    
                    
                      std::cout<<"Recieved ACK : "<< flag <<std::endl;

                      ack.data = flag;
                      velACK_pub.publish(ack);
                  }

                ROS_DEBUG("seems to be a real data package: long enough and found end characters");
                // get quaternion values
                int16_t w = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 2]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 3]);
                int16_t x = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 4]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 5]);
                int16_t y = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 6]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 7]);
                int16_t z = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 8]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 9]);

                double wf = w/16384.0;
                double xf = x/16384.0;
                double yf = y/16384.0;
                double zf = z/16384.0;

                tf::Quaternion orientation(xf, yf, zf, wf);

                if (!base_zero_orientation_set)
                {
                  base_zero_orientation = orientation;
                  base_zero_orientation_set = true;
                }

                //http://answers.ros.org/question/10124/relative-rotation-between-two-quaternions/
               
                base_diff_orientation = base_zero_orientation.inverse() * orientation;

                 // get gyro values
                int16_t gx = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 10]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 11]);
                int16_t gy = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 12]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 13]);
                int16_t gz = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 14]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 15]);
                // calculate rotational velocities in rad/s
                // without the last factor the velocities were too small
                // http://www.i2cdevlib.com/forums/topic/106-get-angular-velocity-from-mpu-6050/
                // FIFO frequency 100 Hz -> factor 10 ?
                // seems 25 is the right factor
                //TODO: check / test if rotational velocities are correct
                double gxf = gx * (4000.0/65536.0) * (M_PI/180.0) * 25.0;
                double gyf = gy * (4000.0/65536.0) * (M_PI/180.0) * 25.0;
                double gzf = gz * (4000.0/65536.0) * (M_PI/180.0) * 25.0;

                // get acelerometer values
                int16_t ax = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 16]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 17]);
                int16_t ay = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 18]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 19]);
                int16_t az = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 20]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 21]);
                // calculate accelerations in m/s²
                double axf = ax * (8.0 / 65536.0) * 9.81;
                double ayf = ay * (8.0 / 65536.0) * 9.81;
                double azf = az * (8.0 / 65536.0) * 9.81;

                // get temperature
                int16_t temperature = (((0xff &(char)base_comms_input[base_comms_data_packet_start + 22]) << 8) | 0xff &(char)base_comms_input[base_comms_data_packet_start + 23]);
                double temperature_in_C = (temperature / 340.0 ) + 36.53;

                

                float base_sumsq = base_diff_orientation.getX() * base_diff_orientation.getX() +
                              base_diff_orientation.getY() * base_diff_orientation.getY() +
                              base_diff_orientation.getZ() * base_diff_orientation.getZ()+
                              base_diff_orientation.getW() * base_diff_orientation.getW() ;

                float head_diff_orientation_sumsq = head_diff_orientation.getX() * head_diff_orientation.getX() +
                              head_diff_orientation.getY() * head_diff_orientation.getY() +
                              head_diff_orientation.getZ() * head_diff_orientation.getZ()+
                              head_diff_orientation.getW() * head_diff_orientation.getW() ;

//  std::cout<<"base_sumsq:"<< base_sumsq <<std::endl;
//    std::cout<<"zero orientation:"<< base_zero_orientation.getX() << " " << base_zero_orientation.getY() << " " << base_zero_orientation.getZ() << " " << base_zero_orientation.getW() <<std::endl;
//   std::cout<<"orientation:"<< orientation.getX() << " " << orientation.getY() << " " << orientation.getZ() << " " << orientation.getW() <<std::endl;
//   std::cout<<"diff orientation:"<< base_diff_orientation.getX() << " " << base_diff_orientation.getY() << " " << base_diff_orientation.getZ() << " " << base_diff_orientation.getW() <<std::endl;
             

                if(base_sumsq > 0.999 )
                {

                  //  std::cout<<"Base Valid orientation read"<<std::endl;
                  base_diff_orientation.normalize();
                if(pub_base_imu)
                  {
                    // publish imu message
                    base_imu.header.frame_id = "base_imu_link";

                    quaternionTFToMsg(base_diff_orientation, base_imu.orientation);

                    base_imu.angular_velocity.x = gxf;
                    base_imu.angular_velocity.y = gyf;
                    base_imu.angular_velocity.z = gzf;

                    base_imu.linear_acceleration.x = axf;
                    base_imu.linear_acceleration.y = ayf;
                    base_imu.linear_acceleration.z = azf;

                    ros::Time measurement_time = ros::Time::now();
                    base_imu.header.stamp = measurement_time;
                   base_imu_pub.publish(base_imu); 
                   // tf_br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "base_imu_link"));
                
                    // publish temperature message
                    base_imu_temperature_msg.header.stamp = measurement_time;
                    base_imu_temperature_msg.header.frame_id = "base_imu_link";
                    base_imu_temperature_msg.temperature = temperature_in_C;

                    base_imu_temperature_pub.publish(base_imu_temperature_msg);

                  
                  }

                 }


                  int IMU_Yaw = ((0x7F & (char)base_comms_input[base_comms_data_packet_start+26]) << 8)  |
                                 (0xFF & (char)base_comms_input[base_comms_data_packet_start+27]);

                  int sign_IMU_Yaw = (char)(base_comms_input[base_comms_data_packet_start+26]) >> 7 == 0 ? 1 : -1;

                  double IMU_th = ((double)IMU_Yaw * (double)sign_IMU_Yaw * 1.0) / 1000.0;;
                //http://answers.ros.org/question/10124/relative-rotation-between-two-quaternions/

            // tf::StampedTransform HeadTransform;
            // try {
            //       listener.lookupTransform("/head_link", "/base_link",
            //                                 ros::Time(0), HeadTransform);
            //     }
            //     catch (tf::TransformException &ex) {
            //       ROS_ERROR("%s",ex.what());
            //       ros::Duration(1.0).sleep();
            //       continue;
            //     }


               
                if(base_comms_input[base_comms_data_packet_start+48] == 1)
                {
                  //  std::cout<<"Base Valid data"<<std::endl;
                  lastOdOTime = ros::Time::now();

                   long X = ((0x7F & (char)base_comms_input[base_comms_data_packet_start+28]) << 24) |
                                ((0xFF & (char)base_comms_input[base_comms_data_packet_start+29]) << 16) |
                                ((0xFF & (char)base_comms_input[base_comms_data_packet_start+30]) << 8)  |
                                (0xFF & (char)base_comms_input[base_comms_data_packet_start+31]);

                  int sign_x = (char)(base_comms_input[base_comms_data_packet_start+28]) >> 7 == 0 ? 1 : -1;
                   
                   long Y = ((0x7F & (char)base_comms_input[base_comms_data_packet_start+32]) << 24) |
                                ((0xFF & (char)base_comms_input[base_comms_data_packet_start+33]) << 16) |
                                ((0xFF & (char)base_comms_input[base_comms_data_packet_start+34]) << 8) |
                                (0xFF & (char)base_comms_input[base_comms_data_packet_start+35]);

                  int sign_y = (char)(base_comms_input[base_comms_data_packet_start+32]) >> 7 == 0 ? 1 : -1;

                   long VX =  ((0x7F & (char)base_comms_input[base_comms_data_packet_start+36]) << 24) |
                                  ((0xFF & (char)base_comms_input[base_comms_data_packet_start+37]) << 16) |
                                  ((0xFF & (char)base_comms_input[base_comms_data_packet_start+38]) << 8)  |
                                  (0xFF & (char)base_comms_input[base_comms_data_packet_start+39]);

                  int sign_vx = (char)(base_comms_input[base_comms_data_packet_start+36]) >> 7 == 0 ? 1 : -1;

                   long VY = ((0x7F & (char)base_comms_input[base_comms_data_packet_start+40]) << 24) |
                                 ((0xFF & (char)base_comms_input[base_comms_data_packet_start+41]) << 16) |
                                 ((0xFF & (char)base_comms_input[base_comms_data_packet_start+42]) << 8)  |
                                 (0xFF & (char)base_comms_input[base_comms_data_packet_start+43]);

                  int sign_vy = (char)(base_comms_input[base_comms_data_packet_start+24]) >> 7 == 0 ? 1 : -1;

                   int Yaw = ((0x7F & (char)base_comms_input[base_comms_data_packet_start+44]) << 8)  |
                                 (0xFF & (char)base_comms_input[base_comms_data_packet_start+45]);

                  int sign_yaw = (char)(base_comms_input[base_comms_data_packet_start+44]) >> 7 == 0 ? 1 : -1;

                   int Wz = ((0x7F & (char)base_comms_input[base_comms_data_packet_start+46]) << 8)  |
                                 (0xFF & (char)base_comms_input[base_comms_data_packet_start+47]);

                  int sign_wz = (char)(base_comms_input[base_comms_data_packet_start+46]) >> 7 == 0 ? 1 : -1;

                   ODO_x = ((double)X * (double)sign_x * 1.0) / 1000.0;
                   ODO_y = ((double)Y * (double)sign_y * 1.0) / 1000.0;
                   ODO_vx = ((double)VX * (double)sign_vx * 1.0) / 1000000.0;
                   ODO_vy = ((double)VY * (double)sign_vy * 1.0) / 1000000.0;
                   ODO_th = ((double)Yaw * (double)sign_yaw * 1.0) / 1000.0;
                   ODO_vth = ((double)Wz * (double)sign_wz * 1.0) / 1000.0;


                  // cout << "X: " << X << endl;
                  // cout << "Y: "   << Y << endl;
                  // cout << "VX: "  << VX << endl;
                  // cout << "VY: "  << VY << endl;
                  // cout << "Yaw: " << Yaw << endl;
                  // cout << "Wz: "  << Wz << endl;

                  // cout << "X: " << ODO_x;
                  // cout << " Y: "   << ODO_y;
                  // cout << " VX: "  << ODO_vx;
                  // cout << " VY: "  << ODO_vy;
                  // cout << " Yaw: " << ODO_th;
                  // cout << " Wz: "  << ODO_vth << endl;


                  
                  // tf::Transform KTransform;
                  // KTransform.setOrigin(HeadTransform.getOrigin());
                  // KTransform.setRotation(HeadTransform.getRotation());
            
                  // tf_br.sendTransform(tf::StampedTransform(KTransform, current_time, "base_link", "camera_link"));

                 //since all odometry is 6DOF we'll need a quaternion created from yaw
                  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(ODO_th);
                 
                  //first, we'll publish the transform over tf
                  geometry_msgs::TransformStamped odom_trans;
                  odom_trans.header.stamp = current_time;
                  odom_trans.header.frame_id = "odom";
                  odom_trans.child_frame_id = "base_link";
              
                  odom_trans.transform.translation.x = ODO_x;
                  odom_trans.transform.translation.y = ODO_y;
                  odom_trans.transform.translation.z = 0.0;
                  odom_trans.transform.rotation = odom_quat;
              
                  
                  //next, we'll publish the odometry message over ROS
                  nav_msgs::Odometry odom;
                  odom.header.stamp = current_time;
                  odom.header.frame_id = "odom";
              
                  //set the position
                  odom.pose.pose.position.x = ODO_x;
                  odom.pose.pose.position.y = ODO_y;
                  odom.pose.pose.position.z = 0.0;
                  odom.pose.pose.orientation = odom_quat;
              
                  //set the velocity
                  odom.child_frame_id = "base_link";
                  odom.twist.twist.linear.x = ODO_vx;
                  odom.twist.twist.linear.y = ODO_vy;
                  odom.twist.twist.angular.z = ODO_vth;
              
                  if(pub_odom)
                  {
                   odom_pub.publish(odom);
                  }


                  if(pub_odom_tf)
                  {
                    tf_br.sendTransform(odom_trans);
                  }

                  if(head_diff_orientation_sumsq > 0.999)
                  {
                    if(pub_head_imu)
                    {
                      head_imu.header.stamp = current_time;
                      head_imu_temperature_msg.header.stamp = current_time;
                      head_imu_pub.publish(head_imu);
                      head_imu_temperature_pub.publish(head_imu_temperature_msg);
                    }

                    if (pub_head_imu_tf)
                    {
                      tf_br.sendTransform(tf::StampedTransform(headImu_transform, current_time, "base_link", "camera_link"));
                    }
                  }

                }
                else
                 if(base_sumsq > 0.999 )
                {
                
                  //  std::cout<<"Base No Data"<<std::endl;
                    base_diff_orientation.normalize();
                    


                  // // tf::Transform KTransform;
                  // // KTransform.setOrigin(HeadTransform.getOrigin());
                  // // //KTransform.setRotation(HeadTransform.getRotation());
            
                  // // tf_br.sendTransform(tf::StampedTransform(KTransform, current_time, "base_link", "camera_link"));


                  //since all odometry is 6DOF we'll need a quaternion created from yaw
                  // geometry_msgs::Quaternion odom_quat;
                  // tf::quaternionTFToMsg(differential_rotation, odom_quat);


                // tf::StampedTransform OdomToMapTransform;
                // tf::Vector3 origin;
                // tf::Quaternion rotation = tf::createQuaternionFromYaw(0);
                // try {
                //       listener.lookupTransform("/map", "/odom",
                //                                 ros::Time(0), OdomToMapTransform);

                //       origin = OdomToMapTransform.getOrigin();
                //       rotation = OdomToMapTransform.getRotation();

                //       double mapToOdomYaw = tf::getYaw(rotation);

                //       if(mapToOdomYaw > 0)
                //       {

                //       }
                //       else
                //       {
                        
                //       }
                      

                //       ROS_ERROR("map to odom Tx: %f, Ty: %f, Yaw: %f",origin.getX(), origin.getY(),
                //       mapToOdomYaw);       
                //     }
                //     catch (tf::TransformException &ex) {
                //       ROS_ERROR("%s",ex.what());
                //       ros::Duration(1.0).sleep();
                //       continue;
                //     }

                  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(ODO_th);
                  //first, we'll publish the transform over tf
                  geometry_msgs::TransformStamped odom_trans;
                  odom_trans.header.stamp = current_time;
                  odom_trans.header.frame_id = "odom";
                  odom_trans.child_frame_id = "base_link";
              
                  odom_trans.transform.translation.x = ODO_x ;
                  odom_trans.transform.translation.y = ODO_y ;
                  odom_trans.transform.translation.z = 0.0;
                  odom_trans.transform.rotation = odom_quat;
              
                  
              
                    
                  
                  //next, we'll publish the odometry message over ROS
                  nav_msgs::Odometry odom;
                  odom.header.stamp = current_time;
                  odom.header.frame_id = "odom";
              
                  //set the position
                  odom.pose.pose.position.x = ODO_x ;
                  odom.pose.pose.position.y = ODO_y ;
                  odom.pose.pose.position.z = 0.0;
                  odom.pose.pose.orientation = odom_quat;
              
                  //set the velocity
                  odom.child_frame_id = "base_link";
                  odom.twist.twist.linear.x = ODO_vx;
                  odom.twist.twist.linear.y = ODO_vy;
                  odom.twist.twist.angular.z = gz;
              
                  if(pub_odom)
                  {
                     odom_pub.publish(odom);
                  }

                  if(pub_odom_tf)
                  {
                    tf_br.sendTransform(odom_trans);
                  }

                  if(head_diff_orientation_sumsq > 0.999)
                  {
                    if(pub_head_imu)
                    {
                      head_imu.header.stamp = current_time;
                      head_imu_temperature_msg.header.stamp = current_time;
                      head_imu_pub.publish(head_imu);
                      head_imu_temperature_pub.publish(head_imu_temperature_msg);
                    }

                    if (pub_head_imu_tf)
                    {
                      tf_br.sendTransform(tf::StampedTransform(headImu_transform, current_time, "base_link", "camera_link"));
                    }
                  }
                
                }
                base_comms_input.erase(0, base_comms_data_packet_start + 54); // delete everything up to and including the processed packet
              }
              else
              {
                if (base_comms_input.length() >= base_comms_data_packet_start + 54)
                { 
                  base_comms_input.erase(0, base_comms_data_packet_start + 1); // delete up to false data_packet_start character so it is not found again
                }
                else
                {
                  // do not delete start character, maybe complete package has not arrived yet
                  base_comms_input.erase(0, base_comms_data_packet_start);
                }
              }

            }

            }
            else
            {
              // no start character found in base_comms_input, so delete everything
              base_comms_input.clear();
            }
          }
        }
      }
      else
      {
        // try and open the serial port
        try
        {

          if(base_connected == true){
            if(find_port(base_port) == true){ 
              ROS_DEBUG_STREAM("try to Open Base Serial");
              base_serial.setPort(base_port);
              base_serial.setBaudrate(115200);
              serial::Timeout to = serial::Timeout::simpleTimeout(1000);
              base_serial.setTimeout(to);
              base_serial.open();
              ROS_DEBUG_STREAM("Base serial opened");
            }
            else
            {

              ROS_WARN_STREAM("Base port not connected");
            }
          }

        }
        catch (serial::IOException& e)
        {
          ROS_ERROR_STREAM("Unable to open serial port " << base_serial.getPort() << ". Trying again in 5 seconds.");
          ros::Duration(5).sleep();
        }

        if(base_serial.isOpen())
        {
          ROS_DEBUG_STREAM("Serial port " << base_serial.getPort() << " initialized and opened.");
        }
      }
    }
    catch (serial::IOException& e)
    {
      ROS_ERROR_STREAM("Error reading from the serial port " << base_serial.getPort() << ". Closing connection.");
      base_serial.close();
    }
    ros::spinOnce();
    r.sleep();
  }
  RunCmdLoop = false;
  if(vel->joinable() && joy_control)
  {
    vel->join();
  }
}
