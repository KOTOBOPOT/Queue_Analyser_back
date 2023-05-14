#include <boost/beast.hpp>
#include <iostream>


#include "routes.h"
#include "server.h"
int main(int argc, char* argv[]) {

    // std::shared_ptr<IVideoSource> vid_src = std::make_shared<FileVideo>("../static/video_examples/ex1.mp4",2);//2 - это кол-во секунд, которое мы пропускаем
    // //std::shared_ptr<IVideoSource> vid_src = std::make_shared<CamVideo>(0);
    
    // VideoProcessor vp = VideoProcessor(vid_src);
    // for (int i = 0; i < 100; ++i) {
    //   std::cout << i << " step . Current people amount from videosource: "
    //             << vp.getQueuePeopleAmount() << std::endl; //Если видео кончилось, возращает -1
    // }

  auto rt = getRouter();
  Server tst(*rt);

  // http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000
  tst.run();

  return 0;
}