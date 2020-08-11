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
#include <dynamic_reconfigure/server.h>
#include <sap/guideConfig.h>
using namespace std;
using namespace Eigen;
#include<std_msgs/Float64.h>
std_msgs::Float64 pitch1;
std_msgs::Float64 yaw1;
//x:distance , y: height
#define _DEBUG
sap::angle msg;
struct _pid{
float SetAngle;
float ActualAngle;
float err;
float err_last;
float Kp,Ki,Kd;
float controll;
float integral;
}pid;


void PID_init(){
printf("PID_init begin \n");
pid.SetAngle=0.0;
pid.ActualAngle=0.0;
pid.err=0.0;
pid.err_last=0.0;
pid.controll=0.0;
pid.integral=0.0;
pid.Kp=0.2;
pid.Ki=0;
pid.Kd=0;
printf("PID_init end \n");
}

float PID_realize(float angle){
	pid.SetAngle=angle;
	pid.err=pid.SetAngle-pid.ActualAngle;
	pid.integral+=pid.err;
	pid.controll=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
	pid.err_last=pid.err;
	pid.ActualAngle=pid.controll*1.0;

return pid.ActualAngle;
}



double dt=0.01,S=20,v = 20,Dt=2,w=1,l=1,u=1,init_k_=1;
double is_nan(double z)
{
if(z==z)
{return z;}
else
{return 0;}


}
/*float GetPitch(float x, float y, float v) {
	float y_temp, y_actual, dy,t;
	float a;
	//double init_k_=1;
	double GRAVITY=9.8;
	y_temp = y;
	
	// by iteration
	for (int i = 0; i < 20; i++) {
		a = (float)atan2(y_temp, x);
		t = (float)((exp(init_k_ * x) - 1) / (init_k_ * v * cos(a)));
		y_actual = (float)(v * sin(a) * t - GRAVITY * t * t / 2);
		dy = y - y_actual;
		y_temp = y_temp + dy;
		if (fabsf(dy) < 0.001) 
			break;
		}
		//printf("iteration num %d: angle %f,temp target y:%f,err of y:%f\n",i+1,a*180/3.1415926535,yTemp,dy);
			return a;
	}*/

