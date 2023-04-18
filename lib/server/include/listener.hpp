#ifndef QUEUE_ANALYSER_SERVER_LISTENER_H_
#define QUEUE_ANALYSER_SERVER_LISTENER_H_
#include <boost/asio.hpp>
#include <memory>
#include <string>

#include "error.hpp"
#include "session.hpp"

// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener> {
 public:
  Listener(boost::asio::io_context& ioc,
           boost::asio::ip::tcp::endpoint endpoint,
           std::shared_ptr<std::string const> const& doc_root);

  // Start accepting incoming connections
  void run() { do_accept(); }

 private:
  boost::asio::io_context& ioc_;
  boost::asio::ip::tcp::acceptor acceptor_;
  std::shared_ptr<std::string const> doc_root_;
  
  void do_accept();

  void on_accept(boost::beast::error_code ec,
                 boost::asio::ip::tcp::socket socket);
};

#endif  // QUEUE_ANALYSER_SERVER_LISTENER_H_