#pragma once

#include <memory>
#include <boost/asio.hpp>
#include "handler.hpp"

class Server {
public:
    Server(int port);
    void run(std::shared_ptr<Handler> handler);

private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;

    void startAccept();
    void handleAccept(std::shared_ptr<Handler> handler, const boost::system::error_code& error);
};
