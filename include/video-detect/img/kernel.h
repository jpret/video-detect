
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_KERNEL_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_KERNEL_H_

#include <initializer_list>
#include <vector>
#include <type_traits>

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

  /**
   *  Get the value of the Kernel for the specified coordinate
   *  @param row the row / y-axis coordinate
   *  @param col the column / x-axis coordinate
   */
  T GetValue(int row, int col) const {
    if (row < matrix_.size()) {
      if (col < matrix_.at(row).size()) {
        return matrix_.at(row).at(col);
      }
    }
    // Return empty value for out of bounds request
    return T();
  }

  /**
   * Get the Row count
   */
  int GetRowCount() const { return matrix_.size(); }

  /**
   * Get the Column count
   */ 
  int GetColCount() const {
    if (!matrix_.empty()) {
      return matrix_.front().size();
    } else {
      return 0;
    }
  }

  /**
   * Get the sum of the contents (only if it is arithmetic)
   */ 
  template <typename Q = T, typename = std::enable_if_t<std::is_arithmetic<Q>::value>>
  Q GetSumOfContents() const {
    Q sum = Q();
    for (const auto &row : matrix_) {
      for (const auto &col : row) {
        sum += col;
      }
    }
    return sum;
  }

private:
  const TwoDimMatrix<T> matrix_;
};

} // namespace img
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_KERNEL_H_