#include <boost/algorithm/string/replace.hpp>

#include "bot_handlers.h"

namespace QueueBot {

SimpleHandler::SimpleHandler(std::string token, std::string msg,
                             std::string help)
    : value_(token), message_(msg), help_(help) {}

std::string SimpleHandler::getHandlerString() { return value_; }

bool SimpleHandler::isHandler(const TgBot::Message::Ptr msg) {
  return msg->text == value_;
}
void SimpleHandler::sendMessage(const TgBot::Bot& bot,
                                TgBot::Message::Ptr msg) {
  bot.getApi().sendMessage(msg->chat->id, message_, false, 0, nullptr);
}

std::string SimpleHandler::getHelp() { return help_; }

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