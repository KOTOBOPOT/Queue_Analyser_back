#ifndef QUEUE_ANALYSER_SERVER_SESSION_H_
#define QUEUE_ANALYSER_SERVER_SESSION_H_
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <memory>

#include "error.hpp"
#include "handler.hpp"

// обрабатывает входящее соединение. Он должен обеспечивать
// чтение запроса, парсинг запроса,
// обработку запроса и отправку ответа
class Session : public std::enable_shared_from_this<Session> {
  // This is the C++11 equivalent of a generic lambda.
  // The function object is used to send an HTTP message.
  struct send_lambda {
    Session& self_;

    explicit send_lambda(Session& self) : self_(self) {}

    template <bool isRequest, class Body, class Fields>
    void operator()(
        boost::beast::http::message<isRequest, Body, Fields>&& msg) const {
      // The lifetime of the message has to extend
      // for the duration of the async operation so
      // we use a shared_ptr to manage it.
      auto sp = std::make_shared<
          boost::beast::http::message<isRequest, Body, Fields>>(std::move(msg));

      // Store a type-erased version of the shared
      // pointer in the class to keep it alive.
      self_.res_ = sp;

      // Write the response
      boost::beast::http::async_write(
          self_.stream_, *sp,
          boost::beast::bind_front_handler(
              &Session::on_write, self_.shared_from_this(), sp->need_eof()));
    }
  };

  //  объект tcp_stream, через который происходит взаимодействие с клиентом
  boost::beast::tcp_stream stream_;
  // буфер для чтения и записи запроса/ответа
  boost::beast::flat_buffer buffer_;
  // указатель на корневой каталог сервера.
  std::shared_ptr<std::string const> doc_root_;
  boost::beast::http::request<boost::beast::http::string_body> req_;
  std::shared_ptr<void> res_;
  send_lambda lambda_;

 public:
  // Take ownership of the stream
  Session(boost::asio::ip::tcp::socket&& socket,
          std::shared_ptr<std::string const> const& doc_root)
      : stream_(std::move(socket)), doc_root_(doc_root), lambda_(*this) {}

  // Start the asynchronous operation
  void run() { do_read(); }

  // будет запускаться в начале работы каждого запроса и будет асинхронно
  // считывать данные из потока
  void do_read();

  // будет вызываться при завершении чтения из потока и будет обрабатывать
  // полученный запрос
  void on_read(boost::beast::error_code ec, std::size_t bytes_transferred);

  // будет вызываться после того, как будет сформирован и отправлен ответ
  // клиенту
  void on_write(bool close, boost::beast::error_code ec,
                std::size_t bytes_transferred);

  // зыкрытие сессии и освобождение ресурсов
  void do_close();
};

#endif  // QUEUE_ANALYSER_SERVER_SESSION_H_