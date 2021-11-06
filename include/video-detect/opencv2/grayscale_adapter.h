/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_GRAYSCALE_ADAPTER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_GRAYSCALE_ADAPTER_H_

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace video_detect {
namespace opencv2 {

class GrayscaleAdapter : public cv::Mat {
 public:
  explicit GrayscaleAdapter(const cv::Mat &mat) {
    // Utilize open cv to convert the 3-channel image to a single channel
    // grayscale image
    cv::cvtColor(mat, *this, cv::COLOR_BGR2GRAY);
  }
};

}  // namespace opencv2
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_GRAYSCALE_ADAPTER_H_
