#ifndef QUEUE_ANALYZER_INCLUDE_JOIN_H_
#define QUEUE_ANALYZER_INCLUDE_JOIN_H_

#include <string>

template <typename Iterator>
std::string join(Iterator begin, Iterator end, char separator = '.') {
  std::ostringstream result;
  if (begin != end) {
    result << *begin++;
    for (; begin != end; ++begin) result << separator << *begin;
  }
  return result.str();
}

#endif  // QUEUE_ANALYZER_INCLUDE_JOIN_H_
