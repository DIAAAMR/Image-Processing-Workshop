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
	int i,j,k,r,rmax;
	const double pi=3.14;
	Mat image;
	image=imread(str,0);
	namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",image);
	rmax=sqrt(image.rows*image.rows+image.cols*image.cols);
	Mat a(rmax,360,CV_8UC1,Scalar(0));
	for(i=0;i<image.rows;i++){
		for(j=0;j<image.cols;j++){
			if(image.at<uchar>(i,j)==255){
				for(k=0;k<361;k++){
	            	r=j*cos((double)k*pi/180)+i*sin((double)k*pi/180);
	            	r=sqrt(pow(r,2));
	            	if(a.at<uchar>((r),k)<256)
	            	a.at<uchar>(r,k)=a.at<uchar>(r,k)+2;
	            }
            }
        }      
	}
	namedWindow("window2",WINDOW_NORMAL);
	imshow("window2",a);
	k=0;
	for(i=0;i<rmax;i++){
		for(j=0;j<361;j++){
			if(a.at<uchar>(i,j)>200)
				k++;
        }
    }
        cout<<k<<endl;

	waitKey(0);
}