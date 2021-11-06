/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_CONV_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_CONV_H_

#include <type_traits>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include "video-detect/mat/mat_2d.h"

namespace video_detect {
namespace mat {

/**
 * This function uses convolution between the provided Matrix and the Mat2D.
 * The template only allows integral types (e.g. int / float)
 * @param mat       a 2D matrix with a single channel depth e.g. a greyscale
 * image
 * @param kernel    an integral Mat2D to use in the Convolution
 * @return          the resulting 2D matrix
 */
template <typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
cv::Mat ConvCvMatKernel(const cv::Mat &mat, const Mat2D<T> &kernel) {
  // Create an empty matrix for the result
  cv::Mat result(mat.rows, mat.cols, CV_8UC1, cv::Scalar(0));

  // Determine offsets
  const int kRowOffset = kernel.GetRowCount() / 2;
  const int kColOffset = kernel.GetColCount() / 2;

  // 2D cv::Mat - Traverse the matrix
  for (int row = 0; row < mat.rows; row++) {
    for (int col = 0; col < mat.cols; col++) {
      // Perform the matrix multiplication
      T sum{};

      for (int x = 0; x < kernel.GetColCount(); x++) {
        for (int y = 0; y < kernel.GetRowCount(); y++) {
          // Get the Mat2D value at this point
          const T kKernelValue = kernel.GetValue(y, x);

          // Get the target matrix coordinate while taking into account the
          // offset of the Mat2D coordinates
          const int kRowTarget = row - kRowOffset + y;
          const int kColTarget = col - kColOffset + x;

          // Only run the summation if the target coordinate is in the bounds
          if (kRowTarget >= 0 && kColTarget >= 0 && kRowTarget < mat.rows &&
              kColTarget < mat.cols) {
            // Multiply the matrix value with the corresponding kernel value
            sum += mat.at<uint8_t>(kRowTarget, kColTarget) * kKernelValue;
          }
        }
      }

      // Set the new pixel value
      result.at<uint8_t>(row, col) = static_cast<uint8_t>(sum);
    }
  }

  return result;
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>,
          typename Q = T,
          typename = std::enable_if_t<std::is_arithmetic<Q>::value>>
Mat2D<T> ConvMat2D(const Mat2D<T> &mat, const Mat2D<Q> &kernel) {
  // Create an empty matrix for the result
  int rows = mat.GetRowCount();
  int cols = mat.GetColCount();

  Mat2D<T> result(rows, cols);

  // Determine offsets
  const int kRowOffset = kernel.GetRowCount() / 2;
  const int kColOffset = kernel.GetColCount() / 2;

  // Mat2D - Traverse the matrix
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      // Perform the matrix multiplication
      T sum{};

      for (int x = 0; x < kernel.GetColCount(); x++) {
        for (int y = 0; y < kernel.GetRowCount(); y++) {
          // Get the Mat2D value at this point
          const T kKernelValue = kernel.GetValue(y, x);

          // Get the target matrix coordinate while taking into account the
          // offset of the Mat2D coordinates
          const int kRowTarget = row - kRowOffset + y;
          const int kColTarget = col - kColOffset + x;

          // Only run the summation if the target coordinate is in the bounds
          if (kRowTarget >= 0 && kColTarget >= 0 && kRowTarget < rows &&
              kColTarget < cols) {
            // Multiply the matrix value with the corresponding kernel value
            sum += mat.GetValue(kRowTarget, kColTarget) * kKernelValue;
          }
        }
      }

      // Set the new pixel value
      result.SetValue(row, col, static_cast<uint8_t>(sum));
    }
  }

  return result;
}

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_CONV_H_
