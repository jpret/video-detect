/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_THRESHOLD_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_THRESHOLD_H_

#include <utility>

#include "video-detect/mat/mat_2d.h"
#include "video-detect/util/chainable_object_receiver.h"

namespace video_detect {
namespace mat {

template <typename MatType, typename KernelType = MatType>
class Threshold : public util::ChainableObjectReceiver<const Mat2D<MatType> &> {
 public:
  explicit Threshold(MatType lower_bound, MatType upper_bound)
      : lower_bound_(lower_bound), upper_bound_(upper_bound) {}

  void Accept(const Mat2D<MatType> &mat) override {
    // Continue the chain with the thresholded image
    util::ChainableObjectReceiver<const Mat2D<MatType> &>::Accept(Apply(mat));
  }

  Mat2D<MatType> Apply(const Mat2D<MatType> &mat) {
    Mat2D<MatType> result(mat.GetRowCount(), mat.GetColCount());
    for (int row = 0; row < mat.GetRowCount(); row++) {
      for (int col = 0; col < mat.GetColCount(); col++) {
        MatType value = mat.GetValue(row, col);
        // Check if the value is in the bounds, else set it to min / max of
        // MatType
        if (value < lower_bound_) {
          result.SetValue(row, col, MatType{});
        } else if (value > upper_bound_) {
          result.SetValue(row, col, (sizeof(MatType) * 256) - 1);
        } else {
          result.SetValue(row, col, value);
        }
      }
    }
    return result;
  }

 private:
  const MatType lower_bound_;
  const MatType upper_bound_;
};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_THRESHOLD_H_
