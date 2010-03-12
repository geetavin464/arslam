#include"Calibrator/CameraCalibrator.h"
#include<exception>


const cv::Mat& CameraCalibrator::getIntrinsicMatrix()
{
	return intrinsic_matrix;
}

const cv::Mat& CameraCalibrator::getRotationMatrix()
{
	return rotation_vector;
}

const cv::Mat& CameraCalibrator::getTranslationVector()
{
	return translation_vector;
}

void CameraCalibrator::calibrate(int bw, int bh)
{
	cv::Size pattSize = cv::Size(bh,bw);
	std::string win1 = "Video Capture";
	std::string win2 = "ChessBoard";

	//cv::namedWindow(win1,0);
	cvNamedWindow(win1.c_str(),0);
	//cv::namedWindow(win2,0);
	
	int success = 0;
	std::vector<cv::Point2f> corners;
	bool found = false;
	// go on with the calibration
	while(success<nViews)
	{

		IplImage* imPtr;
		
		try
		{
			// here we call fr_.readFrame; later we'll be capturing images at regular intervals, then this won't be required
			fr_.readFrame();
			imPtr = fr_.getLastFrame();
			cv::imshow(win1,cv::Mat(imPtr));
			found = findChessboardCorners(cv::Mat(imPtr),pattSize,corners); // finds approx corners in image
			if(cv::waitKey(50) == 27)
				break;
		}
		catch (cv::Exception& e)
		{
		}
		
		
		if(!found)
			continue;

		cv::Mat img(imPtr);
		
		// finds accurately the corners
		cv::cornerSubPix(img,corners,cv::Size(5,5),cv::Size(-1,-1),
			cv::TermCriteria(cv::TermCriteria::MAX_ITER+cv::TermCriteria::EPS,30,0.1));//specifies the termination criteria

		cv::drawChessboardCorners(img,pattSize,corners,found);
		cv::imshow(win2,img);
		cv::waitKey();
		success++;

	} // while(success<nViews)
}