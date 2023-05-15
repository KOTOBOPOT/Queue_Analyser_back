#include "vid_process.h"

#include <vector>

#include "cam_video.h"
#include "file_video.h"
#include "video_processor.h"

std::unique_ptr<VideoProcessor> getVideoProcessor(const std::string& filename,
                                                  float skip_secs,
                                                  const cv::Rect& queue_box) {
  auto vid_source = std::make_shared<FileVideo>(filename, skip_secs);
  queueVidSource queue_vid = queueVidSource(vid_source, queue_box);

  auto vp =
      std::make_unique<VideoProcessor>(std::vector<queueVidSource>{queue_vid});
  return vp;
}

std::unique_ptr<VideoProcessor> getVideoProcessor(const int cam_index,
                                                  const cv::Rect& queue_box) {
  auto vid_source = std::make_shared<CamVideo>(cam_index);
  queueVidSource queue_vid = queueVidSource(vid_source, queue_box);

  auto vp =
      std::make_unique<VideoProcessor>(std::vector<queueVidSource>{queue_vid});
  return vp;
}

// std::unique_ptr<VideoProcessor> getVideoProcessor(
//     const std::vector<std::string>& vid_sources_filenames) {}

// std::unique_ptr<VideoProcessor> getVideoProcessor(
//     const std::vector<int> cam_indexes) {}
