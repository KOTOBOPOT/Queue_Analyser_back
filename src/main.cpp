#include <boost/beast.hpp>
#include <iostream>

#include "server.h"
#include "routes.h"

int main(int argc, char* argv[]) {
  auto rt = getRouter();
  Server tst(*rt);

  tst.run();
  // start_write_to_db(/*...*/);

  return 0;
}