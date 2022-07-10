#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;

int isvalid(int x,int y,int rows,int cols)
{
	if(x<0||y<0||x>=rows||y>=cols)
		return 0;
	return 1;
}

int dijkstra(Mat *a, int p , double d[], int parent[], int v[],int sy, int sx)
{
    int i,j,k,l;
    int m,n;
    Mat b((*a).rows,(*a).cols,CV_8UC1,Scalar(255));
    j=sx+sy*(*a).cols;
    d[j]= 0;
    for(m= -1; m<2; m++){
    	for(n= -1; n<2; n++){
    		if(m!= 0 || n!= 0){
    			if(isvalid(m + sy, n + sx, (*a).rows, (*a).cols)){
    			    if((*a).at<uchar>(m + j / (*a).cols, n + (j%(*a).cols))){
    					if((d[j] + sqrt((double)m * (double)m + (double)n * (double)n)) < d[j + n + m * (*a).cols]){
                        	d[j + n + m * (*a).cols]= d[j] + sqrt((double)m * (double)m + (double)n * (double)n);
                        	parent[j + n + m * (*a).cols]= j;
    					}
    			    }
    			}
    		}
        }
    }
    v[j]=1;
    for(i=0;i<p;i++){
    	k=INT_MAX;
    	for(l=0;l<p;l++){
		    if(v[l]==0){
			    if(d[l]<k){
				    k=d[l];
				    j=l;
			    }

		    }
        
	    }
        for(m= -1; m<2; m++){
        	for(n= -1; n<2; n++){
        		if(m!= 0 || n!= 0){
        			if(isvalid(m + j / ((*a).cols), n + (j % (*a).cols), (*a).rows, (*a).cols)){
        			    if((*a).at<uchar>(m + j / (*a).cols, n + (j % (*a).cols))!= 0){
        			    	if(v[j + n + m* (*a).cols]== 0){
	        					if((d[j] + sqrt((double)m * (double)m + (double)n * (double)n)) < d[j + n + m * (*a).cols]){
	                            	d[j + n + m * (*a).cols]=d[j]+sqrt((double)m * (double)m + (double)n * (double)n);
	                            	parent[j + n + m * (*a).cols] = j;
	                            }
        					}
        			    }
        			}
        		}
            }
        }  
        v[j]= 1; 
        b.at<uchar>(j / (*a).cols, j % (*a).cols)=0;
        namedWindow("window2",WINDOW_NORMAL);
        imshow("window2",b);
        waitKey(1);
    }
}


int main()
{
	int e,f,g,h,i,j,k;
	cout<<"input the source and destination point: "<<endl;
	cin>>e>>f>>g>>h;
	Mat image;
	image=imread("rrt.png",0);
	int size=(image.rows)*(image.cols);
	double d[size];
	for(i=0;i<size;i++){
		d[i]=INT_MAX;
	}
	int parent[size];
	int v[size]={0};
	for(i=0;i<size;i++){
		parent[i]=i;
	}
	j=h*(image.cols)+g;
	dijkstra(&image,size,d,parent,v,e,f);
	image.at<uchar>(h,g)=0;
	cout<<d[j];
    while(j!=f*(image.cols)+e){
    	j=parent[j];
    	image.at<uchar>(j/image.cols,j%image.cols)=0;
    }
    namedWindow("window1",WINDOW_NORMAL);
	imshow("window1",image);
	waitKey(0);
}