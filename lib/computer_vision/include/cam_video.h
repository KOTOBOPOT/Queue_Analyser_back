#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_CAM_VIDEO_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_CAM_VIDEO_H_

#include "i_video_source.h"

class CamVideo final : public IVideoSource {
 public:
  CamVideo(int cam_index);
  void getPicture(cv::Mat& pic) override;

 private:
  int camera_index_;
};

#endif