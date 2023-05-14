#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_VIDEO_PROCESSOR_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_VIDEO_PROCESSOR_H_

#include <opencv2/opencv.hpp>
#include <string>

#include "cv_pic_processor.h"
#include "i_video_source.h"

const cv::Rect kDefaultQueueBox = cv::Rect(
    100, 0, 650, 250);  //(100,0)-coordinates of left-up box corner. 100 - shift
                        // from left side, 0 - from top, (650,250) - sides
                        // sizes. 650 - horizontal, 250 - vertical
class queueVidSource {
 public:
  queueVidSource(std::shared_ptr<IVideoSource> vid_source, const cv::Rect& queue_box)
      : vid_source_(vid_source), queue_box_(queue_box) {}
   queueVidSource(std::shared_ptr<IVideoSource> vid_source)
      : vid_source_(vid_source), queue_box_(kDefaultQueueBox) {}
 
  cv::Rect queue_box_;
  std::shared_ptr<IVideoSource> vid_source_;
};
class VideoProcessor {
 public:
  VideoProcessor(std::vector<queueVidSource>
                     vid_sources);

  std::vector<int> getQueuePeopleAmount();
  void setCudaState(bool cuda_state);

 public:
  bool isVideoOpened();
  bool isEndOfVideo();
  static bool isPersonInBox(const cv::Rect& person_box,
                            const cv::Rect& queue_box = kDefaultQueueBox);
  std::vector<cv::Rect> getPeopleBoxes();

 public:
  std::shared_ptr<IVideoSource> video_source_;

  cv::Mat frame_;  // Current frame. It's public for external visualization
  cv::Rect
      queue_box_;  // If person get into this box, person counts as in queue
 private:
  CVPicProcessor pic_processor_ = CVPicProcessor();
  bool is_cuda_ = false;
};

#endif