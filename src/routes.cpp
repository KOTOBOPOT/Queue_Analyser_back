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

std::unique_ptr<Router> getRouter(const std::string& path_to_db) {
  auto rt =
      std::make_unique<Router>(std::make_shared<SQLiteHandler>(path_to_db));

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

  rt->addHandler("GET", "/getFromDb", [&rt](const Request& req) {
    auto target = req.target().to_string();
    auto pos = target.find("?");

    if (pos != std::string::npos) {
      std::string queryString = target.substr(pos + 1);
      auto params = parseQueryString(queryString);
      auto start = params.find("period");
      if (start != params.end()) {
        // Примерный вид работы с БД
        auto param_1 = string_to_datetime(
            start->second);  // На место "..." нужно вставить
                             // начальное время интервала в формате
                             // YYYY-MM-DD HH:MM:SS.sss 20230421154821002
        auto param_2 = string_to_datetime(
            "2023-04-21 15:52:41.762");  // На место "..." нужно вставить
                                         // конечное время интервала в формате
                                         // 20230421154821002
        auto entries = rt->db_handler_->selectEntriesOverInterval(
            param_1,
            param_2);  // В entries сохраняется вектор чисел, снимков очереди
        std::string result = join(entries.begin(), entries.end(),
                                  ',');  // Здесь массив преобразуется в строку
                                         // чисел, разделенных пробелами

        result += "\nperiod : " + start->second;
        return generateResponse<StringResponse>(req, StringResponse{result});
      } else {
        return generateResponse<StringResponse>(
            req, StringResponse{"Missing required parameter 'period'"},
            boost::beast::http::status::bad_request);
      }
    }
    return generateResponse<StringResponse>(
        req, StringResponse{"Missing required parameter 'period'"},
        boost::beast::http::status::bad_request);
  });

  return rt;
}