/**
 * @brief В этом файле написан класс ошибки открытия источника данных
 * @author Виктор Борисов (KOTOBOPOT)
 */

#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_FILE_OPEN_EXC_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_FILE_OPEN_EXC_H_

#include "files_base_exception.h"

class FileOpenException : public FileBaseException {
 public:
  explicit FileOpenException(std::string &&msg)
      : FileBaseException(std::move(msg)){};
};

#endif  //QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_FILE_OPEN_EXC_H_