#ifdef _DEBUG 
void callback(sap::guideConfig &config, uint32_t level) {
        dt=config.dt;
	S=config.S;
	v=config.v;
        Dt=config.Dt;
	w=config.w;
	l=config.l;
        u=config.u;
	init_k_=config.init_k;

	ROS_INFO("111");
}
#endif //_DEBUG
void chatterCallback1(const geometry_msgs::Point::ConstPtr& abc)  
{  
ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",abc->x,abc->y,abc->z);

double yaw,pitch,s;

//double dt=0.01,S=20,v = 20,Dt=2,w=1,l=1,u=1;

/*carEigen::MatrixXd A(9,9);
A << 1, 0, 0, dt, 0,  0,  1/2*dt*dt,0,0,
     0, 1, 0, 0,  0, 0,  0,   0,  0,
     0, 0, 1, 0,  0,  dt, 0,  0,  1/2*dt*dt,
     0, 0, 0, 1,  0,  0,  dt, 0,  0,
     0, 0, 0, 0,  1,  0,  0,  dt, 0,
     0, 0, 0, 0,  0,  1,  0,  0,  dt,
     0, 0, 0, 0,  0,  0,  1,  0,  0,
     0, 0, 0, 0,  0,  0,  0,  1,  0,
     0, 0, 0, 0,  0,  0,  0,  0,  1;

Eigen::MatrixXd C(3,9);
C <<1, 0, 0, 0, 0, 0,0,0,0,
    0, 1, 0, 0, 0, 0,0,0,0,
    0, 0, 1, 0, 0, 0,0,0,0;

Eigen::MatrixXd P(9,9);
P <<     1, 0, 0, l, 0, 0, u, 0, 0,
	 0, 1, 0, 0, l, 0, 0, u, 0,
	 0, 0, 1, 0, 0, l, 0, 0, u,
	 l, 0, 0, 1, 0, 0, l, 0, 0,
	 0, l, 0, 0, 1, 0, 0, l, 0,
	 0, 0, l, 0, 0, 1, 0, 0, l,
	 u, 0, 0, l, 0, 0, 1, 0, 0,
	 0, u, 0, 0, l, 0, 0, 1, 0,
	 0, 0, u, 0, 0, l, 0, 0, 1;

Eigen::MatrixXd Q(9,9);
Q <<     0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, w, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, w, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, w;

Eigen::MatrixXd R(3,3);
R << 0, 0, 0,
     0, S, 0,
     0, 0, 0;

Eigen::VectorXd x(9);
x << 0, 0, 0, 0, 0, 0, 0, 0, 0;
  geometry_msgs::Point point;
  

 
  Eigen::MatrixXd y_meas(3,1);
  y_meas << abc->x/100,abc->y/100,abc->z/100;

  x = A * x;
  Eigen::MatrixXd A_T = A.transpose();

  P = A * P*A_T + Q;
	
  Eigen::MatrixXd temp1, temp2, Ct;
  
  Ct = C.transpose();
  temp1 = C * P * Ct + R;
  
  temp2 = temp1.inverse();

  Eigen::MatrixXd K = P * Ct*temp2;

  Eigen::VectorXd y = C * x;
  x = x + K * (y_meas - y);

  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(9,9);
  P = (I - K * C)*P;
  
 double after_x,after_y,after_z;
//after_x=x (0,0) + x(3, 0)*Dt;
//after_y=x (1,0) + x(4, 0)*Dt;
//after_z=x (2,0) + x(5, 0)*Dt;
after_x = x (0,0) + x(3, 0)*Dt + 1 / 2*x(6, 0)*Dt*Dt;
//after_y = x (1,0) + x(4, 0)*Dt + 1 / 2*x(7, 0)*Dt*Dt;
after_y = x (1,0);
after_z = x (2,0) + x(5, 0)*Dt + 1 / 2*x(8, 0)*Dt*Dt;
ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",after_x,after_y,after_z);
ROS_INFO("i heard point.Vx:%f\tpoint.Vy:%f\tpoint.Vz:%f\t",x(3, 0),x(4, 0),x(5, 0));
ROS_INFO("i heard point.Vx:%f\tpoint.Vy:%f\tpoint.Vz:%f\t",x(6, 0),x(7, 0),x(8, 0));
  s=sqrt(pow(after_z,2)+pow(after_x,2));
  //yaw=180-atan2(after_x,after_z)*180/3.14;
  //pitch=180- GetPitch(s,after_y,v)*180/3.14;
   yaw=PID_realize(atan2(after_z,after_x));


	
  msg.yaw = is_nan(yaw);
  //pitch=GetPitch(s,after_y,v);
  pitch=PID_realize(atan2(after_y,s));

*/
/*dfcEigen::MatrixXd A(3,3);
A << 1, 0, 0, dt, 0,  0,  1/2*dt*dt,0,0,
     0, 1, 0, 0,  0, 0,  0,   0,  0,
     0, 0, 1, 0,  0,  dt, 0,  0,  1/2*dt*dt,
     0, 0, 0, 1,  0,  0,  dt, 0,  0,
     0, 0, 0, 0,  1,  0,  0,  dt, 0,
     0, 0, 0, 0,  0,  1,  0,  0,  dt,
     0, 0, 0, 0,  0,  0,  1,  0,  0,
     0, 0, 0, 0,  0,  0,  0,  1,  0,
     0, 0, 0, 0,  0,  0,  0,  0,  1;

Eigen::MatrixXd C(3,9);
C <<1, 0, 0, 0, 0, 0,0,0,0,
    0, 1, 0, 0, 0, 0,0,0,0,
    0, 0, 1, 0, 0, 0,0,0,0;

Eigen::MatrixXd P(9,9);
P <<     1, 0, 0, l, 0, 0, u, 0, 0,
	 0, 1, 0, 0, l, 0, 0, u, 0,
	 0, 0, 1, 0, 0, l, 0, 0, u,
	 l, 0, 0, 1, 0, 0, l, 0, 0,
	 0, l, 0, 0, 1, 0, 0, l, 0,
	 0, 0, l, 0, 0, 1, 0, 0, l,
	 u, 0, 0, l, 0, 0, 1, 0, 0,
	 0, u, 0, 0, l, 0, 0, 1, 0,
	 0, 0, u, 0, 0, l, 0, 0, 1;

Eigen::MatrixXd Q(9,9);
Q <<     0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, w, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, w, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, w;

Eigen::MatrixXd R(3,3);
R << 0, 0, 0,
     0, S, 0,
     0, 0, 0;

Eigen::VectorXd x(9);
x << 0, 0, 0, 0, 0, 0, 0, 0, 0;
  geometry_msgs::Point point;
  

 
  Eigen::MatrixXd y_meas(3,1);
  y_meas << abc->x/100,abc->y/100,abc->z/100;

  x = A * x;
  Eigen::MatrixXd A_T = A.transpose();

  P = A * P*A_T + Q;
	
  Eigen::MatrixXd temp1, temp2, Ct;
  
  Ct = C.transpose();
  temp1 = C * P * Ct + R;
  
  temp2 = temp1.inverse();

  Eigen::MatrixXd K = P * Ct*temp2;

  Eigen::VectorXd y = C * x;
  x = x + K * (y_meas - y);

  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(9,9);
  P = (I - K * C)*P;
  
 double after_x,after_y,after_z;
//after_x=x (0,0) + x(3, 0)*Dt;
//after_y=x (1,0) + x(4, 0)*Dt;
//after_z=x (2,0) + x(5, 0)*Dt;
after_x = x (0,0) + x(3, 0)*Dt + 1 / 2*x(6, 0)*Dt*Dt;
//after_y = x (1,0) + x(4, 0)*Dt + 1 / 2*x(7, 0)*Dt*Dt;
after_y = x (1,0);
after_z = x (2,0) + x(5, 0)*Dt + 1 / 2*x(8, 0)*Dt*Dt;
ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",after_x,after_y,after_z);
ROS_INFO("i heard point.Vx:%f\tpoint.Vy:%f\tpoint.Vz:%f\t",x(3, 0),x(4, 0),x(5, 0));
ROS_INFO("i heard point.Vx:%f\tpoint.Vy:%f\tpoint.Vz:%f\t",x(6, 0),x(7, 0),x(8, 0));
  s=sqrt(pow(after_z,2)+pow(after_x,2));
  //yaw=180-atan2(after_x,after_z)*180/3.14;
  //pitch=180- GetPitch(s,after_y,v)*180/3.14;
   yaw=PID_realize(atan2(after_z,after_x));


	
  msg.yaw = is_nan(yaw);
  //pitch=GetPitch(s,after_y,v);
  pitch=PID_realize(atan2(after_y,s));

*/
Eigen::MatrixXd A(9,9);
A << 1, 0, 0, dt, 0,  0,  1/2*dt*dt,0,0,
     0, 1, 0, 0,  0, 0,  0,   0,  0,
     0, 0, 1, 0,  0,  dt, 0,  0,  1/2*dt*dt,
     0, 0, 0, 1,  0,  0,  dt, 0,  0,
     0, 0, 0, 0,  1,  0,  0,  dt, 0,
     0, 0, 0, 0,  0,  1,  0,  0,  dt,
     0, 0, 0, 0,  0,  0,  1,  0,  0,
     0, 0, 0, 0,  0,  0,  0,  1,  0,
     0, 0, 0, 0,  0,  0,  0,  0,  1;

Eigen::MatrixXd C(3,9);
C <<1, 0, 0, 0, 0, 0,0,0,0,
    0, 1, 0, 0, 0, 0,0,0,0,
    0, 0, 1, 0, 0, 0,0,0,0;

Eigen::MatrixXd P(9,9);
P <<     1, 0, 0, l, 0, 0, u, 0, 0,
	 0, 1, 0, 0, l, 0, 0, u, 0,
	 0, 0, 1, 0, 0, l, 0, 0, u,
	 l, 0, 0, 1, 0, 0, l, 0, 0,
	 0, l, 0, 0, 1, 0, 0, l, 0,
	 0, 0, l, 0, 0, 1, 0, 0, l,
	 u, 0, 0, l, 0, 0, 1, 0, 0,
	 0, u, 0, 0, l, 0, 0, 1, 0,
	 0, 0, u, 0, 0, l, 0, 0, 1;

Eigen::MatrixXd Q(9,9);
Q <<     0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, w, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, w, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, w;

Eigen::MatrixXd R(3,3);
R << 0, 0, 0,
     0, S, 0,
     0, 0, 0;

Eigen::VectorXd x(9);
x << 0, 0, 0, 0, 0, 0, 0, 0, 0;
  geometry_msgs::Point point;
  

 
  Eigen::MatrixXd y_meas(3,1);
  y_meas << abc->x/100,abc->y/100,abc->z/100;

  x = A * x;
  Eigen::MatrixXd A_T = A.transpose();

  P = A * P*A_T + Q;
	
  Eigen::MatrixXd temp1, temp2, Ct;
  
  Ct = C.transpose();
  temp1 = C * P * Ct + R;
  
  temp2 = temp1.inverse();

  Eigen::MatrixXd K = P * Ct*temp2;

  Eigen::VectorXd y = C * x;
  x = x + K * (y_meas - y);

  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(9,9);
  P = (I - K * C)*P;
  
 double after_x,after_y,after_z;
//after_x=x (0,0) + x(3, 0)*Dt;
//after_y=x (1,0) + x(4, 0)*Dt;
//after_z=x (2,0) + x(5, 0)*Dt;
after_x = x (0,0) + x(3, 0)*Dt + 1 / 2*x(6, 0)*Dt*Dt;
//after_y = x (1,0) + x(4, 0)*Dt + 1 / 2*x(7, 0)*Dt*Dt;
after_y = x (1,0);
after_z = x (2,0) + x(5, 0)*Dt + 1 / 2*x(8, 0)*Dt*Dt;
ROS_INFO("i heard point.x:%f\tpoint.y:%f\tpoint.z:%f\t",after_x,after_y,after_z);
ROS_INFO("i heard point.Vx:%f\tpoint.Vy:%f\tpoint.Vz:%f\t",x(3, 0),x(4, 0),x(5, 0));
ROS_INFO("i heard point.Vx:%f\tpoint.Vy:%f\tpoint.Vz:%f\t",x(6, 0),x(7, 0),x(8, 0));
  s=sqrt(pow(after_z,2)+pow(after_x,2));
  //yaw=180-atan2(after_x,after_z)*180/3.14;
  //pitch=180- GetPitch(s,after_y,v)*180/3.14;
   yaw=PID_realize(atan2(after_z,after_x));


	
  msg.yaw = is_nan(yaw);
  //pitch=GetPitch(s,after_y,v);
  pitch=PID_realize(atan2(after_y,s));
  msg.pitch=is_nan(pitch);
  cout<<is_nan(yaw)<<'\n'<<is_nan(pitch)<<endl;
  ros::NodeHandle n;
  ros::Publisher  pserial = n.advertise<sap::angle>("control", 1000);
        ros::Publisher pub_pitch = n.advertise<std_msgs::Float64>("/swivel/swivel/swiveljoint2_position_controller/command", 1);
	ros::Publisher pub_yaw = n.advertise<std_msgs::Float64>("/swivel/swivel/swiveljoint1_position_controller/command", 1);
  //pserial.publish(msg);
		pitch1.data=is_nan(pitch);
		yaw1.data=is_nan(yaw);
pub_pitch.publish(pitch1);
pub_yaw.publish(yaw1);
pserial.publish(msg);

}  



