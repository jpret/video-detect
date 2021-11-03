
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FRAME_ANALYZER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FRAME_ANALYZER_H_

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace cppeng {
namespace video_detect {

class FrameAnalyzer {
  void Analyze(cv::Mat img) { std::cout << "Analyze!" << std::endl; }
};

} // namespace video_detect
} // namespace cppeng

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FRAME_ANALYZER_H_