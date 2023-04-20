#include <boost/beast/http.hpp>
#include <optional>
#include <vector>

#pragma once
#include "route.hpp"

class Router {
 public:
  void addHandler(std::string method, std::string path,
                  Route::Handler handler) {
    routes_.emplace_back(std::move(method), std::move(path),
                         std::move(handler));
  }

  std::optional<Route::Handler> findHandler(const Route::Request& req) const {
    for (const auto& route : routes_) {
      if (route.method() == req.method_string() &&
          route.path() == req.target()) {
        return route.handler();
      }
    }
    return std::nullopt;
  }

 private:
  std::vector<Route> routes_;
};