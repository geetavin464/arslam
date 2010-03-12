#include "ImageCollector/FrameReader.h"
#include <iostream>

void FrameReader::readFrame()
{
	IplImage* temp = cvQueryFrame(inDevice_);
	if(NULL == temp)
	{// this doesn't help here. last grabbed frame is returned
		// think of another way of dealing with this
		// ideally throw an exception here
		assert(0 && "I am Blind!!!! Capture Device Not Available!");
	}
	if(bufPtr_!=buffer_.begin())
	{
		bufPtr_++;
	}
	if(bufPtr_ == buffer_.end())
		bufPtr_ = buffer_.begin();

	if(*bufPtr_ != NULL)
		cvReleaseImage(&(*bufPtr_));

	*bufPtr_ = cvCloneImage(temp);
}

IplImage* FrameReader::getLastFrame() const
{	
	return (*bufPtr_);
}

FrameReader::ImBuffer::const_iterator FrameReader::getFrameItr()const 
{
	return buffer_.begin();
}