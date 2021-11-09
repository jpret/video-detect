/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_THRESHOLD_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_THRESHOLD_H_

#include <algorithm>
#include <utility>

#include "video-detect/mat/mat_2d.h"

namespace video_detect {
namespace mat {

template <typename MatType, typename KernelType = MatType>
class Threshold {
 public:
  explicit Threshold(MatType lower_bound, MatType upper_bound, MatType minimum,
                     MatType maximum)
      : range_{std::make_pair<MatType, MatType>(std::move(lower_bound),
                                                std::move(upper_bound))},
        minimum_(minimum),
        maximum_(maximum) {}

  Mat2D<MatType> Apply(const Mat2D<MatType> &mat) {
    Mat2D<MatType> result(mat.GetRowCount(), mat.GetColCount());
    for (int row = 0; row < mat.GetRowCount(); row++) {
      for (int col = 0; col < mat.GetColCount(); col++) {
        MatType value = mat.GetValue(row, col);
        MatType new_value = MatType{};
        // Check if the value is in the bounds, else set it to min / max of
        // MatType
        auto it = range_.begin();
        bool found_range = false;
        while (!found_range && it != range_.end()) {
          // Change the value if it is out of bounds
          if (value < it->first) {
            new_value = minimum_;
          } else if (value > it->second) {
            new_value = maximum_;
          } else {
            // Set the new_value, it is in bounds and stop the search
            new_value = mat.GetValue(row, col);
            found_range = true;
          }
          it++;
        }
        result.SetValue(row, col, new_value);
      }
    }
    return result;
  }

 private:
  const std::vector<std::pair<MatType, MatType>> range_;
  const MatType minimum_;
  const MatType maximum_;
};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_THRESHOLD_H_
