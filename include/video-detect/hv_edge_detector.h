/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_

#include <memory>
#include <utility>
#include <vector>

#include "video-detect/mat/filter.h"
#include "video-detect/mat/kernel_defs.h"
#include "video-detect/util/object_receiver.h"

namespace video_detect {

/**
 * The HVEdgeDetector class converts and filters a received matrix to find
 * horizontal and vertical edges
 */
class HVEdgeDetector : public util::ObjectReceiver<const mat::Mat2D<uint8_t>&> {
 public:
  explicit HVEdgeDetector(bool export_images) {
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

  void Accept(const mat::Mat2D<uint8_t>& img) override {
    if (!handler_chain.empty()) {
      handler_chain.front()->Accept(img);
    }
  }

 private:
  std::vector<std::unique_ptr<util::ObjectReceiver<const mat::Mat2D<uint8_t>&>>>
      handler_chain;
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
