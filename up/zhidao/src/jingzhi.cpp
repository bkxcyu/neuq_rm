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
#include <dynamic_reconfigure/server.h>
#include <sap/sapConfig.h>
using namespace std;
double x,y,z;
void chatterCallback1(const geometry_msgs::Point::ConstPtr& abc)  
{  
x=abc->x;
y=abc->y;
z=abc->z;
ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",x,y,z);
}

void callback(sap::sapConfig &config, uint32_t level) {
  /*ROS_INFO("Reconfigure Request: %f %f %f %s %d", 
            config.point3d_x, config.point3d_y, config.point3d_z,
            config.yes?"True":"False", 
            config.size);*/
            x=config.point3d_x;
			y=config.point3d_y;
			z=config.point3d_z;
			ROS_INFO("%f,%f,%f",x,y,z);
}

int main(int argc, char **argv)
{	
	
	ros::init(argc,argv,"sap");
	ros::NodeHandle n;
	dynamic_reconfigure::Server<sap::sapConfig> server;
    dynamic_reconfigure::Server<sap::sapConfig>::CallbackType f;
	double yaw,pitch,v=20,s;
	geometry_msgs::Point point;
	sap::angle msg;
	ros::Publisher  pserial = n.advertise<sap::angle>("control", 1000);	  
	ros::Rate loop_rate(10);
	f = boost::bind(&callback, _1, _2);
	server.setCallback(f);
	ros::Subscriber point3dsub = n.subscribe("point3d",2,chatterCallback1);
    while(ros::ok())
	{
	    //cout<<"ssss"<<endl;
		s=sqrt(pow(x,2)+pow(y,2));
		yaw=atan(double(y)/double(x));
		pitch=atan((2*pow(v,2)*s-sqrt(4*pow(v,4)*pow(s,2)-8*9.8*pow(v,2)*pow(s,2)*z-4*9.8*9.8*pow(s,4)))/(2*9.8*pow(s,2)));
		msg.pitch=pitch;
		msg.yaw=yaw;
		cout<<"pitch"<<pitch<<endl;
		cout<<"yaw"<<yaw<<endl;
		pserial.publish(msg);  
		ros::spinOnce();
		loop_rate.sleep();
	}
return 0;
}
