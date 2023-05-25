#include "bot_handlers/simple_handler.h"

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

}  // namespace QueueBot