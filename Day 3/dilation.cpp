//runs
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;
int main()
{
	string str;
	cout<<"enter the path of image you want to input: "; 
	getline(cin,str);
	int i,j,k,l;
	double b=1;
	Mat image;
	image=imread(str,0);
	Mat a(image.rows,image.cols,CV_8UC1,Scalar(0));
	namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",image);
	for(i=1;i<image.rows;i++){
	    for(j=1;j<=image.cols;j++){
	    	b=0;
	    	for(k=-1;k<2;k++){
	    		for(l=-1;l<2;l++){
	    		    if(image.at<uchar>(i+k,j+l)==255){
                       a.at<uchar>(i,j)=255;
	    		    }
	    		}
	    	
            }
        }
    }
    namedWindow("window2",WINDOW_NORMAL);
	imshow("window2",a);
	waitKey(0);
}	