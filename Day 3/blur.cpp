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

void meanblr(Mat *image, Mat *a)
{
	
	int i,j,k,l;
	double b=0;
	for(i=1;i<(*image).rows-1;i++){
	    for(j=1;j<(*image).cols-1;j++){
	    	b=0;
	    	for(k=-1;k<2;k++){
	    		for(l=-1;l<2;l++){
	    		    b=(b+((double)((*image).at<uchar>(i+k,j+l)))/9);
	    		}
	    	}
            (*a).at<uchar>(i,j)= (unsigned int)b;
        }
    }
   
}

void medblr(Mat *image, Mat *a)
{
	
	int b, c, i,j,k,l;
	int m[9];
	for(i=1;i<(*image).rows-1;i++){
	    for(j=1;j<(*image).cols-1;j++){
	    	for(k=-1;k<2;k++){
	    		for(l=-1;l<2;l++){
	    			if(k-l==0){
	    		    	m[4+2*k+2*l]=(*image).at<uchar>(i+k,j+l);	
	    		    }	
	    		    else {
	    		    	m[4+3*k+l]=(*image).at<uchar>(i+k,j+l);
	    		    }
	    		}
	    	}
	    	for(k=8;k>0;k--){
				b=0;
				for(l=0;l<=k;l++){
		            if(m[l]>m[b]){
		            	b=l;
		            }
				}
				l--;
				c=m[l];
		        m[l]=m[b];
		        m[b]=c;
			}
            (*a).at<uchar>(i,j)= m[4];
            for(b=0;b<9;b++){
            	m[b]=0;
            }
        }
    }
   
}	

int main()
{
	char c;
	string str;
	cout<<"enter the path of image you want to input: "; 
	getline(cin,str);
	cout<<"enter m for meanblur, n for median blur or g for gaussian blur: "; 
	cin>>c;
	int i,j,k,l,uth=0,lth=0;
	Mat image;
	image=imread(str,0);
	namedWindow("window1",WINDOW_NORMAL);
    imshow("window1",image);
	Mat a(image.rows,image.cols,CV_8UC1,Scalar(0));
	if(c=='g')
		gausblr(&image,&a);
	else if(c=='m')
		meanblr(&image,&a);
	else if(c=='n')
		medblr(&image,&a);
	namedWindow("window2",WINDOW_NORMAL);
    imshow("window2",a);
    waitKey(0);
}    