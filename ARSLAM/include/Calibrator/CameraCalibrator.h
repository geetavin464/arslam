#ifndef CAMERA_CALIBRATOR_H
#define CAMERA_CALIBRATOR_H

#include <string>
#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <cxcore.h>
#include <cxtypes.h> 
#include "ImageCollector/FrameReader.h"



class CameraCalibrator
{
private: 
	FrameReader& fr_;
	cv::Mat intrinsic_matrix;
	cv::Mat distortion_coeffs;
	cv::Mat rotation_vector;
	cv::Mat translation_vector;
	uchar nViews;
public:
	CameraCalibrator(FrameReader& fr, uchar nv = 2):
	  fr_(fr),
	  nViews(nv)
	{
		intrinsic_matrix = cv::Mat(3,3,CV_32FC1);
		distortion_coeffs = cv::Mat(5,1,CV_32FC1);
		rotation_vector = cv::Mat(3,nViews,CV_32FC1);
		translation_vector = cv::Mat(3,nViews,CV_32FC1);
	}
	~CameraCalibrator(){}

	const cv::Mat& getRotationMatrix(); // returns a const ref to the rotation vector (compact Rodrigues form)
	const cv::Mat& getTranslationVector(); // returns a const ref to translation vector 
	const cv::Mat& getIntrinsicMatrix(); // returns a const ref to intrinsic matrix
	void calibrate(int bw, int bh); // Initiate the calibration procedure
};

#endif