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

TEST(MatTests, MatTestMatrixMultiplication) {
  // Create Mat2D
  Mat2D<int> mat_1({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
  Mat2D<int> mat_2({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});

  // Perform multiplication
  auto result = mat_1 * mat_2;

  // Test sum of contents
  EXPECT_EQ(result.GetValue(0, 0), 0);
  EXPECT_EQ(result.GetValue(0, 1), 1);
  EXPECT_EQ(result.GetValue(0, 2), 4);
  EXPECT_EQ(result.GetValue(1, 0), 9);
  EXPECT_EQ(result.GetValue(1, 1), 16);
  EXPECT_EQ(result.GetValue(1, 2), 25);
  EXPECT_EQ(result.GetValue(2, 0), 36);
  EXPECT_EQ(result.GetValue(2, 1), 49);
  EXPECT_EQ(result.GetValue(2, 2), 64);
}

TEST(MatTests, MatTestMatrixDivision) {
  // Create Mat2D
  Mat2D<int> mat_1({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
  Mat2D<int> mat_2({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});

  // Perform multiplication
  auto result = mat_1 / mat_2;

  // Test sum of contents
  EXPECT_EQ(result.GetValue(0, 0), 0);  // test division by zero -> expect zero
  EXPECT_EQ(result.GetValue(0, 1), 1);
  EXPECT_EQ(result.GetValue(0, 2), 1);
  EXPECT_EQ(result.GetValue(1, 0), 1);
  EXPECT_EQ(result.GetValue(1, 1), 1);
  EXPECT_EQ(result.GetValue(1, 2), 1);
  EXPECT_EQ(result.GetValue(2, 0), 1);
  EXPECT_EQ(result.GetValue(2, 1), 1);
  EXPECT_EQ(result.GetValue(2, 2), 1);
}

TEST(MatTests, MatTestMatrixSqrt) {
  // Create Mat2D
  Mat2D<int> mat({{0, 1, 4}, {9, -16, 25}, {36, 49, 64}});

  // Perform multiplication
  auto result = mat.Sqrt();

  // Test sum of contents
  EXPECT_EQ(result.GetValue(0, 0), 0);
  EXPECT_EQ(result.GetValue(0, 1), 1);
  EXPECT_EQ(result.GetValue(0, 2), 2);
  EXPECT_EQ(result.GetValue(1, 0), 3);
  EXPECT_EQ(result.GetValue(1, 1), 0);  // test a negative -> expect zero
  EXPECT_EQ(result.GetValue(1, 2), 5);
  EXPECT_EQ(result.GetValue(2, 0), 6);
  EXPECT_EQ(result.GetValue(2, 1), 7);
  EXPECT_EQ(result.GetValue(2, 2), 8);
}

TEST(MatTests, MatTestMatrixAtan2) {
  // Create Mat2D
  Mat2D<float> mat_1({{8, 7, 6}, {5, 4, 3}, {2, 1, 0}});
  Mat2D<float> mat_2({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});

  // Perform multiplication
  auto result = mat_1.Atan2(mat_2);

  // Test sum of contents
  EXPECT_TRUE(result.GetValue(0, 0) == static_cast<float>(atan2(0, 8)));
  EXPECT_TRUE(result.GetValue(0, 1) == static_cast<float>(atan2(1, 7)));
  EXPECT_TRUE(result.GetValue(0, 2) == static_cast<float>(atan2(2, 6)));
  EXPECT_TRUE(result.GetValue(1, 0) == static_cast<float>(atan2(3, 5)));
  EXPECT_TRUE(result.GetValue(1, 1) == static_cast<float>(atan2(4, 4)));
  EXPECT_TRUE(result.GetValue(1, 2) == static_cast<float>(atan2(5, 3)));
  EXPECT_TRUE(result.GetValue(2, 0) == static_cast<float>(atan2(6, 2)));
  EXPECT_TRUE(result.GetValue(2, 1) == static_cast<float>(atan2(7, 1)));
  EXPECT_TRUE(result.GetValue(2, 2) == static_cast<float>(atan2(8, 0)));
}

TEST(MatTests, MatTestMatrixToDegrees) {
  // Create Mat2D
  Mat2D<float> mat({{0, M_PI_4, M_PI_2},
                    {3*M_PI_4, M_PI, -3*M_PI_4},
                    {-M_PI_2, -M_PI_4, 2*M_PI}});

  // Perform multiplication
  auto result = mat.ToDegrees();

  // Test sum of contents
  EXPECT_EQ(result.GetValue(0, 0), 0);
  EXPECT_EQ(result.GetValue(0, 1), 45);
  EXPECT_EQ(result.GetValue(0, 2), 90);
  EXPECT_EQ(result.GetValue(1, 0), 135);
  EXPECT_EQ(result.GetValue(1, 1), 180);
  EXPECT_EQ(result.GetValue(1, 2), 225);
  EXPECT_EQ(result.GetValue(2, 0), 270);
  EXPECT_EQ(result.GetValue(2, 1), 315);
  EXPECT_EQ(result.GetValue(2, 2), 360);
}

TEST(MatTests, MatTestMatrixNormalize) {
  // Create Mat2D
  Mat2D<uint8_t> mat({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});

  // Perform multiplication
  auto result = mat.Normalize(10, 100);

  // Test sum of contents
  EXPECT_EQ(result.GetValue(0, 0), 0);
  EXPECT_EQ(result.GetValue(0, 1), 10);
  EXPECT_EQ(result.GetValue(0, 2), 20);
  EXPECT_EQ(result.GetValue(1, 0), 30);
  EXPECT_EQ(result.GetValue(1, 1), 40);
  EXPECT_EQ(result.GetValue(1, 2), 50);
  EXPECT_EQ(result.GetValue(2, 0), 60);
  EXPECT_EQ(result.GetValue(2, 1), 70);
  EXPECT_EQ(result.GetValue(2, 2), 80);
}

}  // namespace mat
}  // namespace video_detect
