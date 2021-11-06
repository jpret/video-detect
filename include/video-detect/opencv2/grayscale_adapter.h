/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_GRAYSCALE_ADAPTER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_GRAYSCALE_ADAPTER_H_

#include <opencv2/core/mat.hpp>

namespace video_detect {
namespace opencv2 {

class GrayscaleAdapter : public cv::Mat {
 public:
  explicit GrayscaleAdapter(const cv::Mat &mat);
};

}  // namespace opencv2
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_GRAYSCALE_ADAPTER_H_
