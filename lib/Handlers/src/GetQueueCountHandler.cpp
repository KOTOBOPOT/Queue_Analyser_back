#include "GetQueueCountHandler.hpp"
#include <random>

namespace {
    int queueCount = 0;
    std::mt19937 randomGenerator(time(nullptr));
}

bool GetQueueCountHandler::canHandle(const Request& request) const {
    return request.getMethod() == "GET" && request.getUrl() == "/getQueueCount";
}

Response GetQueueCountHandler::handle(const Request& request) const {
    std::uniform_int_distribution<int> dist(0, 1);
    if (dist(randomGenerator) == 0) {
        ++queueCount;
    } else {
        --queueCount;
    }
    return Response(200, std::to_string(queueCount), {{"Content-Type", "text/plain"}});
}

std::shared_ptr<Handler> GetQueueCountHandler::findHandler(const Request& request) {
    if (canHandle(request)) {
        return shared_from_this();
    } else {
        return nullptr;
    }
}
