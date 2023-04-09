#include "handler.hpp"
#include "server.hpp"
#include "session.hpp"


Server::Server(int port) : acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
                           socket_(io_service_) {
}

void Server::run(std::shared_ptr<Handler> handler) {
    startAccept();
    io_service_.run();
}

void Server::startAccept() {
    acceptor_.async_accept(socket_, [this](const boost::system::error_code& error) {
        if (!error) {
            auto handler = std::make_shared<Handler>();
            handleAccept(handler, error);
        } else {
            startAccept();
        }
    });
}

void Server::handleAccept(std::shared_ptr<Handler> handler, const boost::system::error_code& error) {
    if (!error) {
        std::make_shared<Session>(std::move(socket_), handler)->start();
    }

    startAccept();
}
