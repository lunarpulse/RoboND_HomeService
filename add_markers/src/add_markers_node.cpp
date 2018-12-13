#include <ros/ros.h>
#include <visualization_msgs/Marker.h>


int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);


  // Set our initial shape type to be a cube

  uint32_t shape = visualization_msgs::Marker::SPHERE;



  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();


    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one

    marker.ns = "basic_shapes";
    marker.id = 0;


    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER

    marker.type = shape;


    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)

    marker.action = visualization_msgs::Marker::ADD;


    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header

    marker.pose.position.x = 3.7885696888;
    marker.pose.position.y = -3.34789133072;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.996707892721;
    marker.pose.orientation.w = -0.081076362694;


    // Set the scale of the marker -- 1x1x1 here means 1m on a side

    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;


    // Set the color -- be sure to set alpha to something non-zero!

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;



    marker.lifetime = ros::Duration(5.0);


    // Publish the marker

//    while (marker_pub.getNumSubscribers() < 1)
//    {
//      if (!ros::ok())
//      {
//        return 0;
//      }
//      ROS_WARN_ONCE("Please create a subscriber to the marker");
//      sleep(1);
//    }
    marker_pub.publish(marker);

    sleep(5);
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

    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);

    marker.action = visualization_msgs::Marker::ADD;
    
    marker.pose.position.x = 3.2410521507;
    marker.pose.position.y = 1.1719406843;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.99829414396;
    marker.pose.orientation.w = -0.0583849477605;

    marker_pub.publish(marker);

    sleep(5);

    //r.sleep();
  }

}

