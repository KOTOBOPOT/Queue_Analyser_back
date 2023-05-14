#include <boost/beast.hpp>
#include <iostream>

#include "server.h"
#include "routes.h"

#include "video_processor.h"

int main(int argc, char* argv[]) {
  VideoProcessor vp = VideoProcessor(0);
  std::cout<<"Current people amount on web camera: " <<vp.getQueuePeopleAmount()<<std::endl;
  
  auto rt = getRouter();
  Server tst(*rt);

  // http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000
  tst.run();

  return 0;
}