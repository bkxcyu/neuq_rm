#include <ros/ros.h> 
#include<iostream>
#include"std_msgs/String.h"
#include<geometry_msgs/Point.h>
#include<position/square.h>
#include <opencv2/opencv.hpp>
#include "cv.h"
#include <pthread.h>
#include <unistd.h>
#include<vector>
#include<algorithm>
#include <cv_bridge/cv_bridge.h>
#include "math.h"
using namespace cv;
using namespace std;
    class SubscribeAndPublish  
    {  
    public:  
      SubscribeAndPublish()  
      {   
        point3dpub = n_.advertise<geometry_msgs::Point>("point3d", 1);  
        point2fsub = n_.subscribe("point2d", 1, &SubscribeAndPublish::callback, this); 
      }  
      
      void callback(const position::square::ConstPtr& msg)  
      {  
        position::square squared;
        vector<cv::Point3f> Points3D;
        Points3D.push_back(cv::Point3f(-3, 7.5, 0));        //P1 三维坐标的单位是毫米
        Points3D.push_back(cv::Point3f(3, 7.5, 0));      //P2
        Points3D.push_back(cv::Point3f(3, -7.5, 0));      //P3
        Points3D.push_back(cv::Point3f(-3, -7.5, 0));
        vector<cv::Point2f> Points2D;
        Point2f P[4];
        Point2f circle;
        P[1].x=msg->zs_x;
        P[1].y=msg->zs_y;
        P[2].x=msg->ys_x;
        P[2].y=msg->ys_y;
        P[3].x=msg->yx_x;
        P[3].y=msg->yx_y;
        P[4].x=msg->zx_x;
        P[4].y=msg->zx_y;
        //circle.x=msg->o_x;
        //circle.x=msg->o_y;
        Points2D.push_back(P[1]);        //P1 单位是像素
        Points2D.push_back(P[2]);        //P2
        Points2D.push_back(P[3]);        //P3
        Points2D.push_back(P[4]);        //P4

          cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64FC1);
          cv::Mat tvec = cv::Mat::zeros(3, 1, CV_64FC1);

              Mat camera_matrix;
              Mat distortion_coefficients;

              FileStorage fs("/home/dzw/1/src/position/out_camera_data.xml", FileStorage::READ);
              fs["camera_matrix"] >> camera_matrix;
              fs["distortion_coefficients"] >>  distortion_coefficients;

          solvePnP(Points3D, Points2D, camera_matrix, distortion_coefficients, rvec, tvec,false, CV_ITERATIVE); 

          cout <<"tvec: "<<tvec<<endl;

          double rm[9];
          cv::Mat rotM(3, 3, CV_64FC1, rm);
          Rodrigues(rvec, rotM);

         // cout <<"rotM: "<<rotM<<endl;

        //ROS_INFO("%f,%f", msg->zs_x,msg->yx_x);
        //double x[3];
       // x[3]=tvec;
        double *data;
        data = tvec.ptr<double>(0);
         //cout<<data[0]<<endl;
         //cout<<data[1]<<endl;
        // cout<<data[2]<<endl;

        geometry_msgs::Point point;
         point.x= data[0];
         point.y= data[1];
         point.z= data[2];
         point3dpub.publish(point); 
         ROS_INFO("i have send x%f y%f z%f", point.x,point.y,point.z);
      }  
    private:  
      ros::NodeHandle n_;   
      ros::Publisher point3dpub;  
      ros::Subscriber point2fsub;  
      
    };//End of class SubscribeAndPublish  
      
    int main(int argc, char **argv)  
    {   
      ros::init(argc, argv, "position"); 
      ros::NodeHandle n_;
      ros::Rate loop_rate(10);
 
     while(ros::ok())  
     {
      SubscribeAndPublish point3dpub;
      ros::spin();
      loop_rate.sleep();
   
     }
      return 0;  
    }  
