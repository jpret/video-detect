/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_BRIDGE_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_BRIDGE_H_

#include <opencv2/core/mat.hpp>
#include <utility>

#include "video-detect/mat/mat_2d.h"
#include "video-detect/util/object_receiver.h"
#include "video-detect/util/worker.h"

namespace video_detect {

class MatBridge : public util::ObjectReceiver<const cv::Mat &> {
 public:
  explicit MatBridge(util::Worker &worker,  // NOLINT(runtime/references)
                     util::ObjectReceiver<const mat::Mat2D<uint8_t> &>
                         &receiver);  // NOLINT(runtime/references)

  void Accept(const cv::Mat &cv_mat) override;

 private:
  util::Worker &worker_;
  util::ObjectReceiver<const mat::Mat2D<uint8_t> &> &receiver_;
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_BRIDGE_H_
