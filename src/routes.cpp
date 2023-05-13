#include "routes.h"

#include <memory>

#include "continuous_nums_to_time_point.h"
#include "generate_response.h"
#include "join.h"
#include "parse_query_string.h"
#include "router.h"
#include "sqlite_handler.h"

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
      auto entries = StringResponse(
          rt->db_handler_->selectEntriesOverIntervalString(start, end));

      return generateResponse(req, entries);
    } catch (const std::exception& e) {
      auto msg = StringResponse(e.what());
      return generateResponse(req, msg,
                              boost::beast::http::status::bad_request);
    }
  });

  rt->addHandler("GET", "/getCurrentValue", [](const Request& req) -> Response {
    static int result = 0;
    if (rand() % 2 || result == 0) {
      result += 5;
    } else {
      result -= 1;
    }
    result %= 25;
    auto content = StringResponse(std::to_string(result));

    return generateResponse(req, content);
  });

  return rt;
}