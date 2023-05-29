#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_I_TG_BOT_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_I_TG_BOT_H_

#include <string>

#include "bot_handlers.h"

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

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_I_TG_BOT_H_