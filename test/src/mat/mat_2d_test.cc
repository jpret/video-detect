/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/mat/mat_2d.h"

#include <gtest/gtest.h>

namespace video_detect {
namespace mat {

TEST(MatTests, MatTestCreateAndGetAttributes) {
  // Create Mat2D
  Mat2D<int> mat({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});

  // Test sizes
  EXPECT_EQ(mat.GetRowCount(), 3);
  EXPECT_EQ(mat.GetColCount(), 3);

  // Test values
  EXPECT_EQ(mat.GetValue(0, 0), 0);
  EXPECT_EQ(mat.GetValue(0, 1), 1);
  EXPECT_EQ(mat.GetValue(0, 2), 2);
  EXPECT_EQ(mat.GetValue(1, 0), 3);
  EXPECT_EQ(mat.GetValue(1, 1), 4);
  EXPECT_EQ(mat.GetValue(1, 2), 5);
  EXPECT_EQ(mat.GetValue(2, 0), 6);
  EXPECT_EQ(mat.GetValue(2, 1), 7);
  EXPECT_EQ(mat.GetValue(2, 2), 8);

  // Test out of range values
  EXPECT_EQ(mat.GetValue(10, 10), int());
  EXPECT_EQ(mat.GetValue(-2, -2), int());
}

TEST(MatTests, MatTestGetSum) {
  // Create Mat2D
  Mat2D<int> mat_int({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
  Mat2D<double> mat_double({{0.5, 1.5, 2.5}, {3.5, 4.5, 5.5}, {6.5, 7.5, 8.5}});
  Mat2D<float> mat_float({{0.5, 1.5, 2.5}, {3.5, 4.5, 5.5}, {6.5, 7.5, 8.5}});

  // Test sum of contents
  EXPECT_EQ(mat_int.GetSumOfContents(), 36);
  EXPECT_EQ(mat_double.GetSumOfContents(), 40.5);
  EXPECT_EQ(mat_float.GetSumOfContents(), 40.5);
}

TEST(MatTests, MatTestMatrixAddition) {
  // Create Mat2D
  Mat2D<int> mat_1({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
  Mat2D<int> mat_2({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});

  // Perform addition
  auto result = mat_1 + mat_2;

  // Test sum of contents
  EXPECT_EQ(result.GetValue(0, 0), 0);
  EXPECT_EQ(result.GetValue(0, 1), 2);
  EXPECT_EQ(result.GetValue(0, 2), 4);
  EXPECT_EQ(result.GetValue(1, 0), 6);
  EXPECT_EQ(result.GetValue(1, 1), 8);
  EXPECT_EQ(result.GetValue(1, 2), 10);
  EXPECT_EQ(result.GetValue(2, 0), 12);
  EXPECT_EQ(result.GetValue(2, 1), 14);
  EXPECT_EQ(result.GetValue(2, 2), 16);
}

}  // namespace mat
}  // namespace video_detect
