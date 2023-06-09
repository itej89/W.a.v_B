#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include <pthread.h>
#include <fstream>

#include<vector>


#include <chrono>
#include <sstream>
#include <string>
#include <thread>
#include <signal.h>
#include <memory>


#include "GoalManager.h"
#include "BotConnectConveyListener.h"
#include "DataTypes/BotConnectManager.h"




#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>


using std::vector;
using namespace fmBotConnect;
std::shared_ptr<BotConnectConveyListener> _BotConnectConveyListener;






int main(int argc, char **argv)
{

  ros::init(argc, argv, "wav_goal_manager");

  ros::NodeHandle nh;

  std::shared_ptr<GoalManager> _GoalManager = std::make_shared<GoalManager>(&nh);

  _BotConnectConveyListener = std::make_shared<BotConnectConveyListener>(_GoalManager);

  _GoalManager->WaitForServer();


  BotConnectManager::Instance->Initialize(_BotConnectConveyListener.get());
  BotConnectManager::Instance->StartBotScanBroadCastMessage();

 
  

  

  ros::Rate r(5); //5hz

  
  while(ros::ok())
  {
        try
        {

        }
        catch (std::exception& e)
        {
          ROS_ERROR_STREAM("Error in process loop\n");
          ros::Duration(5).sleep();
        }
    ros::spinOnce();
    r.sleep();
  }
  
}
