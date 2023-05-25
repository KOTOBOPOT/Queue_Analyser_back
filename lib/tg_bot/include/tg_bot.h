#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_TG_BOT_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_TG_BOT_H_

#include <tgbot/tgbot.h>

#include <memory>
#include <string>
#include <vector>

#include "bot_handlers.h"
#include "handler_creator.h"

namespace QueueBot {
class ITgBot {
 public:
  ITgBot(std::string token){};
  virtual ~ITgBot() = default;

  virtual void addMenuButton(IBotHandler::Ptr handler) = 0;
  virtual void addKeyboardButton(IBotHandler::Ptr handler, size_t row,
                                 size_t col) = 0;
  virtual void run() = 0;
};

class SimpleBot : public ITgBot {
 public:
  SimpleBot(std::string token);

  void addKeyboardButton(IBotHandler::Ptr handler, size_t row,
                         size_t col) override;
  void addMenuButton(IBotHandler::Ptr handler) override;
  void run() override;

 private:
  TgBot::Bot bot_;
  TgBot::ReplyKeyboardMarkup::Ptr keyboard_;
  std::vector<IBotHandler::Ptr> handlers_;
  std::vector<TgBot::BotCommand::Ptr> commands_;
};
}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_TG_BOT_H_