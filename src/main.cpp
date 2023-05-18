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
    Server tst(*rt);
    // http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000
    tst.run();
  });

  // Создаем второй поток для цикла while(true)
  // TODO: Добавить db_handler внутрь video_processor чтобы через него
  // взаимодействовать с бд. Пока костыльно прокидываю роутер
  std::thread video_thread([&rt]() {
    while (true) {
      // auto vid_processor =
      //     getVideoProcessor("../static/video_examples/ex1.mp4", 0.1);

      auto vid_processor = getVideoProcessor();

      std::shared_ptr<FileVideo> fv1 =
          std::make_shared<FileVideo>("../static/video_examples/ex1.mp4", 0.5);
      std::shared_ptr<FileVideo> fv2 = std::make_shared<FileVideo>(
          "../static/video_examples/sample.mp4", 0.1);
      std::shared_ptr<CamVideo> fv3 = std::make_shared<CamVideo>(0);

      vid_processor->pushBackVideoSource(
          fv1);  // Добавляем в видео_процессор источники для видео
      vid_processor->pushBackVideoSource(
          fv2, cv::Rect(10, 50, 500,
                        500));  // можно также указывать прямоугольник очереди
      vid_processor->pushBackVideoSource(fv3, cv::Rect(10, 50, 500, 500));

      vid_processor->setVisualizeVidSourceIndex(
          2);  // какое видео выводим. Указан индекс 2 - индекс в соответствии с
               // pushBackVideoSource().  В данном случае выводится видео с веб
               // камеры ноутбука

      std::cout << "Reopen video..." << std::endl;
      std::vector<int> people_amounts = vid_processor->getQueuePeopleAmount();
      while (((people_amounts[0]) != -1) || (people_amounts[1] != -1)) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Current people amount from first videosource: "
                  << people_amounts[0]
                  << ". From second videosource: " << people_amounts[1]
                  << ". From third: " << people_amounts[2]
                  << std::endl;  // Если видео кончилось, возращает -1

        auto time_now = std::chrono::system_clock::now();
        rt->db_handler_->insertEntry(people_amounts[0], time_now, 1);
        people_amounts = vid_processor->getQueuePeopleAmount();
      }
    }
  });

  // Дожидаемся окончания работы потоков
  video_thread.join();
  server_thread.join();

  return 0;
}