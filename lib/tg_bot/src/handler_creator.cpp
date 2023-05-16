#include "handler_creator.h"

namespace QueueBot {
IBotHandler::Ptr SimpleCreator::create(nlohmann::json handlerData) {
  return std::make_unique<SimpleHandler>(
      handlerData.at("token").get<std::string>(),
      handlerData.at("data").get<std::string>(),
      handlerData.at("help").get<std::string>());
}
}  // namespace QueueBot