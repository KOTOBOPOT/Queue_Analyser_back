#include "video_processor.h"

#include <opencv2/opencv.hpp>
#include <vector>

#include "cam_video.h"
#include "file_video.h"
#include "frame_visualizer.h"

VideoProcessor::VideoProcessor(std::shared_ptr<IVideoSource> vid_source,
                               const cv::Rect queue_box) {
  queueVidSource queue_vid_source = queueVidSource(vid_source, queue_box);
  queue_video_sources_.push_back(queue_vid_source);
  pic_processor_ = std::make_shared<CVPicProcessor>();
}

VideoProcessor::VideoProcessor() {
  pic_processor_ = std::make_shared<CVPicProcessor>();
}
VideoProcessor::VideoProcessor(const std::string& model_file_path) {
  pic_processor_ = std::make_shared<CVPicProcessor>(model_file_path);
}

void VideoProcessor::setVisualizeVidSourceIndex(int vid_source_index) {
  visualize_vid_source_index_ = vid_source_index;
}

void VideoProcessor::pushBackVideoSource(
    std::shared_ptr<IVideoSource> vid_source, cv::Rect queue_box) {
  queueVidSource queue_vid_source = queueVidSource(vid_source, queue_box);
  queue_video_sources_.push_back(queue_vid_source);
}

bool VideoProcessor::isVideoOpened() {
  return video_source_->isCaptureOpened();
}

std::vector<cv::Rect> VideoProcessor::getPeopleBoxes() {
  std::vector<Detection> cv_model_output;
  std::vector<cv::Rect> people_boxes;
  int people_count = 0;

  pic_processor_->getBoxes(frame_, cv_model_output);

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

std::vector<int>
VideoProcessor::getQueuePeopleAmount() {  // if video had ended returns -1
  std::vector<int> people_amount_vec;
  if (queue_video_sources_.empty()) {
    return std::vector<int>{};
  }

  std::vector<cv::Rect> people_in_queue;
  std::vector<cv::Rect> people_not_in_queue;

  for (int i = 0; i < queue_video_sources_.size(); ++i) {
    video_source_ = queue_video_sources_[i].video_source_;
    queue_box_ = queue_video_sources_[i].queue_box_;
    video_source_->getPicture(frame_);
    if (isEndOfVideo()) {
      people_amount_vec.push_back(-1);
      continue;
    }
    std::vector<cv::Rect> people_boxes = getPeopleBoxes();

    int people_amount = people_boxes.size();
    int people_in_queue_amount = 0;

    if (visualize_vid_source_index_ != i) {  // if not need to visualize
      for (int j = 0; j < people_amount; ++j) {
        auto people_box = people_boxes[j];
        if (isPersonInBox(people_box, queue_box_)) {
          ++people_in_queue_amount;
        }
      }
    } else {
      for (int j = 0; j < people_amount; ++j) {
        cv::Rect person_box = people_boxes[j];
        if (isPersonInBox(person_box, queue_box_)) {
          ++people_in_queue_amount;
          people_in_queue.push_back(person_box);
          continue;
        }
        people_not_in_queue.push_back(person_box);
      }
      visualize_queue(frame_, people_in_queue, people_not_in_queue, queue_box_);
    }

    people_amount_vec.push_back(
        people_in_queue_amount);  
  }
  return people_amount_vec;
}
bool VideoProcessor::isPersonInBox(const cv::Rect& person_box,
                                   const cv::Rect& queue_box) {

  int intersectionArea = (person_box & queue_box).area();
  //int unionArea = person_box.area() + queue_box.area() - intersectionArea;
  //double iou = (double)intersectionArea / (double)unionArea;
  return intersectionArea>0;
}

bool VideoProcessor::isEndOfVideo() { return frame_.empty(); }

void VideoProcessor::setCudaState(bool cuda_state) { is_cuda_ = cuda_state; }
