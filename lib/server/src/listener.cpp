#include "listener.h"

Listener::Listener(Router& router, boost::asio::io_context& ioc,
                   boost::asio::ip::tcp::endpoint endpoint,
                   std::shared_ptr<std::string const> const& doc_root)
    : router_(router),
      ioc_(ioc),
      acceptor_(boost::asio::make_strand(ioc)),
      doc_root_(doc_root) {
  boost::beast::error_code ec;

  // Open the acceptor
  acceptor_.open(endpoint.protocol(), ec);
  if (ec) {
    fail(ec, "open");
    return;
  }

  // Allow address reuse
  acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
  if (ec) {
    fail(ec, "set_option");
    return;
  }

  // Bind to the server address
  acceptor_.bind(endpoint, ec);
  if (ec) {
    fail(ec, "bind");
    return;
  }

  // Start listening for connections
  acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
  if (ec) {
    fail(ec, "listen");
    return;
  }
}

void Listener::doAccept() {
  // Прием нового соединения
  acceptor_.async_accept(boost::asio::make_strand(ioc_),
                         boost::beast::bind_front_handler(&Listener::onAccept,
                                                          shared_from_this()));
}

void Listener::onAccept(boost::beast::error_code ec,
                        boost::asio::ip::tcp::socket socket) {
  if (ec) {
    fail(ec, "accept");
  } else {
    // Создание объекта Session и передача ему принятого сокета
    auto session = std::make_shared<Session>(router_, std::move(socket), doc_root_);

    // Запуск обработки соединения в отдельном потоке
    session->run();
  }

  // Accept another connection
  doAccept();
}