#ifndef QUEUE_ANALYSER_SERVER_GENERATE_RESPONSE_H_
#define QUEUE_ANALYSER_SERVER_GENERATE_RESPONSE_H_
#include "route.hpp"

using Response = Route::Response;
using Request = Route::Request;

struct StringResponse : public std::string {
  static constexpr const char* contentType = "text/plain";
};

template<typename T>
Response generateResponse(const Request& req, const T& content) {
  Response res;
  res.version(req.version());
  res.result(boost::beast::http::status::ok);
  res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
  res.set(boost::beast::http::field::content_type, T::contentType);
  res.set(boost::beast::http::field::access_control_allow_origin, "*");
  res.keep_alive(req.keep_alive());
  res.body() = content;
  res.prepare_payload();
  return res;
}

#endif  // QUEUE_ANALYSER_SERVER_GENERATE_RESPONSE_H_