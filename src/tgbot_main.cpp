#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>

#include "bot.h"

int main(int argc, char** argv) {
  std::ifstream token_file("/app/configs/tg_bot_token.json");
  if (!token_file.is_open())
  {
    std::cout <<  "Не найден файл токена для телеграмм бота "
                  "или возникла ошибка при его открытии" << std::endl;
    return 1;
  }

  nlohmann::json token;
  token_file >> token;


  auto bot =
      QueueBot::SimpleBot(token.at("token"));

  std::ifstream file("/app/configs/tg_bot_menu.json");
  if (!token_file.is_open())
  {
    std::cout <<  "Не найден файл меню для телеграмм бота "
                  "или возникла ошибка при его открытии" << std::endl;
    return 1;
  }

  nlohmann::json menu;

  file >> menu;

  std::shared_ptr<IDataSource> db = std::make_unique<SQLiteHandler>("/app/db/db.db");

  QueueBot::CreatorChouser chouser;
  chouser += {"simple_tag", std::make_unique<QueueBot::SimpleCreator>()};
  chouser += 
      {"current_data_tag", std::make_unique<QueueBot::CurrentDataCreator>(db)};

  for (auto& val : menu.at("buttons")) {
    bot.addKeyboardButton(chouser.create(val.at("handler")),
                          val.at("row").get<size_t>(),
                          val.at("col").get<size_t>());
  }
  bot.run();
}