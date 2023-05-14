#include <gtest/gtest.h>

#include <boost/beast.hpp>
#include <sstream>

#include "error.h"

TEST(ErrorHandling, FailTest) {
  boost::system::error_code error = boost::asio::error::connection_reset;
  std::stringstream output_stream;
  std::streambuf* original_cerr_buffer = std::cerr.rdbuf(output_stream.rdbuf());

  fail(error, "Failed to connect to the server");

  std::cerr.rdbuf(original_cerr_buffer);
  EXPECT_EQ(output_stream.str(),
            "Failed to connect to the server: Connection reset by peer\n");
}
