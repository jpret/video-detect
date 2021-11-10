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

/**
 * @brief The MatBridge class provides a bridge between the external libraries /
 * code and the cppengineer/video-detect code.
 *
 */
class MatBridge : public util::ObjectReceiver<const cv::Mat &> {
 public:
  /**
   * @brief Construct a new Mat Bridge object
   *
   * @param worker a thread worker to schedule incoming work through the bridge
   * @param receiver the receiver which will receive any information through the
   * worker
   */
  explicit MatBridge(util::Worker &worker,  // NOLINT(runtime/references)
                     util::ObjectReceiver<const mat::Mat2D<uint8_t> &>
                         &receiver);  // NOLINT(runtime/references)

  /**
   * @brief Accept a OpenCV Mat object
   *
   * @param cv_mat a 3-Channel (RGB) unsigned char opencv matrix
   */
  void Accept(const cv::Mat &cv_mat) override;

 private:
  util::Worker &worker_;
  util::ObjectReceiver<const mat::Mat2D<uint8_t> &> &receiver_;
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_BRIDGE_H_
