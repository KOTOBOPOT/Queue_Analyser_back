#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_FRAME_VISUALIZER_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_FRAME_VISUALIZER_H_

#include <opencv2/opencv.hpp>
#include <vector>

const std::vector<cv::Scalar> kVisualizeColors = {
    cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 255),
    cv::Scalar(255, 0, 0)};
const cv::Scalar kInQueueColor = kVisualizeColors[0];
const cv::Scalar kNotInQueueColor = kVisualizeColors[1];

void visualize_queue(cv::Mat& frame, std::vector<cv::Rect> people_in_queue,
                     std::vector<cv::Rect> people_not_in_queue,
                     const cv::Rect& queue_box);

#endif  // QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_FRAME_VISUALIZER_H_