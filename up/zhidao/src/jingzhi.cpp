#include"ros/ros.h"
#include"std_msgs/String.h"
#include<ros/ros.h>
#include<boost/thread.hpp>
#include<geometry_msgs/Point.h>
#include<geometry_msgs/PoseStamped.h>
#include<geometry_msgs/Twist.h>
#include<iostream>
#include<cmath>
#include <cstdlib>
#include<sap/angle.h>
//#include <dynamic_reconfigure/server.h>
//#include <sap/sapConfig.h>
#include<std_msgs/Float64.h>
using namespace std;
double x,y,z;
std_msgs::Float64 pitch1;
std_msgs::Float64 yaw1;
void chatterCallback1(const geometry_msgs::Point::ConstPtr& abc)  
{  
x=abc->x/100;
y=abc->y/100;
z=abc->z/100;
ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",x,y,z);
}
double is_nan(double z)
{
if(z==z)
{return z;}
else
{return 0;}


}
/*1
void callback(sap::sapConfig &config, uint32_t level) {
        x=config.point3d_x;
	y=config.point3d_y;
	z=config.point3d_z;
	ROS_INFO("%f,%f,%f",x,y,z);
}*/

int main(int argc, char **argv)
{	
	
	ros::init(argc,argv,"sap");
	ros::NodeHandle n;
	//1dynamic_reconfigure::Server<sap::sapConfig> server;
   //1 dynamic_reconfigure::Server<sap::sapConfig>::CallbackType f;
	double yaw,pitch,v=20,s;
	geometry_msgs::Point point;
	sap::angle msg;
	ros::Publisher  pserial = n.advertise<sap::angle>("control", 1000);
        ros::Publisher pub_pitch = n.advertise<std_msgs::Float64>("/swivel/swivel/swiveljoint2_position_controller/command", 1);
	ros::Publisher pub_yaw = n.advertise<std_msgs::Float64>("/swivel/swivel/swiveljoint1_position_controller/command", 1);
	ros::Rate loop_rate(10);
	//1f = boost::bind(&callback, _1, _2);
	//1server.setCallback(f);
	ros::Subscriber point3dsub = n.subscribe("point3d",2,chatterCallback1);
    while(ros::ok())
	{
		s=sqrt(pow(x,2)+pow(z,2));
		yaw=is_nan(atan2(double(z),double(x)));

		pitch=is_nan(atan2(double(y),double(s)));
		
//pitch=is_nan(atan2((2*pow(v,2)*s-sqrt(4*pow(v,4)*pow(s,2)-8*9.8*pow(v,2)*pow(s,2)*z-4*9.8*9.8*pow(s,4))),(2*9.8*pow(s,2))));
//pitch = is_nan(atan2((pow(v, 2) - sqrt(pow(v, 4) - 9.8*(9.8*pow(s, 2) + 2 * pow(v, 2)*y))) , (9.8*s)));
		cout<<"pitch"<<pitch<<endl;
		cout<<"yaw"<<yaw<<endl;
		msg.pitch=pitch;
		msg.yaw=yaw;
		pserial.publish(msg);
		pitch1.data=pitch;
		yaw1.data=yaw;
		pub_pitch.publish(pitch1);
		pub_yaw.publish(yaw1);
		ros::spinOnce();
		loop_rate.sleep();
	}
return 0;
}
