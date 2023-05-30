#include "handler_creators/all_data_creator.h"

namespace QueueBot {
AllDataCreator::AllDataCreator(std::shared_ptr<IDataSource> database,
                               nlohmann::json names)
    : database_(database), names_(names) {}

IBotHandler::Ptr AllDataCreator::create(nlohmann::json handlerData) {
  return std::make_unique<AllDataHandler>(
      handlerData.at("token").get<std::string>(),
      handlerData.at("data").get<std::string>(),
      handlerData.at("help").get<std::string>(), database_, names_);
}

}  // namespace QueueBot