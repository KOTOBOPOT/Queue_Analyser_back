/**
 * @brief В этом файле написан класс ошибки открытия источника данных
 * @author Виктор Борисов (KOTOBOPOT)
 */

#ifndef QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_CV_OPEN_VIDEO_SOURCE_EXC_H_
#define QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_CV_OPEN_VIDEO_SOURCE_EXC_H_

#include "cv_base_exception.h"

class CVOpenVidSourceException : public CVBaseException {
 public:
  explicit CVOpenVidSourceException(std::string &&msg)
      : CVBaseException(std::move(msg)){};
};

#endif  //QUEUE_ANALYSER_LIB_COMPUTER_VISION_INCLUDE_COMPUTER_VISION_EXCEPTIONS_CV_OPEN_VIDEO_SOURCE_EXC_H_