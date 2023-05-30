#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_CREATOR_CHOUSER_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_CREATOR_CHOUSER_H_

#include <map>
#include <nlohmann/json.hpp>
#include <utility>

#include "handler_creator.h"
#include "tg_bot.h"

namespace QueueBot {
class CreatorChouser {
 public:
  CreatorChouser() = default;
  ~CreatorChouser() = default;

  IBotHandler::Ptr create(nlohmann::json value);
  void operator+=(std::pair<std::string, IHandlerCreator::Ptr>&& value);

 private:
  std::map<std::string, IHandlerCreator::Ptr> creators_;
};
}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_CREATOR_CHOUSER_H_