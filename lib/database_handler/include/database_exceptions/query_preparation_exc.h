/**
 * @file query_preparation_exc.cpp
 * @brief В этом файле написан класс ошибки приведения SQL запроса в бинарный вид
 * @author Михаил Овакимян (DaMagus26)
 */

#ifndef LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_QUERY_PREPARATION_H_
#define LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_QUERY_PREPARATION_H_

#include "db_base_exception.h"

class QueryPreparationException : DBBaseException {
 public:
  explicit QueryPreparationException(std::string &&msg) : DBBaseException(std::move(msg)) {};
};

#endif //LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_QUERY_PREPARATION_H_