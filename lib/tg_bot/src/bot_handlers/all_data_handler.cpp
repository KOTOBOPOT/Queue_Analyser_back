#include <boost/algorithm/string/replace.hpp>

#include "bot_handlers/all_data_handler.h"
#include <iostream>

namespace QueueBot {
AllDataHandler::AllDataHandler(
      std::string token, std::string msg, std::string help, 
      std::shared_ptr<IDataSource> database, nlohmann::json& names)
    : value_(token), message_(msg), help_(help), database_(database), 
      names_(names) {}

std::string AllDataHandler::getHandlerString() { return value_; }

TgBot::InlineKeyboardMarkup::Ptr AllDataHandler::createKeyboard_() {
  TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(std::make_unique<TgBot::InlineKeyboardMarkup>());
  std::vector<TgBot::InlineKeyboardButton::Ptr> row;
  TgBot::InlineKeyboardButton::Ptr btn(std::make_unique<TgBot::InlineKeyboardButton>());
  btn->text = "Обновить";
  btn->callbackData = "refresh";
  row.push_back(btn);
  inline_keyboard->inlineKeyboard.push_back(row);
  return inline_keyboard;
}

std::string AllDataHandler::getMessage_() {
  std::string message = "";
  for (auto& i : names_.at("names")) {
    std::string temp = message_;
    boost::replace_all(temp, "%2", i.at("title").get<std::string>());
    auto row = database_->selectLastEntryJSON(i.at("id").get<size_t>());
    try {
      int count = row.at(std::to_string(i.at("id").get<size_t>())).at("amount");
      boost::replace_all(temp, "%1", std::to_string(count));
    }
    catch (...) {
      boost::replace_all(temp, "%1", "Недоступно");
    }
    message += temp;
  }
  return message;
}

void AllDataHandler::editMessage_(TgBot::Bot& bot, TgBot::Message::Ptr msg)
{
  try {
      bot.getApi().editMessageText(getMessage_(), 
        msg->chat->id, msg->messageId, "", 
        "", false, createKeyboard_());
  }
  catch (...) {}
}

bool AllDataHandler::isHandler(const TgBot::Message::Ptr msg) {
  return msg->text == value_;
}

void AllDataHandler::sendMessage(TgBot::Bot& bot,
                                 TgBot::Message::Ptr msg) {
  bot.getEvents().onCallbackQuery([&](TgBot::CallbackQuery::Ptr query) {
    std::string button_text = query->data;
    if (button_text == "refresh") {
      editMessage_(bot, query->message);
    }
  });
  bot.getApi().sendMessage(msg->chat->id, getMessage_(), false, 0, createKeyboard_());
}

std::string AllDataHandler::getHelp() { return help_; }

}  // namespace QueueBot