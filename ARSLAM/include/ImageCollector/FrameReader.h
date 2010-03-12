#ifndef FRAME_READER_H
#define FRAME_READER_H
#include<highgui.h>
#include<vector>


class FrameReader
{
public:
	typedef std::vector<IplImage*> ImBuffer;
private:
	cv::Ptr<CvCapture> inDevice_;
	ImBuffer buffer_;
	ImBuffer::iterator bufPtr_;
	int bufSize_;
	
public:
	FrameReader()
	{
		inDevice_ = NULL;
		bufSize_ = 0;
	}
	FrameReader(cv::Ptr<CvCapture> dev, int nFrames=5)
	{
		inDevice_ = dev;
		bufSize_ = nFrames;
		buffer_.reserve(bufSize_);
		buffer_.assign(bufSize_,NULL);
		bufPtr_ = buffer_.begin();
		
		CvSize s;
		s.width = (int)cvGetCaptureProperty(inDevice_,CV_CAP_PROP_FRAME_WIDTH);
		s.height = (int)cvGetCaptureProperty(inDevice_,CV_CAP_PROP_FRAME_HEIGHT);
	}

	~FrameReader()
	{
		buffer_.clear();
	}
	void readFrame();
	IplImage* getLastFrame() const;
	ImBuffer::const_iterator getFrameItr() const;
};

#endif // FRAME_READER_H