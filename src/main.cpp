#include <iostream>
#include <thread>
#include <vector>

#include "cam_video.h"
#include "file_video.h"
#include "routes.h"
#include "server.h"
#include "video_processors.h"

int main(int argc, char* argv[]) {
  auto rt = getRouter();
  // Создаем первый поток для сервера
  std::thread server_thread([&rt]() {
    Server tst(*rt, "0.0.0.0");
    // http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000
    tst.run();
  });

  // Создаем второй поток для цикла while(true)
  SQLiteHandler db_handler("/app/db/db.db");
  std::thread video_thread([&db_handler]() {
    while (true) {
      auto vid_processor = getVideoProcessor();

      auto fv1 = std::make_shared<FileVideo>(
          "/app/static/video_examples/ex1.mp4", 0.5);
      auto fv2 = std::make_shared<FileVideo>(
          "/app/static/video_examples/sample.mp4", 0.1);
      auto fv3 = std::make_shared<CamVideo>(0);

      vid_processor->pushBackVideoSource(
          fv1);  // Добавляем в видео_процессор источники для видео
      vid_processor->pushBackVideoSource(
          fv2, cv::Rect(10, 50, 500,
                        500));  // можно также указывать прямоугольник очереди
      vid_processor->pushBackVideoSource(fv3, cv::Rect(10, 50, 500, 500));

      //Убрал визулизацию
      //vid_processor->setVisualizeVidSourceIndex(
      //   1);  // какое видео выводим. Указан индекс 2 - индекс в соответствии с
               // pushBackVideoSource().  В данном случае выводится видео с веб
               // камеры ноутбука

      std::cout << "Reopen video..." << std::endl;
      std::vector<int> people_amounts = vid_processor->getQueuePeopleAmount();
      while (((people_amounts[0]) != -1) && (people_amounts[1] != -1)) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Current people amount from first videosource: "
                  << people_amounts[0]
                  << ". From second videosource: " << people_amounts[1]
                  // << ". From third: " << people_amounts[2]
                  << std::endl;  // Если видео кончилось, возращает -1

        auto time_now = std::chrono::system_clock::now();

        for (int vid_index = 0; vid_index < people_amounts.size();
             ++vid_index) {
          db_handler.insertEntry(people_amounts[vid_index], time_now,
                                 vid_index);
        }

        people_amounts = vid_processor->getQueuePeopleAmount();
      }
    }
  });

  // Дожидаемся окончания работы потоков
  video_thread.join();
  server_thread.join();

  return 0;
}