#include "file_video.h"

#include <opencv2/opencv.hpp>

#include "../include/computer_vision_exceptions/cv_open_video_source_exc.h"

FileVideo::FileVideo(const std::string& filename, float skip_secs) {
  filename_ = filename;

  skip_secs_ = skip_secs;

  capture_.open(filename);
  if (!isCaptureOpened()) {
    throw CVOpenVidSourceException(
        "Failed to open file video source with name: " +
        filename);//std::cerr << "Error opening video file\n";
  }
  fps_ = capture_.get(cv::CAP_PROP_FPS);
  ;
  skip_frames_ = fps_ * skip_secs_;
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