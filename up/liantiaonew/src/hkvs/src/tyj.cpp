
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
#include <hkvs/vel.h>

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
cv::Point left_top;
cv::Point left_bottom;
cv::Point right_top;
cv::Point right_bottom;

cv::Point pt1;
cv::Point pt2;
cv::Point pt3;
cv::Point pt4;

cv::Point pt5;
cv::Point pt6;
cv::Point pt7;
cv::Point pt8;

cv_bridge::CvImagePtr cv_ptr;



class ImageConverter
{
private:
    hkvs::square squared;
    hkvs::vel vel_linear;
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    //image_transport::Subscriber sub = it.subscribe( "/rrbot/camera1/image_raw", 1, imageCalllback );
    ros::Publisher squarepub = nh_.advertise<hkvs::square>("point2d", 1);
    ros::Publisher velpub = nh_.advertise<hkvs::vel>("vel_linear", 1);
public:

    cv::RotatedRect& adjustRec(cv::RotatedRect& rec);
    int judgeAngle(cv::RotatedRect& rec,cv::RotatedRect& rec1);
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
    void image_process(cv::Mat frame){
        imshow("original",frame);
        vector<RotatedRect> contours_minRects;//所有轮廓的最小外接矩形
        vector<Rect> contoursRects;//所有轮廓的外接矩形
        vector<vector<Point> > contours;//所有灯轮廓
        clock_t start,finish;
        double totaltime;
        start = clock();
        int hi = 0;
        int mode=0;//0 red 1 blue
        Mat image,binary,binary1;
        int stateNum = 4;
        int measureNum = 2;
        frame.copyTo(binary1);
        KalmanFilter KF(stateNum, measureNum, 0);
        //Mat processNoise(stateNum, 1, CV_32F);
        Mat measurement = Mat::zeros(measureNum, 1, CV_32F);
        KF.transitionMatrix = (Mat_<float>(stateNum, stateNum) << 1, 0, 1, 0,//A 状态转移矩阵
            0, 1, 0, 1,
            0, 0, 1, 0,
            0, 0, 0, 1);
        //这里没有设置控制矩阵B，默认为零
        setIdentity(KF.measurementMatrix);//H=[1,0,0,0;0,1,0,0] 测量矩阵
        setIdentity(KF.processNoiseCov, Scalar::all(1e-5));//Q高斯白噪声，单位阵
        setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));//R高斯白噪声，单位阵
        setIdentity(KF.errorCovPost, Scalar::all(1));//P后验误差估计协方差矩阵，初始化为单位阵
        randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));//初始化状态为随机值

        Mat thres_whole;//,inputafter;
        vector<Mat> splited;

        split(frame, splited);
        cvtColor(frame, thres_whole, CV_BGR2GRAY);

        threshold(thres_whole, thres_whole, 50, 255, THRESH_BINARY);
        //imshow("a",thres_whole);
        if(mode == 0){
            subtract(splited[2], splited[0], binary);
            threshold(binary, binary, 100, 255, THRESH_BINARY);// red
        }
        else if(mode == 1){
            subtract(splited[0], splited[2],binary);
            threshold(binary,binary,160,255,THRESH_BINARY);//blue
        }
            
        imshow("pre",binary);
        findContours(binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

            //cout << "coutours size:" << contours.size() << endl;
        Mat dst = frame.clone();
        double MaxValue=0;

        for (size_t i = 0; i < contours.size(); i++){

            float point_x;
            float x_bias;
            float x_k=0.04;//电机初始线速度k值
            float linear_old;
            int linear_x;

            if (contours[i].size() < 5) break;
                
            vector<Point> points;
            double area = contourArea(contours[i]);
            //cout<<"area= "<<area<<endl;
            //cout<<"area0= "<<area<<endl;
            if (area <300 || 200000 < area) continue;
                //cout<<"area0= "<<area<<endl;
            drawContours(frame, contours, static_cast<int>(i), Scalar(0), 2);  
            points = contours[i];
            RotatedRect rrect = fitEllipse(points);
            cv::Point2f* vertices = new cv::Point2f[4];
            rrect.points(vertices);

            //float aim = rrect.size.height/rrect.size.width;

            //if(aim > 1.8&& aim < 2.6){
            // cout<<"aim="<<aim<<endl;
            for (int j = 0; j < 4; j++){
                 cv::line(binary1, vertices[j], vertices[(j + 1) % 4], cv::Scalar(0, 255, 0),4);
            }

            

            for(size_t j = 1;j < contours.size();j++){

                vector<Point> pointsA;
                double area = contourArea(contours[j]);
                //cout<<"area1= "<<area<<endl;
                if (area < 300 || 200000 < area) continue;
                //cout<<"area1= "<<area<<endl;
                pointsA = contours[j];

                RotatedRect rrectA = fitEllipse(pointsA);
		Point2f verticesA[4];      //定义矩形的4个顶点
		rrectA.points(verticesA);   //计算矩形的4个顶点
                
                float aimA = rrectA.size.height/rrectA.size.width;
                //if(aimA > 2.0)continue;
                //if(aimA > 3.0){
                //cout<<"aimA="<<aimA<<endl;

                //cout<<"center="<<rrect.center.x<<" "<<rrect.center.y<<endl;
                //cout<<"centeA="<<rrectA.center.x<<" "<<rrectA.center.y<<endl;
                float distance = sqrt((rrect.center.x-rrectA.center.x)*(rrect.center.x-rrectA.center.x)+
                                              (rrect.center.y-rrectA.center.y)*(rrect.center.y-rrectA.center.y));

                    //if (middle > distance  )
                          //  middle = distance;
                        //}*/
                   // }
                        //cout<<"distance="<<distance<<endl;
                if (distance!=0){
                    //if( middle > 10){      //这个距离也要根据实际情况调


                    //cv::circle(binary1,Point((rrect.center.x+rrectA.center.x)/2,(rrect.center.y+rrectA.center.y)/2),15,cv::Scalar(0,0,255),4);
                    Mat prediction = KF.predict();
                    Point predict_pt = Point((int)prediction.at<float>(0), (int)prediction.at<float>(1));
                    measurement.at<float>(0) = (float)rrect.center.x;
                    measurement.at<float>(1) = (float)rrect.center.y;
                    KF.correct(measurement);
		    
		    pt1=vertices[0];
		    pt2=vertices[1];
		    pt3=vertices[2];
		    pt4=vertices[3];

		    pt5=verticesA[0];
		    pt6=verticesA[1];
		    pt7=verticesA[2];
		    pt8=verticesA[3];
		    adjustRec(rrect);
		    adjustRec(rrectA);
		    int judge=judgeAngle(rrect,rrectA);
     		    if(judge==1){
			left_bottom=pt5;
	    	    	left_top=pt6;
		    	right_top = pt3;
		    	right_bottom=pt4;				
		    }
		    else if(judge==2){
			left_bottom=pt5;
	    	    	left_top=pt6;
		    	right_top = pt1;
		    	right_bottom=pt2;				
		    }
		    else if(judge==3){
			left_bottom=pt7;
	    	    	left_top=pt8;
		    	right_top = pt3;
		    	right_bottom=pt4;				
		    }
		    else if(judge==4){
			left_bottom=pt7;
	    	    	left_top=pt8;
		    	right_top = pt1;
		    	right_bottom=pt2;				
		    }

		    
                    int a1 = rrect.center.x-0.5*rrect.size.width;
                    int a2 = rrect.center.y-0.5*rrect.size.height;
                    int b1 = rrectA.center.x+0.5*rrectA.size.width;
                    int b2 = a2;
                    int c1 = a1;
                    int c2 = rrect.center.y+0.5*rrect.size.height;
                    int d1 = b1;
                    int d2 = c2;  
                  
		    line(binary1,left_bottom,left_top,Scalar(0,255,255),1);
		    line(binary1,left_top,right_top,Scalar(0,255,255),1);
		    line(binary1,right_top,right_bottom,Scalar(0,255,255),1);
		    line(binary1,right_bottom,left_bottom,Scalar(0,255,255),1);


                    int point_x=(rrect.center.x+rrectA.center.x)/2;                 
                    //cout<<"point_x="<<point_x<<endl;
                    x_bias=720-point_x;
                    //cout<<"x_bias="<<x_bias<<endl;
                    linear_old=x_bias*x_k;
                    //cout<<"linear_x_old="<<linear_old<<endl;   

                    if(linear_old>60){
                        linear_old=60;
                    }
                    else if(linear_old<-60){
                        linear_old=-60;
                    }
                    linear_x=linear_old*10000;
                    vel_linear.vel = -linear_x; 

                    velpub.publish(vel_linear);
                    //cout<<"linear_0="<<linear_x<<endl;
                    //Rect r(a1,a2,b1-a1,c2-a2); 
                    //cout<<"size="<<(b1-a1)*(c2-a2)<<endl;
                    //rectangle(binary1, r, Scalar(0, 255, 255), 3);
                    //circle(binary1, predict_pt, 3, Scalar(34, 255, 255), -1);

                    //squared.zs_x=a1;squared.zs_y=1080-a2;cout<<"zuoshang"<<squared.zs_x<<".."<<squared.zs_y<<endl;

                    //squared.ys_x=b1;squared.ys_y=1080-b2;cout<<"youshang"<<squared.ys_x<<".."<<squared.ys_y<<endl;

                    //squared.zx_x=c1;squared.zx_y=1080-c2;cout<<"youshang"<<squared.zx_x<<".."<<squared.zx_y<<endl;

                    //squared.yx_x=d1;squared.yx_y=1080-d2;cout<<"youxia"<<squared.yx_x<<".."<<squared.yx_y<<endl;
                    squared.square_num=1;
                    squarepub.publish(squared);

                    rrect.center.x = (int)prediction.at<float>(0);
                    rrect.center.y = (int)prediction.at<float>(1);


                    }
                       /*else{
                            x_bias=1;
                            linear_x=x_bias*x_k;
                             vel_linear.vel = linear_x;
                             cout<<"linear_1="<<linear_x<<endl;
                            velpub.publish(vel_linear);
                        }*/
                }
            //}
            imshow("frame",binary1); 
            waitKey(1);
            	    delete[]vertices;
            finish = clock();
            totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
            //cout<<"Time whole"<<totaltime<<"秒"<<endl;

        
    }
    }
};

RotatedRect& ImageConverter::adjustRec(cv::RotatedRect& rec)
{
	using std::swap;

	float& width = rec.size.width;
	float& height = rec.size.height;
	float& angle = rec.angle;


	while (angle >= 90.0) angle -= 180.0;
	while (angle < -90.0) angle += 180.0;

	
	
		if (angle >= 45.0)
		{
			swap(width, height);
			angle -= 90.0;
		}
		else if (angle < -45.0)
		{
			swap(width, height);
			angle += 90.0;
		}
	

	return rec;
}

int ImageConverter::judgeAngle(cv::RotatedRect& rec,cv::RotatedRect& rec1){
	float& angle = rec.angle;
	float& angle1 = rec1.angle;
	if (angle>0 && angle1>0) return 1;
	else if(angle>0 && angle1<0)return 2;
	else if(angle<0 && angle1>0)return 3;
	else return 4;

}
 


int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_listener");
    ImageConverter ic;
    ros::spin();
    return 0;
}
