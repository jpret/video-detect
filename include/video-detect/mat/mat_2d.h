/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_MAT_2D_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_MAT_2D_H_

#include <initializer_list>
#include <type_traits>
#include <utility>
#include <vector>

#include "video-detect/mat/vector_2d.h"

namespace video_detect {
namespace mat {

/**
 * The Mat2D class represents a 2D templated vector for use as a matrix
 */
template <typename T>
class Mat2D {
 public:
  /**
   * A Mat2D constructor using a 2D brace-enclosed initializer list
   *
   * @example Mat2D matrix{{0, 1}, {1, 0}};
   */
  explicit Mat2D(Vector2D<T> &&matrix) : matrix_(std::move(matrix)) {}

  /**
   * @brief Construct a new Mat 2D object by size
   *
   * @param rows the amount of rows (y)
   * @param cols the amount of colums (x)
   */
  explicit Mat2D(int rows, int cols) { Resize(rows, cols); }

  /**
   *  Get the value of the Mat2D at the specified coordinate
   *  @param row the row / y-axis coordinate
   *  @param col the column / x-axis coordinate
   */
  T GetValue(int row, int col) const {
    if (row < matrix_.size()) {
      if (col < matrix_.at(row).size()) {
        return matrix_.at(row).at(col);
      }
    }
    // Return empty value for an out of range request
    return T();
  }

  /**
   *  Set the value of the Mat2D at the specified coordinate
   *  @param row the row / y-axis coordinate
   *  @param col the column / x-axis coordinate
   *  @param value the new value to set
   */
  T SetValue(int row, int col, T value) {
    if (row < matrix_.size()) {
      if (col < matrix_.at(row).size()) {
        matrix_.at(row).at(col) = value;
      }
    }
    // Return empty value for an out of range request
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
  template <typename Q = T,
            typename = std::enable_if_t<std::is_arithmetic<Q>::value>>
  Q GetSumOfContents() const {
    Q sum = Q();
    for (const auto &row : matrix_) {
      for (const auto &col : row) {
        sum += col;
      }
    }
    return sum;
  }

  /**
   * @brief Resize the matrix
   *
   * @param rows the new row count
   * @param cols the new column count
   */
  void Resize(int rows, int cols) {
    // Resize the Vector2D
    matrix_.resize(rows);
    for (auto &row : matrix_) {
      row.resize(cols);
    }
  }

 private:
  Vector2D<T> matrix_;
};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_MAT_2D_H_
