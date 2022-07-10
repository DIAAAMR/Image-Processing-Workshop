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
	int i,j=0,k,l=0;
	unsigned int f[256];
	unsigned int s[256];
	unsigned int sf[256];
	Mat image;
	image=imread(str,0);
	namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",image);
	for(i=0;i<256;i++){
		f[i]=0;
	}	
	for(i=0;i<256;i++){
		sf[i]=0;
	}
	for(i=0;i<image.rows;i++){
	    for(j=0;j<image.cols;j++){
	    	k=image.at<uchar>(i,j);
	    	f[k]=f[k]+1;
	    	if(f[k]>l){
	    		l=f[k];
	    	}
	    }
	}
	Mat a(l,256,CV_8UC1,Scalar(255));
	for(j=0;j<256;j++){
	    for(i=0;i<l;i++){ 
	        if(f[j]>=i){ 
               a.at<uchar>(l-1-i,j)=0;
            }   
        }
    }
    namedWindow("window2",WINDOW_NORMAL);
    imshow("window2",a);
    for(i=0;i<256;i++){
    	j=j+f[i]*255;
    	k=j/(image.rows*image.cols);
    	s[i]=k;
    }
    Mat b(image.rows,image.cols,CV_8UC1,Scalar(255));
    for(i=0;i<image.rows;i++){
	    for(j=0;j<image.cols;j++){
	    	k=image.at<uchar>(i,j);
        	b.at<uchar>(i,j)=s[k];
        }
    }
    namedWindow("window3",WINDOW_NORMAL);
    imshow("window3",b); 
    l=0;
    for(i=0;i<256;i++){
    	k=s[i];
    	sf[k]=sf[k]+f[i];
    	if(f[k]>l){
	    	l=f[k];
	    }		
    }
    Mat c(l,256,CV_8UC1,Scalar(255));
	for(j=0;j<256;j++){
	    for(i=0;i<l;i++){ 
	        if(sf[j]>=i){ 
               c.at<uchar>(l-1-i,j)=0;
            }   
        }
    }
    namedWindow("window4",WINDOW_NORMAL);
    imshow("window4",c);
    waitKey(0);   	
}    

