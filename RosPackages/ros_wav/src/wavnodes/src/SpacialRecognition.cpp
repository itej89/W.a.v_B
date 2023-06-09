// #include <boost/gil/extension/io/jpeg_io.hpp>

// #include <geometry_msgs/Quaternion.h>
// #include <ros/ros.h>
// #include <sensor_msgs/PointCloud2.h>
// #include <sensor_msgs/Image.h>
// #include <sensor_msgs/CameraInfo.h>


// #include <sensor_msgs/Imu.h>
// #include <sensor_msgs/Joy.h>
// #include <sensor_msgs/Temperature.h>
// #include <std_msgs/String.h>
// #include <std_srvs/Empty.h>
// #include <string>
// #include <tf/transform_broadcaster.h>
// #include <tf/transform_datatypes.h>
// #include <tf/transform_listener.h>
// #include <geometry_msgs/Twist.h>
// #include <nav_msgs/Odometry.h>
// #include <mutex>
// #include <thread>
// #include <iostream>

// #include "rtabmap_ros/RGBDImage.h"





// #include "nlohmann/json.hpp"
// using json = nlohmann::json;



// #include "ZlibHelper.h"
// #include "cppbase64.h"

// #include "TCPModule/DataTypes/Extras/IPEndPoint.h"
// #include "TCPModule/TransportLayer/Helpers/RecievedData.h"
// #include "TCPModule/DataTypes/Delegates/TransportClientConvey.h"
// #include "TCPModule/TransportLayer/TcpClient.h"

// using namespace fmCommon;


// using namespace std;


// bool InitializeTCPConnection()
// {
//       TcpClient::Instance->TcpClientInit("192.168.0.140", 3583);

//       bool IsConnectionEstablished = false;

//       do{
//        std::cout << "Trying to Connect..." <<std::endl;
//           IsConnectionEstablished = TcpClient::Instance->TryConnect(TcpClient::Instance->RemoteEndPoint);
//             std::this_thread::sleep_for(std::chrono::milliseconds(1));
//       }while (!IsConnectionEstablished);

//       if(IsConnectionEstablished)
//        std::cout << "Connection Established" <<std::endl;

//       return IsConnectionEstablished;
// }

// // A callable object
// class ProcessImage : public TransportClientConvey{
//   private:
//    std::string ReponseString = "";
// public:

//   void DataRecieved(RecievedData recievedData) {
//     if(recievedData.recvBuffer.size() > 0)
//     {
//       std::string buf_str(recievedData.recvBuffer.begin(), recievedData.recvBuffer.end());
//       ReponseString += buf_str;
//       if (!json::accept(ReponseString))
//       {
//           std::cerr << "parse error" << std::endl;
//       }
//       else{
//           std::cout << "Ack recieved"  << std::endl;
//           ReponseString = "";
//           done = true;
//       }
//     }
//   }
//   void Disconnected() {}
//   void Timeout(int code) {

//     TcpClient::Instance->Disconnect();
//     InitializeTCPConnection();
//     std::cout << "Timeout recieved"  << std::endl;
//       done = true;
//   }


//   std::atomic<bool> done{true};
//   std::shared_ptr<std::thread> HandlerThread;

//     void Handler(rtabmap_ros::RGBDImage rgbd)
//     {
//       auto CameraInfo = rgbd.rgbCameraInfo;
//       auto CameraRGB= rgbd.rgb;
//       auto CameraDepth = rgbd.depth;

//       std::vector<uint8_t> ImageFrame;

//       const unsigned width  = CameraRGB.width;
//       const unsigned height = CameraRGB.height;

//       // Raw data.
//       unsigned char r[width * height];  // red
//       unsigned char g[width * height];  // green
//       unsigned char b[width * height];  // blue

//       for(int i =0; i<width * height; i++)
//       {
//         b[i] = CameraRGB.data[(i*3)];
//         g[i] = CameraRGB.data[(i*3)+1];
//         r[i] = CameraRGB.data[(i*3)+2];
//       }

