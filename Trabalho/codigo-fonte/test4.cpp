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
	
	VideoCapture cap("http://192.168.0.35:8080/video");
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
	Mat frame;
	cap >> frame;

	imshow("Frame",frame);
	char c = (char)waitKey(0);
	api->End();
	return 0;
}
