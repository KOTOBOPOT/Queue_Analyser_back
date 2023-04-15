#include "server.hpp"
#include "listener.hpp"
#include <boost/asio.hpp>


void Server::run() {
    boost::asio::io_context ioc_{threads_};

    std::make_shared<Listener>(
        ioc_,
        boost::asio::ip::tcp::endpoint{address_, port_},
        doc_root_)->run();


    std::vector<std::thread> v;
    v.reserve(threads_ - 1);
    for(auto i = threads_ - 1; i > 0; --i)
        v.emplace_back(
        [&ioc_]
        {
            ioc_.run();
        });
    

    std::cout << "Server listening on http://" << address_.to_string() << ":" << port_ << std::endl;
    ioc_.run();
    std::cout << "Server stopped" << std::endl;
};