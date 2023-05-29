#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_CURRENT_DATA_CREATOR_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_CURRENT_DATA_CREATOR_H_

#include "handler_creators/i_handler_creator.h"
#include "sqlite_handler.h"

namespace QueueBot {
class CurrentDataCreator : public IHandlerCreator {
 public:
  CurrentDataCreator(std::shared_ptr<IDataSource> database,
                     nlohmann::json names);
  IBotHandler::Ptr create(nlohmann::json handlerData) override;

 private:
  std::shared_ptr<IDataSource> database_;
  nlohmann::json names_;
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_CURRENT_DATA_CREATOR_H_