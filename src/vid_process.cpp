#include <vector>

#include "cam_video.h"
#include "file_video.h"
#include "video_processor.h"

std::unique_ptr<VideoProcessor> getVideoProcessor(const std::string& filename) {
    

}

std::unique_ptr<VideoProcessor> getVideoProcessor(const int cam_index) {}

std::unique_ptr<VideoProcessor> getVideoProcessor(
    const std::vector<std::string>& vid_sources_filenames) {}

std::unique_ptr<VideoProcessor> getVideoProcessor(
    const std::vector<int> cam_indexes) {}
