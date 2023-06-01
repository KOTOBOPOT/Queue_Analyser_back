#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <iostream>

#include "parse_query_string.h"

TEST(ParsingParams, TargetWithoutQuestionSymbolTest) {
  std::string target = "http://localhost:8080/getFromDb";
  auto params = parseQueryString(target);

  EXPECT_EQ(params.empty(), true);
}

TEST(ParsingParams, ParsingZeroParamTest) {
  std::string target = "http://localhost:8080/getFromDb?";
  auto params = parseQueryString(target);

  EXPECT_EQ(params.empty(), true);
}

TEST(ParsingParams, ParsingOneParamTest) {
  std::string target = "http://localhost:8080/getFromDb?start=20";
  auto params = parseQueryString(target);

  EXPECT_EQ(params["start"], "20");
}

TEST(ParsingParams, ParsingTwoParamsTest) {
  std::string target =
      "http://localhost:8080/"
      "getFromDb?start=20230501000000000&end=20230501235900000";
  auto params = parseQueryString(target);

  EXPECT_EQ(params["start"], "20230501000000000");
}

TEST(ParsingParams, ParsingManyParamsTest) {
  std::string target =
      "http://localhost:8080/"
      "getFromDb?start=20230501000000000&end=20230501235900000&umbrella=rs";
  auto params = parseQueryString(target);

  EXPECT_EQ(params.size(), 3);
}

TEST(ParsingParams, ParsingMistakeEqualInParamsTest) {
  std::string target = "http://localhost:8080/getFromDb?s&abra=0";
  auto params = parseQueryString(target);

  EXPECT_EQ(params["s"], "");
}

TEST(ParsingParams, ParsingEmpptyInParamsTest) {
  std::string target = "http://localhost:8080/getFromDb?s&abra=0&b=";
  auto params = parseQueryString(target);

  EXPECT_EQ(params["b"], "");
}

TEST(ParsingParams, ParsingMultipleParamsTest) {
  std::string target =
      "http://localhost:8080/getFromDb?start=20230501000000000&end=20230501235900000";
  auto params = parseQueryString(target);

  EXPECT_EQ(params["start"], "20230501000000000");
  EXPECT_EQ(params["end"], "20230501235900000");
}