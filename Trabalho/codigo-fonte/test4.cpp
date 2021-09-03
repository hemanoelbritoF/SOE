#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <wiringPi.h>

using namespace std;
using namespace cv;

int main()
{
	wiringPiSetup();
	system("gpio mode 0 in");
	
	
	char *outText;
	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	if(api->Init(NULL,"eng"))
	{
		fprintf(stderr, "error\n");
		exit(1);
	}
	api->SetPageSegMode(tesseract::PSM_AUTO);
	
	
	while(1)
	{
		
		if(!digitalRead(0))
			break;
		
	}
	
	VideoCapture cap("http://192.168.0.35:8080/video");
	Mat frame;
	cap >> frame;
	//api->SetImage(frame.data, frame.cols, frame.rows, 3, frame.step);
	int imheight = frame.rows;
	int imwidth = frame.cols;
	
	frame = frame(Range(imheight/1.5 + 90,imheight-140),Range(0,imwidth));
	api->SetImage(frame.data, frame.cols, frame.rows, 3, frame.step);
	
	imshow("Frame",frame);
	cap.release();
	
	char c = (char)waitKey(0);
	outText = api->GetUTF8Text();
	printf("O resultado é:%s\n",outText);
	api->End();
	delete api;
	delete [] outText;
	return 0;
}
