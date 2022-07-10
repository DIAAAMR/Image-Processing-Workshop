#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;

void meanblr(Mat *image, Mat *a, int p, int q, int r, int s)
{
	
	int i,j,k,l;
	double b,c,d;
	for(i=1;i<(*image).rows-1;i++){
	    for(j=1;j<(*image).cols-1;j++){
	    	b=0;
	    	c=0;
	    	d=0;
	    	if(((i>=p)&&(i<=p+r))&&((j>=q)&&(j<=q+s))){
	    		(*a).at<Vec3b>(i,j)[0]=(*image).at<Vec3b>(i,j)[0];
		    	(*a).at<Vec3b>(i,j)[1]=(*image).at<Vec3b>(i,j)[1];
		    	(*a).at<Vec3b>(i,j)[2]=(*image).at<Vec3b>(i,j)[2];
	        } 
	        else{
	        	for(k=-1;k<2;k++){
		    		for(l=-1;l<2;l++){
		    		    b=(b+((double)((*image).at<Vec3b>(i+k,j+l)[0]))/9);
		    		    c=(c+((double)((*image).at<Vec3b>(i+k,j+l)[1]))/9);
		    		    d=(d+((double)((*image).at<Vec3b>(i+k,j+l)[2]))/9);
		    		}
		    	}
	            (*a).at<Vec3b>(i,j)[0]= (unsigned int)b;
	            (*a).at<Vec3b>(i,j)[1]= (unsigned int)c;
	            (*a).at<Vec3b>(i,j)[2]= (unsigned int)d;
	        }   
        }
    }
   
}

int main()
{
	int i,j,k,l,q,r,s,t;
	int d=0,th=0;
	char c;
	string str, tem;
	cout<<"enter the path of image you want to check: "; 
	getline(cin,str);
	Mat image,temp;
	image=imread(str,CV_LOAD_IMAGE_COLOR);
	Mat a(image.rows,image.cols,CV_8UC3,Scalar(0,0,0));
	cout<<"if you want to extract out portion of image to match it enter type S, if want to enter your own template enter T : "; 
	cin>> c;
	if(c=='S'){
	    cout<<"enter the coordinates between which you want to extract template x1 y1 x2 y2 : ";
		cin >> q >> r >> s >> t;
		Mat temp(t-r+1,s-q+1,CV_8UC3,Scalar(0,0,0));
		for(i=r;i<=t;i++){
			for(j=q;j<=s;j++){
				temp.at<Vec3b>(i-r,j-q)[0]=image.at<Vec3b>(i,j)[0];
				temp.at<Vec3b>(i-r,j-q)[1]=image.at<Vec3b>(i,j)[1];
				temp.at<Vec3b>(i-r,j-q)[2]=image.at<Vec3b>(i,j)[2];				
			}
		}
		for(i=0;i<image.rows;i++){
			for(j=0;j<image.cols;j++){
				d=0;
				for(k=0;k<t-r+1;k++){
					for(l=0;l<s-q+1;l++){
						d=d+sqrt(pow((temp.at<Vec3b>(k,l)[0]-image.at<Vec3b>(i+k,j+l)[0]),2));
						d=d+sqrt(pow((temp.at<Vec3b>(k,l)[1]-image.at<Vec3b>(i+k,j+l)[1]),2));
						d=d+sqrt(pow((temp.at<Vec3b>(k,l)[2]-image.at<Vec3b>(i+k,j+l)[2]),2));				
					}
				}
				d=d/(3*((t-r+1)*(s-q+1)));
				if(d<=th){
					cout<<"coordinates where image starts to match is "<<j<<","<<i;
					for(k=0;k<4;k++){
						if(k%2==0){
							meanblr(&image,&a,i,j,t-r+1,s-q+1);
						}	
						if(k%2!=0){
							meanblr(&a,&image,i,j,t-r+1,s-q+1);
						}
					}
					break;	
				}	
			}
			if(d<=th){
				break;
			}
		}	
	}
	if(c=='T'){
		cout<<"enter the path of temp: ";
		getline(cin,tem);
		Mat temp=imread(tem,CV_LOAD_IMAGE_COLOR);
		for(i=0;i<image.rows;i++){
			for(j=0;j<image.cols;j++){
				d=0;
				for(k=0;k<temp.rows;k++){
					for(l=0;l<temp.cols;l++){
						d=d+sqrt(pow((temp.at<Vec3b>(k,l)[0]-image.at<Vec3b>(i+k,j+l)[0]),2));
						d=d+sqrt(pow((temp.at<Vec3b>(k,l)[1]-image.at<Vec3b>(i+k,j+l)[1]),2));
						d=d+sqrt(pow((temp.at<Vec3b>(k,l)[2]-image.at<Vec3b>(i+k,j+l)[2]),2));				
					}
				}
				d=d/(3*((temp.rows)*(temp.cols)));
				if(d<=th){
					cout<<"coordinates where image starts to match is "<<j<<","<<i<<endl;
					for(k=0;k<4;k++){
						if(k%2==0){
							meanblr(&image,&a,i,j,temp.rows,temp.cols);
						}	
						if(k%2!=0){
							meanblr(&a,&image,i,j,temp.rows,temp.cols);
						}
					}
					break;	
				}	
			}
			if(d<=th){
				break;
			}
		}	
	}
	namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",image);
	waitKey(0);
}