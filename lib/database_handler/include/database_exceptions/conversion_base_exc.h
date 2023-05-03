/**
 * @file db_access_exc.cpp
 * @brief В этом файле написан класс ошибки неверного формата данных о времени
 * @author Михаил Овакимян (DaMagus26)
 */

#ifndef QUEUEANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_CONVERSION_BASE_EXC_H_
#define QUEUEANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_CONVERSION_BASE_EXC_H_

#include <string>
#include <exception>

class ConversionBaseException : public std::exception {
 public:
  explicit ConversionBaseException(std::string&& msg) : msg_(std::move(msg)) {};
  const char * what() const noexcept override {
    return msg_.c_str();
  }
 private:
  std::string msg_;
};

#endif //QUEUEANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_CONVERSION_BASE_EXC_H_
