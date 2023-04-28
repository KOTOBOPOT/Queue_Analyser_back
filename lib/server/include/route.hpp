#ifndef QUEUE_ANALYSER_SERVER_ROUTE_H_
#define QUEUE_ANALYSER_SERVER_ROUTE_H_
#include <functional>
#include <string>

class Route {
 public:
  using Request = boost::beast::http::request<boost::beast::http::string_body>;
  using Response =
      boost::beast::http::response<boost::beast::http::string_body>;
  using Handler = std::function<boost::beast::http::response<
      boost::beast::http::string_body>(const Request& req)>;

  Route(std::string method, std::string path, Handler handler)
      : method_(std::move(method)),
        path_(std::move(path)),
        handler_(std::move(handler)) {}

  const std::string& method() const { return method_; }
  const std::string& path() const { return path_; }
  const Handler& handler() const { return handler_; }

 private:
  std::string method_;
  std::string path_;
  Handler handler_;
};

#endif  // QUEUE_ANALYSER_SERVER_ROUTE_H_