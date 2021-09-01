#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap("http://192.168.0.41:8080/video");
	if(!cap.isOpened())
	{
		cout << "Error opening" << endl;
	    return -1;
	}
	
	while(1)
	{
		Mat frame;
		cap >> frame;
		if(frame.empty())
			break;
		
		imshow("Frame",frame);
		
		char c = (char)waitKey(33);
		if(c==27)
			break;
	}
	
	cap.release();
	
	destroyAllWindows();
	return 0;
}
