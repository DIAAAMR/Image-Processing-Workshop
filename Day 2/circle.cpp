#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;
int main()
{

	Mat a(1000,1000,CV_8UC1,Scalar(0));
	int i, j, k;
	i=j=0;
	for(i=0;i<=1000;i++){
		for(j=0;j<=1000;j++){
			k=sqrt(pow((i-500),2)+pow((j-500),2));
			if(k<=200){
				a.at<uchar>(i,j)=255;
			}

		}

	}
	namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",a);	
    waitKey(0);
}    