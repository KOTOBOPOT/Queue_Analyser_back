#include "routes.h"

#include <memory>

#include "generate_response.h"
#include "join.h"
#include "parse_query_string.h"
#include "router.h"
#include "sqlite_handler.h"
#include "string_to_time_point.h"

using Response = Router::Response;
using Request = Router::Request;

std::unique_ptr<Router> getRouter() {
  auto rt = std::make_unique<Router>();
  rt->addHandler("GET", "/getCurrentValue", [](const Request& req) -> Response {
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

  rt->addHandler("GET", "/getFromDb", [](const Request& req) {
    auto target = req.target().to_string();
    auto pos = target.find("?");
    std::string result = "getFromDb query";
    if (pos != std::string::npos) {
      std::string queryString = target.substr(pos + 1);
      auto params = parseQueryString(queryString);
      auto it = params.find("period");
      if (it != params.end()) {
        // Примерный вид работы с БД
        auto param_1 = string_to_datetime(
            "2023-04-21 15:48:21.002");  // На место "..." нужно вставить
                                         // начальное время интервала в формате
                                         // YYYY-MM-DD HH:MM:SS.sss
        auto param_2 = string_to_datetime(
            "2023-04-21 15:52:41.762");  // На место "..." нужно вставить
                                         // конечное время интервала в формате
                                         // YYYY-MM-DD HH:MM:SS.sss

        SQLiteHandler db_handler(
            "lib/database_handler/database/db.db");  // Вероятно это стоит
                                                     // вынести в конструктор
                                                     // Router и сделать его
                                                     // полем
        auto entries = db_handler.selectEntriesOverInterval(
            param_1,
            param_2);  // В entries сохраняется вектор чисел, снимков очереди
        result = join(entries.begin(), entries.end(),
                      ',');  // Здесь массив преобразуется в строку чисел,
                             // разделенных пробелами

        result += "\nperiod : " + it->second;
      } else {
        return generateResponse<StringResponse>(
            req, StringResponse{"Missing required parameter 'period'"},
            boost::beast::http::status::bad_request);
      }
    }
    return generateResponse<StringResponse>(req, StringResponse{result});
  });

  return rt;
}