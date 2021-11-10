/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_KERNEL_DEFS_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_KERNEL_DEFS_H_

#include "video-detect/mat/mat_2d.h"

namespace video_detect {
namespace mat {

constexpr int k3x3 = 24;
static const Mat2D<float> kKernelGaussian3x3{
    {{1.f / k3x3, 2.f / k3x3, 1.f / k3x3},
     {2.f / k3x3, 4.f / k3x3, 2.f / k3x3},
     {1.f / k3x3, 2.f / k3x3, 1.f / k3x3}}};

constexpr int k5x5 = 273;
static const Mat2D<float> kKernelGaussian5x5{
    {{1.f / k5x5, 4.f / k5x5, 7.f / k5x5, 4.f / k5x5, 1.f / k5x5},
     {4.f / k5x5, 16.f / k5x5, 26.f / k5x5, 16.f / k5x5, 4.f / k5x5},
     {7.f / k5x5, 26.f / k5x5, 41.f / k5x5, 26.f / k5x5, 7.f / k5x5},
     {4.f / k5x5, 16.f / k5x5, 26.f / k5x5, 16.f / k5x5, 4.f / k5x5},
     {1.f / k5x5, 4.f / k5x5, 7.f / k5x5, 4.f / k5x5, 1.f / k5x5}}};

static const Mat2D<int8_t> kSobelX3x3{{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}};

static const Mat2D<int8_t> kSobelY3x3{{{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}}};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_KERNEL_DEFS_H_
