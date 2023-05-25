#include <boost/algorithm/string/replace.hpp>

#include "bot_handlers/current_data_handler.h"

namespace QueueBot {
CurrentDataHandler::CurrentDataHandler(
      std::string token, std::string msg,
      std::string help, std::shared_ptr<IDataSource> database)
    : value_(token), message_(msg), help_(help), database_(database) {}

std::string CurrentDataHandler::getHandlerString() { return value_; }

bool CurrentDataHandler::isHandler(const TgBot::Message::Ptr msg) {
  return msg->text == value_;
}
void CurrentDataHandler::sendMessage(const TgBot::Bot& bot,
                                     TgBot::Message::Ptr msg) {
  std::string message = message_;
  int count = database_->selectLastEntry(0);

  boost::replace_all(message, "%1", std::to_string(count));

  bot.getApi().sendMessage(msg->chat->id, message, false, 0, nullptr);
}

std::string CurrentDataHandler::getHelp() { return help_; }

}  // namespace QueueBot