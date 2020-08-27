#include <time.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>
#include<memory>
#include <opencv2/ml/ml.hpp>
#include<iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml.hpp>
#include<ros/ros.h>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.h>
#include<image_transport/image_transport.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include <hkvs/square.h>
//#include "ArmorDetector.h"
#include <cmath>

using namespace std;
using namespace cv;

ostringstream oss;
int num = 0;
Mat dealimage;
Mat src;
int k = 0;
Mat yangben_gray;
Mat yangben_thresh;
cv::Mat frame;

cv_bridge::CvImagePtr cv_ptr;
class ImageConverter
{
private:
    hkvs::square squared;
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    //image_transport::Subscriber sub = it.subscribe( "/rrbot/camera1/image_raw", 1, imageCalllback );
    ros::Publisher squarepub = nh_.advertise<hkvs::square>("point2d", 1);
public:
    ImageConverter()
    : it_(nh_)
    {
        //设置订阅摄像机

        image_sub_ = it_.subscribe("camera/image_raw", 1, &ImageConverter::imageCalllback, this);
    }

    ~ImageConverter(){
    }
    void imageCalllback(const sensor_msgs::ImageConstPtr& msg)
    {
            //ROS_INFO("Received \n");
            try{
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            //cv::imshow( "video", cv_bridge::toCvShare(msg, "bgr8")->image );
        }
        catch( cv_bridge::Exception& e )
        {
            ROS_ERROR( "Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str() );
            return;
        }
        frame=cv_ptr->image;
        image_process(frame);
    }
    void image_process(cv::Mat frame)
{
                Mat HSVImg;
                double MaxValue=0;
                imshow("frame",frame);
                Mat binary;
                Mat dst; // 二值化后的image
                vector<RotatedRect> vContour; // 发现的旋转矩形
                vector<Mat> channels;
                frame.copyTo(binary);
                Mat dst_BR = Mat::zeros(frame.size(), frame.type());
                Mat BrightnessLut(1, 256, CV_8UC1);
                for (int i = 0; i < 256; i++) {
                        BrightnessLut.at<uchar>(i) = saturate_cast<uchar>(i -100);//100为减低图像亮度，需调
                }
                LUT(frame, BrightnessLut, dst_BR);

                imshow("lower_bright", dst_BR);

                          /* cvtColor(dst_BR,HSVImg,COLOR_BGR2HSV);
                           split(HSVImg, channels);
                           minMaxLoc(channels[2], 0, &MaxValue, 0, 0);
                           cout << "单通道图像最大值： " << MaxValue << endl;
                           threshold(channels[2], channels[2], MaxValue*0.98, 255, THRESH_BINARY);
                           Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
                           medianBlur(channels[2], channels[2], 3);
                           morphologyEx(channels[2], channels[2], MORPH_DILATE, element, Point(-1, -1), 1);
                           imshow("V", channels[2]);*/

                           /* vector< vector<Point> > contours;
                            //imshow("pre_treatment",image);
                            findContours(channels[2].clone(), contours, RETR_LIST, CHAIN_APPROX_NONE);
                            Mat drawingImg = Mat::zeros(frame.size(), CV_8UC3);

                            for (int i = 0; i < contours.size(); i++) {
                                for (int j = i + 1; j < contours.size(); j++) {

                                    //判断是否为相同灯条
                                    float Contour_angle = abs(vContour[i].angle - vContour[j].angle); //角度
                                    if (Contour_angle >= _Armor.Light_Contour_angle)
                                        continue;
                                    //长度差比率
                                    float Contour_Len1 = abs(vContour[i].size.height - vContour[j].size.height) / max(vContour[i].size.height, vContour[j].size.height);
                                    //宽度差比率
                                    float Contour_Len2 = abs(vContour[i].size.width - vContour[j].size.width) / max(vContour[i].size.width, vContour[j].size.width);
                                    if (Contour_Len1 > _Armor.Light_Contour_Len || Contour_Len2 > _Armor.Light_Contour_Len)
                                        continue;
                                    //装甲板匹配
                                    RotatedRect Rect;
                                    Rect.center.x = (vContour[i].center.x + vContour[j].center.x) / 2.; //x坐标
                                    Rect.center.y = (vContour[i].center.y + vContour[j].center.y) / 2.; //y坐标
                                    Rect.angle = (vContour[i].angle + vContour[j].angle) / 2.; //角度
                                    float nh, nw, yDiff, xDiff;
                                    nh = (vContour[i].size.height + vContour[j].size.height) / 2; //高度
                                    // 宽度
                                    nw = sqrt((vContour[i].center.x - vContour[j].center.x) * (vContour[i].center.x - vContour[j].center.x) + (vContour[i].center.y - vContour[j].center.y) * (vContour[i].center.y - vContour[j].center.y));
                                    float ratio = nw / nh; // 匹配到的装甲板的长宽比
                                    xDiff = abs(vContour[i].center.x - vContour[j].center.x) / nh; //x差比率
                                    yDiff = abs(vContour[i].center.y - vContour[j].center.y) / nh; //y差比率
                                    Rect.size.height = nh;
                                    Rect.size.width = nw;

                                }
                            }*/



        
    }

};
int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_listener");
    ImageConverter ic;
    ros::spin();
    return 0;
}
