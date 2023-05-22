#include <boost/beast.hpp>
#include <iostream>
#include <filesystem>

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

  while (true) {
    std::cout << "Loop started" << std::endl;
    // auto vid_processor = getVideoProcessor(0);
    auto vid_processor =
        getVideoProcessor("/static/video_examples/ex1.mp4", 2);

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