#include <gtest/gtest.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include "continuous_nums_to_time_point.h"
#include "string_to_time_point.h"
#include "database_exceptions/invalid_format_exc.h"

TEST(ContinuousNumsConversionTest, BasicTest) {
  std::string time_str = "20220224053000000";
  auto actual_time = continuous_nums_to_datetime(time_str);
  auto exp_time = std::chrono::system_clock::from_time_t(1645669800);

  EXPECT_EQ(exp_time, actual_time);
}

TEST(ContinuousNumsConversionTest, InvalidFormatTest) {
  std::string time_str = "202202240530000009";
  EXPECT_THROW(continuous_nums_to_datetime(time_str), InvalidFormatException);
}

TEST(ISONumsConversionTest, BasicTest) {
  std::string time_str = "2022-02-24 05:30:00.000";
  auto actual_time = string_to_datetime(time_str);
  auto exp_time = std::chrono::system_clock::from_time_t(1645669800);

  EXPECT_EQ(exp_time, actual_time);
}
