#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;
int main()
{

	Mat a(7,7,CV_8UC1,Scalar(0));
	int i, j, k;
	i=j=1;
	for(i=0;i<=7;i++){
		for(j=0;j<=7;j++){
			if((i+j)%2==0){
				a.at<uchar>(i,j)=255;
			}
		}	
	}
	namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",a);	
    waitKey(0);
   } 	