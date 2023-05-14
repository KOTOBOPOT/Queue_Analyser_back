#include <boost/beast.hpp>
#include <iostream>

#include "server.h"
#include "routes.h"

#include "VideoProcessor.h"

int main(int argc, char* argv[]) {
  VideoProcessor vp = VideoProcessor(0);
  std::cout<<"Current people amount on web camera: " <<vp.getQueuePeopleAmount()<<std::endl;
  
  auto rt = getRouter();
  Server tst(*rt);

  tst.run();

  return 0;
}