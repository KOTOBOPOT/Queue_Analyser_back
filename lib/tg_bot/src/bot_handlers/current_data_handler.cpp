#include <boost/algorithm/string/replace.hpp>

#include "bot_handlers/current_data_handler.h"
#include <iostream>

namespace QueueBot {
CurrentDataHandler::CurrentDataHandler(
      std::string token, std::string msg,
      std::string help, std::shared_ptr<IDataSource> database)
    : value_(token), message_(msg), help_(help), database_(database), 
      room_id_(0) {}

std::string CurrentDataHandler::getHandlerString() { return value_; }

TgBot::InlineKeyboardMarkup::Ptr CurrentDataHandler::createKeyboard_() {
  TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(std::make_unique<TgBot::InlineKeyboardMarkup>());
  std::vector<TgBot::InlineKeyboardButton::Ptr> row;
  for (size_t i = 0; i < 2; i++) // Временный костыль
  {
    TgBot::InlineKeyboardButton::Ptr btn(std::make_unique<TgBot::InlineKeyboardButton>());
    if (i == room_id_)
      btn->text = "* " + std::to_string(i) + " *";
    else
      btn->text = std::to_string(i);
    btn->callbackData = "room_id_" + std::to_string(i);
    row.push_back(btn);
  }
  inline_keyboard->inlineKeyboard.push_back(row);
  return inline_keyboard;
}

std::string CurrentDataHandler::getMessage_() {
  std::string message = message_;
  auto row = database_->selectLastEntryJSON(room_id_);
  int count = row.at(std::to_string(room_id_)).at("amount");
  boost::replace_all(message, "%1", std::to_string(count));
  return message;
}

void CurrentDataHandler::editMessage_(TgBot::Bot& bot, TgBot::Message::Ptr msg)
{
  try {
      bot.getApi().editMessageText(getMessage_(), 
        msg->chat->id, msg->messageId, "", 
        "", false, createKeyboard_());
    }
    catch (...) {}
}

bool CurrentDataHandler::isHandler(const TgBot::Message::Ptr msg) {
  return msg->text == value_;
}
void CurrentDataHandler::sendMessage(TgBot::Bot& bot,
                                     TgBot::Message::Ptr msg) {
  bot.getEvents().onCallbackQuery([&](TgBot::CallbackQuery::Ptr query) {
    std::string button_text = query->data;
    if (button_text == "room_id_0") {
      room_id_ = 0;
      editMessage_(bot, query->message);
    }
    else if (button_text == "room_id_1") {
      room_id_ = 1;
      editMessage_(bot, query->message);
    }
  });
  bot.getApi().sendMessage(msg->chat->id, getMessage_(), false, 0, createKeyboard_());
}

std::string CurrentDataHandler::getHelp() { return help_; }

}  // namespace QueueBot