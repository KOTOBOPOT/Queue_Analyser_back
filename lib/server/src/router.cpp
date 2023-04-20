#include "router.hpp"

#include <optional>

std::optional<Route::Handler> Router::findHandler(
    const Route::Request& req) const {
  for (const auto& route : routes_) {
    if (route.method() == req.method_string() && route.path() == req.target()) {
      return route.handler();
    }
  }
  return std::nullopt;
}