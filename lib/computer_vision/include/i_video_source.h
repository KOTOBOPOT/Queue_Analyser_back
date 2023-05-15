#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_I_VIDEO_SOURCE_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_I_VIDEO_SOURCE_H_

#include <opencv2/opencv.hpp>

class IVideoSource {
 public:
  // virtual ~IVideoSource();
  virtual void getPicture(cv::Mat& pic) = 0;
  bool isCaptureOpened();
  bool isEndOfVideo();

 public:
  cv::Mat frame_;             // Current frame
  cv::VideoCapture capture_;  // Video source
};

#endif  // QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_I_VIDEO_SOURCE_H_