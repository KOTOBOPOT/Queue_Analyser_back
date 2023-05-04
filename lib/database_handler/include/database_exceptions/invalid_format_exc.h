/**
 * @file query_execution_exc.cpp
 * @brief В этом файле написан класс ошибки неверного формата данных
 * @author Михаил Овакимян (DaMagus26)
 */

#ifndef QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_INVALID_FORMAT_EXC_H_
#define QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_INVALID_FORMAT_EXC_H_

#include "conversion_base_exc.h"

class InvalidFormatException : public ConversionBaseException {
 public:
  explicit InvalidFormatException(std::string &&msg)
      : ConversionBaseException(std::move(msg)){};
};

#endif  // QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_INVALID_FORMAT_EXC_H_
