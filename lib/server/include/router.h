#ifndef QUEUE_ANALYSER_LIB_SERVER_INCLUDE_ROUTER_H_
#define QUEUE_ANALYSER_LIB_SERVER_INCLUDE_ROUTER_H_

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <memory>
#include <optional>
#include <vector>

#include "sqlite_handler.h"

class Router {
 public:
  using Request = boost::beast::http::request<boost::beast::http::string_body>;
  using Response =
      boost::beast::http::response<boost::beast::http::string_body>;
  using Handler = std::function<boost::beast::http::response<
      boost::beast::http::string_body>(const Request& req)>;
  struct Route {
    Route(std::string&& _method, std::string&& _path, Handler&& _handler)
        : method(std::move(_method)),
          path(std::move(_path)),
          handler(std::move(_handler)) {}

    std::string method;
    std::string path;
    Handler handler;
  };

  Router(std::shared_ptr<IDataSource> db_handler)
      : db_handler_(std::move(db_handler)){};

  // move constructor
  Router(Router&& other) noexcept : routes_(std::move(other.routes_)) {}

  // move assignment operator
  Router& operator=(Router&& other) noexcept {
    routes_ = std::move(other.routes_);
    return *this;
  }

  void addHandler(std::string method, std::string path, Handler handler) {
    routes_.emplace_back(std::move(method), std::move(path),
                         std::move(handler));
  }

  std::optional<Handler> findHandler(const Request& req) const;

  std::shared_ptr<IDataSource> db_handler_;

 private:
  std::vector<Route> routes_;
};

#endif  // QUEUE_ANALYSER_LIB_SERVER_INCLUDE_ROUTER_H_