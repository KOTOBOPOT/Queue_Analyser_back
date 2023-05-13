#include <gtest/gtest.h>
#include "generate_response.h"
#include "router.h"

TEST(GenerateResponse, BasicTest) {
  Router::Request req;
  StringResponse content;
  auto res = generateResponse(req, content);
  EXPECT_EQ(res.result_int(), 200);
  EXPECT_EQ(res.version(), 11);
  EXPECT_EQ(res[boost::beast::http::field::server], BOOST_BEAST_VERSION_STRING);
  EXPECT_EQ(res[boost::beast::http::field::content_type], "text/plain");
  EXPECT_EQ(res[boost::beast::http::field::access_control_allow_origin], "*");
  EXPECT_TRUE(res.keep_alive());
  EXPECT_EQ(res.body(), content);
}

TEST(GenerateResponse, CustomStatusTest) {
  Router::Request req;
  StringResponse content;
  auto res = generateResponse(req, content, boost::beast::http::status::not_found);
  EXPECT_EQ(res.result_int(), 404);
}

TEST(GenerateResponse, NoKeepAliveTest) {
  Router::Request req;
  StringResponse content;
  req.keep_alive(false);
  auto res = generateResponse(req, content);
  EXPECT_FALSE(res.keep_alive());
}

TEST(GenerateResponse, CorrectResponseBodyTest) {
  Router::Request req;
  StringResponse content("My text response");
  req.keep_alive(false);
  auto res = generateResponse(req, content);
  EXPECT_EQ(res.body(), "My text response");
}

// Тестируем новую структуру с другим типом контента
struct CustomType : public std::string {
  static constexpr const char* contentType = "application/octet-stream";
};

TEST(GenerateResponse, CustomContentTypeTest) {
  Router::Request req;
  CustomType content;
  auto res = generateResponse(req, content);
  EXPECT_EQ(res[boost::beast::http::field::content_type], CustomType::contentType);
}