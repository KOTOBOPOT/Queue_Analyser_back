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

      // Create a JSON object
      json jsonObj;

      jsonObj["entries"] =
          rt->db_handler_->selectEntriesOverIntervalString(start, end);
      // Convert the JSON object to a string
      auto jsonStr = JsonResponse(jsonObj.dump());

      return generateResponse(req, jsonStr);
    } catch (const std::exception& e) {
      auto msg = StringResponse(e.what());
      return generateResponse(req, msg,
                              boost::beast::http::status::bad_request);
    }
  });

  rt->addHandler("GET", "/getCurrentValue", [](const Request& req) -> Response {
    // Your code here
    static int peopleAmount = 10;  // Example value
    if (rand() % 2 || peopleAmount == 0) {
      peopleAmount += 5;
    } else {
      peopleAmount -= 1;
    }
    peopleAmount %= 25;
    // Create a JSON object
    json jsonObj;
    jsonObj["time"] = peopleAmount;

    // Generate the response using the JSON object
    auto jsonStr = JsonResponse(jsonObj.dump());
    return generateResponse(req, jsonStr);
  });

  rt->addHandler("GET", "/getTestArray", [](const Request& req) -> Response {
    // Your code here
    static int Test = 10;  // Example value
    if (rand() % 2 || Test == 0) {
      Test += 5;
    } else {
      Test -= 1;
    }
    Test %= 25;

    // Create a JSON array
    json jsonArray;
    for (int i = 0; i < 5; i++) {
        json obj;
        obj["22:01:00"] = Test + i;
        jsonArray.push_back(obj);
    }
    // Generate the response using the JSON object
    auto jsonStr = JsonResponse(jsonArray.dump());
    return generateResponse(req, jsonStr);
  });

  return rt;
}