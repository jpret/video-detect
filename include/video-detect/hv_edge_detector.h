/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_

#include <memory>
#include <string>
#include <vector>

#include "video-detect/mat/mat_2d.h"
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

  void Accept(const mat::Mat2D<uint8_t> &mat) override;

 private:
  const bool export_images_;
  const std::string export_path_;

  typedef const mat::Mat2D<uint8_t> ConstMatU8;
  typedef mat::Mat2D<uint8_t> MatU8;

  void ExportImage(ConstMatU8 &mat,                // NOLINT(runtime/references)
                   const std::string &name_base);  // NOLINT(runtime/references)
  MatU8 ApplyGaussianFilter(ConstMatU8 &mat);      // NOLINT(runtime/references)
  MatU8 ApplyThresholdFilter(ConstMatU8 &mat);     // NOLINT(runtime/references)
  MatU8 ApplyEdgeDetectionFilter(
      ConstMatU8 &mat);                       // NOLINT(runtime/references)
  MatU8 ApplyContourFinder(ConstMatU8 &mat);  // NOLINT(runtime/references)
  MatU8 ApplyLinearFeatureFinder(ConstMatU8 &mat);  // NOLINT(runtime/references)
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_HV_EDGE_DETECTOR_H_
