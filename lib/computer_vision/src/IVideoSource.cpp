#include "i_video_source.h"

IVideoSource::~IVideoSource() { capture_.release(); }

bool IVideoSource::isCaptureOpened() { return capture_.isOpened(); }

bool IVideoSource::isEndOfVideo() { return frame_.empty(); }