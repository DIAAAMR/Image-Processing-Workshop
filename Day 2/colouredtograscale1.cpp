#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	string str;
	cout<<"enter the path of image you want to input: "; 
	getline(cin,str);
	int i,j;
	Mat image;
	image=imread(str,CV_LOAD_IMAGE_COLOR);
	Mat a(image.rows,image.cols,CV_8UC1,Scalar(0));
	for(i=0;i<=image.rows;i++){
	    for(j=0;j<=image.cols;j++){
				a.at<uchar>(i,j)=(unsigned int)(((int)image.at<Vec3b>(i,j)[0]+ (int)image.at<Vec3b>(i,j)[1]+ (int)image.at<Vec3b>(i,j)[2])/3);

        }
    }     
       namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",image);
	namedWindow("window2",WINDOW_NORMAL);
	imshow("window2",a);	
    waitKey(0);
}    