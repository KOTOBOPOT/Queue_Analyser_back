#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_H_

#include <tgbot/tgbot.h>

#include <iostream>
#include <memory>
#include <string>

#include "sqlite_handler.h"

namespace QueueBot {
class IBotHandler {
 public:
  using Ptr = std::shared_ptr<IBotHandler>;
  IBotHandler(){};
  virtual ~IBotHandler() = default;

  virtual std::string getHandlerString() = 0;
  virtual bool isHandler(const TgBot::Message::Ptr msg) = 0;
  virtual void sendMessage(const TgBot::Bot& bot, TgBot::Message::Ptr msg) = 0;
  virtual std::string getHelp() = 0;
};

class SimpleHandler : public IBotHandler {
 public:
  SimpleHandler(std::string token, std::string msg, std::string help);

  std::string getHandlerString() override;
  bool isHandler(const TgBot::Message::Ptr msg) override;
  void sendMessage(const TgBot::Bot& bot, TgBot::Message::Ptr msg) override;
  std::string getHelp() override;

 private:
  std::string value_;
  std::string message_;
  std::string help_;
};

class CurrentDataHandler : public IBotHandler {
 public:
  CurrentDataHandler(std::string token, std::string msg, std::string help, 
                     std::shared_ptr<IDataSource> database);

  std::string getHandlerString() override;
  bool isHandler(const TgBot::Message::Ptr msg) override;
  void sendMessage(const TgBot::Bot& bot, TgBot::Message::Ptr msg) override;
  std::string getHelp() override;

 private:
  std::string value_;
  std::string message_;
  std::string help_;
  std::shared_ptr<IDataSource> database_;
};

}  // namespace QueueBot

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_HANDLERS_H_