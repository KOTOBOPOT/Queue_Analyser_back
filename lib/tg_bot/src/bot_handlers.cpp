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

}  // namespace QueueBot