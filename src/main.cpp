#include <boost/beast.hpp>
#include <iostream>

#include "generate_response.h"
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

  rt.addHandler("GET", "/getTen", [](const Request& req) {
    std::string result = "getTen query 10";
    auto target = req.target().to_string();
    auto pos = target.find("?");  // ищем позицию символа "?"
    if (pos != std::string::npos) {
      std::string query_string = target.substr(pos + 1);  // извлекаем строку параметров
      std::istringstream ss(query_string);  // создаем строковый поток
      std::string param_name, param_value;
      while (std::getline(ss, param_name, '=') && std::getline(ss, param_value, '&')) {
        result += "\n" + param_name + " : " + param_value;  // добавляем параметр в строку результата
      }
    }
    return generateResponse<StringResponse>(req, StringResponse{result});
  });

  rt.addHandler("POST", "/getTwo", [](const Request& req) {
    return generateResponse<StringResponse>(req,
                                            StringResponse{"getTwo query 2"});
  });

  Server tst(rt);
  tst.run();

  return 0;
}