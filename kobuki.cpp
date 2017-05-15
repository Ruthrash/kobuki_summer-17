#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
using namespace std;
float xc = 0.0, yc = 0.0, tc = 0.0; //current pose
float xg = 0.0, yg = 0.0, tg = 0.0; //goal points
float v = 0.0, w = 0.0; //linear and angular velocities 

void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg) // odometry subscriber callback
{
	xc = msg->pose.pose.position.x;
	yc = msg->pose.pose.position.y;
	//tc = get from quartenion;
}
void goalCallback(const geometry_msgs::Twist::ConstPtr& gmsg)// goal subcriber callback
{
	xg = gmsg->linear.x;
	yg = gmsg->linear.y;
}
float PID()// Calculate the angular velocity 
{ 
  float t_error = 0.0, tIerror = 0.0, tDerror = 0.0, old_t_error = 0.0;	
  tg = atan2((yg-yc)/(xg-xc));
  t_error = tg - tc;
  t_kp = 4; t_ki = 0.0; t_kd = 0.0;//setting PID gains
  float  omega = 0.0; 
  tDerror = t_error - old_t_error;
  tIerror = tIerror + t_error;
  omega = t_kp * t_error + t_ki * tIerror + t_kd * tDerror;
  old_t_error = t_error;
  //cout << "omega = "<< omega << endl;
  return omega ;

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "kobuki"); //kobuki is the node's name
	ros::NodeHandle nh;
	ros::Publisher chatter_pub = nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",1000);//velocity publisher
	ros::Subscriber sub = nh.subscribe("/goal", 1000, goalCallback); //goal subscriber
	ros::Subscriber subg = nh.subscribe("/odom", 1000, chatterCallback);//odometry subscriber
	ros::Rate loop_rate(10);


	while(ros::ok()) //while ros is running properly
	{
		cout <<"The goal is "<<xg<<", "<<yg<<" Current postion is "<<xc<<", "<<yc<<"\n";
		geometry_msgs::Twist velocity; //a message object
		v = 0.1;
		w = PID();
		velocity.linear.x = v;
		velocity.angular.z = w;
		chatter_pub.publish(velocity);
		ros::spinOnce();
		loop_rate.sleep();

	}
	return 0;
}