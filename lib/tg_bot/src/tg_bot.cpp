#include "tg_bot.h"

#include <iostream>

namespace QueueBot {
SimpleBot::SimpleBot(std::string token)
    : ITgBot(token),
      bot_(token),
      keyboard_(std::make_unique<TgBot::ReplyKeyboardMarkup>()) {
  keyboard_->resizeKeyboard = true;
  keyboard_->oneTimeKeyboard = false;

  bot_.getEvents().onCommand("start", [&](TgBot::Message::Ptr message) {
    this->bot_.getApi().sendMessage(
        message->chat->id, "Пожалуйста выберите столовую", false, 0, keyboard_);
  });
  TgBot::BotCommand::Ptr command = std::make_unique<TgBot::BotCommand>();
  command->command = "start";
  command->description = "Запустить бота";

  commands_.push_back(command);
  bot_.getApi().setMyCommands(commands_);

  bot_.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
    std::cout << message->text << std::endl;
    auto it = this->handlers_.begin();

    while (it != this->handlers_.end() && !(*it)->isHandler(message)) it++;

    if (it != this->handlers_.end()) {
      (*it)->sendMessage(bot_, message);
    }
    // else
    ;  // TODO: Exception
  });
}

void SimpleBot::addKeyboardButton(IBotHandler::Ptr handler, size_t row,
                                  size_t col) {
  TgBot::KeyboardButton::Ptr button(std::make_unique<TgBot::KeyboardButton>());
  button->text = handler->getHandlerString();
  if (keyboard_->keyboard.size() < row) keyboard_->keyboard.resize(row);

  if (keyboard_->keyboard[row - 1].size() < col)
    keyboard_->keyboard[row - 1].resize(col);

  keyboard_->keyboard[row - 1][col - 1] = button;

  handlers_.push_back(handler);
}

void SimpleBot::addMenuButton(IBotHandler::Ptr handler) {
  bot_.getEvents().onCommand(handler->getHandlerString(),
                             [&](TgBot::Message::Ptr message) {
                               handler->sendMessage(this->bot_, message);
                             });
  TgBot::BotCommand::Ptr command = std::make_unique<TgBot::BotCommand>();
  command->command = handler->getHandlerString();
  command->description = handler->getHelp();

  commands_.push_back(command);
  bot_.getApi().setMyCommands(commands_);
}

void SimpleBot::run() {
  std::cout << "Bot username: " << this->bot_.getApi().getMe()->username
            << std::endl;
  TgBot::TgLongPoll longPoll(bot_);
  while (true) {
    longPoll.start();
  }
}
}  // namespace QueueBot