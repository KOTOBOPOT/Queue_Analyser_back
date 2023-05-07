#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "../include/continuous_nums_to_time_point.h"
#include "../include/database_exceptions/invalid_format_exc.h"
#include "../include/database_exceptions/reformat_exc.h"

bool is_number(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
                                    s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

std::chrono::system_clock::time_point continuous_nums_to_datetime(const std::string& str) {
  std::tm tm = {};

  if (str.length() != 17 || !is_number(str)) {
    throw InvalidFormatException("Invalid string length: " + str + " (must be 17 characters long)");
  }

  std::stringstream ss;
  ss << str.substr(0, 4) << '-' << str.substr(4, 2) << '-' << str.substr(6, 2) << ' '; // date
  ss << str.substr(8, 2) << ':' << str.substr(10, 2) << ':' << str.substr(12, 2) << '.' << str.substr(14, 3); // time

  char decimal_point;
  int milliseconds;

  ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S") >> decimal_point >> milliseconds;
  if (ss.fail() || decimal_point != '.') {
    throw ReformatException("Failed to parse the custom format string: " + str);
  }

  auto time_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(std::mktime(&tm)));
  time_since_epoch += std::chrono::milliseconds(milliseconds);
  return std::chrono::system_clock::time_point(time_since_epoch);
}