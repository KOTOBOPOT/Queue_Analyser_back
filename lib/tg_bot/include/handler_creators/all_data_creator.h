#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_ALL_DATA_CREATOR_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_ALL_DATA_CREATOR_H_

#include "sqlite_handler.h"
#include "handler_creators/i_handler_creator.h"

namespace QueueBot {
class AllDataCreator : public IHandlerCreator {
 public:
  AllDataCreator(std::shared_ptr<IDataSource> database, nlohmann::json names);
  IBotHandler::Ptr create(nlohmann::json handlerData) override;
 private:
  std::shared_ptr<IDataSource> database_;
  nlohmann::json names_;
  
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_ALL_DATA_CREATOR_H_