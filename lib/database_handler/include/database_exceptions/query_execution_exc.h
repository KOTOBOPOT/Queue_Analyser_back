/**
 * @file query_execution_exc.cpp
 * @brief В этом файле написан класс ошибки исполнения SQL запроса
 * @author Михаил Овакимян (DaMagus26)
 */

#ifndef QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_QUERY_EXECUTION_H_
#define QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_QUERY_EXECUTION_H_

#include "db_base_exception.h"

class QueryExecutionException : public DBBaseException {
 public:
  explicit QueryExecutionException(std::string &&msg) : DBBaseException(std::move(msg)) {};
};

#endif //QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_QUERY_EXECUTION_H_