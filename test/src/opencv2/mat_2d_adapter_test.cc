/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/opencv2/mat_2d_adapter.h"

#include <gtest/gtest.h>

#include <opencv2/core/mat.hpp>

#include "video-detect/mat/mat_2d.h"


namespace video_detect {
namespace opencv2 {

TEST(OpenCv2Tests, TestCvMatToMat2DAdapter) {
  // Create single channel (uint8_t) matrix (using the templated Mat_ version to
  // allow for using the << overload)
  cv::Mat_<uint8_t> opencv_mat(3, 3);

  // Populate a test matrix
  opencv_mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;

  // Create a 3x3 Mat2D using the adaptor
  const mat::Mat2D<uint8_t> result = Mat2DAdapter<uint8_t>(opencv_mat);

  // Test the expected result
  EXPECT_EQ(result.GetValue(0, 0), 1);
  EXPECT_EQ(result.GetValue(0, 1), 2);
  EXPECT_EQ(result.GetValue(0, 2), 3);
  EXPECT_EQ(result.GetValue(1, 0), 4);
  EXPECT_EQ(result.GetValue(1, 1), 5);
  EXPECT_EQ(result.GetValue(1, 2), 6);
  EXPECT_EQ(result.GetValue(2, 0), 7);
  EXPECT_EQ(result.GetValue(2, 1), 8);
  EXPECT_EQ(result.GetValue(2, 2), 9);
}

}  // namespace opencv2
}  // namespace video_detect
