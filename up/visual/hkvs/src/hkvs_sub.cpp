#include <ros/ros.h>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.h>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <hkvs/square.h>
using namespace cv;

#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;

cv_bridge::CvImagePtr cv_ptr;
int frame_number=0;
cv::Mat img;

class ImageConverter
{
private:
    ros::NodeHandle nh_;
    //用于将msg信息转换为openCV中的Mat数据
    image_transport::ImageTransport it_;
    //订阅摄像头发布的信息
    image_transport::Subscriber image_sub_;
    hkvs::square squared;
    ros::Publisher squarepub = nh_.advertise<hkvs::square>("point2d", 1000);
public:
    ImageConverter()
    : it_(nh_)
    {
        //设置订阅摄像机

        image_sub_ = it_.subscribe("/camera/image_raw", 1, &ImageConverter::imageCb, this);
    }

    ~ImageConverter(){
    }

    //收到摄像机后的回调函数
    void imageCb(const sensor_msgs::ImageConstPtr& msg){
        try{
            //将收到的消息使用cv_bridge转移到全局变量图像指针cv_ptr中，其成员变量image就是Mat型的图片
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }

        catch (cv_bridge::Exception& e){
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        //处理图片信息
        img=cv_ptr->image;
        image_process(img); //得到了cv::Mat类型的图象，在CvImage指针的image中，将结果传送给处理函数   
    }
    /*
       这是图象处理的主要函数，一般会把图像处理的主要程序写在这个函数中。这里的例子只是一个彩色图象到灰度图象的转化
    */
    void image_process(cv::Mat img) 
    {
       cv::Mat img_out;
       Mat binBrightImg;
       Mat image;
                    //Mat dstImage = Mat::zeros(src.rows, src.cols, CV_8UC3);
                    cvtColor(img,image,COLOR_BGR2GRAY,1);
                    cv::threshold(image, binBrightImg, 210, 255, cv::THRESH_BINARY);
                    cv::Mat element = cv::getStructuringElement(2, cv::Size(3, 3));
                    dilate(binBrightImg, binBrightImg, element);
                    cv::imshow("b",binBrightImg);

     vector<vector<Point> > contours;
                   vector<Vec4i> hierarchy;
	               findContours(binBrightImg,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE,Point());

	               Mat imageContours=Mat::zeros(binBrightImg.size(),CV_8UC1);	//最小外接矩形画布

	               for(int i=0;i<contours.size();i++)
	                {		
		            //绘制轮廓
		                drawContours(imageContours,contours,i,Scalar(255),1,8,hierarchy);



		            //绘制轮廓的最小外结矩形
		                RotatedRect rect=minAreaRect(contours[i]);
		                Point2f P[4];
		                rect.points(P);
		                for(int j=0;j<=3;j++)
		                    {
			                    line(imageContours,P[j],P[(j+1)%4],Scalar(255),2);
                                cout<< "rect_center" << j << P[j] << endl;
                                if(j=0){squared.zs_x=P[j].x;squared.zs_y=P[j].y;}
                                if(j=1){squared.ys_x=P[j].x;squared.ys_y=P[j].y;}
                                if(j=2){squared.yx_x=P[j].x;squared.yx_y=P[j].y;}
                                if(j=3){squared.zx_x=P[j].x;squared.zx_y=P[j].y;}
		                    }
                                      cout<<"ffffffffffffffffffffffffffffffff"<<endl;
                                               squarepub.publish(squared);

                    }
	                cv::imshow("MinAreaRect",img);	
	
       //cv::cvtColor(img, img_out, CV_RGB2GRAY);  //转换成灰度图象



       /*if(frame_number<=40) frame_number++;
       else frame_number=0;
       string Img_Name = "../rosimage/image"+to_string(frame_number)+".jpg";
       imwrite(Img_Name,img);
       cv::imshow("INPUT", img);*/
       //cv::imshow("OUTPUT", img_out);
       cv::waitKey(5);
    }
};

int main(int argc, char** argv)
{

    ros::init(argc, argv, "image_converter");


    ImageConverter ic;
    //循环等待
    ros::spin();
    return 0;
}
