#include "session.hpp"

Session::Session(boost::asio::ip::tcp::socket socket, std::shared_ptr<Handler> handler)
    : socket_(std::move(socket)), handler_(std::move(handler)) {}

void Session::start() {
    boost::asio::async_read(socket_, boost::asio::buffer(data_, max_length),
                                 std::bind(&Session::handleRead, shared_from_this(),
                                           std::placeholders::_1, std::placeholders::_2));
}

void Session::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
        // Обработка запроса
        Request request;
        try {
            request = Request::parse(std::string(data_, bytes_transferred));
        } catch (const std::exception& e) {
            // Ошибка в запросе
            Response response(400, e.what(), {{"Content-Type", "text/plain"}});
            boost::asio::async_write(socket_, boost::asio::buffer(response.to_string()),
                                     std::bind(&Session::handleWrite, shared_from_this(),
                                               std::placeholders::_1));
            return;
        }

        // Поиск и выполнение обработчика
        std::shared_ptr<Handler> handler = handler_->findHandler(request);
        if (handler) {
            Response response = handler->handle(request);
            boost::asio::async_write(socket_, boost::asio::buffer(response.to_string()),
                                     std::bind(&Session::handleWrite, shared_from_this(),
                                               std::placeholders::_1));
        } else {
            // Обработчик не найден
            Response response(404, "Not Found", {{"Content-Type", "text/plain"}});
            boost::asio::async_write(socket_, boost::asio::buffer(response.to_string()),
                                     std::bind(&Session::handleWrite, shared_from_this(),
                                               std::placeholders::_1));
        }
    }
}

void Session::handleWrite(const boost::system::error_code& error) {
    if (!error) {
        socket_.close();
    }
}
