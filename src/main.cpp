#include <boost/beast.hpp>
#include <iostream>

#include "server.h"
#include "routes.h"

int main(int argc, char* argv[]) {
  auto rt = getRouter();
  Server tst(*rt);

  // http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000
  tst.run();

  return 0;
}