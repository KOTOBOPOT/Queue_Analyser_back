#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>

#include "bot.h"
#include "const.h"

int main(int argc, char** argv) {
  std::shared_ptr<QueueBot::SimpleBot> bot;

  {
    std::ifstream token_file(DOC_ROOT + "/configs/tg_bot_token.json");
    if (!token_file.is_open()) {
      std::cerr << "Не найден файл токена для телеграмм бота "
                   "или возникла ошибка при его открытии"
                << std::endl;
      return 1;
    }

    nlohmann::json token;
    try {
      token_file >> token;
    } catch (...) {
      std::cerr << "Неверный формат файла с токеном" << std::endl;
      return 1;
    }

    try {
      bot = std::make_unique<QueueBot::SimpleBot>(token.at("token"));
    } catch (...) {
      std::cerr << "Невозможно запустить бота" << std::endl;
      return 1;
    }

    std::ifstream file(DOC_ROOT + "/configs/tg_bot_menu.json");
    if (!token_file.is_open()) {
      std::cerr << "Не найден файл меню для телеграмм бота "
                   "или возникла ошибка при его открытии"
                << std::endl;
      return 1;
    }

    std::ifstream names_file(DOC_ROOT + "/configs/names.json");
    if (!names_file.is_open()) {
      std::cerr << "Не найден файл имён столовых "
                   "или возникла ошибка при его открытии"
                << std::endl;
      return 1;
    }

    nlohmann::json names;
    try {
      names_file >> names;
    } catch (...) {
      std::cerr << "Неверный формат файла с именами" << std::endl;
      return 1;
    }

    std::shared_ptr<IDataSource> db =
        std::make_unique<SQLiteHandler>(DOC_ROOT + "/db/db.db");

    QueueBot::CreatorChouser chouser;
    chouser += {"simple_tag", std::make_unique<QueueBot::SimpleCreator>()};
    chouser +=
        {"all_data_tag", std::make_unique<QueueBot::AllDataCreator>(db, names)};
    chouser += {"current_data_tag",
                std::make_unique<QueueBot::CurrentDataCreator>(db, names)};

    nlohmann::json menu;
    file >> menu;

    for (auto& val : menu.at("buttons")) {
      bot->addKeyboardButton(chouser.create(val.at("handler")),
                             val.at("row").get<size_t>(),
                             val.at("col").get<size_t>());
    }
  }

  bot->run();
}