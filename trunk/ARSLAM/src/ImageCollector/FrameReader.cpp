#include "ImageCollector/FrameReader.h"
#include <iostream>
#include <exception>

void FrameReader::readFrame()
{
	//IplImage temp = cvQueryFrame(inDevice_);
	cv::Mat temp;
	if(!inDevice_.isOpened())
	{
		// ideally throw an exception here
		assert(0 && "I am Blind!!!! Capture Device Not Available!");
	}
	inDevice_ >> temp;
	buffer_.push_back(temp);
	if(buffer_.size() > bufSize_)
		buffer_.pop_front();
}

cv::Mat& FrameReader::getLastFrame()
{	
	return buffer_.back();
}

FrameReader::ImBuffer::const_iterator FrameReader::getFrameItr()const 
{
	return buffer_.begin();
}