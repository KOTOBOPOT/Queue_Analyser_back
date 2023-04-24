#include "router.h"

#include <boost/beast.hpp>
#include <optional>

#include "generate_response.h"

std::optional<Router::Handler> Router::findHandler(
    const Router::Request& req) const {
  for (const auto& route : routes_) {
    if (route.method == req.method_string() && route.path == req.target()) {
      return route.handler;
    }
  }
  return std::nullopt;
}