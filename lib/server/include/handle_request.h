#ifndef QUEUE_ANALYSER_SERVER_HANDLE_REQUEST_H_
#define QUEUE_ANALYSER_SERVER_HANDLE_REQUEST_H_
#include <boost/beast.hpp>
#include <iostream>

#include "error.h"
#include "generate_response.h"
#include "route.h"
#include "router.h"

static int result = 0;

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template <class Body, class Allocator, class Send>
void handleRequest(Router& router, boost::beast::string_view doc_root,
                   boost::beast::http::request<
                       Body, boost::beast::http::basic_fields<Allocator>>&& req,
                   Send&& send) {
  // Make sure we can handle the method
  // Returns a bad request response
  if (req.method() != boost::beast::http::verb::get &&
      req.method() != boost::beast::http::verb::head)
    return send(generateResponse<StringResponse>(
        req, StringResponse{"Unknown HTTP-method"},
        boost::beast::http::status::bad_request));

  // Request path must be absolute and not contain "..".
  if (req.target().empty() || req.target()[0] != '/' ||
      req.target().find("..") != boost::beast::string_view::npos)
    return send(generateResponse<StringResponse>(
        req, StringResponse{"Illegal request-target"},
        boost::beast::http::status::bad_request));

  // Try find handler for request
  auto handle = router.findHandler(req);
  if (handle.has_value()) {
    Route::Response response = handle.value()(req);
    return send(std::move(response));
  }

  // Build the path to the requested file
  std::string path = path_cat(doc_root, req.target());
  if (req.target().back() == '/') path.append("index.html");

  // Attempt to open the file
  boost::beast::error_code ec;
  boost::beast::http::file_body::value_type body;
  body.open(path.c_str(), boost::beast::file_mode::scan, ec);

  // Handle the case where the file doesn't exist
  // Returns a not found response
  if (ec == boost::beast::errc::no_such_file_or_directory)
    return send(generateResponse<StringResponse>(
        req,
        StringResponse{"The resource '" + std::string(req.target()) +
                       "' was not found."},
        boost::beast::http::status::internal_server_error));

  // Handle an unknown error
  // Returns a not found response
  if (ec)
    return send(generateResponse<StringResponse>(
        req, StringResponse{std::string(ec.message())},
        boost::beast::http::status::internal_server_error));

  // Cache the size since we need it after the move
  auto const size = body.size();

  // Respond to HEAD request
  if (req.method() == boost::beast::http::verb::head) {
    boost::beast::http::response<boost::beast::http::empty_body> res{
        boost::beast::http::status::ok, req.version()};
    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(boost::beast::http::field::content_type, mime_type(path));
    res.content_length(size);
    res.keep_alive(req.keep_alive());
    return send(std::move(res));
  }

  // Respond to GET request
  boost::beast::http::response<boost::beast::http::file_body> res{
      std::piecewise_construct, std::make_tuple(std::move(body)),
      std::make_tuple(boost::beast::http::status::ok, req.version())};
  res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
  res.set(boost::beast::http::field::content_type, mime_type(path));
  res.content_length(size);
  res.keep_alive(req.keep_alive());
  return send(std::move(res));
}

#endif  // QUEUE_ANALYSER_SERVER_HANDLE_REQUEST_H_