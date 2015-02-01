#include<iostream>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
void glcm(Mat &);
Mat img=imread("/home/jeenal/Pictures/1.jpg",CV_LOAD_IMAGE_UNCHANGED);            //input image
if(img.empty())
{
 cout<<"no image";
 return 0;
}

glcm(img);                                                                      //call to glcm function
namedWindow("Image",CV_WINDOW_AUTOSIZE);
imshow("Image",img);
waitKey(0);
return 0;

}



void glcm(Mat &img)
{
  float energy=0,contrast=0,homogenity=0,IDM=0,entropy=0,mean1=0;
  int row=img.rows,col=img.cols;
  Mat gl=Mat::zeros(256,256,CV_32FC1);
  
  //creating glcm matrix with 256 levels,radius=1 and in the horizontal direction 
  for(int i=0;i<row;i++)
     for(int j=0;j<col-1;j++)
         gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))=gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))+1;   
  
 // normalizing glcm matrix for parameter determination
  gl=gl+gl.t();            
  gl=gl/sum(gl)[0];
 
 
 for(int i=0;i<256;i++)
    for(int j=0;j<256;j++)
        {
        energy=energy+gl.at<float>(i,j)*gl.at<float>(i,j);            //finding parameters
        contrast=contrast+(i-j)*(i-j)*gl.at<float>(i,j);
        homogenity=homogenity+gl.at<float>(i,j)/(1+abs(i-j));
        if(i!=j)
          IDM=IDM+gl.at<float>(i,j)/((i-j)*(i-j));                      //Taking k=2;
        if(gl.at<float>(i,j)!=0)
          entropy=entropy-gl.at<float>(i,j)*log10(gl.at<float>(i,j));
        mean1=mean1+0.5*(i*gl.at<float>(i,j)+j*gl.at<float>(i,j));
        }
 cout<<"energy="<<energy<<endl;
 cout<<"contrast="<<contrast<<endl;
 cout<<"homogenity="<<homogenity<<endl;
 cout<<"IDM="<<IDM<<endl;
 cout<<"entropy="<<entropy<<endl;
 cout<<"mean="<<mean1<<endl;
}



