#ifndef QUEUE_ANALYSER_INCLUDE_VIDEO_PROCESSORS_H_
#define QUEUE_ANALYSER_INCLUDE_VIDEO_PROCESSORS_H_
#include <vector>

#include "video_processor.h"

std::unique_ptr<VideoProcessor> getVideoProcessor(
    const std::string& filename, float skip_secs,
    const cv::Rect& queue_box);

std::unique_ptr<VideoProcessor> getVideoProcessor(
    const int cam_index, const cv::Rect& queue_box = kDefaultQueueBox);

std::unique_ptr<VideoProcessor> getVideoProcessor();

std::unique_ptr<VideoProcessor> getVideoProcessor(std::string model_file_path);

#endif  // QUEUE_ANALYSER_INCLUDE_VIDEO_PROCESSORS_H_