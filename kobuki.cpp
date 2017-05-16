#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
//#include <tgmath.h>
//#include <tf/transform_broadcaster.h>
//#include <Quartenion.h>
#include <tf/tf.h>
using namespace std;
float xc = 0.0, yc = 0.0, tc = 0.0; //current pose
float xg = 0.0, yg = 0.0, tg = 0.0; //goal points
float v = 0.0, w = 0.0; //linear and angular velocities 
float t_error = 0.0;

void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg) // odometry subscriber callback
{
	xc = msg->pose.pose.position.x;
	yc = msg->pose.pose.position.y;
	double offset = 0;
	//tc = get from quartenion;
	/*tf::Matrix3x3 m(q);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);*/
	geometry_msgs::Quaternion odom_quat = msg->pose.pose.orientation;
	double yaw = tf::getYaw(odom_quat);
	tc = yaw;
	cout<<"The yaw is "<<yaw*180*7/22<<"\n";
}

void goalCallback(const geometry_msgs::Twist::ConstPtr& gmsg)// goal subcriber callback
{
	xg = gmsg->linear.x;
	yg = gmsg->linear.y;
	//cout<<"The goal is "<<atan((yg-yc)/(xg-xc))<<"\n";
}

float PID()// Calculate the angular velocity 
{ 
  float tIerror = 0.0, tDerror = 0.0, old_t_error = 0.0;	
  tg = atan((yg-yc)/(xg-xc));
  //cout<<"The goal is "<<tg<<"\n";
  t_error = tg - tc;
  float t_kp = 4, t_ki = 0.0, t_kd = 0.0;//setting PID gains
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
		//cout <<"The goal is "<<xg<<", "<<yg<<" Current postion is "<<xc<<", "<<yc<<"\n";
		geometry_msgs::Twist velocity; //a message object
		v = 0.0;


		//w = PID();
		//cout<<"The omega is "<<w<<"\n";
		//cout<<"The error is "<<t_error<<"\n";
		velocity.linear.x = v;
		velocity.angular.z = w;
		chatter_pub.publish(velocity);
		ros::spinOnce();
		loop_rate.sleep();

	}
	return 0;
}