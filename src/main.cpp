#include "server.hpp"
// #include "database_handler/api.hpp"  // ?
#include "api.hpp"
#include "bot.hpp"
#include "model.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    database_handler();
    bot();
    model();

    Server tst;
    tst.run();

    return 0;
}