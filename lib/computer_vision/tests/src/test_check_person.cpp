// Testing is isPersonInBoxFunction from VideoProcessor
#include <gtest/gtest.h>

#include <opencv2/opencv.hpp>

#include "video_processor.h"

TEST(PersonInBoxTest, BasicCase) {
  cv::Rect queue_box = cv::Rect(300, 100, 600, 250);
  cv::Rect person_box = cv::Rect(800, 200, 600, 250);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check if no points in box
TEST(PersonInBoxTest, NoPointsInBoxCase) {
  cv::Rect queue_box = cv::Rect(0, 0, 100, 100);
  cv::Rect person_box = cv::Rect(200, 200, 100, 100);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, false);
}

// Check for Left Up Corner in Box
TEST(PersonInBoxTest, LeftUpCornerCase) {
  cv::Rect queue_box = cv::Rect(300, 100, 600, 250);
  cv::Rect person_box = cv::Rect(700, 250, 500, 350);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check for Right Up Corner in Box
TEST(PersonInBoxTest, RightUpCornerCase) {
  cv::Rect queue_box = cv::Rect(300, 200, 600, 200);
  cv::Rect person_box = cv::Rect(0, 300, 600, 300);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check for Left Down Corner in Box
TEST(PersonInBoxTest, LeftDownCornerCase) {
  cv::Rect queue_box = cv::Rect(300, 200, 600, 200);
  cv::Rect person_box = cv::Rect(600, 100, 500, 200);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check for Right Down Corner in Box
TEST(PersonInBoxTest, RightDownCornerCase) {
  cv::Rect queue_box = cv::Rect(300, 200, 600, 200);
  cv::Rect person_box = cv::Rect(200, 100, 200, 200);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check for 2 Up points in Box
TEST(PersonInBoxTest, TwoUpPointsCase) {
  cv::Rect queue_box = cv::Rect(300, 200, 600, 200);
  cv::Rect person_box = cv::Rect(500, 300, 200, 500);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check for 2 Down points in Box
TEST(PersonInBoxTest, TwoDownPointsCase) {
  cv::Rect queue_box = cv::Rect(300, 200, 600, 200);
  cv::Rect person_box = cv::Rect(500, 100, 200, 200);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check for 2 Right Side points in Box
TEST(PersonInBoxTest, TwoRightPointsCase) {
  cv::Rect queue_box = cv::Rect(300, 200, 600, 200);
  cv::Rect person_box = cv::Rect(200, 350, 200, 100);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check for 2 Left Side points in Box
TEST(PersonInBoxTest, TwoLeftPointsCase) {
  cv::Rect queue_box = cv::Rect(300, 200, 600, 200);
  cv::Rect person_box = cv::Rect(600, 250, 400, 100);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}

// Check for all points in Box
TEST(PersonInBoxTest, AllPointsCase) {
  cv::Rect queue_box = cv::Rect(300, 200, 600, 200);
  cv::Rect person_box = cv::Rect(600, 250, 100, 100);
  bool expected = VideoProcessor::isPersonInBox(person_box, queue_box);
  EXPECT_EQ(expected, true);
}
