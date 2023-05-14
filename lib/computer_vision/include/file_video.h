#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_FILE_VIDEO_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_FILE_VIDEO_H_

#include "i_video_source.h"

class FileVideo final : public IVideoSource {
 public:
  FileVideo(const std::string& filename, size_t fps, float skip_secs);
  void getPicture(cv::Mat& pic) override;

 private:
  void skipFrames();
  void skipFrame();

 private:
  std::string filename_;
  size_t fps_;
  float skip_secs_;
  size_t skip_frames_;
};

#endif