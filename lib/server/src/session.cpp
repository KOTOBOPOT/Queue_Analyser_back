#include "session.hpp"

void Session::do_read() {
  // Make the request empty before reading,
  // otherwise the operation behavior is undefined.
  req_ = {};

  // Set the timeout.
  stream_.expires_after(std::chrono::seconds(30));

  // Read a request
  boost::beast::http::async_read(
      stream_, buffer_, req_,
      boost::beast::bind_front_handler(&Session::on_read, shared_from_this()));
}

void Session::on_read(boost::beast::error_code ec,
                      std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  // This means they closed the connection
  if (ec == boost::beast::http::error::end_of_stream) {
    std::cout << "ec == http::error::end_of_stream REQ TARGET" << req_.target()
              << std::endl;
    return do_close();
  }
  if (ec) return fail(ec, "read");

  // Send the response
  handle_request(*doc_root_, std::move(req_), lambda_);
}

void Session::on_write(bool close, boost::beast::error_code ec,
                       std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec) return fail(ec, "write");

  if (close) {
    // This means we should close the connection, usually because
    // the response indicated the "Connection: close" semantic.
    return do_close();
  }

  // We're done with the response so delete it
  res_ = nullptr;

  // Read another request
  do_read();
}

void Session::do_close() {
  // Send a TCP shutdown
  boost::beast::error_code ec;
  stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);

  // At this point the connection is closed gracefully
}