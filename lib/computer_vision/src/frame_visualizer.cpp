#include "frame_visualizer.h"

#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

void visualize_queue(cv::Mat& frame, std::vector<cv::Rect> people_in_queue,
                     std::vector<cv::Rect> people_not_in_queue,
                     const cv::Rect& queue_box) {
  cv::rectangle(frame, queue_box, kInQueueColor, 3);
  for (auto person_box : people_in_queue) {
    cv::rectangle(frame, person_box, kInQueueColor, 3);
  }
  for (auto person_box : people_not_in_queue) {
    cv::rectangle(frame, person_box, kNotInQueueColor, 3);
  }
  
  cv::imshow("output", frame);
  cv::waitKey(0);//need for imshow method working


}