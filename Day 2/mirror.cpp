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
	unsigned int b,g,r;
	Mat image;
	image=imread(str,CV_LOAD_IMAGE_COLOR);
	for(i=0;i<=image.rows;i++){
	    for(j=0;j<=(image.cols)/2;j++){
				b=image.at<Vec3b>(i,j)[0];
				g=image.at<Vec3b>(i,j)[1];
				r=image.at<Vec3b>(i,j)[2];
				image.at<Vec3b>(i,j)[0]=image.at<Vec3b>(i,((image.cols)-j))[0];
				image.at<Vec3b>(i,j)[1]=image.at<Vec3b>(i,((image.cols)-j))[1];
				image.at<Vec3b>(i,j)[2]=image.at<Vec3b>(i,((image.cols)-j))[2];
				image.at<Vec3b>(i,((image.cols)-j))[0]=b;
				image.at<Vec3b>(i,((image.cols)-j))[1]=g;
				image.at<Vec3b>(i,((image.cols)-j))[2]=r;


        }
    }     
       namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",image);
    waitKey(0);
}    