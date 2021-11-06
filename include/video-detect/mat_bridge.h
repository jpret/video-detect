/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_BRIDGE_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_BRIDGE_H_

#include <utility>

#include <opencv2/core/mat.hpp>

#include "video-detect/mat/mat_2d.h"
#include "video-detect/opencv2/grayscale_adapter.h"
#include "video-detect/opencv2/mat_2d_adapter.h"
#include "video-detect/util/object_receiver.h"
#include "video-detect/util/worker.h"

namespace video_detect {

class MatBridge : public util::ObjectReceiver<const cv::Mat &> {
 public:
  explicit MatBridge(util::Worker &worker,  // NOLINT(runtime/references)
                     util::ObjectReceiver<const mat::Mat2D<uint8_t> &>
                         &receiver)  // NOLINT(runtime/references)
      : worker_(worker), receiver_(receiver) {}

  void Accept(const cv::Mat &cv_mat) override {
    // Convert the incoming cv_mat to a single channel matrix (grayscale)
    cv::Mat img_gray = opencv2::GrayscaleAdapter(cv_mat);

    // Perform the bridging work by the worker to not hold up the calling chain
    worker_.Accept([this, img_gray = std::move(img_gray)]() {
      receiver_.Accept(opencv2::Mat2DAdapter<uint8_t>(img_gray));
    });
  }

 private:
  util::Worker &worker_;
  util::ObjectReceiver<const mat::Mat2D<uint8_t> &> &receiver_;
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_BRIDGE_H_
