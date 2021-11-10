/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/frame_size_estimator.h"

#include <iostream>
#include <set>
#include <utility>

#include "video-detect/mat/filter.h"
#include "video-detect/mat/kernel_defs.h"
#include "video-detect/mat/threshold.h"
#include "video-detect/opencv2/export_u8_mat_2d.h"
#include "video-detect/opencv2/mat_2d_adapter.h"
#include "video-detect/opencv2/util.h"

namespace video_detect {

FrameSizeEstimator::FrameSizeEstimator(bool export_images,
                                       const std::string& export_path,
                                       int confidence_level)
    : export_images_(export_images),
      export_path_(export_path),
      confidence_level_(confidence_level),
      best_estimate_found_(false) {}

void FrameSizeEstimator::Accept(const mat::Mat2D<uint8_t>& mat) {
  //
  // This is the main image analysis strategy
  //

  // 1. Apply a gaussian filter to smooth the image
  MatU8 result = ApplyGaussianFilter(mat);

  // 2. Apply a threshold filter to remove out of bounds values
  //    This reduces noise later on
  result = ApplyThresholdFilter(result);

  // 3. Apply a Sobel edge detection filter
  //    the resultant matrix is the sobel magnitude matrix
  result = ApplyEdgeDetectionFilter(result);

  // 4. Apply a Contour finder using the edge detected matrix
  result = ApplyContourFinder(result);

  // 5. Approximate contours with linear features
  result = ApplyLinearFeatureFinder(result);

  // 6. Use the linear features image and find corners
  auto corners = ApplyCornerFinder(result);

  // 7. Update the counted frame sizes based on the corners and the frame
  //    size of the image
  UpdateFrameSizes(corners, result.GetRowCount(), result.GetColCount());

  // 8. Update and print the current best estimate frame size
  UpdateBestEstimateFrameSizes(result.GetRowCount(), result.GetColCount(), 5);
}

void FrameSizeEstimator::ExportImage(ConstMatU8& mat,
                                     const std::string& name_base) {
  // If the export images flag is set, export the image
  if (export_images_) {
    // Create the image exporter
    opencv2::ExportU8Mat2D exporter(name_base, export_path_);

    // Export the image
    exporter.Accept(mat);
  }
}

FrameSizeEstimator::MatU8 FrameSizeEstimator::ApplyGaussianFilter(
    ConstMatU8& mat) {
  // Create filter
  mat::Filter<uint8_t, float> filter(mat::kKernelGaussian3x3);

  // Export input image
  ExportImage(mat, "GaussianFilterInput");

  // Filter image
  MatU8 result = filter.Apply(mat);

  // Export output image
  ExportImage(result, "GaussianFilterOutput");

  // Return result
  return result;
}

FrameSizeEstimator::MatU8 FrameSizeEstimator::ApplyThresholdFilter(
    ConstMatU8& mat) {
  // Create filter
  mat::Threshold<uint8_t> threshold(100, 200, 0, 255);

  // Export input image
  ExportImage(mat, "ThresholdFilterInput");

  // Filter image
  MatU8 result = threshold.Apply(mat);

  // Export output image
  ExportImage(result, "ThresholdFilterOutput");

  // Return result
  return result;
}

FrameSizeEstimator::MatU8 FrameSizeEstimator::ApplyEdgeDetectionFilter(
    ConstMatU8& mat) {
  // Create filters
  mat::Filter<uint8_t, int8_t> x_filter(mat::kSobelX3x3);
  mat::Filter<uint8_t, int8_t> y_filter(mat::kSobelY3x3);

  // Export input image
  ExportImage(mat, "EdgeDetectionFilterInput");

  // Filter images
  auto x_mat = x_filter.Apply(mat).CastTo<float>();
  auto y_mat = y_filter.Apply(mat).CastTo<float>();

  // Calculate Sobel Magnitude => mag = sqrt(x_mat² + y_mat²);
  auto result_mag =
      ((x_mat * x_mat) + (y_mat * y_mat)).Sqrt().CastTo<uint8_t>();

  // Export output images - checking with int to prevent casting
  if (export_images_) {
    ExportImage(x_mat.CastTo<uint8_t>(), "EdgeDetectionFilterOutput_X");
    ExportImage(y_mat.CastTo<uint8_t>(), "EdgeDetectionFilterOutput_Y");
    ExportImage(result_mag, "EdgeDetectionFilterOutputMag");
  }

  // Calculate the magnitude image
  return result_mag.CastTo<uint8_t>();
}

FrameSizeEstimator::MatU8 FrameSizeEstimator::ApplyContourFinder(
    ConstMatU8& mat) {
  // Use open cv to calculate the contours
  auto result = opencv2::Mat2DAdapter<uint8_t>(
      opencv2::FindContoursMatrix(opencv2::ConvertMat2DToCvMat(mat)));

  // Export images
  ExportImage(result, "ContourFinderOutput");

  // Return
  return result;
}

FrameSizeEstimator::MatU8 FrameSizeEstimator::ApplyLinearFeatureFinder(
    ConstMatU8& mat) {
  // Local variables
  static const int kLineLengthH = 20;
  static const int kLineLengthV = 15;
  int line_counter = 0;
  MatU8 result_h(mat.GetRowCount(), mat.GetColCount());
  MatU8 result_v(mat.GetRowCount(), mat.GetColCount());

  // Find linear features -> HORIZONTAL
  for (int row = 0; row < mat.GetRowCount(); row++) {
    for (int col = 0; col < mat.GetColCount(); col++) {
      // Go through each column to check if we have a linear line
      if (mat.GetValue(row, col) == 255) {
        ++line_counter;
      } else if (line_counter >= kLineLengthH) {
        // This means we have a horizontal line -> color it in!
        for (int x = col - line_counter; x <= col; x++) {
          result_h.SetValue(row, x, 255);
        }
        line_counter = 0;
      } else {
        // This means we did not detect a horizontal line
        line_counter = 0;
      }
    }
    line_counter = 0;
  }

  // Find linear features -> VERTICAL
  for (int col = 0; col < mat.GetColCount(); col++) {
    for (int row = 0; row < mat.GetRowCount(); row++) {
      // Go through each column to check if we have a linear line
      if (mat.GetValue(row, col) == 255) {
        ++line_counter;
      } else if (line_counter >= kLineLengthV) {
        // This means we have a vertical line -> color it in!
        for (int y = row - line_counter; y <= row; y++) {
          result_v.SetValue(y, col, 255);
        }
        line_counter = 0;
      } else {
        // This means we did not detect a vertical line
        line_counter = 0;
      }
    }
    line_counter = 0;
  }

  auto result = result_v + result_h;
  ExportImage(result, "LinearFeatureFinderOutput");
  return result;
}

std::map<int, int> FrameSizeEstimator::ApplyCornerFinder(ConstMatU8& mat) {
  // Local variables
  MatU8 result(mat.GetRowCount(), mat.GetColCount());
  std::map<int, int> corners;
  static const int kLineLength = 10;

  // Find corners features
  for (int col = 0; col < mat.GetColCount(); col++) {
    for (int row = 0; row < mat.GetRowCount(); row++) {
      // Go through each column to check if we have a corner line
      // First ensure that we are on a Horizontal line

      // Check if we are on a horizontal line
      int line_counter = 0;
      int x = col - kLineLength;

      // Continue the loop for the set line length, stop if the line
      // counter has reached that length
      while ((x <= col + kLineLength) && (line_counter < kLineLength)) {
        if (mat.GetValue(row, x) == 255) {
          line_counter++;
        }

        x++;
      }

      // This means we are on a horizontal line
      if (line_counter >= kLineLength) {
        // Check if we are on a vertical line crossing
        line_counter = 0;

        // Continue the loop for the set line length, stop if the line
        // counter has reached that length
        int y = row - kLineLength;
        while ((y <= row + kLineLength) && (line_counter < kLineLength)) {
          if (mat.GetValue(y, col) == 255) {
            line_counter++;
          }

          y++;
        }

        // This means we are on a vertical line which also means we are on a
        // corner where a H-Line and V-Line meets which increases the
        // probability that this is in fact a frame corener
        if (line_counter >= kLineLength) {
          result.SetValue(row, col, 255);
          // Add to corners
          corners.insert(std::make_pair(row, col));
        }
      }
    }
  }

  // Export output image
  ExportImage(result, "CornerFinderOutput");

  // Return corners
  return corners;
}

void FrameSizeEstimator::UpdateFrameSizes(std::map<int, int> corners, int rows,
                                          int cols) {
  // We know that the frames should fit into the width x height of the image
  // We can thus check to see if the founded corners fits into that window
  for (const auto& corner : corners) {
    float result_row = (rows * 1.f);

    // Ensure that the corner's row is not zero to prevent zero-division
    if (corner.first > 0) {
      // Divide the total rows i.e. window height by the corner's row-position
      result_row /= (corner.first * 1.f);

      // Truncate the value to 1 decimal
      result_row = truncf(result_row * 10) / 10;

      // Check if the value has a zero-digit as a first decimal
      if (static_cast<int>(result_row * 10) % 10 == 0) {
        // This means we have divided the height of the matrix perfectly by the
        // row-position of the corner.
        auto it = rows_.find(static_cast<int>(result_row));
        if (it != rows_.end()) {
          // Add the candidate amount of rows in the height of the window to its
          // cummulative sum
          it->second += static_cast<int>(result_row);
        } else if (static_cast<int>(result_row) != rows) {
          // Insert the first occurance of this exact row count into the
          // row count holder
          rows_[static_cast<int>(result_row)] = 1;
        }
      }
    }

    // Now perform the same for the columns
    float result_col = (cols * 1.f);

    // Ensure that the corner's column is not zero to prevent zero-division
    if (corner.second > 0) {
      // Divide the total columns i.e. window width by the corner's col-position
      result_col /= (corner.second * 1.f);

      // Truncate the value to 1 decimal
      result_col = truncf(result_col * 10) / 10;

      // Check if the value has a zero-digit as a first decimal
      if (static_cast<int>(result_col * 10) % 10 == 0) {
        // This means we have divided the width of the matrix perfectly by the
        // col-position of the corner.
        auto it = cols_.find(static_cast<int>(result_col));
        if (it != cols_.end()) {
          // Add the candidate amount of cols in the width of the window to its
          // cummulative sum
          it->second += static_cast<int>(result_col);
        } else if (static_cast<int>(result_col) != cols) {
          // Insert the first occurance of this exact col count into the
          // col count holder
          cols_[static_cast<int>(result_col)] = 1;
        }
      }
    }
  }
}

void FrameSizeEstimator::UpdateBestEstimateFrameSizes(int rows, int cols,
                                                      int boundary) {
  //
  // The values in the cummulative row/col counters are amounts that are valid
  // above a certain confidence level (to prevent outliers) This means that for
  // a 600 px width you will have something like the following:
  // 6  [35] - Indicating the first frame in a window
  // 2  [18] - Indicating the third frame in a window
  // 1  [1]  - Indicating a corner on the edge of the window
  // 3  [21] - Indicating the second frame of the window
  // 64 [3]  - Outlier
  //
  // This part of the algorithm thus detects whether the
  // values are all part of the maximum amount of frames i.e. 1,2,3,6 are all
  // feasible values for a 6-column wide frame window

  // Modulo the rows
  std::map<int, int> result_row;
  for (const auto& row_outer : rows_) {
    result_row[row_outer.first] = 0;
    // Modulo each row with the current row and sum
    for (const auto& row_inner : rows_) {
      int result = row_outer.first % row_inner.first;
      result_row[row_outer.first] += result;
    }
  }
  // The minimum row would be the most feasible (and divisible) option
  auto row = std::min_element(
      result_row.begin(), result_row.end(),
      [this](const auto& l, const auto& r) {
        // Weight the frequency with the modulo
        float left = (1.f * l.second) / (1.f * rows_.find(l.first)->second);
        float right = (1.f * r.second) / (1.f * rows_.find(r.first)->second);
        return left < right;
      });

  // Modulo the cols
  std::map<int, int> result_col;
  for (const auto& col_outer : cols_) {
    result_col[col_outer.first] = 0;

    // Modulo each row with the current col and sum
    for (const auto& col_inner : cols_) {
      int result = col_outer.first % col_inner.first;
      result_col[col_outer.first] += result;
    }
  }
  // The minimum col would be the most feasible (and divisible) option
  auto col = std::min_element(
      result_col.begin(), result_col.end(),
      [this](const auto& l, const auto& r) {
        // Weight the frequency with the modulo
        float left = (1.f * l.second) / (1.f * cols_.find(l.first)->second);
        float right = (1.f * r.second) / (1.f * cols_.find(r.first)->second);
        return left < right;
      });

  if (export_images_) {
    // Print the rows
    std::cout << "Rows: ";
    for (auto& r : rows_) {
      if (r.first == row->first) {
        std::cout << '*';
      }
      std::cout << r.first << "[" << r.second
                << ", mod_res: " << result_row.find(r.first)->second << "] ";
    }
    std::cout << std::endl;

    // Print the cols
    std::cout << "Columns: ";
    for (auto& c : cols_) {
      if (c.first == col->first) {
        std::cout << '*';
      }
      std::cout << c.first << "[" << c.second
                << ", mod_res: " << result_col.find(c.first)->second << "] ";
    }
    std::cout << std::endl;
  }

  // Boundary - Implement the confidence level here
  int row_size = (rows_.find(row->first)->second >= boundary)
                     ? (1.f * rows) / (1.f * row->first)
                     : rows;
  int col_size = (cols_.find(col->first)->second >= boundary)
                     ? (1.f * cols) / (1.f * col->first)
                     : cols;

  // A best estimate has been found if the cummulitive
  // sum of the selected row & col is larger than the
  // boundary
  if (rows_.find(row->first)->second >= boundary &&
      cols_.find(col->first)->second >= boundary) {
    if (export_images_) {
      std::cout << "Found Best Estimate!" << std::endl;
    }
    best_estimate_found_ = true;
  }

  // Return best case row + col if it is above the boundary
  frame_size_ = std::make_pair(col_size, row_size);
}

std::pair<int, int> FrameSizeEstimator::GetBestEstimateFrameSize() {
  return frame_size_;
}

}  // namespace video_detect
