#include "router.hpp"
#include "server.hpp"
// #include "database_handler/api.hpp"  // ?
#include <boost/beast.hpp>
#include <iostream>

#include "api.hpp"
#include "bot.hpp"
#include "model.hpp"

using Response = Route::Response;
using Request = Route::Request;

int main(int argc, char* argv[]) {
  database_handler();
  bot();
  model();

  Router my_route;
  my_route.addHandler(
      "GET", "/getCurrentValue", [](const Request& req) -> Response {
        static int result = 0;
        Response res;
        res.version(req.version());
        res.result(boost::beast::http::status::ok);
        res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(boost::beast::http::field::content_type, "text/plain");
        res.set(boost::beast::http::field::access_control_allow_origin, "*");
        res.keep_alive(req.keep_alive());
        if (rand() % 2 || result == 0) {
          result += 5;
        } else {
          result -= 1;
        }
        result %= 25;
        res.body() = std::to_string(result);
        res.prepare_payload();
        return res;
      });

  //   my_route.addHandler("GET", "/path", [](const Request& req) -> Response {
  //     boost::beast::http::response<boost::beast::http::string_body> res;
  //     res.version(req.version());
  //     res.result(boost::beast::http::status::ok);
  //     res.set(boost::beast::http::field::server, "My server");
  //     res.set(boost::beast::http::field::content_type, "text/plain");
  //     res.keep_alive(req.keep_alive());
  //     res.body() = "Response body";
  //     res.prepare_payload();
  //     return res;
  //   });

  Server tst(my_route);
  tst.run();

  return 0;
}