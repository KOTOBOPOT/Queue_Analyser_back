#pragma once

#include <boost/asio.hpp>
#include <memory>
#include "handler.hpp"

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::ip::tcp::socket socket, std::shared_ptr<Handler> handler);
    void start();

private:
    boost::asio::ip::tcp::socket socket_;
    std::shared_ptr<Handler> handler_;
    enum { max_length = 1024 };
    char data_[max_length];

    void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
    void handleWrite(const boost::system::error_code& error);
};
