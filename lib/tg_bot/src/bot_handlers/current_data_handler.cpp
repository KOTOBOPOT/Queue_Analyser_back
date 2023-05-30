#include "bot_handlers/current_data_handler.h"

#include <boost/algorithm/string/replace.hpp>
#include <iostream>

namespace QueueBot {
CurrentDataHandler::CurrentDataHandler(std::string token, std::string msg,
                                       std::string help,
                                       std::shared_ptr<IDataSource> database,
                                       nlohmann::json& names)
    : value_(token),
      message_(msg),
      help_(help),
      database_(database),
      room_id_(0),
      names_(names) {}

std::string CurrentDataHandler::getHandlerString() { return value_; }

TgBot::InlineKeyboardMarkup::Ptr CurrentDataHandler::createKeyboard_() {
  TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(
      std::make_unique<TgBot::InlineKeyboardMarkup>());
  std::vector<TgBot::InlineKeyboardButton::Ptr> row;
  for (auto& i : names_.at("names")) {
    TgBot::InlineKeyboardButton::Ptr btn(
        std::make_unique<TgBot::InlineKeyboardButton>());
    if (i.at("id").get<size_t>() == room_id_)
      btn->text = "👉 " + i.at("title").get<std::string>() + " 👈";
    else
      btn->text = i.at("title").get<std::string>();
    btn->callbackData = "room_id_" + std::to_string(i.at("id").get<size_t>());
    row.push_back(btn);
  }
  inline_keyboard->inlineKeyboard.push_back(row);
  return inline_keyboard;
}

std::string CurrentDataHandler::getMessage_() {
  std::string message = message_;
  auto row = database_->selectLastEntryJSON(room_id_);
  try {
    int count = row.at(std::to_string(room_id_)).at("amount");
    if (count < 0)
      boost::replace_all(message, "%1", "Нет данных");
    else
      boost::replace_all(message, "%1", std::to_string(count));
  } catch (...) {
    boost::replace_all(message, "%1", "Нет данных");
  }

  boost::replace_all(
      message, "%2",
      names_.at("names")[room_id_].at("title").get<std::string>());
  return message;
}

void CurrentDataHandler::editMessage_(TgBot::Bot& bot,
                                      TgBot::Message::Ptr msg) {
  try {
    bot.getApi().editMessageText(getMessage_(), msg->chat->id, msg->messageId,
                                 "", "", false, createKeyboard_());
  } catch (...) {
  }
}

bool CurrentDataHandler::isHandler(const TgBot::Message::Ptr msg) {
  return msg->text == value_;
}
void CurrentDataHandler::sendMessage(TgBot::Bot& bot, TgBot::Message::Ptr msg) {
  bot.getEvents().onCallbackQuery([&](TgBot::CallbackQuery::Ptr query) {
    std::string button_text = query->data;

    if (button_text.find("room_id_") != std::string::npos) {
      button_text.erase(0, 8);
      room_id_ = std::stoi(button_text);
      editMessage_(bot, query->message);
    }
  });
  bot.getApi().sendMessage(msg->chat->id, getMessage_(), false, 0,
                           createKeyboard_());
}

std::string CurrentDataHandler::getHelp() { return help_; }

}  // namespace QueueBot