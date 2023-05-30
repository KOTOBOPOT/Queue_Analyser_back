#include "cam_video.h"

#include <opencv2/opencv.hpp>

#include "../include/computer_vision_exceptions/cv_open_video_source_exc.h"

CamVideo::CamVideo(int cam_index) {
  camera_index_ = cam_index;
  capture_.open(camera_index_);
  if (!isCaptureOpened()) {
    throw CVOpenVidSourceException(
        "Failed to open camera video source with index: " +
        std::to_string(camera_index_));
    // std::cerr << "Error opening camera source\n";
  }
}

void CamVideo::getPicture(cv::Mat& pic) { capture_.read(pic); }