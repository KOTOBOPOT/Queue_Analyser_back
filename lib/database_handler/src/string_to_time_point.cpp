/**
 * @file string_to_time_point.cpp
 * @brief В этом файле описана функция перевода строки со временем в time_point
 * @author Михаил Овакимян (DaMagus26)
 */

#include "../include/string_to_time_point.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::chrono::system_clock::time_point string_to_datetime(
    const std::string& str) {
  std::tm tm = {};
  std::istringstream ss(str);
  char decimal_point;
  int milliseconds;

  ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S") >> decimal_point >>
      milliseconds;
  if (ss.fail() || decimal_point != '.') {
    std::cerr << "Failed to parse the custom format string: " << str
              << std::endl;
    return std::chrono::system_clock::time_point::min();
  }

  auto time_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::seconds(std::mktime(&tm)));
  time_since_epoch += std::chrono::milliseconds(milliseconds);
  return std::chrono::system_clock::time_point(time_since_epoch);
}