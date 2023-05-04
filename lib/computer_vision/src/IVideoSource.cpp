#include "IVideoSource.h"

IVideoSource::~IVideoSource(){
    capture_.release();
}

bool IVideoSource::isCaptureOpened() { return capture_.isOpened(); }

bool IVideoSource::isEndOfVideo() { return frame_.empty(); }