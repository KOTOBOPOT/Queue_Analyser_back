#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_CURRENT_DATA_HANDLER_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_CURRENT_DATA_HANDLER_H_

#include "bot_handlers/i_bot_handler.h"
#include "sqlite_handler.h"

namespace QueueBot {
class CurrentDataHandler : public IBotHandler {
 public:
  CurrentDataHandler(std::string token, std::string msg, std::string help, 
                     std::shared_ptr<IDataSource> database);

  std::string getHandlerString() override;
  bool isHandler(const TgBot::Message::Ptr msg) override;
  void sendMessage(const TgBot::Bot& bot, TgBot::Message::Ptr msg) override;
  std::string getHelp() override;

 private:
  std::string value_;
  std::string message_;
  std::string help_;
  std::shared_ptr<IDataSource> database_;
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_CURRENT_DATA_HANDLER_H_