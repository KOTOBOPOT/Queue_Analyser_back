#ifndef QUEUE_ANALYSER_INCLUDE_VIDEO_PROCESS_H_
#define QUEUE_ANALYSER_INCLUDE_ROUTES_H_
#include <vector>

#include "video_processor.h"

std::unique_ptr<VideoProcessor> getVideoProcessor(
    const std::string& filename, float skip_secs = 0.5,
    const cv::Rect& queue_box = kDefaultQueueBox);

std::unique_ptr<VideoProcessor> getVideoProcessor(
    const int cam_index, const cv::Rect& queue_box = kDefaultQueueBox);

#endif