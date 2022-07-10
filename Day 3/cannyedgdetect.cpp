#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;
void gausblr(Mat *image, Mat *a)
{
	
	int i,j,k,l;
	double b=0;
	for(i=1;i<(*image).rows-1;i++){
	    for(j=1;j<(*image).cols-1;j++){
	    	b=0;
	    	for(k=-1;k<2;k++){
	    		for(l=-1;l<2;l++){
	    		    b=(b+((double)((*image).at<uchar>(i+k,j+l)))/pow(2,(2+k*k+l*l)));
	    		}
	    	}
            (*a).at<uchar>(i,j)= (unsigned int)b;
        }
    }
   
}	


int main()
{
	string str;
	cout<<"enter the path of image you want to input: "; 
	getline(cin,str);
	int i,j,k,l,uth=0,lth=0;
	double b=0;
	Mat image,c;
	image=imread(str,0);
	Mat a(image.rows,image.cols,CV_8UC1,Scalar(0));
	gausblr(&image, &a);
	namedWindow("window1",WINDOW_NORMAL);
	createTrackbar("lth","window1",&lth,600);
	createTrackbar("uth","window1",&uth,600);
	while(1){
		Canny(a, c, lth,uth,3 );
		imshow("window1",c);
		waitKey(1);
	}
}	