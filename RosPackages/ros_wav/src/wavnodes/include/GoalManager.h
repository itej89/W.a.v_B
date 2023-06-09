#pragma once

#include <memory>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

class GoalManager{
  private:

  typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
  std::unique_ptr<MoveBaseClient> ac;

  public:
  GoalManager(ros::NodeHandle *nh);
  void WaitForServer();

  void SendGoal(float x, float y, float z, float ax, float ay, float az, float aw);

};