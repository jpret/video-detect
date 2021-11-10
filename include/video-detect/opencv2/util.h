/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_UTIL_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_UTIL_H_

#include <utility>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "video-detect/mat/mat_2d.h"

namespace video_detect {
namespace opencv2 {

static cv::Mat ConvertMat2DToCvMat(const mat::Mat2D<uint8_t> &mat) {
  // Create the cv::Mat matrix
  cv::Mat cv_mat(mat.GetRowCount(), mat.GetColCount(), CV_8UC1, cv::Scalar(0));

  // Set the values for the cv matrix
  for (int row = 0; row < mat.GetRowCount(); row++) {
    for (int col = 0; col < mat.GetColCount(); col++) {
      cv_mat.at<uint8_t>(row, col) = mat.GetValue(row, col);
    }
  }

  return cv_mat;
}

static cv::Mat FindContoursMatrix(const cv::Mat &mat) {
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;

  cv::findContours(mat, contours, hierarchy, cv::RETR_TREE,
                   cv::CHAIN_APPROX_NONE);

  cv::Mat mat_contour(mat.rows, mat.cols, CV_8UC1, cv::Scalar(0));

  drawContours(mat_contour, contours, -1, cv::Scalar(255), 1);

  return mat_contour;
}

}  // namespace opencv2
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_UTIL_H_
