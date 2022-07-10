#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;

void medblr(Mat *image, Mat *a)
{
	
	int b, c, d,e, i,j,k,l;
	int r[9];
	int g[9];
	int s[9];
	for(i=1;i<(*image).rows-1;i++){
	    for(j=1;j<(*image).cols-1;j++){
	    	if(((*a).at<Vec3b>(i,j)[0]==255)&&((*a).at<Vec3b>(i,j)[1]==255)&&((*a).at<Vec3b>(i,j)[2]==255)){
		    	for(k=-1;k<2;k++){
		    		for(l=-1;l<2;l++){	
		    			if(k*k+l*l!=0){	    			
			    		    s[4+3*k+l]=(*image).at<Vec3b>(i+k,j+l)[0];
			    		    g[4+3*k+l]=(*image).at<Vec3b>(i+k,j+l)[1];
			    		    r[4+3*k+l]=(*image).at<Vec3b>(i+k,j+l)[2];	
			    		}
			    		else{
			    			s[4+3*k+l]=0;
			    			s[4+3*k+l]=0;
			    			s[4+3*k+l]=0;
			    		}    	    		    
		    		}
		    	}
		    	for(k=8;k>0;k--){
					b=0;
					c=0;
					d=0;
					for(l=0;l<=k;l++){
			            if(s[l]>s[b]){
			            	b=l;
			            }
			            if(g[l]>g[c]){
			            	c=l;
			            }
			            if(r[l]>r[d]){
			            	d=l;
			            }
					}
					l--;
					e=s[l];
			        s[l]=s[b];
			        s[b]=e;
			        e=g[l];
			        g[l]=g[c];
			        g[c]=e;
			        e=r[l];
			        r[l]=r[d];
			        r[d]=e;
				}
	            (*a).at<Vec3b>(i,j)[0]= s[4]+s;
	            (*a).at<Vec3b>(i,j)[1]= g[4];
	            (*a).at<Vec3b>(i,j)[2]= r[4];
	            for(b=0;b<9;b++){
	            	s[b]=0;
	            	g[b]=0;
	            	r[b]=0;
	            }	
            }
        }
    }
   
}	

int main(){
	int i,j,x,y;
	double t;
	string str;
	cout<<"enter the path of image you want to rotate: "; 
	getline(cin,str);
	cout<<"enter the angle (in theta) by which you want to rotate image in anti-clockwise direction: ";
	cin>>t;
	t=t*3.14/180;
	Mat image;
	image=imread(str,CV_LOAD_IMAGE_COLOR);
	Mat rotate(2*image.rows,2*image.cols,CV_8UC3,Scalar(255,255,255));
	Mat a(2*image.rows,2*image.cols,CV_8UC3,Scalar(255,255,255));
	for(i=0;i<image.rows;i++){
		for(j=0;j<image.cols;j++){
			x=image.cols - ((image.cols)/2-j)*cos(t)-((image.rows)/2-i)*sin(t);
			y=image.rows - ((image.rows)/2-i)*cos(t)+((image.cols)/2-j)*sin(t);
			rotate.at<Vec3b>(y,x)[0]=image.at<Vec3b>(i,j)[0];
			rotate.at<Vec3b>(y,x)[1]=image.at<Vec3b>(i,j)[1];
			rotate.at<Vec3b>(y,x)[2]=image.at<Vec3b>(i,j)[2];
		}
	}
    medblr(&rotate,&a);
	namedWindow("window1",WINDOW_NORMAL);
	namedWindow("window2",WINDOW_NORMAL);
	imshow("window1",image);
	imshow("window2",a);
	namedWindow("window3",WINDOW_NORMAL);
	imshow("window3",rotate);
	waitKey(0);		
}