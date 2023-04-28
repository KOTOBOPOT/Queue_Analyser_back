#include <opencv2/opencv.hpp>

const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;
const float SCORE_THRESHOLD = 0.2;
const float NMS_THRESHOLD = 0.4;
const float CONFIDENCE_THRESHOLD = 0.4;
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
  void initModel();
  void detect(cv::Mat &image, cv::dnn::Net &net, std::vector<Detection> &output,
              const std::vector<std::string> &className);
  void load_net(cv::dnn::Net &net, bool is_cuda);  
  cv::Mat format_yolov5(const cv::Mat &source);
  std::vector<std::string> load_class_list(); 
 private:
  cv::dnn::Net net_;
  std::vector<std::string> class_list_;
  bool is_cuda_ = false;
};
