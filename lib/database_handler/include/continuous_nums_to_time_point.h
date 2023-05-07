#ifndef QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_CONTINUOUS_NUMS_TO_TIME_POINT_H_
#define QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_CONTINUOUS_NUMS_TO_TIME_POINT_H_

#include <chrono>
#include <string>

std::chrono::system_clock::time_point continuous_nums_to_datetime(
    const std::string& str);

#endif  // QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_CONTINUOUS_NUMS_TO_TIME_POINT_H_
