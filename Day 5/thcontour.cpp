#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
using namespace std;
using namespace cv;
RNG rng(12345);

int main(int , char **)
{
	int i,j,uth=0,lth=0,uthh, lths, lthv,lthh, uths, uthv;
VideoCapture cap(0);
if(!cap.isOpened())
	return -1;
    namedWindow("binary",WINDOW_NORMAL);
    namedWindow("hsv",WINDOW_NORMAL);
    namedWindow("blur",WINDOW_NORMAL);
    namedWindow("WebCam",WINDOW_NORMAL);
    namedWindow("canny",WINDOW_NORMAL);
    namedWindow("contour",WINDOW_NORMAL);
	createTrackbar("uthh","binary",&uthh,255);
	createTrackbar("lthh","binary",&lthh,255);
	createTrackbar("uths","binary",&uths,255);
	createTrackbar("lths","binary",&lths,255);
	createTrackbar("uthv","binary",&uthv,255);
	createTrackbar("lthv","binary",&lthv,255);
	createTrackbar("lth","canny",&lth,600);
	createTrackbar("uth","canny",&uth,600);
	while(1)
	{
		int i,j,uth=0,lth=0;
		Mat image,e;
		cap>>image;
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		Mat d(image.rows,image.cols,CV_8UC3,Scalar(0,0,0));
		Mat a(image.rows,image.cols,CV_8UC3,Scalar(0,0,0));
		Mat b(image.rows,image.cols,CV_8UC1,Scalar(0));
		Mat c(image.rows,image.cols,CV_8UC1,Scalar(0));
		GaussianBlur(image,d,Size(3,3),0,0);
		cvtColor(image, e, CV_BGR2HSV);
		imshow("WebCam",image);
		imshow("blur",d);
		imshow("hsv",e);
	        for(i=0;i<image.rows;i++){
	        	for(j=0;j<image.cols;j++){
	        		if((e.at<Vec3b>(i,j)[0]<=uthh)&&(e.at<Vec3b>(i,j)[1]>=lths)&&(e.at<Vec3b>(i,j)[2]>=lthv)&&(e.at<Vec3b>(i,j)[0]>=lthh)&&(e.at<Vec3b>(i,j)[1]<=uths)&&(e.at<Vec3b>(i,j)[2]<=uthv)){
	        			a.at<Vec3b>(i,j)[2]=255;
	        			a.at<Vec3b>(i,j)[1]=0;
	        			a.at<Vec3b>(i,j)[0]=0;
	        		}
	        		else{
	        			a.at<Vec3b>(i,j)[2]=0;
	        			a.at<Vec3b>(i,j)[1]=0;
	        			a.at<Vec3b>(i,j)[0]=0;
	        		}

	        	}
	        }
	    imshow("binary",a);
		Canny(a, b, lth,uth,3 );
		imshow("canny",b);
		findContours(b,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(c,contours,-1,color,2,8);
		imshow("contour",c);
		waitKey(1);
	}
}