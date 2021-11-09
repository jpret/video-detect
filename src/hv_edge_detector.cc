/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/hv_edge_detector.h"

#include <utility>

#include "video-detect/mat/filter.h"
#include "video-detect/mat/kernel_defs.h"
#include "video-detect/mat/threshold.h"
#include "video-detect/opencv2/detect.h"
#include "video-detect/opencv2/export_u8_mat_2d.h"
#include "video-detect/opencv2/mat_2d_adapter.h"
#include "video-detect/opencv2/util.h"

namespace video_detect {

HVEdgeDetector::HVEdgeDetector(bool export_images,
                               const std::string& export_path)
    : export_images_(export_images), export_path_(export_path) {}

void HVEdgeDetector::Accept(const mat::Mat2D<uint8_t>& mat) {
  // Temporary: use the OpenCV way
  // opencv2::Detect(export_path_, opencv2::ConvertMat2DToCvMat(mat));

  // 1. Add a gaussian filter to smooth image
  MatU8 result = ApplyGaussianFilter(mat);

  // 2. Add a threshold filter to remove out of bounds values
  result = ApplyThresholdFilter(result);

  // 3. Add Sobel edge detection filter
  result = ApplyEdgeDetectionFilter(result);

  // 4. Add Contour finder
  result = ApplyContourFinder(result);

  // 5. Approximate contours with linear features
  result = ApplyLinearFeatureFinder(result);

  // 6. Find rectangles with "frame-like" attributes
}

void HVEdgeDetector::ExportImage(ConstMatU8& mat,
                                 const std::string& name_base) {
  // If the export images flag is set, export the image
  if (export_images_) {
    // Create the image exporter
    opencv2::ExportU8Mat2D exporter(name_base, export_path_);

    // Export the image
    exporter.Accept(mat);
  }
}

HVEdgeDetector::MatU8 HVEdgeDetector::ApplyGaussianFilter(ConstMatU8& mat) {
  // Create filter
  mat::Filter<uint8_t, float> filter(mat::kKernelGaussian3x3);

  // Export input image
  //ExportImage(mat, "GaussianFilterInput");

  // Filter image
  MatU8 result = filter.Apply(mat);

  // Export output image
  //ExportImage(result, "GaussianFilterOutput");

  // Return result
  return result;
}

HVEdgeDetector::MatU8 HVEdgeDetector::ApplyThresholdFilter(ConstMatU8& mat) {
  // Create filter
  mat::Threshold<uint8_t> threshold(100, 200, 0, 255);

  // Export input image
  //ExportImage(mat, "ThresholdFilterInput");

  // Filter image
  MatU8 result = threshold.Apply(mat);

  // Export output image
  //ExportImage(result, "ThresholdFilterOutput");

  // Return result
  return result;
}

HVEdgeDetector::MatU8 HVEdgeDetector::ApplyEdgeDetectionFilter(
    ConstMatU8& mat) {
  // Create filters
  mat::Filter<uint8_t, int8_t> x_filter(mat::kSobelX3x3);
  mat::Filter<uint8_t, int8_t> y_filter(mat::kSobelY3x3);

  // Export input image
  //ExportImage(mat, "EdgeDetectionFilterInput");

  // Filter images
  auto x_mat = x_filter.Apply(mat).CastTo<float>();
  auto y_mat = y_filter.Apply(mat).CastTo<float>();

  // Calculate Sobel Magnitude => mag = sqrt(x_mat² + y_mat²);
  auto result_mag =
      ((x_mat * x_mat) + (y_mat * y_mat)).Sqrt().CastTo<uint8_t>();

  // Export output images - checking with int to prevent casting
  if (export_images_) {
    //ExportImage(x_mat.CastTo<uint8_t>(), "EdgeDetectionFilterOutput_X");
    //ExportImage(y_mat.CastTo<uint8_t>(), "EdgeDetectionFilterOutput_Y");
    //ExportImage(result_mag, "EdgeDetectionFilterOutputMag");
  }

  // Calculate the magnitude image
  return result_mag.CastTo<uint8_t>();
}

HVEdgeDetector::MatU8 HVEdgeDetector::ApplyContourFinder(ConstMatU8& mat) {
  // Use open cv to calculate the contours
  return opencv2::Mat2DAdapter<uint8_t>(
      opencv2::FindContoursMatrix(opencv2::ConvertMat2DToCvMat(mat)));
  return mat;
}

HVEdgeDetector::MatU8 HVEdgeDetector::ApplyLinearFeatureFinder(
    ConstMatU8& mat) {

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
        // This means we had a horizontal line -> color it in!
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
        // This means we had a vertical line -> color it in!
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

}  // namespace video_detect
