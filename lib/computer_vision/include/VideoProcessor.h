#include <opencv2/opencv.hpp>
#include <string>

#include "CVPicProcessor.h"

//TODO: сделать интерфейс взаимодействия с видеоданными. 
//Решение предыдущей проблемы с тем, что time_period - не используется в видео с камеры:
// Тупо сделать так, чтобы тайм период задавался только в  файловом(а не камера) конструкторе 
//VideoProcessor и нигде не сохранялся кроме
// как в объекте FileVideoSource. 
class VideoProcessor {
 public:
  VideoProcessor(const std::string& filename, size_t fps = 28,
                 float time_period = 0);  // Means that each 0.5 sec get measure
  ~VideoProcessor();
  int getPeopleAmount();
  void updateTimePeriod(float time_period);
  void setCudaState(bool cuda_state);

 public:
  void readFrame();
  bool isCaptureOpened();
  bool isEndOfVideo();
  void skipFrames();
  bool isPersonInBox(cv::Rect& person_box);
 public:
  cv::Mat frame_;             // Current frame
  cv::VideoCapture capture_;  // Video source
 private:
  CVPicProcessor pic_processor_ = CVPicProcessor();
  bool is_cuda_ = false;
  float time_period_;
  size_t fps_;
  size_t skip_frames_ = 0;  // for videofiles
  cv::Rect queue_box_ = cv::Rect(100, 0, 650, 250);
};
