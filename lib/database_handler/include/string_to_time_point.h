/**
 * @file string_to_time_point.h
 * @brief В этом файле описана функция перевода строки со временем в time_point
 * @author Михаил Овакимян (DaMagus26)
 */

#ifndef QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_STRING_TO_TIME_POINT_H_
#define QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_STRING_TO_TIME_POINT_H_

#include <chrono>
#include <string>

std::chrono::system_clock::time_point string_to_datetime(
    const std::string& str);

#endif  // QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_STRING_TO_TIME_POINT_H_
