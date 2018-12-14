#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
ros::Publisher marker_pub;
float current_goal_pose[2] = {FLT_MAX, FLT_MAX};
float previous_goal_pose[2] = {FLT_MAX, FLT_MAX};
bool pickedUp = false;
static visualization_msgs::Marker marker;
uint32_t shape = visualization_msgs::Marker::SPHERE;

void mark(uint32_t shape){

  // Cycle between different shapes
  switch (shape)
  {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
  }
  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  
  if(pickedUp){
    ROS_INFO("Object Picked up");
    marker.color.a = 0.0;
  } 
  else{
    ROS_INFO("Object Dropped off");
    marker.color.a = 1.0;
  } 

  // Publish the marker
  // while (marker_pub.getNumSubscribers() < 1)
  // {
  //   if (!ros::ok())
  //   {
  //     return;
  //   }
  //   ROS_WARN_ONCE("Please create a subscriber to the marker");
  //   sleep(1);
  // }
  marker_pub.publish(marker);

}
void odom_callback(const nav_msgs::Odometry::ConstPtr &odomMsg){
	float px = odomMsg->pose.pose.position.x;
	float py = odomMsg->pose.pose.position.y;
	float e = 0.25f;
  
  if((px > current_goal_pose[0] -e and px < current_goal_pose[0] + e ) and (current_goal_pose[1] +e > py and py > current_goal_pose[1] -e))
  {
    pickedUp = !pickedUp;
    ROS_INFO("Arrived a goal location.");
    current_goal_pose[0] = FLT_MAX;
    current_goal_pose[1] = FLT_MAX;
    mark(shape);
    ros::Duration(1.0).sleep();
  }
}
void mv_cgoal_callback(const geometry_msgs::PoseStamped::ConstPtr &pose){
  float newGoal[2] = {pose->pose.position.x,pose->pose.position.y};
  
  if((newGoal[0] != previous_goal_pose[0]) && (newGoal[1] != previous_goal_pose[1])){
    ROS_INFO("Recieved a new goal pose.");

    previous_goal_pose[0] = current_goal_pose[0]; //backup current goal
    previous_goal_pose[1] = current_goal_pose[1];
    
    current_goal_pose[0] = newGoal[0]; //updating new goal if new goal was issued
    current_goal_pose[1] = newGoal[1];
    
    //display the mark
    marker.pose.position.x = current_goal_pose[0];
    marker.pose.position.y = current_goal_pose[1];
    mark(shape);
    marker_pub.publish(marker);
  }
  return ;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
 
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("/odom", 1, &odom_callback);
  ros::Subscriber mb_current_goal = n.subscribe("/move_base/current_goal", 1, &mv_cgoal_callback);
 
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;
  
  marker.lifetime = ros::Duration(60.0);

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 1.0;
  marker.pose.orientation.w = 0.0;


  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.2;
  marker.scale.y = 0.2;
  marker.scale.z = 0.2;


  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.250f;
  marker.color.g = 1.0f;
  marker.color.b = 0.250f;
  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  ros::spin();

  return 0;
}


