#pragma once
#include "session.hpp"
#include "error.hpp"

#include <memory>
#include <string>
#include <boost/asio.hpp>

// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener>
{
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;

public:
    Listener(
        boost::asio::io_context& ioc,
        boost::asio::ip::tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root);

    // Start accepting incoming connections
    void run() {
        do_accept();
    }

private:
    void do_accept();

    void on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
};