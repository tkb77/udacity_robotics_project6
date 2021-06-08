#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

double pick_x = 0.6;
double pick_y = 3.6;
double drop_x = 0.3;
double drop_y = -3.2;
ros::Publisher marker_pub;
	
visualization_msgs::Marker marker;

int main( int argc, char** argv )
{
  ros::init(argc, argv, "test_add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  
  marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = visualization_msgs::Marker::CUBE;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pick_x;
    marker.pose.position.y = pick_y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.15;
    marker.scale.y = 0.15;
    marker.scale.z = 0.15;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
  
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN("Please create a subscriber to the marker");
      sleep(1);
    }
    ROS_INFO("Publishing pick cube");
    marker_pub.publish(marker);

    ros::Duration(5.0).sleep();

    ROS_INFO("Delete pick cube");
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);

    ros::Duration(5.0).sleep();

    ROS_INFO("Publishing pick cube at drop zone");
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = drop_x;
    marker.pose.position.y = drop_y;
    marker_pub.publish(marker);
	
    r.sleep();	
  	
    ros::spin();
  
    return 0;
}
