#include "video_processor.h"

#include <opencv2/opencv.hpp>
#include <vector>

#include "cam_video.h"
#include "file_video.h"
VideoProcessor::VideoProcessor(std::vector<queueVidSource> vid_sources) {
  video_source_ =
      vid_sources[0].vid_source_;  // Пока для одного объекта сделал, потом
                                   // сделаю для нескольких
  queue_box_ = vid_sources[0].queue_box_;
}

bool VideoProcessor::isVideoOpened() {
  return video_source_->isCaptureOpened();
}

std::vector<cv::Rect> VideoProcessor::getPeopleBoxes() {
  std::vector<Detection> cv_model_output;
  std::vector<cv::Rect> people_boxes;
  int people_count = 0;

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

std::vector<int> VideoProcessor::getQueuePeopleAmount() {  // if video had ended returns -1
  video_source_->getPicture(frame_);
  if (isEndOfVideo()) {
    return std::vector<int>{-1};
  }
  std::vector<cv::Rect> people_boxes = getPeopleBoxes();

  size_t people_amount = people_boxes.size();
  int people_in_queue_amount = 0;

  for (int i = 0; i < people_amount; ++i) {
    auto people_box = people_boxes[i];
    if (isPersonInBox(people_box)) {
      ++people_in_queue_amount;
    }
  }
  return std::vector<int>{people_in_queue_amount};//Пока для одного объекта. Это задел на будущее
}
bool VideoProcessor::isPersonInBox(const cv::Rect& person_box,
                                   const cv::Rect& queue_box) {
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

bool VideoProcessor::isEndOfVideo() { return frame_.empty(); }

void VideoProcessor::setCudaState(bool cuda_state) { is_cuda_ = cuda_state; }
