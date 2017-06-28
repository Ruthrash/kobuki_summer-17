#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
using namespace std;
void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
	cout<<msg->pose.pose.position.x<<", "<<msg->pose.pose.position.y<<"\n" ;
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/odom", 1000, chatterCallback);
	ros::spin();
	return 0;
}