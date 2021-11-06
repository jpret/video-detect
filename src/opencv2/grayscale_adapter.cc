/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/opencv2/grayscale_adapter.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace video_detect {
namespace opencv2 {

GrayscaleAdapter::GrayscaleAdapter(const cv::Mat &mat) {
  // Utilize open cv to convert the 3-channel image to a single channel
  // grayscale image
  cv::cvtColor(mat, *this, cv::COLOR_BGR2GRAY);
}

}  // namespace opencv2
}  // namespace video_detect
