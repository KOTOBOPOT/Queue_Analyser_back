#include "handler_creators/current_data_creator.h"

namespace QueueBot {
CurrentDataCreator::CurrentDataCreator(std::shared_ptr<IDataSource> database,
                                        nlohmann::json names) 
  : database_(database), names_(names) {}

IBotHandler::Ptr CurrentDataCreator::create(nlohmann::json handlerData) {
  return std::make_unique<CurrentDataHandler>(
      handlerData.at("token").get<std::string>(),
      handlerData.at("data").get<std::string>(),
      handlerData.at("help").get<std::string>(),
      database_, names_);
}

}  // namespace QueueBot