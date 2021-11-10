/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/mat_bridge.h"

#include <utility>

#include "video-detect/opencv2/grayscale_adapter.h"
#include "video-detect/opencv2/mat_2d_adapter.h"

namespace video_detect {

MatBridge::MatBridge(
    util::Worker &worker,
    util::ObjectReceiver<const mat::Mat2D<uint8_t> &> &receiver)
    : worker_(worker), receiver_(receiver) {}

void MatBridge::Accept(const cv::Mat &cv_mat) {
  // Convert the incoming cv_mat to a single channel matrix (grayscale)
  cv::Mat img_gray = opencv2::GrayscaleAdapter(cv_mat);

  // Perform the bridging work by the worker to not hold up the calling chain
  worker_.Accept([this, img_gray = std::move(img_gray)]() {
    // Pass on the matrix to the receiver which expects a grayscale image
    // Thus, a single channel unsigned char 2D matrix
    receiver_.Accept(opencv2::Mat2DAdapter<uint8_t>(img_gray));
  });
}

}  // namespace video_detect
