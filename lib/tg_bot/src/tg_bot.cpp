#include <iostream>

#include "tg_bot.h"

namespace QueueBot
{
  SimpleBot::SimpleBot(std::string token) :   
                        ITgBot(token), 
                        _bot(token), 
                        _keyboard(std::make_unique<TgBot::ReplyKeyboardMarkup>())
  {
    _keyboard->resizeKeyboard = true;
    _keyboard->oneTimeKeyboard = false;

    _bot.getEvents().onCommand("start", [&](TgBot::Message::Ptr message) {
      this->_bot.getApi().sendMessage(message->chat->id, "Бот запущен", false, 0, _keyboard);
    });
    TgBot::BotCommand::Ptr command = std::make_unique<TgBot::BotCommand>();
    command->command = "start";
    command->description = "Запустить бота";

    _commands.push_back(command);
    _bot.getApi().setMyCommands(_commands);

    _bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
      std::cout << message->text << std::endl;
      auto it = this->_handlers.begin();
      
      while (it != this->_handlers.end() && !(*it)->isHandler(message))
        it++;

      if (it != this->_handlers.end())
      {
        (*it)->sendMessage(_bot, message);
      }
      // else
        ; // TODO: Exception 
    });
  }

  void SimpleBot::addKeyboardButton(IBotHandler::Ptr handler, size_t row, size_t col)
  {
    TgBot::KeyboardButton::Ptr button(std::make_unique<TgBot::KeyboardButton>());
    button->text = handler->getHandlerString();
    if (_keyboard->keyboard.size() < row)
      _keyboard->keyboard.resize(row);
    
    if (_keyboard->keyboard[row-1].size() < col)
      _keyboard->keyboard[row-1].resize(col);

    _keyboard->keyboard[row-1][col-1] = button;

    _handlers.push_back(handler);
  }

  void SimpleBot::addMenuButton(IBotHandler::Ptr handler) 
  {
    _bot.getEvents().onCommand(
      handler->getHandlerString(), 
      [&](TgBot::Message::Ptr message) 
      { 
        handler->sendMessage(this->_bot, message); 
      }
    );
    TgBot::BotCommand::Ptr command = std::make_unique<TgBot::BotCommand>();
    command->command = handler->getHandlerString();
    command->description = handler->getHelp();

    _commands.push_back(command);
    _bot.getApi().setMyCommands(_commands);
  }

  void SimpleBot::run()
  {
    std::cout << "Bot username: " << this->_bot.getApi().getMe()->username << std::endl;
    TgBot::TgLongPoll longPoll(_bot);
    while (true) {
      longPoll.start();
    }
  }
}