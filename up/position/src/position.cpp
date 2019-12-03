#include <ros/ros.h> 
#include<iostream>
#include"std_msgs/String.h"
#include<geometry_msgs/Point.h>
#include<aim/square.h>
#include <opencv2/opencv.hpp>
#include "cv.h"
#include <pthread.h>
#include <unistd.h>
using namespace cv;

    class SubscribeAndPublish  
    {  
    public:  
      SubscribeAndPublish()  
      {  
    
        pub9 = n_.advertise<geometry_msgs::Point>("chatter2", 1);  
   
        sub_ = n_.subscribe("chatter1", 1, &SubscribeAndPublish::callback, this); 
      }  
      
      void callback(const aim::square::ConstPtr& msg)  
      {  
        aim::square squared;
        

        Point2f P[4];
	Point2f circle;
  P[1].x=msg->zs_x;
	P[1].y=msg->zs_y;
	P[2].x=msg->zx_x;
	P[2].y=msg->zx_y;
	P[3].x=msg->ys_x;
	P[3].y=msg->ys_y;
	P[4].x=msg->yx_x;
	P[4].y=msg->yx_y;
	circle.x=msg->o_x;
	circle.x=msg->o_y;
        ROS_INFO("%f,%f", msg->zs_x,msg->yx_x);
        geometry_msgs::Point point;
         point.x=92.8;
         point.y=18.4;
         point.z=77.6;
         pub9.publish(point); 
         ROS_INFO("i have send x%f y%f z%f", point.x,point.y,point.z);
      }  
    private:  
      ros::NodeHandle n_;   
      ros::Publisher pub9;  
      ros::Subscriber sub_;  
      
    };//End of class SubscribeAndPublish  
      
    int main(int argc, char **argv)  
    {   
      ros::init(argc, argv, "test"); 
      ros::NodeHandle n_;
      ros::Rate loop_rate(10);
     while(ros::ok())  
     {
      SubscribeAndPublish test;
      ros::spin();
      loop_rate.sleep();
    
     }
      return 0;  
    }  