int main(int argc, char **argv)
{	
	
	ros::init(argc,argv,"sap");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	dynamic_reconfigure::Server<sap::guideConfig> server;
        dynamic_reconfigure::Server<sap::guideConfig>::CallbackType f;
	f = boost::bind(&callback, _1, _2);
	server.setCallback(f);
    while(ros::ok())
	{
		/*std_msgs::String msg1;
		std::stringstream ss1;
		msg1.data=ss1.str();
		std_msgs::String msg2;
		std::stringstream ss2;
		msg2.data=ss2.str(); */
		ros::Subscriber point3dsub = n.subscribe("point3d",100,chatterCallback1);
        ros::Publisher pub_pitch = n.advertise<std_msgs::Float64>("/swivel/swiveljoint2_position_controller/command", 1);
	ros::Publisher pub_yaw = n.advertise<std_msgs::Float64>("/swivel/swiveljoint1_position_controller/command", 1);
ros::Publisher  pserial = n.advertise<sap::angle>("control", 1000);
	    //ros::Subscriber sub2 = n.subscribe("**",100,chatterCallback2);
	    //ros::Subscriber sub3 = n.subscribe("**",100,chatterCallback3);
	    //ros::Subscriber sub2 = n.subscribe("**",100,chatterCallback2);
		//ros::Publisher  pserial = n.advertise<sap::angle>("control", 1000);
		//ros::Publisher  pub2 = n.advertise<std_msgs::String>("chatter2", 1000); 
		//ros::MultiThreadedSpinner spinner(2);
                //spinner.spin();
	    
		ros::spin();
		loop_rate.sleep();
	}
return 0;
}
