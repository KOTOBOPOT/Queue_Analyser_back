#include <boost/beast.hpp>
#include <iostream>

#include "generate_response.h"
#include "parse_query_string.h"
#include "router.h"
#include "server.h"
// #include "database_handler/api.hpp"  // ?
using Response = Router::Response;
using Request = Router::Request;

int main(int argc, char* argv[]) {
  Router rt;
  rt.addHandler("GET", "/getCurrentValue", [](const Request& req) -> Response {
    static int result = 0;
    if (rand() % 2 || result == 0) {
      result += 5;
    } else {
      result -= 1;
    }
    result %= 25;
    return generateResponse<StringResponse>(
        req, StringResponse{std::to_string(result)});
  });

  rt.addHandler("GET", "/getFromDb", [](const Request& req) {
    auto target = req.target().to_string();
    auto pos = target.find("?");
    std::string result = "getFromDb query";
    if (pos != std::string::npos) {
      std::string queryString = target.substr(pos + 1);
      auto params = parseQueryString(queryString);
      auto it = params.find("period");
      if (it != params.end()) {
        result += "\nperiod : " + it->second;
      } else {
        return generateResponse<StringResponse>(
            req, StringResponse{"Missing required parameter 'period'"},
            boost::beast::http::status::bad_request);
      }
    }
    return generateResponse<StringResponse>(req, StringResponse{result});
  });

  Server tst(rt);
  tst.run();

  return 0;
}