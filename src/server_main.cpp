#include "routes.h"
#include "server.h"
#include "const.h"

int main(int argc, char* argv[]) {
  auto rt = getRouter(DOC_ROOT + "/db/db.db");
  Server tst(*rt, "0.0.0.0", 8080, DOC_ROOT + "/src/views");
  tst.run();

  return 0;
}