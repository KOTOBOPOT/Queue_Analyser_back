#include <boost/beast.hpp>
#include <iostream>

#include "api.hpp"
#include "bot.hpp"
#include "generate_response.hpp"
#include "model.hpp"
#include "router.hpp"
#include "server.hpp"
// #include "database_handler/api.hpp"  // ?
using Response = Route::Response;
using Request = Route::Request;

int main(int argc, char* argv[]) {
  database_handler();
  bot();
  model();

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

  rt.addHandler("GET", "/getTen", [](const Request& req) {
    return generateResponse<StringResponse>(req,
                                            StringResponse{"getTen query 10"});
  });

  rt.addHandler("POST", "/getTwo", [](const Request& req) {
    return generateResponse<StringResponse>(req,
                                            StringResponse{"getTwo query 2"});
  });

  Server tst(rt);
  tst.run();

  return 0;
}