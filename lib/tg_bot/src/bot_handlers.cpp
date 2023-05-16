#include <boost/algorithm/string/replace.hpp>

#include "bot_handlers.h"

namespace QueueBot {

SimpleHandler::SimpleHandler(std::string token, std::string msg,
                             std::string help)
    : _value(token), _message(msg), _help(help) {}

std::string SimpleHandler::getHandlerString() { return _value; }

bool SimpleHandler::isHandler(const TgBot::Message::Ptr msg) {
  return msg->text == _value;
}
void SimpleHandler::sendMessage(const TgBot::Bot& bot,
                                TgBot::Message::Ptr msg) {
  bot.getApi().sendMessage(msg->chat->id, _message, false, 0, nullptr);
}

std::string SimpleHandler::getHelp() { return _help; }

CurrentDataHandler::CurrentDataHandler(
      std::string token, std::string msg,
      std::string help, std::shared_ptr<IDataSource> database)
    : _value(token), _message(msg), _help(help), _database(database) {}

std::string CurrentDataHandler::getHandlerString() { return _value; }

bool CurrentDataHandler::isHandler(const TgBot::Message::Ptr msg) {
  return msg->text == _value;
}
void CurrentDataHandler::sendMessage(const TgBot::Bot& bot,
                                     TgBot::Message::Ptr msg) {
  std::string message = _message;
  int count = _database->selectLastEntry(0);

  boost::replace_all(message, "%1", std::to_string(count));

  bot.getApi().sendMessage(msg->chat->id, message, false, 0, nullptr);
}

std::string CurrentDataHandler::getHelp() { return _help; }

}  // namespace QueueBot