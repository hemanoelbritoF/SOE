
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
	VideoCapture cap("http://192.168.0.35:8080/video");
	char *outText;
	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
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
		Mat frame;
		cap >> frame;
		if(frame.empty())
			break;
		
		api->SetImage(frame.data, frame.cols, frame.rows, 3, frame.step);
		outText = api->GetUTF8Text();
		//if(i%2==0)
		//	imshow("Frame",frame);
		
		char c = (char)waitKey(33);
		if(c==27)
			break;
			
		printf("%s\n",outText);
		i++;
	}
	
	
	api->End();
	delete api;
	delete [] outText;
	
	
	
	return 0;
}
