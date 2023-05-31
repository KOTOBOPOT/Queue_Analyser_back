#include "video_processors.h"

#include <vector>

#include "cam_video.h"
#include "file_video.h"
#include "video_processor.h"


std::unique_ptr<VideoProcessor> getVideoProcessor() {
  auto vp = std::make_unique<VideoProcessor>();
  return vp;
}
std::unique_ptr<VideoProcessor> getVideoProcessor(
    std::string model_file_path) {  // не const, т.к компилятор ругается, если
                                     // передавать ""+"" значения
  auto vp = std::make_unique<VideoProcessor>(model_file_path);
  return vp;
}
