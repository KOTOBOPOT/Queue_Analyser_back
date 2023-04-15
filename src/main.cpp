#include <server.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    // // Check command line arguments.
    // if (argc != 5)
    // {
    //     std::cerr <<
    //         "Usage: http-server-async <address> <port> <doc_root> <threads>\n" <<
    //         "Example:\n" <<
    //         "    http-server-async 0.0.0.0 8080 . 1\n";
    //     return 1;
    // }
    // auto const address = net::ip::make_address(argv[1]);
    // auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    // auto const doc_root = std::make_shared<std::string>(argv[3]);
    // auto const threads = std::max<int>(1, std::atoi(argv[4]));

    Server tst;

    tst.run();

    return 0;
}