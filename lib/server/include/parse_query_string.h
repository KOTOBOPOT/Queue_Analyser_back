#ifndef QUEUE_ANALYSER_LIB_SERVER_INCLUDE_PARSE_QUERY_STRING_H_
#define QUEUE_ANALYSER_LIB_SERVER_INCLUDE_PARSE_QUERY_STRING_H_

#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> parseQueryString(
    const std::string& queryString);

#endif  // QUEUE_ANALYSER_LIB_SERVER_INCLUDE_PARSE_QUERY_STRING_H_
