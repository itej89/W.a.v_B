#include "GoalManager.h"

  GoalManager::GoalManager(ros::NodeHandle *nh){
      this->ac = std::unique_ptr<MoveBaseClient>(new MoveBaseClient("/planner/move_base", true));
  }

  void GoalManager::WaitForServer()
  {
    ROS_INFO("Waiting for the move_base action server");
    this->ac->waitForServer(ros::Duration(60));
    ROS_INFO("Connected to move base server");
  }

  void GoalManager::SendGoal(float x, float y, float z, float ax, float ay, float az, float aw)
  {
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.position.y = y;
    goal.target_pose.pose.position.z = z;
    goal.target_pose.pose.orientation.x = ax;
    goal.target_pose.pose.orientation.y = ay;
    goal.target_pose.pose.orientation.z = az;
    goal.target_pose.pose.orientation.w = aw;
    ROS_INFO("");
    ROS_INFO("Sending goal");
    this->ac->sendGoal(goal);
    // Wait for the action to return
    this->ac->waitForResult();
    if (this->ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("You have reached the goal!");
    else
    ROS_INFO("The base failed for some reason");
  }

