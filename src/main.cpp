#include <iostream>
#include <thread>

#include "routes.h"
#include "server.h"
#include "video_processors.h"

int main(int argc, char* argv[]) {
  // Создаем первый поток для цикла while(true)
  std::thread video_thread([]() {
    while (true) {
      auto vid_processor =
          getVideoProcessor("../static/video_examples/ex1.mp4", 0.2);

      for (int i = 0; i < 28; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << i << " step. Current people amount from videosource: "
                  << vid_processor->getQueuePeopleAmount()[0]
                  << std::endl;  // Если видео кончилось, возращает -1
        //[0] значит, что для первой видеозаписи(getQueuePeopleAmount возращает
        // вектор специально, задел на будущее под несколько записей)
      }
    }
  });

  // Создаем второй поток для сервера
  std::thread server_thread([]() {
    auto rt = getRouter();
    Server tst(*rt);
    // http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000
    tst.run();
  });

  // Дожидаемся окончания работы потоков
  video_thread.join();
  server_thread.join();

  return 0;
}