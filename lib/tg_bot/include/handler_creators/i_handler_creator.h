#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_I_HANDLER_CREATOR_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_I_HANDLER_CREATOR_H_

#include <memory>
#include <nlohmann/json.hpp>

#include "bot_handlers.h"

namespace QueueBot {
class IHandlerCreator {
 public:
  using Ptr = std::shared_ptr<IHandlerCreator>;
  IHandlerCreator() = default;
  ~IHandlerCreator() = default;

  virtual IBotHandler::Ptr create(nlohmann::json handlerData) = 0;
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_HANDLER_CREATOR_I_HANDLER_CREATOR_H_