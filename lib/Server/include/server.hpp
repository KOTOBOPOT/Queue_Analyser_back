#pragma once
#include <memory>
#include <string>
#include <boost/asio.hpp>

class Server {
public:
    Server(
        const std::string& address = "127.0.0.1", 
        unsigned short port = 8080, 
        const std::string& doc_root = ".",
        const int threads = 1)
        : address_(boost::asio::ip::make_address(address)),
          port_(port),
          doc_root_(std::make_shared<std::string>(doc_root)),
          threads_(threads) {}

    void run();

private:
    // Router& router_;
    // tcp::acceptor acceptor_;
    // tcp::socket socket_;
    const boost::asio::ip::address address_;
    const unsigned short port_;
    const std::shared_ptr<std::string> doc_root_;
    const int threads_ = 1;
};