#include"Calibrator/CameraCalibrator.h"
#include<exception>


const cv::Mat& CameraCalibrator::getIntrinsicMatrix()const
{
	return intrinsic_matrix;
}

const std::vector<cv::Mat>& CameraCalibrator::getRotationMatrix()const
{
	return rotation_vector;
}

const cv::Mat& CameraCalibrator::getDistortionCoeffs()const
{
	return distortion_coeffs;
}
const std::vector<cv::Mat>& CameraCalibrator::getTranslationVector()const
{
	return translation_vector;
}

void CameraCalibrator::calibrate(int bw, int bh)
{
	pattSize_ = cv::Size(bw,bh);
	std::string win1 = "Video Capture";
	std::string win2 = "ChessBoard";
	std::string win3 = "Gray Image";
	
	cv::namedWindow(win1,0);
	cv::namedWindow(win2,0);
	//cv::namedWindow(win3,0);
	
	cv::Mat imPtr;

	int success = 0;
	std::vector<cv::Point2f> cornersIm;
	std::vector<cv::Point3f> cornersW;
	std::vector<std::vector<cv::Point2f>> imagePoints;
	std::vector<std::vector<cv::Point3f>> worldPoints;
	bool found = false;
	// go on with the calibration
	while(success<nViews)
	{	
		
		try
		{
			// here we call fr_.readFrame; later we'll be capturing images at regular intervals, then this won't be required
			fr_.readFrame();
			imPtr = fr_.getLastFrame();
			cv::imshow(win1,imPtr);
			found = findChessboardCorners(imPtr,pattSize_,cornersIm); // finds approx corners in image
			if(cornersIm.size() != pattSize_.height*pattSize_.width)
				found = false;
		}
		catch (cv::Exception& e)
		{
		}
		
		
		if(!found)
			continue;
		
		

		cv::Mat img(imPtr);
		cv::Mat grayImg(imPtr.rows,imPtr.cols,CV_8UC1);
		try
		{
			
			cv::cvtColor(img,grayImg,CV_BGR2GRAY,1);
#ifdef _DEBUG_MODE_
			std::string name = "image";
			char c = '0' + success;
			name += c;
			name += ".png";
			imwrite(name,img);
#endif //_DEBUG_MODE_
			// finds accurately the corners
			cv::cornerSubPix(grayImg,cornersIm,cv::Size(5,5),cv::Size(-1,-1),
				cv::TermCriteria(cv::TermCriteria::MAX_ITER+cv::TermCriteria::EPS,30,0.1));//specifies the termination criteria
		}
		catch (cv::Exception* e)
		{
		}
		
		// add corners found in this image to the vector of points for calibration
		
		std::vector<cv::Point2f>::iterator it = cornersIm.begin();
		for(int i = 0;it!=cornersIm.end();++it,++i)
			cornersW.push_back(cv::Point3f(i/pattSize_.width,i%pattSize_.width,0.0f));
		worldPoints.push_back(cornersW);
		imagePoints.push_back(cornersIm);

		cv::drawChessboardCorners(img,pattSize_,cornersIm,found);
		cv::imshow(win2,img);
		
		cv::waitKey();
		success++;
		cornersW.clear();
		cornersIm.clear();



	} // while(success<nViews)
	
	calibrateCamera(worldPoints,imagePoints,cv::Size(imPtr.cols,imPtr.rows),intrinsic_matrix,distortion_coeffs,rotation_vector,translation_vector,0);

	return;

}

void CameraCalibrator::writeToFile()const
{
	cvSave("Mint.xml",&CvMat(intrinsic_matrix));
	cvSave("DistCoeff.xml",&CvMat(distortion_coeffs));


	std::vector<cv::Mat>::const_iterator rItStart = getRotationMatrix().begin();
	std::vector<cv::Mat>::const_iterator rItEnd = getRotationMatrix().end();
	std::vector<cv::Mat>::const_iterator rIt;
	int cnt = 1;
	for(rIt=rItStart;rIt<rItEnd;++rIt, ++cnt)
	{
		char c = '0' + cnt;
		std::string name = "rMat";
		name+=c;
		name+=".xml";
		cv::Mat temp;
		cv::Rodrigues(*rIt,temp);
		cvSave(name.c_str(),&CvMat(temp));
	}
	
	std::vector<cv::Mat>::const_iterator tItStart = getTranslationVector().begin();
	std::vector<cv::Mat>::const_iterator tItEnd = getTranslationVector().end();
	std::vector<cv::Mat>::const_iterator tIt;
	cnt = 1;
	for(tIt=tItStart;tIt<tItEnd;++tIt,++cnt)
	{
		char c = '0' + cnt;
		std::string name = "tvec";
		name+=c;
		name+=".xml";
		cvSave(name.c_str(),&CvMat(*tIt));
	}
}

void CameraCalibrator::testReprojection()
{
	std::string imagefn;
	//std::string rfn = "rMat";
	//std::string tfn = "tvec";
	//std::string 

	std::vector<cv::Point3f> ptsWorld;
	std::vector<cv::Point2f> imgPts;
	int nPoints = pattSize_.width*pattSize_.height;

	for(int i = 0;i<nPoints;++i)
		ptsWorld.push_back(cv::Point3f(i/pattSize_.width,i%pattSize_.width,0.0f));

	
	std::string win1 = "image";
	cv::namedWindow(win1,0);

	for(int i = 0;i<nViews;++i)
	{
		imagefn = "image";
		char c = '0' + i;
		imagefn += c;
		imagefn += ".png";

		cv::Mat img = cv::imread(imagefn);
		projectPoints(ptsWorld,rotation_vector[i],translation_vector[i],intrinsic_matrix,distortion_coeffs,imgPts);
		drawChessboardCorners(img,pattSize_,imgPts,true);
		imshow(win1,img);
		cv::waitKey(0);
	}
}