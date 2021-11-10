/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/mat/conv.h"

#include <gtest/gtest.h>

#include "video-detect/mat/mat_2d.h"

namespace video_detect {
namespace mat {

TEST(MatTests, ConvTestConvMat2DMatKernel) {
  // Create a test matrix
  Mat2D<uint8_t> mat{{{1, 1, 1, 0, 0},
                      {0, 1, 1, 1, 0},
                      {0, 0, 1, 1, 1},
                      {0, 0, 1, 1, 0},
                      {0, 1, 1, 0, 0}}};

  // Create a 3x3 Mat2D for this test
  const Mat2D<float> kernel_3x3{
      {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}}};

  // Perform the convolution
  Mat2D<uint8_t> result = ConvMat2D<uint8_t, float>(mat, kernel_3x3);

  // Test the expected -> EXCLUDING the edge
  EXPECT_EQ(result.GetValue(1, 1), 4);
  EXPECT_EQ(result.GetValue(1, 2), 3);
  EXPECT_EQ(result.GetValue(1, 3), 4);
  EXPECT_EQ(result.GetValue(2, 1), 2);
  EXPECT_EQ(result.GetValue(2, 2), 4);
  EXPECT_EQ(result.GetValue(2, 3), 3);
  EXPECT_EQ(result.GetValue(3, 1), 2);
  EXPECT_EQ(result.GetValue(3, 2), 3);
  EXPECT_EQ(result.GetValue(3, 3), 4);
}

}  // namespace mat
}  // namespace video_detect
