/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_

#include <memory>
#include <utility>
#include <vector>

#include "video-detect/mat/gaussian_blur.h"
#include "video-detect/mat/grayscale_adaptor.h"
#include "video-detect/mat/sobel_xy_filter.h"
#include "video-detect/util/object_receiver.h"
#include "video-detect/util/worker.h"

namespace video_detect {

/**
 * The EdgeDetector class converts and filters a received image to find
 * horizontal and vertical edges
 */
class HVEdgeDetector : public util::ObjectReceiver<cv::Mat> {
 public:
  explicit HVEdgeDetector(util::Worker &worker,  // NOLINT(runtime/references)
                          bool export_images)
      : worker_(worker) {
    // Setup the conversion chain strategy:
    // 1. A grayscale adaptor
    auto grayscale_adaptor =
        std::make_unique<mat::GrayscaleAdaptor>(export_images);

    // 2. A Gaussian blur filter -> requires a grayscale image as input
    auto gaussian_blur = std::make_unique<mat::GaussianBlur>(export_images);
    grayscale_adaptor->AppendToChain(*gaussian_blur);

    // 3. Sobel Edge detection filter
    auto sobel_xy_filter = std::make_unique<mat::SobelXYFilter>(export_images);
    grayscale_adaptor->AppendToChain(*sobel_xy_filter);

    // 4. Edge extractor
    // TODO(jangabriel) add extractor

    // Push the items to the vector owning the chain instances
    handler_chain.push_back(std::move(grayscale_adaptor));
    handler_chain.push_back(std::move(gaussian_blur));
    handler_chain.push_back(std::move(sobel_xy_filter));
  }

  void Accept(cv::Mat img) override {
    // Send the image to the handler chain via the worker
    if (!handler_chain.empty()) {
      // Pass the handler chain entry point to the worker via a lambda
      // This will now be handled by the worker
      worker_.Accept([this, img = std::move(img)]() {
        handler_chain.front()->Accept(img);
      });
    }
  }

 private:
  util::Worker &worker_;
  std::vector<std::unique_ptr<util::ObjectReceiver<const cv::Mat &>>>
      handler_chain;
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
