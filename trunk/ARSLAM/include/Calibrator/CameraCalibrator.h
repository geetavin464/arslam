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
	std::vector<cv::Mat> rotation_vector;
	std::vector<cv::Mat> translation_vector;
	cv::Size pattSize_;
	uchar nViews;
public:
	CameraCalibrator(FrameReader& fr, uchar nv = 2):
	  fr_(fr),
	  nViews(nv)
	{
		intrinsic_matrix = cv::Mat(3,3,CV_32FC1);
		distortion_coeffs = cv::Mat(5,1,CV_32FC1);
		pattSize_ = cv::Size(0,0);
		//rotation_vector = cv::Mat(3,nViews,CV_32FC1);
		//translation_vector = cv::Mat(3,nViews,CV_32FC1);
	}
	~CameraCalibrator(){}

	const std::vector<cv::Mat>& getRotationMatrix() const; // returns a const ref to the rotation vector (compact Rodrigues form)
	const std::vector<cv::Mat>& getTranslationVector()const; // returns a const ref to translation vector 
	const cv::Mat& getIntrinsicMatrix() const; // returns a const ref to intrinsic matrix
	const cv::Mat& getDistortionCoeffs() const; // returns a const ref to the distortion coefficients
	void calibrate(int bw, int bh); // Initiate the calibration procedure
	void writeToFile()const;
	void testReprojection();
};

#endif