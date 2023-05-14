#include "i_video_source.h"

#include<iostream>
//IVideoSource::~IVideoSource() { std::cout<<"Capture is released"<<std::endl;capture_.release(); }

bool IVideoSource::isCaptureOpened() { return capture_.isOpened(); }

bool IVideoSource::isEndOfVideo() { return frame_.empty(); }