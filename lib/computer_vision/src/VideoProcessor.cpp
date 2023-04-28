#include "VideoProcessor.h"

#include <opencv2/opencv.hpp>
#include <vector>

VideoProcessor::VideoProcessor(const std::string& filename, size_t fps,
                               float time_period) {
  fps_ = fps;
  time_period_ = time_period;
  capture_.open(filename);  // cv::VideoCapture capture_(filename);
  if (!isCaptureOpened()) {
    std::cerr << "Error opening video file\n";
  };
  readFrame();
}
VideoProcessor::~VideoProcessor() { capture_.release(); }
void VideoProcessor::skipFrames() {
  if (isEndOfVideo()) {
    return;
  }
  skip_frames_ = time_period_ * fps_;
  size_t skipped_frames_counter = 0;
  for (; skipped_frames_counter <= skip_frames_; ++skipped_frames_counter) {
    if (isEndOfVideo()) {
      std::cout << "Video Has Ended" << std::endl;
      return;
    }
    readFrame();
  }
}
bool VideoProcessor::isCaptureOpened() { return capture_.isOpened(); }
int VideoProcessor::getPeopleAmount() {  // if video had ended returns -1
  std::vector<Detection> output;
  int people_count = 0;
  skipFrames();

  if (isEndOfVideo()) {
    return -1;
  }

  pic_processor_.getBoxes(frame_, output);

  int detections = output.size();

  for (int i = 0; i < detections; ++i) {
    auto detection = output[i];
    auto box = detection.box;
    auto classId = detection.class_id;
    if (classId != kPeopleClassId) {  // Skip all not people classes
      continue;
    }

    //    if(queue_box_.contains())
    
    const auto color_queue =
        cv::Scalar(0, 0, 255);  // colors[classId % colors.size()];
    const auto color_not_queue =
        cv::Scalar(0, 255, 255);  // colors[classId % colors.size()];
    if (isPersonInBox(box)) {
     // cv::rectangle(frame_, box, color_queue, 3);
      ++people_count;
    } else {
     // cv::rectangle(frame_, box, color_not_queue, 3);
    }

    // cv::rectangle(frame_, cv::Point(box.x, box.y - 20),
    //               cv::Point(box.x + box.width, box.y), color, cv::FILLED);
    
   // cv::putText(frame_, "person", cv::Point(box.x, box.y - 5),
    //            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
   // cv::rectangle(frame_, queue_box_, color_queue, 3);
  }

  return people_count;
}
bool VideoProcessor::isPersonInBox(cv::Rect& person_box) {
  size_t person_box_width = person_box.width;
  size_t person_box_height = person_box.height;
  size_t person_box_x = person_box.x;
  size_t person_box_y = person_box.y;

  cv::Point left_up_point = cv::Point(person_box_x, person_box_y);
  cv::Point left_down_point =
      cv::Point(person_box_x, person_box_y + person_box_height);
  cv::Point right_up_point =
      cv::Point(person_box_x + person_box_width, person_box_y);
  cv::Point right_down_point = cv::Point(person_box_x + person_box_width,
                                         person_box_y + person_box_height);

  // bool contains_at_least_one_point = false;
  bool contains_at_least_one_point = queue_box_.contains(left_up_point);
  contains_at_least_one_point =
      contains_at_least_one_point | queue_box_.contains(left_down_point);
  contains_at_least_one_point =
      contains_at_least_one_point | queue_box_.contains(right_up_point);
  contains_at_least_one_point =
      contains_at_least_one_point | queue_box_.contains(right_down_point);
  return contains_at_least_one_point;
}
void VideoProcessor::updateTimePeriod(float time_period) {
  if (time_period >= 0) {
    time_period_ = time_period;
  }
}
bool VideoProcessor::isEndOfVideo() {
  return frame_.empty();
}  // frame_.empty();}//!isCaptureOpened(); }
void VideoProcessor::setCudaState(bool cuda_state) { is_cuda_ = cuda_state; }
void VideoProcessor::readFrame() { capture_.read(frame_); }

// void VideoProcessor::initModel(){load_net(net_, is_cuda_);}