#include "../include/continuous_nums_to_time_point.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/database_exceptions/invalid_format_exc.h"
#include "../include/database_exceptions/reformat_exc.h"

bool is_number(const std::string& str) {
  return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c) {
                         return !std::isdigit(c);
                       }) == str.end();
}

std::chrono::system_clock::time_point continuous_nums_to_datetime(
    const std::string& str) {
  std::tm tm = {};

  if (str.length() != 17 || !is_number(str)) {
    throw InvalidFormatException("Invalid string length: " + str + " (must be 17 characters long)");
  }

  std::stringstream date_ss;
  date_ss << str.substr(0, 4) << '-' << str.substr(4, 2) << '-' << str.substr(6, 2)
     << ' ';  // date
  date_ss << str.substr(8, 2) << ':' << str.substr(10, 2) << ':' << str.substr(12, 2)
     << '.' << str.substr(14, 3);  // time

  char decimal_point;
  int milliseconds;

  date_ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S") >> decimal_point >>
          milliseconds;
  if (date_ss.fail() || decimal_point != '.') {
    throw ReformatException("Failed to parse the custom format string: " + str);
  }

  auto time_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::seconds(std::mktime(&tm)));
  time_since_epoch += std::chrono::milliseconds(milliseconds);
  return std::chrono::system_clock::time_point(time_since_epoch);
}