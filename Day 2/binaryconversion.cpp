#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	string str;
	int i,j,th=0;
	cout<<"enter the path of image you want to input: "; 
	getline(cin,str);
	Mat image;
	image=imread(str,0);
	namedWindow("window2",WINDOW_NORMAL);
        imshow("window2",image);
	namedWindow("window1",WINDOW_NORMAL);
	createTrackbar("th","window1",&th,255);
	while(1){
		Mat a(image.rows,image.cols,CV_8UC1,Scalar(0));
        for(i=0;i<image.rows;i++){
        	for(j=0;j<image.cols;j++){
        		if(image.at<uchar>(i,j)>th){
        			a.at<uchar>(i,j)=255;
        		}

        	}
        }
        imshow("window1",a);
        waitKey(1);
	}
}	