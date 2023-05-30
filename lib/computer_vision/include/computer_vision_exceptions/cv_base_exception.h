/**
 * @brief В этом файле написан класс базовой ошибки работы с CV
 * @author Виктор Борисов (KOTOBOPOT)DaMagus26
 */

#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_CV_BASE_EXCEPTION_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_CV_BASE_EXCEPTION_H_

#include <exception>
#include <string>

class CVBaseException : public std::exception {
 public:
  explicit CVBaseException(std::string&& msg) : msg_(std::move(msg)){};
  const char* what() const noexcept override { return msg_.c_str(); }

 private:
  std::string msg_;
};


#endif  // QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_CV_BASE_EXCEPTION_H_
