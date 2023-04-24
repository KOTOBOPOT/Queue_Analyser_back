//
// Created by Михаил Овакимян on 24.04.2023.
//

#ifndef LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_DB_BASE_EXCEPTION_H_
#define LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_DB_BASE_EXCEPTION_H_

#include <string>
#include <exception>

class DBBaseException : public std::exception {
 public:
  explicit DBBaseException(std::string&& msg) : msg_(std::move(msg)) {};
  const char * what() const noexcept override {
      return msg_.c_str();
  }
 private:
  std::string msg_;
};

#endif //LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_DB_BASE_EXCEPTION_H_
