#ifndef QUEUE_ANALYSER_SERVER_ROUTER_H_
#define QUEUE_ANALYSER_SERVER_ROUTER_H_
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <optional>
#include <vector>

#include "route.h"

class Router {
 public:
  Router() = default;

  // move constructor
  Router(Router&& other) noexcept : routes_(std::move(other.routes_)) {}

  // move assignment operator
  Router& operator=(Router&& other) noexcept {
    routes_ = std::move(other.routes_);
    return *this;
  }

  void addHandler(std::string method, std::string path,
                  Route::Handler handler) {
    routes_.emplace_back(std::move(method), std::move(path),
                         std::move(handler));
  }

  std::optional<Route::Handler> findHandler(const Route::Request& req) const;

 private:
  std::vector<Route> routes_;
};

#endif  // QUEUE_ANALYSER_SERVER_ROUTER_H_