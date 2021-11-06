/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/hv_edge_detector.h"

#include <utility>

#include "video-detect/mat/filter.h"
#include "video-detect/mat/kernel_defs.h"

namespace video_detect {

HVEdgeDetector::HVEdgeDetector(bool export_images) {
  // Setup the conversion chain strategy
  // 1. A Gaussian blur filter -> requires a grayscale image as input
  auto gaussian_blur =
      std::make_unique<mat::Filter<uint8_t, float>>(mat::kKernelGaussian3x3);

  // 2. Horizontal edge detection filter

  // 3. Vertical edge detection filter

  // 4. Split the chain

  // 5. Combine the chain

  // Push the items to the vector owning the chain instances
  // handler_chain.push_back(std::move(grayscale_adaptor));
  handler_chain.push_back(std::move(gaussian_blur));
}

void HVEdgeDetector::Accept(const mat::Mat2D<uint8_t>& img) {
  if (!handler_chain.empty()) {
    handler_chain.front()->Accept(img);
  }
}

}  // namespace video_detect
