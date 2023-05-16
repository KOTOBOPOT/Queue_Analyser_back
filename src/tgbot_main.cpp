#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>

#include "bot.h"

int main(int argc, char** argv) {
  auto bot =
      QueueBot::SimpleBot("6216802370:AAHtsAHiNSVm4PZv2r1YZHdQu5ap63LF8kE");

  std::ifstream file("../configs/tg_bot_menu.json");
  nlohmann::json menu;
  file >> menu;

  QueueBot::CreatorChouser chouser;
  chouser += {"simple_tag", std::make_unique<QueueBot::SimpleCreator>()};

  std::cout << menu.dump() << std::endl;

  for (auto& val : menu.at("buttons")) {
    std::cout << val.dump() << std::endl;
    bot.addKeyboardButton(chouser.create(val.at("handler")),
                          val.at("row").get<size_t>(),
                          val.at("col").get<size_t>());
  }
  bot.run();
}