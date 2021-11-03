#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "video-detect/img/kernel.h"

namespace video_detect {
namespace img {

TEST(ImgTests, KernelTestCreateAndGetAttributes) {

  // Create Kernel
  Kernel<int> kernel({{0,1,2},{3,4,5},{6,7,8}});

  // Test sizes
  EXPECT_EQ(kernel.GetRowCount(), 3);
  EXPECT_EQ(kernel.GetColCount(), 3);

  // Test values
  EXPECT_EQ(kernel.GetValue(0,0), 0);
  EXPECT_EQ(kernel.GetValue(0,1), 1);
  EXPECT_EQ(kernel.GetValue(0,2), 2);
  EXPECT_EQ(kernel.GetValue(1,0), 3);
  EXPECT_EQ(kernel.GetValue(1,1), 4);
  EXPECT_EQ(kernel.GetValue(1,2), 5);
  EXPECT_EQ(kernel.GetValue(2,0), 6);
  EXPECT_EQ(kernel.GetValue(2,1), 7);
  EXPECT_EQ(kernel.GetValue(2,2), 8);

  // Test out of range values
  EXPECT_EQ(kernel.GetValue(10,10), int());
  EXPECT_EQ(kernel.GetValue(-2,-2), int());
}

} // namespace util
} // namespace video_detect