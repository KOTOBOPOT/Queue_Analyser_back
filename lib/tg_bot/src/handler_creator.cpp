#include "handler_creator.h"

namespace QueueBot {
IBotHandler::Ptr SimpleCreator::create(nlohmann::json handlerData) {
  return std::make_unique<SimpleHandler>(
      handlerData.at("token").get<std::string>(),
      handlerData.at("data").get<std::string>(),
      handlerData.at("help").get<std::string>());
}

CurrentDataCreator::CurrentDataCreator(std::shared_ptr<IDataSource> database) 
  : database_(database) {}

IBotHandler::Ptr CurrentDataCreator::create(nlohmann::json handlerData) {
  return std::make_unique<CurrentDataHandler>(
      handlerData.at("token").get<std::string>(),
      handlerData.at("data").get<std::string>(),
      handlerData.at("help").get<std::string>(),
      database_);
}
}  // namespace QueueBot