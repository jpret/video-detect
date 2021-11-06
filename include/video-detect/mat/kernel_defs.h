/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_KERNEL_DEFS_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_KERNEL_DEFS_H_

#include "video-detect/mat/mat_2d.h"

namespace video_detect {
namespace mat {

static const Mat2D<float> kKernelGaussian3x3{{{1.f / 24, 2.f / 24, 1.f / 24},
                                              {2.f / 24, 4.f / 24, 2.f / 24},
                                              {1.f / 24, 2.f / 24, 1.f / 24}}};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_KERNEL_DEFS_H_
