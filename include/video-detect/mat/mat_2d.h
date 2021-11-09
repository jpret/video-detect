/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_MAT_2D_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_MAT_2D_H_

#include <cmath>
#include <initializer_list>
#include <ostream>
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
   * @example Mat2D<int> matrix{{0, 1}, {1, 0}};
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

  /**
   * @brief Calculate the sum of the matrices at each index
   *
   * @param other the other matrix to sum with this one
   * @return Mat2D<T> the resultant matrix with same size as this matrix
   */
  Mat2D<T> operator+(const Mat2D<T> &other) const {
    Mat2D<T> result(GetRowCount(), GetColCount());
    for (int row = 0; row < GetRowCount(); row++) {
      for (int col = 0; col < GetColCount(); col++) {
        // Sum the contents at the position
        result.SetValue(row, col,
                        GetValue(row, col) + other.GetValue(row, col));
      }
    }
    return result;
  }

  /**
   * @brief Calculate the multiplication of the matrices at each index
   *
   * @param other the other matrix to multiply with this one
   * @return Mat2D<T> the resultant matrix with same size as this matrix
   */
  Mat2D<T> operator*(const Mat2D<T> &other) const {
    Mat2D<T> result(GetRowCount(), GetColCount());
    for (int row = 0; row < GetRowCount(); row++) {
      for (int col = 0; col < GetColCount(); col++) {
        // Multiply the contents at the position
        result.SetValue(row, col,
                        GetValue(row, col) * other.GetValue(row, col));
      }
    }
    return result;
  }

  /**
   * @brief Calculate the division of the matrices at each index
   *
   * @param other the other matrix to divide this one by
   * @return Mat2D<T> the resultant matrix with same size as this matrix
   */
  Mat2D<T> operator/(const Mat2D<T> &other) const {
    Mat2D<T> result(GetRowCount(), GetColCount());
    for (int row = 0; row < GetRowCount(); row++) {
      for (int col = 0; col < GetColCount(); col++) {
        T value = other.GetValue(row, col);
        // Do not divide by zero
        if (value != 0) {
          result.SetValue(row, col, GetValue(row, col) / value);
        }
      }
    }
    return result;
  }

  /**
   * @brief Calculate the sqrt of the matrix
   *
   * @return Mat2D<T> the resultant matrix
   */
  Mat2D<T> Sqrt() const {
    Mat2D<T> result(GetRowCount(), GetColCount());
    for (int row = 0; row < GetRowCount(); row++) {
      for (int col = 0; col < GetColCount(); col++) {
        // sqrt() the contents at the position
        T value = GetValue(row, col);
        if (value >= 0) {
          result.SetValue(row, col, sqrt(value));
        }
      }
    }
    return result;
  }

  /**
   * @brief Calculate the atan2(y/x) value of the matrix at each index
   *
   * @param other the other matrix as the y-parameter for atan2(y,x) i.e.
   * arctan2(y/x)
   * @return Mat2D<T> the resultant matrix
   */
  Mat2D<T> Atan2(const Mat2D<T> &other) const {
    Mat2D<T> result(GetRowCount(), GetColCount());
    for (int row = 0; row < GetRowCount(); row++) {
      for (int col = 0; col < GetColCount(); col++) {
        // atan2(y,x) the contents at the position
        T x_value = GetValue(row, col);
        T y_value = other.GetValue(row, col);
        if (x_value != 0 || y_value != 0) {
          result.SetValue(row, col, static_cast<T>(atan2(y_value, x_value)));
        }
      }
    }
    return result;
  }

  /**
   * @brief Convert radians to degrees
   *
   * @return Mat2D<T> the resultant matrix
   */
  Mat2D<T> ToDegrees() const {
    Mat2D<T> result(GetRowCount(), GetColCount());
    for (int row = 0; row < GetRowCount(); row++) {
      for (int col = 0; col < GetColCount(); col++) {
        // Convert to degrees
        T value =
            static_cast<T>((GetValue(row, col) * 1.f) / (2 * M_PI) * (360));
        // Rotate into range [0;360]
        while (value < 0 || value > 360) {
          if (value < 0) {
            value += 360;
          } else if (value > 360) {
            value -= 360;
          }
        }
        result.SetValue(row, col, value);
      }
    }
    return result;
  }

  /**
   * @brief Normalize a matrix at each position
   *
   * @param max     the current expected maximum value
   * @param new_max the new maximum value to normalize to
   * @return Mat2D<T> the resultant matrix
   */
  Mat2D<T> Normalize(T max, T new_max) const {
    Mat2D<T> result(GetRowCount(), GetColCount());
    for (int row = 0; row < GetRowCount(); row++) {
      for (int col = 0; col < GetColCount(); col++) {
        // Normalize the contents at the position
        T value = GetValue(row, col);
        T new_value =
            static_cast<T>(((value * 1.f) / (max * 1.f)) * (new_max * 1.f));
        result.SetValue(row, col, new_value);
      }
    }
    return result;
  }

  /**
   * @brief Change the underlying type to a new Type
   *
   * @return Mat2D<T> the resultant matrix with same size as this matrix, but
   * with different type
   */
  template <typename NewType>
  Mat2D<NewType> CastTo() const {
    Mat2D<NewType> result(GetRowCount(), GetColCount());
    for (int row = 0; row < GetRowCount(); row++) {
      for (int col = 0; col < GetColCount(); col++) {
        // Cast the contents at the position
        result.SetValue(row, col, static_cast<NewType>(GetValue(row, col)));
      }
    }
    return result;
  }

  friend std::ostream &operator<<(std::ostream &os, const Mat2D<T>& mat) {
    for (const auto &row : mat.matrix_) {
      for (const auto &col : row) {
        os << std::to_string(col) << " ";
      }
      os << "\n";
    }
    return os;
  }

 private:
  Vector2D<T> matrix_;
};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_MAT_2D_H_
