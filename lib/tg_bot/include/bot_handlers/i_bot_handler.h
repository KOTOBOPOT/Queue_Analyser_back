#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_I_BOT_HANDLER_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_I_BOT_HANDLER_H_

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <tgbot/tgbot.h>

namespace QueueBot {
class IBotHandler {
 public:
  using Ptr = std::shared_ptr<IBotHandler>;
  IBotHandler(){};
  virtual ~IBotHandler() = default;

  virtual std::string getHandlerString() = 0;
  virtual bool isHandler(const TgBot::Message::Ptr msg) = 0;
  virtual void sendMessage(const TgBot::Bot& bot, TgBot::Message::Ptr msg) = 0;
  virtual std::string getHelp() = 0;
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_I_BOT_HANDLER_H_