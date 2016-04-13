#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main()
{
 Mat image;
 CvCapture* capture;
 //image = imread( "test-1.pgm", CV_LOAD_IMAGE_GRAYSCALE);
      
    // Read the video stream
    capture = cvCaptureFromCAM( -1 );  
  
    // Load haar cascade (.xml file)
    CascadeClassifier car_cascade;
    CascadeClassifier upperbody_cascade;
    //HOGDescriptor hog;
    //hog.load("/home/zain/opencv-2.4.9/data/hogcascades/hogcascade_pedestrians.xml");
    car_cascade.load( "/home/zain/opencv-2.4.9/data/haarcascades/cas2.xml" );
    upperbody_cascade.load( "/home/zain/opencv-2.4.9/data/haarcascades/haarcascade_upperbody.xml" );
    
 
 while(1)
 {
 image = cvQueryFrame( capture );
    // Detect cars
    std::vector<Rect> cars;
    //std::vector<Rect> human;
    std::vector<Rect> upperbody;
    Mat gray;
    cvtColor(image, gray, CV_BGR2GRAY);
    Mat bw;
    adaptiveThreshold(~gray, bw, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    // Show binary image
    imshow("binary", bw);
    //hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    //hog.detectMultiScale(gray, human, 0, Size(8,8), Size(32,32), 1.05, 2);
    car_cascade.detectMultiScale( gray, cars, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    upperbody_cascade.detectMultiScale( gray, upperbody, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
 
  
    // Draw circles on the detected cars
  //  for( int i = 0; i < cars.size(); i++ )
  //  {
  //      Point center( cars[i].x + cars[i].width*0.5, cars[i].y + cars[i].height*0.5 );
  //      ellipse( image, center, Size( cars[i].width*0.5, cars[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
  //  }

       for(int i = 0; i < cars.size(); i++)
		{
                        if((cars[i].x + cars[i].width) > (cars[i].y + cars[i].height))
                        {
			Point pt1(cars[i].x + cars[i].width, cars[i].y + cars[i].height);
			Point pt2(cars[i].x, cars[i].y);

			rectangle(image, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
                        }
		}
      
       for(int i = 0; i < upperbody.size(); i++)
		{
			Point pt1(upperbody[i].x + upperbody[i].width, upperbody[i].y + upperbody[i].height);
			Point pt2(upperbody[i].x, upperbody[i].y);

			rectangle(image, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		}
      // for(int i = 0; i < human.size(); i++)
	//	{
	//		Point pt1(human[i].x + human[i].width, human[i].y + human[i].height);
	//		Point pt2(human[i].x, human[i].y);

	//		rectangle(image, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
	//	}
    imshow( "Detector", image );
    if(waitKey(1) == 'q') break;
 }
waitKey(0);

            
}
