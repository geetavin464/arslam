#ifndef FRAME_READER_H
#define FRAME_READER_H
#include<highgui.h>
#include<list>


class FrameReader
{
public:
	typedef std::list<cv::Mat> ImBuffer;
private:
	cv::VideoCapture inDevice_;
	ImBuffer buffer_;
	ImBuffer::iterator bufPtr_;
	size_t bufSize_;
	int* temp_;
	
public:
	FrameReader()
	{
		bufSize_ = 0;
	}
	FrameReader(cv::VideoCapture& dev, int nFrames=5):
		inDevice_(dev),
		bufSize_(nFrames)	
	{
		temp_ = new int[5];
		for(int i = 0;i<5;i++)
			temp_[i] = i;
		//buffer_.reserve(bufSize_);
		//buffer_.assign(bufSize_,NULL);
		bufPtr_ = buffer_.begin();
		
		cv::Size s;
		s.width = (int)dev.get(CV_CAP_PROP_FRAME_WIDTH);
		s.height = (int)dev.get(CV_CAP_PROP_FRAME_HEIGHT);
	}

	~FrameReader()
	{
		delete temp_;
		buffer_.clear();
	}
	void readFrame();
	cv::Mat& getLastFrame();
	ImBuffer::const_iterator getFrameItr() const;
};

#endif // FRAME_READER_H