#include "cv_pic_processor.h"

#include <fstream>
#include <iostream>

#include "../include/computer_vision_exceptions/file_open_exc.h"

CVPicProcessor::CVPicProcessor() {
  class_list_ = loadClassList();
  loadNet(net_, is_cuda_);
}

void CVPicProcessor::loadNet(cv::dnn::Net &net, bool is_cuda) {
  auto result = cv::dnn::readNet("/app/static/model/yolov5s.onnx");
  if (is_cuda_) {
    // Attempt to use CUDA
    result.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    result.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
  } else {
    // Running on CPU
    result.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    result.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
  }
  net = result;
}

cv::Mat CVPicProcessor::formatYoloV5(const cv::Mat &source) {
  int col = source.cols;
  int row = source.rows;
  int _max = MAX(col, row);
  cv::Mat result = cv::Mat::zeros(_max, _max, CV_8UC3);
  source.copyTo(result(cv::Rect(0, 0, col, row)));
  return result;
}

void CVPicProcessor::getBoxes(cv::Mat &image, std::vector<Detection> &output) {
  detect(image, net_, output, class_list_);
}

void CVPicProcessor::detect(cv::Mat &image, cv::dnn::Net &net,
                            std::vector<Detection> &output,
                            const std::vector<std::string> &className) {
  cv::Mat blob;

  auto input_image = formatYoloV5(image);

  cv::dnn::blobFromImage(input_image, blob, 1. / 255.,
                         cv::Size(kInputWidth, kInputHeight), cv::Scalar(),
                         true, false);
  net.setInput(blob);
  std::vector<cv::Mat> outputs;
  net.forward(outputs, net.getUnconnectedOutLayersNames());

  float x_factor = input_image.cols / kInputWidth;
  float y_factor = input_image.rows / kInputHeight;

  float *data = (float *)outputs[0].data;

  const int kDimensionsAmount = 85;
  const int kRowsAmount = 25200;

  std::vector<int> class_ids;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;

  for (int i = 0; i < kRowsAmount; ++i) {
    float confidence = data[4];
    if (confidence >= kConfidenceThreshold) {
      float *classes_scores = data + 5;
      cv::Mat scores(1, className.size(), CV_32FC1, classes_scores);
      cv::Point class_id;
      double max_class_score;
      minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
      if (max_class_score > kScoreThreshold) {
        confidences.push_back(confidence);

        class_ids.push_back(class_id.x);

        float x = data[0];
        float y = data[1];
        float w = data[2];
        float h = data[3];
        int left = int((x - 0.5 * w) * x_factor);
        int top = int((y - 0.5 * h) * y_factor);
        int width = int(w * x_factor);
        int height = int(h * y_factor);
        boxes.push_back(cv::Rect(left, top, width, height));
      }
    }

    data += kDimensionsAmount;
  }

  std::vector<int> nms_result;
  cv::dnn::NMSBoxes(boxes, confidences, kScoreThreshold, kNmsThreshold,
                    nms_result);
  for (int i = 0; i < nms_result.size(); i++) {
    int idx = nms_result[i];
    Detection result;
    result.class_id = class_ids[idx];
    result.confidence = confidences[idx];
    result.box = boxes[idx];
    output.push_back(result);
  }
}

std::vector<std::string> CVPicProcessor::loadClassList() {
  std::vector<std::string> class_list;
  std::ifstream ifs("/app/static/model/classes.txt");
  if (!ifs) {
    throw FileOpenException(
        "Failed to load classes file for detection");
  }
  std::string line;
  while (getline(ifs, line)) {
    class_list.push_back(line);
  }
  ifs.close();
  return class_list;
}