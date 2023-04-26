#include "router.h"

#include <boost/beast.hpp>
#include <optional>
#include <iostream>

#include "generate_response.h"

std::optional<Router::Handler> Router::findHandler(
    const Router::Request& req) const {
  std::string target = req.target().to_string();  // преобразуем URI в строку
  target = target.substr(0, target.find("?"));

  for (const auto& route : routes_) {
    if (route.method == req.method_string() && route.path == target) {
      return route.handler;
    }
  }
  return std::nullopt;
}