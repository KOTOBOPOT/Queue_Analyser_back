/**
 * @file db_access_exc.cpp
 * @brief В этом файле написан класс ошибки подключения к БД
 * @author Михаил Овакимян (DaMagus26)
 */

#pragma once
#include <string>
#include <exception>

 class DBAccessException : public std::exception {
 public:
   explicit DBAccessException(std::string&& msg) : msg_(std::move(msg)) {};
  const char * what() const noexcept override {
    return msg_.c_str();
  }
 private:
  std::string msg_;
};