#ifndef QUEUE_ANALYSER_LIB_SERVER_INCLUDE_ERROR_H_
#define QUEUE_ANALYSER_LIB_SERVER_INCLUDE_ERROR_H_
#include <boost/beast.hpp>
#include <iostream>

// Report a failure
void fail(boost::beast::error_code ec, char const* what);

#endif  // QUEUE_ANALYSER_LIB_SERVER_INCLUDE_ERROR_H_
