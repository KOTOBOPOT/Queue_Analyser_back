#ifndef QUEUE_ANALYSER_LIB_SERVER_INCLUDE_SERVER_H_
#define QUEUE_ANALYSER_LIB_SERVER_INCLUDE_SERVER_H_
#include <boost/asio.hpp>
#include <memory>
#include <string>

#include "router.h"

class Server {
 public:
  Server(Router& router, const std::string& address = "127.0.0.1",
         unsigned short port = 8080,
         const std::string& doc_root = "/app/src/views", const int threads = 1)
      : router_(router),
        address_(boost::asio::ip::make_address(address)),
        port_(port),
        doc_root_(std::make_shared<std::string>(doc_root)),
        threads_(threads) {}

  void run();

 private:
  Router& router_;  // Переделать в умный указатель
  const boost::asio::ip::address address_;
  const unsigned short port_;
  const std::shared_ptr<std::string const> doc_root_;
  const int threads_ = 1;
};

#endif  // QUEUE_ANALYSER_LIB_SERVER_INCLUDE_SERVER_H_