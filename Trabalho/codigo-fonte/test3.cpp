
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main()
{
	int i =0;
	VideoCapture cap(0);
	cap.set(CAP_PROP_FRAME_HEIGHT, 1944);
    cap.set(CAP_PROP_FRAME_WIDTH, 2592);
	Mat frame;
	Mat resized_frame;
	Mat grayscale;
	Mat grayscalecp;
	
	char *outText;
	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	
	int x=920;
	int y=1200;
	Rect text_rect(x,y,200,20);
	
	if(api->Init(NULL,"eng"))
	{
		fprintf(stderr, "error\n");
		exit(1);
	}
	
	//Pix *image = pixRead("/home/pi/2021-09-01-102232_1184x624_scrot.png");
	//api->SetImage(image);
	
	api->SetPageSegMode(tesseract::PSM_AUTO);
	
	
	while(1)
	{
		
		cap >> frame;
		if(frame.empty())
			break;
		
		Rect text_rect(x,y,600,60);
		rectangle(frame,text_rect,Scalar(255,0,0),6,8,0);
		resize(frame, resized_frame, Size(800, 450), INTER_LINEAR);
		//printf("%d,%d\n",x,y);
		
		//if(i%2==0)
		imshow("Frame",resized_frame);
		
		char c = (char)waitKey(0);
		if(c==27)//esc
			break;
		
		if(c==105||c==107)//i || k
		{
				if(c==107)//i
				{
					y+=10;
				}
				else//k
				{
					y-=10;
					if(y<0)
						y=0;
				}
				
				
		}	
		
		if(c==106||c==108)//j || l
		{
				if(c==106)//j
				{
					x-=10;
					if(x<0)
						x=0;
				}
				else//l
				{
					x+=10;
					
				}
			
				
		}
		
		i++;
	}
	cap.release();
	system("raspistill -o image.jpg -br 50 -sh 100 -sa -100 -ex auto");
	frame = imread("image.jpg");
	Rect cut(x,y,600,60);
	cvtColor(frame(cut),grayscale,COLOR_RGB2GRAY);
	
	imshow("Frame",grayscale);
	waitKey(0);
	int val=80;
	
	while(1)
	{
	
	imshow("Frame",grayscale);
	char c = (char)waitKey(0);
	printf("%d,%d\n",x,y);
	if(c==27)//esc
		break;
	
    }
    grayscalecp = grayscale;
    //threshold(grayscale ,grayscale ,127,255, THRESH_BINARY+THRESH_OTSU );
    imshow("Frame",grayscale);
    waitKey(0);
	api->SetImage(grayscale.data, grayscale.cols, grayscale.rows, 3, grayscale.step);
	outText = api->GetUTF8Text();
	printf("%s\n",outText);
	
	api->End();
	delete api;
	delete [] outText;
	
	
	
	return 0;
}
