#include <highgui.h>
#include "ImageCollector/FrameReader.h"
#include "Calibrator/CameraCalibrator.h"
#include <iostream>
#include <exception>
#include <conio.h>
#include <arslam.hpp>


#pragma comment(lib,"ARSLAM.lib")

using namespace std;

int main(int argc, char** argv)
{

	cv::VideoCapture cam1(1);
	if(!cam1.isOpened()) 
	{
		std::cout<<"Camera Unavailable";
		return -1;
		// throw exception
	}	

	
	//cv::Mat A1(3,3,CV_32F,1);
	//CvMat A = CvMat(A1);
	//
	////for(int i = 0;i<3;++i)
	////	for(int j = 0;j<3;++j)
	////		A.at(i,j) = 1.0f;
	//cvSave("mat.xml",&CvMat(A1));

	/*
	* test CameraCalibrator
	*/

	FrameReader f1(cam1,5);
	CameraCalibrator c(f1,3);
	c.calibrate(8,6);
	//c.writeToFile();
	c.testReprojection();
	
	/*
	*	test FrameReader
	*/
	//string str1 = "Trust Camera";
	//FrameReader f1(cam1,5);
	//int win1 = cvNamedWindow(str1.c_str(),0);

	//while(true)
	//{
	//	f1.readFrame();
	//	cv::Mat im1 = f1.getLastFrame();
	//	cv::imshow(str1, im1);
	//	
	//	if(cvWaitKey(50) == 27)
	//		break;
	//}
	//cvDestroyWindow(str1.c_str());	


	return 0;
}