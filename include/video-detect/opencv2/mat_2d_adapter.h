/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_MAT_2D_ADAPTER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_MAT_2D_ADAPTER_H_

#include <opencv2/core/mat.hpp>
#include <utility>

#include "video-detect/mat/mat_2d.h"
#include "video-detect/mat/vector_2d.h"

namespace video_detect {
namespace opencv2 {

/**
 * @brief The Mat2DAdapter changes a cv::Mat to a Mat2D class
 *
 * @tparam T the type of 2D Matrix to use
 */
template <typename T>
class Mat2DAdapter : public mat::Mat2D<T> {
 public:
  explicit Mat2DAdapter(const cv::Mat &mat)
      : mat::Mat2D<T>(mat.rows, mat.cols) {
    // Set all the values
    for (int row = 0; row < mat.rows; row++) {
      for (int col = 0; col < mat.cols; col++) {
        mat::Mat2D<T>::SetValue(row, col, mat.at<T>(row, col));
      }
    }
  }
};

}  // namespace opencv2
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_MAT_2D_ADAPTER_H_