//       boost::gil::rgb8c_planar_view_t view =
//       boost::gil::planar_rgb_view(width, height, r, g, b, width);

//       boost::gil::jpeg_write_view("/tmp/tmp.jpg", view);



//       if (FILE *fp = fopen("/tmp/tmp.jpg", "r"))
//       {
//         fseek(fp, 0L, SEEK_END);
//         long sz = ftell(fp);
//         rewind(fp);


//       for(int i=0; i<8; i++)
//         ImageFrame.push_back((sz >> (8*i)) & 0xFF);

//         char buf[1024];
//         while (size_t len = fread(buf, 1, sizeof(buf), fp))
//           {
//           ImageFrame.insert(ImageFrame.end(), buf, buf + len);
//           }
//         fclose(fp);
//       }




//       // for(int i=0 ;i<4; i++)
//       // ImageFrame.push_back((CameraRGB.height >> (8*i)) & 0xFF);

//       // for(int i=0 ;i<4; i++)
//       // ImageFrame.push_back((CameraRGB.width >> (8*i)) & 0xFF);


//       // ImageFrame.insert(ImageFrame.end(), CameraRGB.data.begin(), CameraRGB.data.end());
//       std::cout << "Frame Length : " << ImageFrame.size() << std::endl;


//       TcpClient::Instance->SendData(ImageFrame);


//     }

//     std::shared_ptr<std::thread> getHandler(rtabmap_ros::RGBDImage rgbd) {
//         if(done){
//           done = false;
//           HandlerThread = std::make_shared<std::thread>(&ProcessImage::Handler, this, rgbd);
//           HandlerThread->detach();
//           return HandlerThread;
//         }
//         else
//         {
//           return nullptr;
//         }

//       }
// };


// class SpacialRecognition{
//   private:
//   bool PARAM;
//   ros::Subscriber rgbd_Sub;


//   public:
//   std::shared_ptr<ProcessImage>  tProcessImage;

//   SpacialRecognition(ros::NodeHandle *nh){
//       tProcessImage = std::make_shared<ProcessImage>();

//         nh->param<bool>("PARAM", PARAM, true);

//         rgbd_Sub = nh->subscribe("/rtabmap/rgbd_image", 1000, &SpacialRecognition::RGBD_callback, this);
//   }

//   void RGBD_callback(const rtabmap_ros::RGBDImage& rgbd)
//   {
//       // std::cout << "Recived Data" <<std::endl;
//       tProcessImage->getHandler(rgbd);
//   }
// };







int main(int argc, char **argv)
{

//   ros::init(argc, argv, "SpacialRecognition");

//   ros::NodeHandle nh;

//   InitializeTCPConnection();

//   SpacialRecognition _SpacialRecognition(&nh);

//   TcpClient::Instance->ClientConvey = std::dynamic_pointer_cast<TransportClientConvey>(_SpacialRecognition.tProcessImage);

//   ros::Rate r(20); //5hz

//   while(ros::ok())
//   {
//         try
//         {

//         }
//         catch (exception& e)
//         {
//           ROS_ERROR_STREAM("Error in process loop\n");
//           ros::Duration(5).sleep();
//         }
//     ros::spinOnce();
//     r.sleep();
//   }

//   if(_SpacialRecognition.tProcessImage->HandlerThread != nullptr)
//        _SpacialRecognition.tProcessImage->HandlerThread->join();

}
























// //Multiple protocol tests


//     // void Handler(rtabmap_ros::RGBDImage rgbd)
//     // {
//     //   auto CameraInfo = rgbd.rgbCameraInfo;
//     //   auto CameraRGB= rgbd.rgb;
//     //   auto CameraDepth = rgbd.depth;

//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "RGB Information" << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "Height : " << CameraRGB.height << std::endl;
//     //   // std::cout << "Width : " << CameraRGB.width << std::endl;
//     //   // std::cout << "step : " << CameraRGB.step << std::endl;
//     //   // std::cout << "Encoding : " << CameraRGB.encoding << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;


