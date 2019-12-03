#include"ros/ros.h"
#include"std_msgs/String.h"
#include<ros/ros.h>
#include<boost/thread.hpp>
#include<geometry_msgs/Point.h>
#include<geometry_msgs/PoseStamped.h>
#include<geometry_msgs/Twist.h>
#include<iostream>
#include"zhidao.h"
#include<cmath>
#include<aim/angle.h>

using namespace std;
GimbalContrl::GimbalContrl(int x,int y,int z)
{
	this->x=x;
	this->y=y;
	this->z=z;

}
//~GimbalContrl(){cout<<dd;};
double GimbalContrl::sets()
{
    this->s=sqrt(pow(x,2)+pow(y,2));
}

double GimbalContrl::setyaw()
{
     this->yaw=atan(y/x);
}

double GimbalContrl::setpitch()
{
 this->pitch=atan((2*pow(v,2)*s-sqrt(4*pow(v,4)*pow(s,2)-8*9.8*pow(v,2)*pow(s,2)*z-4*9.8*9.8*pow(s,4)))/(2*9.8*pow(s,2)));
}

double GimbalContrl::getyaw()
{
return yaw;
}

double GimbalContrl::gets()
{
return s;
}
double GimbalContrl::getpitch()
{
return pitch;
}

//类定义完成
//
//
///
////
/////
//////
///////
////////

void chatterCallback1(const geometry_msgs::Point::ConstPtr& abc)  
{  
  geometry_msgs::Point point;
  aim::angle msg;
  ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",abc->x,abc->y,abc->z);
  GimbalContrl hhh(abc->x,abc->y,abc->z);
  hhh.sets();
  hhh.setyaw();
  hhh.setpitch();
  cout<<"pitch"<<hhh.getpitch()<<"   s\t"<<hhh.gets()<<"    yaw\t"<<hhh.getyaw()<<endl;
  //send(hhh.getpitch(),hhh.gets(),hhh.getyaw())
  msg.pitch=hhh.getpitch();
  msg.yaw=hhh.getyaw();
  msg.s=hhh.gets();
  ros::NodeHandle n;
  ros::Publisher  pserial = n.advertise<aim::angle>("chatter3", 1000);
  pserial.publish(msg);

 //pub.publish(msg1); 
}  
void chatterCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg)  
{  
  geometry_msgs::Point point;
  point.x = 1;
  point.y = 2;
  point.z = 3;

 //pub.publish(msg1); 
}  
void chatterCallback3(const geometry_msgs::Twist::ConstPtr& msg)  
{  
  geometry_msgs::Twist twist;
  twist.linear.x = 1;
  twist.linear.y = 2;
  twist.linear.z = 3;

 //pub.publish(msg1); 
}  


int main(int argc, char **argv)
{
	ros::init(argc,argv,"sap");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
    while(ros::ok())
	{
		/*std_msgs::String msg1;
		std::stringstream ss1;
		msg1.data=ss1.str();
		std_msgs::String msg2;
		std::stringstream ss2;
		msg2.data=ss2.str(); */
		
		ros::Subscriber sub1 = n.subscribe("chatter2",100,chatterCallback1);
	    //ros::Subscriber sub2 = n.subscribe("**",100,chatterCallback2);
	    //ros::Subscriber sub3 = n.subscribe("**",100,chatterCallback3);
	    //ros::Subscriber sub2 = n.subscribe("**",100,chatterCallback2);
		ros::Publisher  pserial = n.advertise<aim::angle>("chatter3", 1000);
		//ros::Publisher  pub2 = n.advertise<std_msgs::String>("chatter2", 1000); 
		//ros::MultiThreadedSpinner spinner(2);
                //spinner.spin();
	    loop_rate.sleep();
		ros::spin();
	}
return 0;
}
