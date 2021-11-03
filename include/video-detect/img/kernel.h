
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_KERNEL_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_KERNEL_H_

#include <initializer_list>
#include <vector>

#include "video-detect/img/two_dim_matrix.h"

namespace video_detect {
namespace img {


/**
 * The Kernel class is used together in the filter operation on a matrix
 */
template <typename T> class Kernel {
public:
  /**
   * A Kernel is initialized using a 2D brace-enclosed initializer list
   *
   * @example Kernel kernel{{0,1}{1,0}};
   */
  explicit Kernel(TwoDimMatrix<T> &&matrix) : matrix_(std::move(matrix)) {}

  T GetValue(int row, int col) {
    if (row < matrix_.size()) {
      if (col < matrix_.at(row).size()) {
        return matrix_.at(row).at(col);
      }
    }
    // Return empty value for out of bounds request
    return T();
  }

  int GetRowCount() { return matrix_.size(); }

  int GetColCount() {
    if (!matrix_.empty()) {
      return matrix_.front().size();
    } else {
      return 0;
    }
  }

private:
  const TwoDimMatrix<T> matrix_;
};

} // namespace img
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_KERNEL_H_