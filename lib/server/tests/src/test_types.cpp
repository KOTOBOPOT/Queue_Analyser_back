// test_mime_type.cpp
#include <gtest/gtest.h>

#include "types.h"

// Функция корректно определяет тип MIME для файлов с
// разными расширениями.
TEST(MimeType, ExtensionHtml) {
  boost::beast::string_view path = "/path/to/file.html";
  auto mime = mime_type(path);
  EXPECT_EQ(mime, "text/html");
}

TEST(MimeType, ExtensionJs) {
  boost::beast::string_view path = "/path/to/script.js";
  auto mime = mime_type(path);
  EXPECT_EQ(mime, "application/javascript");
}

TEST(MimeType, ExtensionUnknown) {
  boost::beast::string_view path = "/path/to/unknown.extension";
  auto mime = mime_type(path);
  EXPECT_EQ(mime, "application/text");
}

// test_path_cat.cpp
// Функция корректно объединяет две строки пути

// базовый путь пустой
TEST(PathCat, BaseEmpty) {
  boost::beast::string_view base = "";
  boost::beast::string_view path = "/path/to/file.html";
  auto result = path_cat(base, path);
  EXPECT_EQ(result, "/path/to/file.html");
}

// Путь, который добавляется, пустой
TEST(PathCat, PathEmpty) {
  boost::beast::string_view base = "/path/to/base";
  boost::beast::string_view path = "";
  auto result = path_cat(base, path);
  EXPECT_EQ(result, "/path/to/base");
}

// Оба пути непустые
TEST(PathCat, BothNonEmpty) {
  boost::beast::string_view base = "/path/to/base";
  boost::beast::string_view path = "/file.html";
  auto result = path_cat(base, path);
  EXPECT_EQ(result, "/path/to/base/file.html");
}

// Оба пути непустые, при этом base оканчивается '/'
TEST(PathCat, BaseWithSlashEnd) {
  boost::beast::string_view base = "/path/to/base/";
  boost::beast::string_view path = "/file.html";
  auto result = path_cat(base, path);
  EXPECT_EQ(result, "/path/to/base/file.html");
}