//     //   // json jdata = CameraRGB.data;
//     //   // json RGBImageRequest;
//     //   // RGBImageRequest["Height"] = CameraRGB.height;
//     //   // RGBImageRequest["Width"] = CameraRGB.width;
//     //   // RGBImageRequest["Step"] = CameraRGB.step;
//     //   // RGBImageRequest["Encoding"] = CameraRGB.encoding;
//     //   // RGBImageRequest["Data"] = CameraRGB.data;



//     //   // const unsigned width  = CameraRGB.width;
//     //   // const unsigned height = CameraRGB.height;

//     //   // // Raw data.
//     //   // unsigned char r[width * height];  // red
//     //   // unsigned char g[width * height];  // green
//     //   // unsigned char b[width * height];  // blue

//     //   // for(int i =0; i<width * height; i++)
//     //   // {
//     //   //   b[i] = CameraRGB.data[(i*3)];
//     //   //   g[i] = CameraRGB.data[(i*3)+1];
//     //   //   r[i] = CameraRGB.data[(i*3)+2];
//     //   // }

//     //   // boost::gil::rgb8c_planar_view_t view =
//     //   // boost::gil::planar_rgb_view(width, height, r, g, b, width);

//     //   // boost::gil::jpeg_write_view("/tmp/tmp.jpg", view);


//     //   // std::vector<uint8_t> ImageFrame;

//     //   // if (FILE *fp = fopen("/tmp/tmp.jpg", "r"))
//     //   // {
//     //   //   char buf[1024];
//     //   //   while (size_t len = fread(buf, 1, sizeof(buf), fp))
//     //   //     {
//     //   //     ImageFrame.insert(ImageFrame.end(), buf, buf + len);
//     //   //     }
//     //   //   fclose(fp);
//     //   // }



//     //   for(int i=0 ;i<4; i++)
//     //   ImageFrame.push_back((CameraRGB.height >> (8*i)) & 0xFF);

//     //   for(int i=0 ;i<4; i++)
//     //   ImageFrame.push_back((CameraRGB.width >> (8*i)) & 0xFF);


//     //   ImageFrame.insert(ImageFrame.end(), CameraRGB.data.begin(), CameraRGB.data.end());
//     //   std::cout << "Frame Length : " << ImageFrame.size() << std::endl;
//     //   TcpClient::Instance->SendData(ImageFrame);

//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "RGB Information" << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "JSON REQUEST : " << RGBImageRequest.dump() << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;


//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "Compressing RGB Information" << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;
//     //   // ZlibHelper _ZlibHelper;
//     //   // std::string str_compressed = _ZlibHelper.compress_string(RGBImageRequest.dump());

//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "Encoding RGB Information" << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;
//     //   // cpr::Payload payload{{"RGDData", base64_encode(RGBImageRequest.dump())}};

//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "Posting RGB Information" << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;
//     //   // cpr::Response r = cpr::Post(cpr::Url{"http://127.0.0.1:3583/IMAGE_INSTACE_SEGMANTATION"}, payload);
//     //   // r.status_code;                  // 200
//     //   // r.header["content-type"];       // application/json; charset=utf-8


//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "RGB Information" << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "Status Code : " << r.status_code   << std::endl;
//     //   // std::cout << "JSON RESPONSE : " <<  r.text   << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;




//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "Depth Information" << std::endl;
//     //   // std::cout << "--------------------"  << std::endl;
//     //   // std::cout << "Height : " << rgbd.depth.height << std::endl;
//     //   // std::cout << "Width : " << rgbd.depth.width << std::endl;
//     //   // std::cout << "step : " << rgbd.depth.step << std::endl;
//     //   // std::cout << "Encoding : " << rgbd.depth.encoding << std::endl;
//     //   // std::cout << "--------------------" << std::endl;
//     //   // std::string JsonDump = RGBImageRequest.dump();
//     //   // std::string base64_encoded =base64_encode(JsonDump);
//     //   // std::vector<uint8_t> vec(JsonDump.begin(), JsonDump.end());
//     //   // TcpClient::Instance->SendData(vec);

//     // }