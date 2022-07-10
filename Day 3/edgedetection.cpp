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
	int i,j,k,l,th=600,sx=0,sy=0;
	Mat image;
	image=imread(str,0);
	
	namedWindow("window1",WINDOW_NORMAL);
	createTrackbar("th","window1",&th,600);
	while(1){

		Mat a(image.rows,image.cols,CV_8UC1,Scalar(0));
	    for(i=1;i<image.rows-1;i++){
	        for(j=1;j<image.cols-1;j++){
	        	sx=sy=0;
	    	    for(k=-1;k<2;k++){
	    		    for(l=-1;l<2;l++){
	    			    
	    		        if(k==0){
	    		    	    sx= sx+2*l*(int)image.at<uchar>(i+k,j+l);
	    		        }
	    		        else{
                            sx= sx+l*(int)image.at<uchar>(i+k,j+l);
	    		        }
	    		        if(l==0){
	    		        	sy= sy+2*l*(int)image.at<uchar>(i+k,j+l);
	    		        }
	    		        else{
                            sy= sy+l*(int)image.at<uchar>(i+k,j+l);
	    		        }
	    		    }
	    	    }
	    	    if(sqrt(sx*sx+sy*sy)>th){
        	        a.at<uchar>(i,j)=255;
                }
            }
        }
	    imshow("window1",a);
	    waitKey(1);
    }
}    	
