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


serial::Serial ser;

float Steering_Rmin  = 363.407; //in mm
float Vx_max  = 200.0; //in mm/sec


float Cache_Lx = 0;
float Cache_Ly = 0;
float Cache_Az = 0;

uint8_t VelocityCommand[] = {0x00, 0x53, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x50, 0x00};

void SendCommand()
{
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

      ser.write(VelocityCommand , 12);
}

void cmd_vel_callback(const geometry_msgs::Twist& vel_cmd)
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

    SendCommand();
}

std::mutex joylock;


bool IsFirstCommand = true;
void joy_callback(const sensor_msgs::Joy& joyStat)
{
  if(joyStat.buttons[4] == 0)
  {
    float left_Trigger = 1- joyStat.axes[2];
    float right_Trigger = 1- joyStat.axes[5];
    float angular_Range = joyStat.axes[0]*17.5/100; // for a Wz max of 0.550rad/sec

    left_Trigger = left_Trigger/2;
    right_Trigger = right_Trigger/2;

    if(joyStat.axes[0] < 0.3 && joyStat.axes[0] > -0.3)
    angular_Range = 0;

    float angular_vel = 3.14 * angular_Range;
    float Lx = 0;
    if(left_Trigger > 0.2)
    {
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
    // std::cout << "Cache_Lx :" << Cache_Lx << std::endl;
    // std::cout << "Cache_Ly :" << Cache_Ly << std::endl;
    // std::cout << "Cache_Az :" << Cache_Az << std::endl;
}

bool RunCmdLoop = false;
void CmdVel_loop()
{ 
   RunCmdLoop = true;

  while(RunCmdLoop)
  {
    if(ser.isOpen())
    {
      SendCommand();
      usleep(300000);
    }
  }
}


bool zero_orientation_set = false;

bool set_zero_orientation(std_srvs::Empty::Request&,
                          std_srvs::Empty::Response&)
{
  ROS_INFO("Zero Orientation Set.");
  zero_orientation_set = false;
  return true;
}

int main(int argc, char **argv)
{

  std::string port;
  bool pub_odom;
  bool pub_odom_tf;
  bool pub_imu;
  uint8_t last_received_message_number;
  bool received_message = false;
  int data_packet_start;
  bool joy_control;

  double linear_acceleration_stddev;
  double angular_velocity_stddev;
  double orientation_stddev;

  tf::Quaternion orientation;
  tf::Quaternion zero_orientation;


  ros::init(argc, argv, "MotionComms");

  

  ros::NodeHandle private_node_handle("~");
  private_node_handle.param<std::string>("port", port, "/dev/ttyUSB1");
  private_node_handle.param<bool>("pub_imu", pub_imu, true);
  private_node_handle.param<bool>("pub_odom", pub_odom, true);
  private_node_handle.param<bool>("pub_odom_tf", pub_odom_tf, true);
  private_node_handle.param<bool>("joy_control", joy_control, true);


  private_node_handle.param<double>("linear_acceleration_stddev", linear_acceleration_stddev, 0.0);
  private_node_handle.param<double>("angular_velocity_stddev", angular_velocity_stddev, 0.0);
  private_node_handle.param<double>("orientation_stddev", orientation_stddev, 0.0);

  ros::NodeHandle nh("baseimu");
  ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("data", 50);
  ros::Publisher imu_temperature_pub = nh.advertise<sensor_msgs::Temperature>("temperature", 50);
  ros::ServiceServer service = nh.advertiseService("set_zero_orientation", set_zero_orientation);


  std::cout<<"port : " << port <<std::endl;

  ros::NodeHandle nodo;
  ros::Publisher odom_pub = nodo.advertise<nav_msgs::Odometry>("/odom", 50);

  ros::NodeHandle nVelACK;
  ros::Publisher velACK_pub = nVelACK.advertise<std_msgs::Byte>("/cmd_vel_ack", 50);


  ros::NodeHandle nvel;
  ros::Subscriber sub = nvel.subscribe("/cmd_vel", 1000, cmd_vel_callback);

  ros::NodeHandle npose;
  ros::Subscriber joySub = npose.subscribe("/joy", 1000, joy_callback);
  thread* vel;
  if(joy_control)
  {
    vel = new thread(CmdVel_loop);
  }

  tf::TransformListener listener;
  tf::TransformBroadcaster tf_br;

  tf::Transform transform;
  tf::Quaternion imuPosition;
  imuPosition.setRPY( 0, 0, -1*M_PI/2 );
  transform.setRotation(imuPosition);
  transform.setOrigin(tf::Vector3(0,0,0));

  ros::Rate r(200); // 200 hz


  sensor_msgs::Imu imu;

  imu.linear_acceleration_covariance[0] = linear_acceleration_stddev;
  imu.linear_acceleration_covariance[4] = linear_acceleration_stddev;
  imu.linear_acceleration_covariance[8] = linear_acceleration_stddev;

  imu.angular_velocity_covariance[0] = angular_velocity_stddev;
  imu.angular_velocity_covariance[4] = angular_velocity_stddev;
  imu.angular_velocity_covariance[8] = angular_velocity_stddev;

  imu.orientation_covariance[0] = orientation_stddev;
  imu.orientation_covariance[4] = orientation_stddev;
  imu.orientation_covariance[8] = orientation_stddev;

  sensor_msgs::Temperature temperature_msg;
  temperature_msg.variance = 0;



  std::string input;
  std::string read;

  double ODO_x = 0;
  double ODO_y = 0;
  double ODO_vx = 0;
  double ODO_vy = 0;
  double ODO_th = 0;
  double ODO_vth = 0;

 

  ros::Time lastOdOTime = ros::Time::now();
  while(ros::ok())
  {
    try
    {
      if (ser.isOpen())
      {
        
        // read string from serial device
        if(ser.available())
        {
          read = ser.readString(ser.available());
          ROS_DEBUG("read %i new characters from serial port, adding to %i characters of old input.", (int)read.size(), (int)input.size());
          input += read;
          while (input.length() >= 54) // while there might be a complete package in input
          {
            //parse for data packets
            data_packet_start = input.find("$\x03");
            if (data_packet_start != std::string::npos)
            {
              if( (0xFF & (char)input[data_packet_start+49]) != 0x00)
              {
                std_msgs::Byte ack;
                int8_t flag = (0xFF & (char)input[data_packet_start+49]);
                ack.data = flag;
                velACK_pub.publish(ack);
              }

              ROS_DEBUG("found possible start of data packet at position %d", data_packet_start);
              if ((input.length() >= data_packet_start + 54) && (input.compare(data_packet_start + 52, 2, "\r\n") == 0))  //check if positions 26,27 exist, then test values
              {
                ROS_DEBUG("seems to be a real data package: long enough and found end characters");
                // get quaternion values
                int16_t w = (((0xff &(char)input[data_packet_start + 2]) << 8) | 0xff &(char)input[data_packet_start + 3]);
                int16_t x = (((0xff &(char)input[data_packet_start + 4]) << 8) | 0xff &(char)input[data_packet_start + 5]);
                int16_t y = (((0xff &(char)input[data_packet_start + 6]) << 8) | 0xff &(char)input[data_packet_start + 7]);
                int16_t z = (((0xff &(char)input[data_packet_start + 8]) << 8) | 0xff &(char)input[data_packet_start + 9]);

                double wf = w/16384.0;
                double xf = x/16384.0;
                double yf = y/16384.0;
                double zf = z/16384.0;

                tf::Quaternion orientation(xf, yf, zf, wf);

                if (!zero_orientation_set)
                {
                  zero_orientation = orientation;
                  zero_orientation_set = true;
                }

                //http://answers.ros.org/question/10124/relative-rotation-between-two-quaternions/
                tf::Quaternion differential_rotation;
                differential_rotation = zero_orientation.inverse() * orientation;

                 // get gyro values
                int16_t gx = (((0xff &(char)input[data_packet_start + 10]) << 8) | 0xff &(char)input[data_packet_start + 11]);
                int16_t gy = (((0xff &(char)input[data_packet_start + 12]) << 8) | 0xff &(char)input[data_packet_start + 13]);
                int16_t gz = (((0xff &(char)input[data_packet_start + 14]) << 8) | 0xff &(char)input[data_packet_start + 15]);
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
                int16_t ax = (((0xff &(char)input[data_packet_start + 16]) << 8) | 0xff &(char)input[data_packet_start + 17]);
                int16_t ay = (((0xff &(char)input[data_packet_start + 18]) << 8) | 0xff &(char)input[data_packet_start + 19]);
                int16_t az = (((0xff &(char)input[data_packet_start + 20]) << 8) | 0xff &(char)input[data_packet_start + 21]);
                // calculate accelerations in m/s²
                double axf = ax * (8.0 / 65536.0) * 9.81;
                double ayf = ay * (8.0 / 65536.0) * 9.81;
                double azf = az * (8.0 / 65536.0) * 9.81;

                // get temperature
                int16_t temperature = (((0xff &(char)input[data_packet_start + 22]) << 8) | 0xff &(char)input[data_packet_start + 23]);
                double temperature_in_C = (temperature / 340.0 ) + 36.53;

                

                float sumsq = differential_rotation.getX() * differential_rotation.getX() +
                              differential_rotation.getY() * differential_rotation.getY() +
                              differential_rotation.getZ() * differential_rotation.getZ()+
                              differential_rotation.getW() * differential_rotation.getW() ;

                if(sumsq > 0.999 )
                {
                  differential_rotation.normalize();
                if(pub_imu)
                  {
                    // publish imu message
                    imu.header.frame_id = "base_imu_link";

                    quaternionTFToMsg(differential_rotation, imu.orientation);

                    imu.angular_velocity.x = gxf;
                    imu.angular_velocity.y = gyf;
                    imu.angular_velocity.z = gzf;

                    imu.linear_acceleration.x = axf;
                    imu.linear_acceleration.y = ayf;
                    imu.linear_acceleration.z = azf;

                    ros::Time measurement_time = ros::Time::now();
                    imu.header.stamp = measurement_time;
                    imu_pub.publish(imu); 
                   // tf_br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "base_imu_link"));
                
                    // publish temperature message
                    temperature_msg.header.stamp = measurement_time;
                    temperature_msg.header.frame_id = "base_imu_link";
                    temperature_msg.temperature = temperature_in_C;

                    imu_temperature_pub.publish(temperature_msg);

                  
                  }

                 }


                  int IMU_Yaw = ((0x7F & (char)input[data_packet_start+26]) << 8)  |
                                 (0xFF & (char)input[data_packet_start+27]);

                  int sign_IMU_Yaw = (char)(input[data_packet_start+26]) >> 7 == 0 ? 1 : -1;

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


               
                if(input[data_packet_start+48] == 1)
                {

                  lastOdOTime = ros::Time::now();

                   long X = ((0x7F & (char)input[data_packet_start+28]) << 24) |
                                ((0xFF & (char)input[data_packet_start+29]) << 16) |
                                ((0xFF & (char)input[data_packet_start+30]) << 8)  |
                                (0xFF & (char)input[data_packet_start+31]);

                  int sign_x = (char)(input[data_packet_start+28]) >> 7 == 0 ? 1 : -1;
                   
                   long Y = ((0x7F & (char)input[data_packet_start+32]) << 24) |
                                ((0xFF & (char)input[data_packet_start+33]) << 16) |
                                ((0xFF & (char)input[data_packet_start+34]) << 8) |
                                (0xFF & (char)input[data_packet_start+35]);

                  int sign_y = (char)(input[data_packet_start+32]) >> 7 == 0 ? 1 : -1;

                   long VX =  ((0x7F & (char)input[data_packet_start+36]) << 24) |
                                  ((0xFF & (char)input[data_packet_start+37]) << 16) |
                                  ((0xFF & (char)input[data_packet_start+38]) << 8)  |
                                  (0xFF & (char)input[data_packet_start+39]);

                  int sign_vx = (char)(input[data_packet_start+36]) >> 7 == 0 ? 1 : -1;

                   long VY = ((0x7F & (char)input[data_packet_start+40]) << 24) |
                                 ((0xFF & (char)input[data_packet_start+41]) << 16) |
                                 ((0xFF & (char)input[data_packet_start+42]) << 8)  |
                                 (0xFF & (char)input[data_packet_start+43]);

                  int sign_vy = (char)(input[data_packet_start+24]) >> 7 == 0 ? 1 : -1;

                   int Yaw = ((0x7F & (char)input[data_packet_start+44]) << 8)  |
                                 (0xFF & (char)input[data_packet_start+45]);

                  int sign_yaw = (char)(input[data_packet_start+44]) >> 7 == 0 ? 1 : -1;

                   int Wz = ((0x7F & (char)input[data_packet_start+46]) << 8)  |
                                 (0xFF & (char)input[data_packet_start+47]);

                  int sign_wz = (char)(input[data_packet_start+46]) >> 7 == 0 ? 1 : -1;

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

                  cout << "X: " << ODO_x;
                  cout << " Y: "   << ODO_y;
                  cout << " VX: "  << ODO_vx;
                  cout << " VY: "  << ODO_vy;
                  cout << " Yaw: " << ODO_th;
                  cout << " Wz: "  << ODO_vth << endl;


                  ros::Time current_time = ros::Time::now();
                  
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
                }
                else
                 if(sumsq > 0.999 )
                {
                
                    differential_rotation.normalize();
                    
                   ros::Time current_time = ros::Time::now();


                  // // tf::Transform KTransform;
                  // // KTransform.setOrigin(HeadTransform.getOrigin());
                  // // //KTransform.setRotation(HeadTransform.getRotation());
            
                  // // tf_br.sendTransform(tf::StampedTransform(KTransform, current_time, "base_link", "camera_link"));


                  //since all odometry is 6DOF we'll need a quaternion created from yaw
                  // geometry_msgs::Quaternion odom_quat;
                  // tf::quaternionTFToMsg(differential_rotation, odom_quat);

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
                  odom.twist.twist.angular.z = gz;
              
                  if(pub_odom)
                  {
                     odom_pub.publish(odom);
                  }

                  if(pub_odom_tf)
                  {
                    tf_br.sendTransform(odom_trans);
                  }
                
                }
                // uint8_t received_message_number = input[data_packet_start + 51];
                // ROS_WARN_STREAM("received message number: " << received_message_number);

                // if (received_message) // can only check for continuous numbers if already received at least one packet
                // {
                //   uint8_t message_distance = received_message_number - last_received_message_number;
                //   if ( message_distance > 1 )
                //   {
                //     ROS_WARN_STREAM("Missed " << message_distance - 1 << " MPU6050 data packets from arduino.");
                //   }
                // }
                // else
                // {
                //   received_message = true;
                // }
                input.erase(0, data_packet_start + 54); // delete everything up to and including the processed packet
              }
              else
              {
                if (input.length() >= data_packet_start + 54)
                { 
                  input.erase(0, data_packet_start + 1); // delete up to false data_packet_start character so it is not found again
                }
                else
                {
                  // do not delete start character, maybe complete package has not arrived yet
                  input.erase(0, data_packet_start);
                }
              }
            }
            else
            {
              // no start character found in input, so delete everything
              input.clear();
            }
          }
        }
      }
      else
      {
        // try and open the serial port
        try
        {
          ser.setPort(port);
          ser.setBaudrate(115200);
          serial::Timeout to = serial::Timeout::simpleTimeout(1000);
          ser.setTimeout(to);
          ser.open();
        }
        catch (serial::IOException& e)
        {
          ROS_ERROR_STREAM("Unable to open serial port " << ser.getPort() << ". Trying again in 5 seconds.");
          ros::Duration(5).sleep();
        }

        if(ser.isOpen())
        {
          ROS_DEBUG_STREAM("Serial port " << ser.getPort() << " initialized and opened.");
        }
      }
    }
    catch (serial::IOException& e)
    {
      ROS_ERROR_STREAM("Error reading from the serial port " << ser.getPort() << ". Closing connection.");
      ser.close();
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
