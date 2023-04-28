#include "parse_query_string.h"

#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> parseQueryString(
    const std::string& queryString) {
  std::unordered_map<std::string, std::string> params;
  std::istringstream ss(queryString);
  std::string param;
  while (std::getline(ss, param, '&')) {
    auto pos = param.find('=');
    if (pos != std::string::npos) {
      params.emplace(param.substr(0, pos), param.substr(pos + 1));
    }
  }
  return params;
}