#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "Aria.h"

#include <iostream.h>
#include <stdio.h>

using namespace std;
using namespace cv;

/* Function Headers */
 void detectAndDisplay(Mat frame);

String face_cascade_name = "haarcascade_frontalface_alt2.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
const char* window = "face detector";
CascadeClassifier face_cascade, eyes_cascade;

int LW=0, RW=0;

int main(int argc,char** argv)
{
	//----------------------------------------------//
	Aria::init();                                                    
	ArArgumentParser parser(&argc, argv);
	parser.loadDefaultArguments();
	ArRobot robot;
	ArRobotConnector rc(&parser, &robot);
	rc.connectRobot();
	robot.runAsync(true);
	//----------------------------------------------//

	Mat frame;
	CvCapture* pCapture;  
	pCapture = cvCreateCameraCapture(0);  //camera acquiring, generally index is -1

	//------------------------------------------------------------------- 1. Load the cascades ---//
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face\n"); return -1; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eye\n"); return -1; };
	
		/*if(!pCapture){
			fprintf(stderr,"Could not initialize capturing...\n");
			return -1;}
		
		if(argc==1){
			pCapture = cvCreateCameraCapture(0);}
		
		else{
			pCapture = cvCreateFileCapture(argv[1]);}

		cvNamedWindow(window, 0);*/
		
		while(1)
		{
			frame = cvQueryFrame(pCapture);  //--------------------- 2. Read the video stream ---//
			
				if( !frame.empty() )         //--------- 3. Apply the classifier to the frame ---//
				{ detectAndDisplay( frame ); }
				else
				{ printf(" --(!) No captured frame -- Break!"); break; }

			//----------------------------------------------//
			robot.lock();
			robot.enableMotors();
			robot.setVel2(LW,RW);
			robot.unlock();
			//----------------------------------------------//

			char c=cvWaitKey(33);
			if(c==27)break;
		}

	cvReleaseCapture(&pCapture);
	cvDestroyWindow(window);

	robot.waitForRunExit();
	return 0;
}

 
/** @function detectAndDisplay */
void detectAndDisplay(Mat frame)
{
  Mat frame_gray, faceROI;
  std::vector<Rect> faces;
  std::vector<Rect> eyes;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

   /* -------------------------------------------- Detect faces ---------------------------------------------- *
	* detectMultiScale函数中frame_gray表示要检测的输入图像为frame_gray，faces表示检测到的人脸目标序列，1.1表示 *
    * 每次图像尺寸减小的比例为1.1，2表示每一个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大 *
    * 小都可以检测到人脸),  CV_HAAR_SCALE_IMAGE 表示不是缩放分类器来检测，而是缩放图像，Size(30, 30)表示目标的 *
    * 最小最大尺寸                                                                                             *
	* -------------------------------------------- ------------ ---------------------------------------------- *
   */
  face_cascade.detectMultiScale( frame_gray, faces, 1.5, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    faceROI = frame_gray( faces[i] );

    //-------------------------------- In each face, detect eyes ------------------------------//
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.5, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );

	    //----------------------------------------------//
		   if(eyes.size() == 1)
		   {
			   if(eyes[0].x > 100)
			 {
				 printf("RT");
				 RW=-30;
				 LW=30;
			 }
				 
			 if(eyes[0].x < 100) 
			 {
				 printf("LF");
				 RW=30;
				 LW=-30;
			 }
		   }

		   if(eyes.size() != 1)
		   {
			     printf("stop");
				 RW=0;
				 LW=0;
		   }
		//----------------------------------------------//
     }
  }
  //-- Show what you got
  imshow(window, frame);
}