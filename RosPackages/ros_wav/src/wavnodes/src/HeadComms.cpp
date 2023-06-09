#include <geometry_msgs/Quaternion.h>
#include <ros/ros.h>
#include "serial/serial.h"
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/Temperature.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>

serial::Serial ser;

//............................................. Head Yaw....Head Pitch...............*//
uint8_t HeadPoseCommand[] = {0x00, 0x53, 0x53, 0x00, 0x00, 0x00, 0x00, 0x53, 0x50, 0x00};
ros::Time LastPoseTrigger;
float Roll_To_Degree = 0;
float Pitch_To_Degree = 0;
bool IsCommandHandled = true;
void joy_callback(const sensor_msgs::Joy& joyStat)
{ 
  if(ser.isOpen() && IsCommandHandled && (ros::Time::now().toNSec() - LastPoseTrigger.toNSec()/1000000.0 > 50))
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

    IsCommandHandled = false;
    ser.write(HeadPoseCommand , 10);
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
  std::string tf_parent_frame_id;
  std::string tf_frame_id;
  std::string frame_id;
  double time_offset_in_seconds;
  bool pub_imu;
  bool pub_imu_tf;
  double linear_acceleration_stddev;
  double angular_velocity_stddev;
  double orientation_stddev;
  uint8_t last_received_message_number;
  bool received_message = false;
  int data_packet_start;

  tf::Quaternion orientation;
  tf::Quaternion zero_orientation;

  ros::init(argc, argv, "HeadComms");

  ros::NodeHandle private_node_handle("~");
  private_node_handle.param<std::string>("port", port, "/dev/ttyUSB2");
  private_node_handle.param<std::string>("tf_parent_frame_id", tf_parent_frame_id, "base_link");
  private_node_handle.param<std::string>("tf_frame_id", tf_frame_id, "camera_link");
  private_node_handle.param<std::string>("frame_id", frame_id, "camera_link");
  private_node_handle.param<double>("time_offset_in_seconds", time_offset_in_seconds, 0.0);
  private_node_handle.param<bool>("pub_imu", pub_imu, true);
  private_node_handle.param<bool>("pub_imu_tf", pub_imu_tf, true);
  private_node_handle.param<double>("linear_acceleration_stddev", linear_acceleration_stddev, 0.0);
  private_node_handle.param<double>("angular_velocity_stddev", angular_velocity_stddev, 0.0);
  private_node_handle.param<double>("orientation_stddev", orientation_stddev, 0.0);

  ros::NodeHandle nh("imu");
  ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("data", 50);
  ros::Publisher imu_temperature_pub = nh.advertise<sensor_msgs::Temperature>("temperature", 50);
  ros::ServiceServer service = nh.advertiseService("set_zero_orientation", set_zero_orientation);


  ros::NodeHandle npose;
  ros::Subscriber sub = npose.subscribe("/joy", 1000, joy_callback);


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

  static tf::TransformBroadcaster tf_br;
  tf::Transform transform;
  transform.setOrigin(tf::Vector3(0.06,0,0.655));
       tf::Quaternion differential_rotation;
           
  std::string input;
  std::string read;
LastPoseTrigger = ros::Time::now();
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
          while (input.length() >= 29) // while there might be a complete package in input
          {
            //parse for data packets
            data_packet_start = input.find("$\x03");
            if (data_packet_start != std::string::npos)
            {
              ROS_DEBUG("found possible start of data packet at position %d", data_packet_start);
              if ((input.length() >= data_packet_start + 29) && (input.compare(data_packet_start + 27, 2, "\r\n") == 0))  //check if positions 26,27 exist, then test values
              {
                ROS_DEBUG("seems to be a real data package: long enough and found end characters");

                if((0xff &(char)input[data_packet_start + 24]) == 0xCC)
                IsCommandHandled = true;
                //get quaternion values
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
                       differential_rotation = zero_orientation.inverse() * orientation;

                }

                //http://answers.ros.org/question/10124/relative-rotation-between-two-quaternions/
           
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
                ROS_DEBUG_STREAM("Temperature [in C] " << temperature_in_C);

                uint8_t received_message_number = input[data_packet_start + 26];
                ROS_DEBUG("received message number: %i", received_message_number);

                if (received_message) // can only check for continuous numbers if already received at least one packet
                {
                  uint8_t message_distance = received_message_number - last_received_message_number;
                  if ( message_distance > 1 )
                  {
                    ROS_WARN_STREAM("Missed " << message_distance - 1 << " MPU6050 data packets from arduino.");
                  }
                }
                else
                {
                  received_message = true;
                }
                last_received_message_number = received_message_number;

                // calculate measurement time
                ros::Time measurement_time = ros::Time::now() + ros::Duration(time_offset_in_seconds);

   float sumsq = differential_rotation.getX() * differential_rotation.getX() +
                              differential_rotation.getY() * differential_rotation.getY() +
                              differential_rotation.getZ() * differential_rotation.getZ()+
                              differential_rotation.getW() * differential_rotation.getW() ;
  std::cout<<"sumsq:"<< sumsq <<std::endl;   
  std::cout<<"zero orientation:"<< zero_orientation.getX() << " " << zero_orientation.getY() << " " << zero_orientation.getZ() << " " << zero_orientation.getW() <<std::endl;
  std::cout<<"orientation:"<< orientation.getX() << " " << orientation.getY() << " " << orientation.getZ() << " " << orientation.getW() <<std::endl;
  std::cout<<"diff orientation:"<< differential_rotation.getX() << " " << differential_rotation.getY() << " " << differential_rotation.getZ() << " " << differential_rotation.getW() <<std::endl;
             
                if(sumsq > 0.999 )
                {
                differential_rotation.normalize();
               
                // publish imu message
                imu.header.stamp = measurement_time;
                imu.header.frame_id = frame_id;

                quaternionTFToMsg(differential_rotation, imu.orientation);

                imu.angular_velocity.x = gxf;
                imu.angular_velocity.y = gyf;
                imu.angular_velocity.z = gzf;

                imu.linear_acceleration.x = axf;
                imu.linear_acceleration.y = ayf;
                imu.linear_acceleration.z = azf;

                if(pub_imu)
                {
                 imu_pub.publish(imu);
                }

                // publish temperature message
                temperature_msg.header.stamp = measurement_time;
                temperature_msg.header.frame_id = frame_id;
                temperature_msg.temperature = temperature_in_C;

                imu_temperature_pub.publish(temperature_msg);

                // publish tf transform
                if (pub_imu_tf)
                {

                  transform.setOrigin(tf::Vector3(0.06,0,0.655));
                  transform.setRotation(differential_rotation);
                  tf_br.sendTransform(tf::StampedTransform(transform, measurement_time, tf_parent_frame_id, tf_frame_id));
                }
              }
                input.erase(0, data_packet_start + 29); // delete everything up to and including the processed packet
              }
              else
              {
                if (input.length() >= data_packet_start + 29)
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
}
