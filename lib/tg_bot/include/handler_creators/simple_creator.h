#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_SIMPLE_CREATOR_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_SIMPLE_CREATOR_H_

#include "handler_creators/i_handler_creator.h"

namespace QueueBot {
class SimpleCreator : public IHandlerCreator {
 public:
  IBotHandler::Ptr create(nlohmann::json handlerData) override;
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_SIMPLE_CREATOR_H_