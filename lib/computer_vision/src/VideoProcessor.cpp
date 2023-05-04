#include <opencv2/opencv.hpp>
#include <vector>

#include "CamVideo.h"
#include "FileVideo.h"
#include "VideoProcessor.h"

VideoProcessor::VideoProcessor(const std::string& filename, size_t fps,
                               float time_period, const cv::Rect& queue_box) {
  video_source_ = std::make_shared<FileVideo>(filename, fps, time_period);
  queue_box_ = queue_box;
  
}

VideoProcessor::VideoProcessor(int camera_index, const cv::Rect& queue_box) {
  video_source_ = std::make_shared<CamVideo>(camera_index);
  queue_box_ = queue_box;
}

bool VideoProcessor::isVideoOpened() {
  return video_source_->isCaptureOpened();
}

std::vector<cv::Rect> VideoProcessor::getPeopleBoxes() {
  std::vector<Detection> cv_model_output;
  std::vector<cv::Rect> people_boxes;
  int people_count = 0;
  video_source_->getPicture(frame_);

  pic_processor_.getBoxes(frame_, cv_model_output);

  int detections = cv_model_output.size();

  for (int i = 0; i < detections; ++i) {
    auto detection = cv_model_output[i];
    auto box = detection.box;
    auto classId = detection.class_id;
    if (classId == kPeopleClassId) {
      people_boxes.push_back(box);  // Add people classes boxes
    }
  }
  return people_boxes;
}

int VideoProcessor::getQueuePeopleAmount() {  // if video had ended returns -1
  std::vector<cv::Rect> people_boxes = getPeopleBoxes();

  if (isEndOfVideo()) {
    return -1;
  }

  size_t people_amount = people_boxes.size();
  int people_in_queue_amount = 0;

  for (int i = 0; i < people_amount; ++i) {
    auto people_box = people_boxes[i];
    if (isPersonInBox(people_box)) {
      ++people_in_queue_amount;
    }
  }
  return people_in_queue_amount;
}
bool VideoProcessor::isPersonInBox(const cv::Rect& person_box, const cv::Rect& queue_box) {
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
  bool contains_at_least_one_point = queue_box.contains(left_up_point);
  contains_at_least_one_point =
      contains_at_least_one_point | queue_box.contains(left_down_point);
  contains_at_least_one_point =
      contains_at_least_one_point | queue_box.contains(right_up_point);
  contains_at_least_one_point =
      contains_at_least_one_point | queue_box.contains(right_down_point);
  return contains_at_least_one_point;
}

bool VideoProcessor::isEndOfVideo() {
  return frame_.empty();
}  

void VideoProcessor::setCudaState(bool cuda_state) { is_cuda_ = cuda_state; }

