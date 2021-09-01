
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main()
{
	char *outText;
	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	if(api->Init(NULL,"eng"))
	{
		fprintf(stderr, "error\n");
		exit(1);
	}
	
	Pix *image = pixRead("/home/pi/2021-09-01-102232_1184x624_scrot.png");
	api->SetImage(image);
	
	outText = api->GetUTF8Text();
	
	printf("%s\n",outText);
	
	api->End();
	delete api;
	delete [] outText;
	
	pixDestroy(&image);
	
	return 0;
}
