/**
 * @file query_execution_exc.cpp
 * @brief В этом файле написан класс ошибки исполнения SQL запроса
 * @author Михаил Овакимян (DaMagus26)
 */

#pragma once
#include <string>
#include <exception>

class QueryExecutionException : public std::exception {
 public:
  explicit QueryExecutionException(std::string&& msg) : msg_(std::move(msg)) {};
  const char * what() const noexcept override {
    return msg_.c_str();
  }
 private:
  std::string msg_;
};