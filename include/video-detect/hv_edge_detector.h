/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_

#include <memory>
#include <string>
#include <vector>

#include "video-detect/mat/mat_2d.h"
#include "video-detect/util/chainable_object_receiver.h"
#include "video-detect/util/object_receiver.h"

namespace video_detect {

/**
 * The HVEdgeDetector class converts and filters a received matrix to find
 * horizontal and vertical edges
 */
class HVEdgeDetector
    : public util::ObjectReceiver<const mat::Mat2D<uint8_t> &> {
 public:
  explicit HVEdgeDetector(bool export_images, const std::string &export_path);

  void Accept(const mat::Mat2D<uint8_t> &img) override;

 private:
  std::vector<
      std::unique_ptr<util::ObjectReceiver<const mat::Mat2D<uint8_t> &>>>
      handler_chain;
  const bool export_images_;
  const std::string export_path_;

  typedef util::ChainableObjectReceiver<const mat::Mat2D<uint8_t> &> Chain;
  void AddExportImage(
      Chain &c, const std::string &name_base);   // NOLINT(runtime/references)
  void AddGaussianFilterToChain(Chain &c);       // NOLINT(runtime/references)
  void AddThresholdFilterToChain(Chain &c);       // NOLINT(runtime/references)
  void AddEdgeDetectionFilterToChain(Chain &c);  // NOLINT(runtime/references)
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
