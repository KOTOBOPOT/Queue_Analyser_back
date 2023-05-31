#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_VIDEO_PROCESSOR_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_VIDEO_PROCESSOR_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "cv_pic_processor.h"
#include "i_video_source.h"

const cv::Rect kDefaultQueueBox = cv::Rect(
    100, 0, 650, 250);  //(100,0)-coordinates of left-up box corner. 100 - shift
// from left side, 0 - from top, (650,250) - sides
// sizes. 650 - horizontal, 250 - vertical

class queueVidSource {
 public:
  queueVidSource(std::shared_ptr<IVideoSource> vid_source,
                 const cv::Rect& queue_box)
      : video_source_(vid_source), queue_box_(queue_box) {}
  queueVidSource(std::shared_ptr<IVideoSource> vid_source)
      : video_source_(vid_source), queue_box_(kDefaultQueueBox) {}

  cv::Rect queue_box_;
  std::shared_ptr<IVideoSource> video_source_;
};
class VideoProcessor {
 public:
  
  VideoProcessor();
  VideoProcessor(std::shared_ptr<IVideoSource> vid_source,
                 cv::Rect queue_box = kDefaultQueueBox);
  VideoProcessor(const std::string& model_file_path);
  void pushBackVideoSource(std::shared_ptr<IVideoSource> vid_source,
                           cv::Rect queue_box = kDefaultQueueBox);
  std::vector<int> getQueuePeopleAmount();
  void setCudaState(bool cuda_state);

 public:
  void setVisualizeVidSourceIndex(int vid_source_index);
  bool isVideoOpened();
  bool isEndOfVideo();
  static bool isPersonInBox(const cv::Rect& person_box,
                            const cv::Rect& queue_box = kDefaultQueueBox);
  std::vector<cv::Rect> getPeopleBoxes();

 public:
  std::shared_ptr<IVideoSource> video_source_;
  std::vector<queueVidSource> queue_video_sources_;
  cv::Mat frame_;  // Current frame. It's public for external visualization
  cv::Rect
      queue_box_;  // If person get into this box, person counts as in queue
 private:
  bool is_cuda_ = false;
  int visualize_vid_source_index_ = -1;  // means no visualize
  CVPicProcessor* pic_processor_;
};

#endif  // QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_VIDEO_PROCESSOR_H_