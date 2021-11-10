/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_CONV_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_CONV_H_

#include <type_traits>
#include <vector>

#include "video-detect/mat/mat_2d.h"

namespace video_detect {
namespace mat {

template <typename MatType,
          typename = std::enable_if_t<std::is_arithmetic<MatType>::value>,
          typename KernelType = MatType,
          typename = std::enable_if_t<std::is_arithmetic<KernelType>::value>>
Mat2D<MatType> ConvMat2D(const Mat2D<MatType> &mat,
                         const Mat2D<KernelType> &kernel) {
  // Create an empty matrix for the result
  int rows = mat.GetRowCount();
  int cols = mat.GetColCount();

  Mat2D<MatType> result(rows, cols);

  // Determine offsets
  const int kRowOffset = kernel.GetRowCount() / 2;
  const int kColOffset = kernel.GetColCount() / 2;

  // Mat2D - Traverse the matrix
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      // Perform the matrix multiplication
      KernelType sum{};

      for (int x = 0; x < kernel.GetColCount(); x++) {
        for (int y = 0; y < kernel.GetRowCount(); y++) {
          // Get the Mat2D value at this point
          const KernelType kKernelValue = kernel.GetValue(y, x);

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
      result.SetValue(row, col, static_cast<MatType>(sum));
    }
  }

  return result;
}

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_CONV_H_
