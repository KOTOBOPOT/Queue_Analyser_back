#include <opencv2/opencv.hpp>

#include "FileVideo.h"

FileVideo::FileVideo(const std::string& filename, size_t fps, float skip_secs) {
  filename_ = filename;

  fps_ = fps;
  skip_secs_ = skip_secs;
  skip_frames_ = fps_ * skip_secs_;

  capture_.open(filename);
  if (!isCaptureOpened()) {
    std::cerr << "Error opening video file\n";
  }
}

void FileVideo::getPicture(cv::Mat& pic) {
  capture_.read(frame_);
  pic = frame_;
  skipFrames();
}

void FileVideo::skipFrames() {
  if (isEndOfVideo()) {
    return;
  }

  size_t skipped_frames_counter = 0;
  for (; skipped_frames_counter <= skip_frames_; ++skipped_frames_counter) {
    if (isEndOfVideo()) {
      return;  // Video Has Ended
    }
    skipFrame();
  }
}


void FileVideo::skipFrame() { capture_.read(frame_); }