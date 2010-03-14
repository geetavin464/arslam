//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <math.h>
//
//#include <cv.h>
//#include <highgui.h>
//#include <cvaux.h>
//#include <cvtypes.h>
//#include <cxcore.h>
//
//
//
//
//int n_boards = 0; 
//const int board_dt = 20; 
//int board_w;
//int board_h;
//int main(int argc, char* argv[]) 
//{
//	if(argc != 4)
//	{
//		printf("ERROR: Wrong number of input parameters\n");
//		return -1;
//	}
//	board_w = atoi(argv[1]);
//	board_h = atoi(argv[2]);
//	n_boards = atoi(argv[3]);
//	int board_n = board_w * board_h;
//	CvSize board_sz = cvSize( board_w, board_h );
//	CvCapture* capture = cvCreateCameraCapture( 1 );//0 for logitech 1 for hp
//	assert( capture );
//	cvNamedWindow( "Calibration" );
//
//	CvMat* image_points = cvCreateMat(n_boards*board_n,2,CV_32FC1);
//	CvMat* object_points = cvCreateMat(n_boards*board_n,3,CV_32FC1);
//	CvMat* point_counts = cvCreateMat(n_boards,1,CV_32SC1);
//	CvMat* intrinsic_matrix = cvCreateMat(3,3,CV_32FC1);
//	CvMat* distortion_coeffs = cvCreateMat(5,1,CV_32FC1);
//	CvMat* rotation_vector = cvCreateMat(4,9,CV_32FC1);
//	CvMat* translation_vector = cvCreateMat(4,3,CV_32FC1);
//	CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
//
//	int corner_count;
//	int successes = 0;
//	int step, frame = 0;
//	IplImage *image = cvQueryFrame( capture );
//	IplImage *gray_image = cvCreateImage(cvGetSize(image),8,1);
//
//	while(successes < n_boards) 
//	{
//
//		if(frame++ % board_dt == 0) 
//		{
//
//			int found = cvFindChessboardCorners(
//				image, board_sz, corners, &corner_count,
//				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
//				);
//
//			cvCvtColor(image, gray_image, CV_BGR2GRAY);
//			cvFindCornerSubPix(gray_image, corners, corner_count,
//				cvSize(11,11),cvSize(-1,-1), cvTermCriteria(
//				CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
//
//			cvDrawChessboardCorners(image, board_sz, corners,
//				corner_count, found);
//			cvShowImage( "Calibration", image );
//
//			if( corner_count == board_n ) 
//			{
//				step = successes*board_n;
//				for( int i=step, j=0; j<board_n; ++i,++j ) 
//				{
//					CV_MAT_ELEM(*image_points, float,i,0) = corners[j].x;
//					CV_MAT_ELEM(*image_points, float,i,1) = corners[j].y;
//					CV_MAT_ELEM(*object_points,float,i,0) = j/board_w;
//					CV_MAT_ELEM(*object_points,float,i,1) = j%board_w;
//					CV_MAT_ELEM(*object_points,float,i,2) = 0.0f;
//				}
//				CV_MAT_ELEM(*point_counts, int,successes,0) = board_n;
//				successes++;
//			}
//		}
//		int c = cvWaitKey(15);
//		if(c == 'p')
//		{
//			c = 0;
//			while(c != 'p' && c != 27)
//			{
//				c = cvWaitKey(250);
//			}
//		}
//		if(c == 27) // user hit Esc
//			return 0;
//		image = cvQueryFrame( capture ); 
//	}
//
//	CvMat* object_points2 = cvCreateMat(successes*board_n,3,CV_32FC1);
//	CvMat* image_points2 = cvCreateMat(successes*board_n,2,CV_32FC1);
//	CvMat* point_counts2 = cvCreateMat(successes,1,CV_32SC1);
//
//	for(int i = 0; i<successes*board_n; ++i) 
//	{
//		CV_MAT_ELEM( *image_points2, float, i, 0) = CV_MAT_ELEM( *image_points, float, i, 0);
//		CV_MAT_ELEM( *image_points2, float,i,1) = CV_MAT_ELEM( *image_points, float, i, 1);
//		CV_MAT_ELEM(*object_points2, float, i, 0) = CV_MAT_ELEM( *object_points, float, i, 0) ;
//		CV_MAT_ELEM( *object_points2, float, i, 1) = CV_MAT_ELEM( *object_points, float, i, 1) ;
//		CV_MAT_ELEM( *object_points2, float, i, 2) = CV_MAT_ELEM( *object_points, float, i, 2) ;
//	}
//	for(int i=0; i<successes; ++i)
//	{ 
//		CV_MAT_ELEM( *point_counts2, int, i, 0) = CV_MAT_ELEM( *point_counts, int, i, 0);
//	}
//	cvReleaseMat(&object_points);
//	cvReleaseMat(&image_points);
//	cvReleaseMat(&point_counts);
//
//	CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
//	CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;
//
//	cvCalibrateCamera2(
//		object_points2, image_points2,
//		point_counts2, cvGetSize( image ),
//		intrinsic_matrix, distortion_coeffs,
//		rotation_vector, translation_vector,0 
//		);
//
//	cvSave("Intrinsics.xml",intrinsic_matrix);
//	cvSave("Distortion.xml",distortion_coeffs);
//	cvSave("rotation.xml",rotation_vector);
//	cvSave("translation.xml",translation_vector);
//
//
//	cvReleaseCapture( &capture );
//	cvDestroyAllWindows();
//
//	printf("I am holy done\n");
//	getch( );
//	return 0;
//}

//#include <cxcore.h>
//#include <cv.h>
//#include <cvtypes.h>
//#include <cvaux.h>
#include <highgui.h>
#include "ImageCollector/FrameReader.h"
#include "Calibrator/CameraCalibrator.h"
#include <iostream>
#include <string>
#include <exception>

#pragma comment(lib,"ARSLAM.lib")

using namespace std;
int main(int argc, char** argv)
{
	int i = 0;
	cout<<i;

	CvMat* M = cvCreateMat(3,4,CV_8UC3);
	/*CvCapture* cam1 = cvCreateCameraCapture(1);
	if(NULL == cam1)
	{	
		std::cout<<"Camera Unavailable";
		return -1;
	}*/
	
	
	///*
	//* test CameraCalibrator
	//*/

	//FrameReader f1(cam1,5);
	//CameraCalibrator c(f1,3);
	//c.calibrate(6,4);
	
	

	/*
	*	test FrameReader
	*/
	/*string str1 = "Trust Camera";
	FrameReader f1(cam1,5);
	int win1 = cvNamedWindow(str1.c_str(),0);

	while(true)
	{
		f1.readFrame();
		IplImage* im1 = f1.getLastFrame();
		cv::imshow(str1, cv::Mat(im1));
		
		if(cvWaitKey(50) == 27)
			break;
	}
	cvDestroyWindow(str1.c_str());	*/


	return 0;
}