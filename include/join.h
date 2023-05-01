#ifndef QUEUE_ANALYZER_INCLUDE_JOIN_H_
#define QUEUE_ANALYZER_INCLUDE_JOIN_H_

#include <string>

template <typename Iterator>
std::string join(Iterator begin, Iterator end, char separator = '.') {
  std::ostringstream o;
  if (begin != end) {
    o << *begin++;
    for (; begin != end; ++begin) o << separator << *begin;
  }
  return o.str();
}

#endif  // QUEUE_ANALYZER_INCLUDE_JOIN_H_
