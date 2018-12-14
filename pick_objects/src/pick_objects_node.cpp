#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects_node node
  ros::init(argc, argv, "pick_objects_node");
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x =2.78205251694;
  goal.target_pose.pose.position.y =1.13228130341;
  goal.target_pose.pose.orientation.z =0.996827650711;
  goal.target_pose.pose.orientation.w =-0.0795904188791;
  ros::Duration(1.5).sleep();

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sendingp pick up location.");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
	  ROS_INFO("Reached the first goal. Moving onto the second goal now.");
	  ROS_INFO("Picking up...");
	  // Sleep for 5 seconds
	  ros::Duration(5.0).sleep();
	  
	  //set drop off location
    goal.target_pose.pose.position.x =3.44253015518;
    goal.target_pose.pose.position.y =-3.48189783096;
    goal.target_pose.pose.orientation.z = 0.997869659399;
    goal.target_pose.pose.orientation.w =-0.0652391205503;

	  // Send the goal position and orientation for the robot to reach
	  ROS_INFO("Sending drop off location.");
	  ac.sendGoal(goal);

	  // Wait an infinite time for the results
	  ac.waitForResult();

	  // Check if the robot reached its goal
	  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
		  ROS_INFO("Reached the second goal.");
		  // Sleep for 5 seconds
		  ros::Duration(5.0).sleep();
	 }
	  else
		  ROS_INFO("The base failed to the drop off location.");

  }
  else
	  ROS_INFO("The base failed to the pickup location.");

  return 0;
}

