
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_

#include "video-detect/img/grayscale_adaptor.h"
#include "video-detect/util/object_receiver.h"
#include "video-detect/util/worker.h"

namespace video_detect {
namespace img {

/**
 * The EdgeDetector class converts and filters a received image to find
 * horizontal and vertical edges
 */
class HVEdgeDetector : public util::ObjectReceiver<cv::Mat> {
public:
  explicit HVEdgeDetector(util::Worker &worker, bool export_images)
      : worker_(worker) {
    // Setup the conversion chain strategy:
    // 1. The grayscale adaptor
    auto grayscale_adaptor = std::make_unique<GrayscaleAdaptor>(export_images);

    // 2. Then a Gaussian filter
    // TODO

    // 3. Sobel Edge detection filter
    // TODO

    // 4. Edge extractor
    // TODO

    // Push the items to the vector owning the chain instances
    handler_chain.push_back(std::move(grayscale_adaptor));
  }

  void Accept(cv::Mat img) override {
    // Send the image to the handler chain via the worker
    if (!handler_chain.empty()) {
      worker_.Accept([this, img]() { handler_chain.front()->Accept(img); });
    }
  }

private:
  util::Worker &worker_;
  std::vector<std::unique_ptr<util::ObjectReceiver<cv::Mat>>> handler_chain;
};

} // namespace img
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_