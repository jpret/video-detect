/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv2/core/mat.hpp>

#include "video-detect/img/conv.h"
#include "video-detect/img/kernel.h"

namespace video_detect {
namespace img {

TEST(ImgTests, ConvTestConvCvMatKernel) {

  // Create signle channel matrix (using the templated Mat_ version to allow for
  // using the << overload)
  cv::Mat_<uint8_t> mat(5, 5);

  // Populate a test matrix
  mat << 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,
      0;

  // Create a 3x3 Kernel for this test
  const Kernel<float> kernel_3x3{
      {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}}};

  // Perform the convolution
  cv::Mat result = ConvCvMatKernel(mat, kernel_3x3);

  // Test the expected -> EXCLUDING the edge
  EXPECT_EQ(result.at<uint8_t>(1, 1), 4);
  EXPECT_EQ(result.at<uint8_t>(1, 2), 3);
  EXPECT_EQ(result.at<uint8_t>(1, 3), 4);
  EXPECT_EQ(result.at<uint8_t>(2, 1), 2);
  EXPECT_EQ(result.at<uint8_t>(2, 2), 4);
  EXPECT_EQ(result.at<uint8_t>(2, 3), 3);
  EXPECT_EQ(result.at<uint8_t>(3, 1), 2);
  EXPECT_EQ(result.at<uint8_t>(3, 2), 3);
  EXPECT_EQ(result.at<uint8_t>(3, 3), 4);
}

} // namespace img
} // namespace video_detect