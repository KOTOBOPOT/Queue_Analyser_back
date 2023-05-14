#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_CV_PIC_PROCESSOR_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_CV_PIC_PROCESSOR_H_

#include <opencv2/opencv.hpp>

// YOLO constants:
const float kInputWidth = 640.0;
const float kInputHeight = 640.0;
const float kScoreThreshold = 0.2;
const float kNmsThreshold = 0.4;
const float kConfidenceThreshold = 0.4;
const int kPeopleClassId = 0;

struct Detection {
  int class_id;
  float confidence;
  cv::Rect box;
};

class CVPicProcessor {
 public:
  CVPicProcessor();
  void getBoxes(cv::Mat &image, std::vector<Detection> &output);

 private:
  void detect(cv::Mat &image, cv::dnn::Net &net, std::vector<Detection> &output,
              const std::vector<std::string> &className);
  void loadNet(cv::dnn::Net &net, bool is_cuda);
  cv::Mat formatYoloV5(const cv::Mat &source);
  std::vector<std::string> loadClassList();

 private:
  cv::dnn::Net net_;
  std::vector<std::string> class_list_;
  bool is_cuda_ = false;
};

#endif