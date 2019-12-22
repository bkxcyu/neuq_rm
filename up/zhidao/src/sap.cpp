#include"ros/ros.h"
#include"std_msgs/String.h"
#include<ros/ros.h>
#include<boost/thread.hpp>
#include<geometry_msgs/Point.h>
#include<geometry_msgs/PoseStamped.h>
#include<geometry_msgs/Twist.h>
#include<iostream>
#include<cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <cstdlib>
#include<sap/angle.h>
using namespace std;
using namespace Eigen;


void chatterCallback1(const geometry_msgs::Point::ConstPtr& abc)  
{  
ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",abc->x,abc->y,abc->z);
double yaw,pitch,v=20,s;
Eigen::MatrixXd A(6,6);
A << 1, 0.02, 0, 0, 0, 0,
     0, 1, 0, 0, 0, 0,
     0, 0, 1, 0.02, 0, 0, 
     0, 0, 0, 1, 0, 0,
     0, 0, 0, 0, 1, 0.02,
     0, 0, 0, 0, 0, 1;

Eigen::MatrixXd H(3,6);
H <<1, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 1, 0;

Eigen::MatrixXd P(6,6);
P << 1, 1, 0, 0, 0, 0,
	 1, 1, 0, 0, 0, 0,
	 0, 0, 1, 1, 0, 0,
	 0, 0, 1, 1, 0, 0,
     0, 0, 0, 0, 1, 1,
     0, 0, 0, 0, 1, 1;

Eigen::MatrixXd Q(6,6);
Q << 0, 0, 0, 0, 0, 0,
	 0, 5, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0,
     0, 0, 0, 5, 0, 0,
     0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 1;

Eigen::MatrixXd R(3,3);
R << 200, 0,   0,
	 0,   200, 0,
     0,   0,   200;

Eigen::VectorXd x(6);
x << 0, 0, 0, 0, 0, 0;
  geometry_msgs::Point point;
  sap::angle msg;
  ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",abc->x,abc->y,abc->z);
  
  Eigen::MatrixXd z_meas(3,1);
  z_meas << abc->x,abc->y,abc->z;

  x = A * x;
cout<<"sssssssssssss";
  Eigen::MatrixXd A_T = A.transpose();

  P = A * P*A_T + Q;
	
  Eigen::MatrixXd temp1, temp2, Ht;
  Ht = H.transpose();
  temp1 = H * P * Ht + R;
  temp2 = temp1.inverse();

  Eigen::MatrixXd K = P * Ht*temp2;

  Eigen::VectorXd z = H * x;
  x = x + K * (z_meas - z);

  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(6,6);
  P = (I - K * H)*P;
 double after_x,after_y,after_z;
  after_x = x (0,0);
  after_y = x (1,0);
  after_z = x (2,0);

  s=sqrt(pow(after_x,2)+pow(after_y,2));
  yaw=atan(after_y/after_x);
  pitch=atan((2*pow(v,2)*s-sqrt(4*pow(v,4)*pow(s,2)-8*9.8*pow(v,2)*pow(s,2)*after_z-4*9.8*9.8*pow(s,4)))/(2*9.8*pow(s,2)));
  
  msg.pitch=pitch;
  msg.yaw=yaw;
  cout<<pitch<<'\n'<<yaw<<endl;
  ros::NodeHandle n;
  ros::Publisher  pserial = n.advertise<sap::angle>("control", 1000);
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
	cout<<"ssss"<<endl;
		/*std_msgs::String msg1;
		std::stringstream ss1;
		msg1.data=ss1.str();
		std_msgs::String msg2;
		std::stringstream ss2;
		msg2.data=ss2.str(); */
		
		ros::Subscriber point3dsub = n.subscribe("point3d",100,chatterCallback1);
	    //ros::Subscriber sub2 = n.subscribe("**",100,chatterCallback2);
	    //ros::Subscriber sub3 = n.subscribe("**",100,chatterCallback3);
	    //ros::Subscriber sub2 = n.subscribe("**",100,chatterCallback2);
		ros::Publisher  pserial = n.advertise<sap::angle>("control", 1000);
		//ros::Publisher  pub2 = n.advertise<std_msgs::String>("chatter2", 1000); 
		//ros::MultiThreadedSpinner spinner(2);
                //spinner.spin();
	    
		ros::spin();
loop_rate.sleep();
	}
return 0;
}
