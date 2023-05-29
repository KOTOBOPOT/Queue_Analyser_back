#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_ALL_DATA_HANDLER_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_ALL_DATA_HANDLER_H_

#include <nlohmann/json.hpp>

#include "bot_handlers/i_bot_handler.h"
#include "sqlite_handler.h"

namespace QueueBot {
class AllDataHandler : public IBotHandler {
 public:
  AllDataHandler(std::string token, std::string msg, std::string help,
                 std::shared_ptr<IDataSource> database, nlohmann::json& names);

  std::string getHandlerString() override;
  bool isHandler(const TgBot::Message::Ptr msg) override;
  void sendMessage(TgBot::Bot& bot, TgBot::Message::Ptr msg) override;
  std::string getHelp() override;

 private:
  std::string value_;
  std::string message_;
  std::string help_;
  std::shared_ptr<IDataSource> database_;
  nlohmann::json names_;

  TgBot::InlineKeyboardMarkup::Ptr createKeyboard_();
  std::string getMessage_();
  void editMessage_(TgBot::Bot& bot, TgBot::Message::Ptr msg);
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_ALL_DATA_HANDLER_H_