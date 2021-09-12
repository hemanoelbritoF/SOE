#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <raspicam/raspicam_cv.h>

using namespace std;
using namespace cv;

int main()
{
	int i = 0;
	//VideoCapture cap("http://video");
	Mat frame;
	raspicam::RaspiCam_Cv cap;
	char* outText;
	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	
	if (api->Init(NULL, "eng"))
	{
		fprintf(stderr, "error\n");
		exit(1);
	}
	api->SetPageSegMode(tesseract::PSM_AUTO);
	if (!cap.isOpened())
	{
		cout << "error2\n";
		return 0;
	}

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