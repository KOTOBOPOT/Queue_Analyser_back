#include <iostream>
#include <filesystem>
#include <thread>

#include "routes.h"
#include "server.h"
#include "video_processors.h"

int main(int argc, char* argv[]) {
  //  Print cwd and it's contents
  //
  //  std::filesystem::path cwd = std::filesystem::current_path();
  //  std::cout << "Current working directory: " << cwd.string() << std::endl;
  //  for (const auto & entry : std::filesystem::directory_iterator(cwd.string()))
  //    std::cout << entry.path() << std::endl;

  auto rt = getRouter();
  // Создаем первый поток для сервера
  std::thread server_thread([&rt]() {
    Server tst(*rt);
    // http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000
    tst.run();
  });

  // Создаем второй поток для цикла while(true)
  // TODO: Добавить db_handler внутрь video_processor чтобы через него
  // взаимодействовать с бд. Пока костыльно прокидываю роутер
  std::thread video_thread([&rt]() {
//    while (true) {
//      auto vid_processor =
//          getVideoProcessor("../static/video_examples/ex1.mp4", 0.1);
//
//      std::cout << "Reopen video..." << std::endl;
//      int amount = 0;
//      while ((amount = vid_processor->getQueuePeopleAmount()[0]) != -1) {
//        std::this_thread::sleep_for(std::chrono::seconds(2));
//        std::cout << "Current people amount from videosource: " << amount
//                  << std::endl;  // Если видео кончилось, возращает -1
//        //[0] значит, что для первой видеозаписи(getQueuePeopleAmount возращает
//        // вектор специально, задел на будущее под несколько записей)
//        auto time_now = std::chrono::system_clock::now();
//        rt->db_handler_->insertEntry(amount, time_now, 1);
//      }
//    }
  });

  // Дожидаемся окончания работы потоков
  video_thread.join();
  server_thread.join();

  return 0;
}