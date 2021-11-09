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
  //

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
  ExportImage(mat, "GaussianFilterInput");

  // Filter image
  MatU8 result = filter.Apply(mat);

  // Export output image
  ExportImage(result, "GaussianFilterOutput");

  // Return result
  return result;
}

HVEdgeDetector::MatU8 HVEdgeDetector::ApplyThresholdFilter(ConstMatU8& mat) {
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

HVEdgeDetector::MatU8 HVEdgeDetector::ApplyEdgeDetectionFilter(
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

HVEdgeDetector::MatU8 HVEdgeDetector::ApplyContourFinder(ConstMatU8& mat) {
  // MatU8 result(mat.GetRowCount(), mat.GetColCount());

  opencv2::FindContoursMatrix(opencv2::ConvertMat2DToCvMat(mat));

  // const int win_w = 3;
  // const int win_h = 10;
  // int sum_prev = 0;

  // for (int row = 0; row < mat.GetRowCount(); row += win_h) {
  //   for (int col = 0; col < mat.GetColCount(); col += win_w) {
  //     int sum_next = 0;
  //     for (int scan_x = 0; scan_x < win_w; scan_x++) {
  //       for (int scan_y = 0; scan_y < win_h; scan_y++) {
  //         sum_next += mat.GetValue(scan_x + col, scan_y + row);
  //       }
  //     }
  //     if (sum_next > sum_prev + 10 || sum_next < sum_prev - 10) {
  //       result.SetValue(row, col, 255);
  //       sum_prev = sum_next;
  //     }
  //   }
  // }

  // ExportImage(result, "ContourFinder");
  return mat;
}

}  // namespace video_detect
