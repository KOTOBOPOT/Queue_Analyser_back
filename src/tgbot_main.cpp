#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>

#include "bot.h"

int main(int argc, char** argv) {
  std::ifstream token_file("../configs/tg_bot_token.json");
  nlohmann::json token;
  token_file >> token;

  auto bot =
      QueueBot::SimpleBot(token.at("token"));

  std::ifstream file("../configs/tg_bot_menu.json");
  nlohmann::json menu;
  file >> menu;

  std::shared_ptr<IDataSource> db = std::make_unique<SQLiteHandler>("../db/db.db");

  QueueBot::CreatorChouser chouser;
  chouser += {"simple_tag", std::make_unique<QueueBot::SimpleCreator>()};
  chouser += 
      {"current_data_tag", std::make_unique<QueueBot::CurrentDataCreator>(db)};

  std::cout << menu.dump() << std::endl;

  for (auto& val : menu.at("buttons")) {
    std::cout << val.dump() << std::endl;
    bot.addKeyboardButton(chouser.create(val.at("handler")),
                          val.at("row").get<size_t>(),
                          val.at("col").get<size_t>());
  }
  bot.run();
}