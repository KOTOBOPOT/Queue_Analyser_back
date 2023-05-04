#include <opencv2/opencv.hpp>

#include "CamVideo.h"

CamVideo::CamVideo(int cam_index) {
  camera_index_ = cam_index;
  capture_.open(camera_index_);
  if (!isCaptureOpened()) {
    std::cerr << "Error opening video file\n";
  }
}

void CamVideo::getPicture(cv::Mat& pic) {
    capture_.read(pic);
}