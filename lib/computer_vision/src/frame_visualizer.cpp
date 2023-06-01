#include "frame_visualizer.h"

#include <opencv2/opencv.hpp>
#include <vector>

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
  cv::namedWindow( "output",cv::WindowFlags::WINDOW_NORMAL); //make window size changeble
  cv::resizeWindow("output", 900, 600); //Setting size of window
  cv::imshow("output", frame);
  cv::waitKey(1);  // need for imshow method working

}