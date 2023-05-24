#include "routes.h"

#include <memory>
#include <nlohmann/json.hpp>

#include "continuous_nums_to_time_point.h"
#include "generate_response.h"
#include "parse_query_string.h"
#include "router.h"
#include "sqlite_handler.h"

using json = nlohmann::json;
using Response = Router::Response;
using Request = Router::Request;

std::unique_ptr<Router> getRouter(const std::string& path_to_db) {
  auto rt =
      std::make_unique<Router>(std::make_shared<SQLiteHandler>(path_to_db));

  rt->addHandler("GET", "/getFromDb", [&rt](const Request& req) {
    try {
      auto params = parseQueryString(req.target().to_string());

      if (params.find("start") == params.end() ||
          params.find("end") == params.end()) {
        StringResponse msg("Missing required parameter 'start' or 'end'");
        return generateResponse(req, msg,
                                boost::beast::http::status::bad_request);
      }

      // начальное время интервала в формате
      // YYYYMMDDHHMMSSsss 20230421154821002
      auto start = continuous_nums_to_datetime(params["start"]);
      auto end = continuous_nums_to_datetime(params["end"]);

      json jsonObj = rt->db_handler_->selectEntriesOverIntervalJSON(start, end);
      // Convert the JSON object to a string
      auto jsonStr = JsonResponse(jsonObj.dump());

      return generateResponse(req, jsonStr);
    } catch (const std::exception& e) {
      auto msg = StringResponse(e.what());
      return generateResponse(req, msg,
                              boost::beast::http::status::bad_request);
    }
  });

  rt->addHandler("GET", "/getCurrentValue", [&rt](const Request& req) -> Response {
    // TODO Сюда добавить запрос на выдачу последней записи о столовой
    json jsonObj = rt->db_handler_->selectEntriesOverIntervalJSON(continuous_nums_to_datetime("20230524000000000"), continuous_nums_to_datetime("20230530235900000"));

    auto jsonStr = JsonResponse(jsonObj.dump());
    return generateResponse(req, jsonStr);
  });

  return rt;
}