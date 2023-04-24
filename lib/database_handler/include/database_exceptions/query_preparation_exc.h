/**
 * @file query_preparation_exc.cpp
 * @brief В этом файле написан класс ошибки приведения SQL запроса в бинарный вид
 * @author Михаил Овакимян (DaMagus26)
 */

#pragma once
#include <string>
#include <exception>

class QueryPreparationException : public std::exception {
 public:
  explicit QueryPreparationException(std::string&& msg) : msg_(std::move(msg)) {};
  const char * what() const noexcept override {
    return msg_.c_str();
  }
 private:
  std::string msg_;
};