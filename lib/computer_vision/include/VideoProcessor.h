#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_VIDEO_PROCESSOR_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_VIDEO_PROCESSOR_H_

#include <opencv2/opencv.hpp>
#include <string>

#include "CVPicProcessor.h"
#include "IVideoSource.h"

const cv::Rect kDefaultQueueBox = cv::Rect(
    100, 0, 650, 250);  //(100,0)-coordinates of left-up box corner. 100 - shift
                        //from left side, 0 - from top, (650,250) - sides sizes.
                        //650 - horizontal, 250 - vertical

class VideoProcessor {
 public:
  // File Video init
  VideoProcessor(
      const std::string& filename, size_t fps = 28,
      float time_period = 0.5, const cv::Rect& queue_box = kDefaultQueueBox);  // Means that each 0.5 sec will get measure
  // Real time camera init
  VideoProcessor(int camera_index = 0,const cv::Rect& queue_box = kDefaultQueueBox);

  //  ~VideoProcessor();
  int getQueuePeopleAmount();
  void setCudaState(bool cuda_state);

 public:
  bool isVideoOpened();
  bool isEndOfVideo();
  bool isPersonInBox(cv::Rect& person_box);
  std::vector<cv::Rect> getPeopleBoxes();

 public:
  std::shared_ptr<IVideoSource> video_source_;

  cv::Mat frame_;  // Current frame. It's public for external visualization
  cv::Rect queue_box_;// If person get into this box, person counts as in queue
 private:
  CVPicProcessor pic_processor_ = CVPicProcessor();
  bool is_cuda_ = false;
};

#endif