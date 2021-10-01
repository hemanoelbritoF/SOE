#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <raspicam/raspicam_cv.h>


using namespace std;
using namespace cv;

int main()
{
	int i = 0;
	VideoCapture cap(0);
	Mat frame;
	//raspicam::RaspiCam_Cv cap;
	//cap.set( CAP_PROP_FORMAT, CV_8UC3 );
	//cap.set( CAP_PROP_FRAME_WIDTH, 1920 );
	//cap.set( CAP_PROP_FRAME_HEIGHT, 1080 );
	//cap.set( CAP_PROP_FPS, 30 );
	//sleep(5);
	if (!cap.isOpened())
	{
		cout << "error2\n";
		return 0;
	}
	char* outText;
	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	
	if (api->Init(NULL, "eng"))
	{
		fprintf(stderr, "error\n");
		exit(1);
	}
	api->SetPageSegMode(tesseract::PSM_AUTO);
	

	while (1)
	{
		cap.grab();
		cap.retrieve(frame);
		api->SetImage(frame.data, frame.cols, frame.rows, 3, frame.step);
		outText = api->GetUTF8Text();
		imshow("Frame", frame);
		char c = (char)waitKey(33);
		if (c == 27)
			break;

		printf("%s\n", outText);
	}
	api->End();
	delete api;
	delete[] outText;
	return 0;
}
