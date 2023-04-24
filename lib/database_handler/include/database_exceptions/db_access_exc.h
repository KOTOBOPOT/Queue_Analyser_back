/**
 * @file db_access_exc.cpp
 * @brief В этом файле написан класс ошибки подключения к БД
 * @author Михаил Овакимян (DaMagus26)
 */

#ifndef QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_DB_ACCESS_EXC_H_
#define QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_DB_ACCESS_EXC_H_

#include "db_base_exception.h"

 class DBAccessException : public DBBaseException {
  public:
   explicit DBAccessException(std::string &&msg) : DBBaseException(std::move(msg)) {};
 };

#endif //QUEUE_ANALYSER_QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_DATABASE_EXCEPTIONS_DB_ACCESS_EXC_H_