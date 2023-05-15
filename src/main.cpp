#include <boost/beast.hpp>
#include <iostream>

#include "routes.h"
#include "server.h"
#include "vid_process.h"

int main(int argc, char* argv[]) {
  while (true) {
    // auto vid_processor = getVideoProcessor(0);
    auto vid_processor =
        getVideoProcessor("../static/video_examples/ex1.mp4", 2);

    for (int i = 0; i < 28; ++i) {
      std::cout << i << " step . Current people amount from videosource: "
                << vid_processor->getQueuePeopleAmount()[0]
                << std::endl;  // Если видео кончилось, возращает -1
    }  //[0] значит, что для первой видеозаписи(getQueuePeopleAmount возращает
       // вектор специально, задел на будущее под несколько записей)
  }

  auto rt = getRouter();
  Server tst(*rt);

  // http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000
  tst.run();

  return 0;
}