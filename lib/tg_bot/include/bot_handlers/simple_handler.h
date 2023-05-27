#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_SIMPLE_HANDLER_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_SIMPLE_HANDLER_H_

#include "bot_handlers/i_bot_handler.h"

namespace QueueBot {
class SimpleHandler : public IBotHandler {
 public:
  SimpleHandler(std::string token, std::string msg, std::string help);

  std::string getHandlerString() override;
  bool isHandler(const TgBot::Message::Ptr msg) override;
  void sendMessage(TgBot::Bot& bot, TgBot::Message::Ptr msg) override;
  std::string getHelp() override;

 private:
  std::string value_;
  std::string message_;
  std::string help_;
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_SIMPLE_HANDLER_H_