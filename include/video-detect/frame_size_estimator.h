/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FRAME_SIZE_ESTIMATOR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FRAME_SIZE_ESTIMATOR_H_

#include <map>
#include <string>
#include <utility>
#include <atomic>

#include "video-detect/mat/mat_2d.h"
#include "video-detect/util/object_receiver.h"

namespace video_detect {

/**
 * The FrameSizeEstimator class converts and filters a received matrix to find
 * horizontal and vertical edges based on a custom image filtering process. The
 * edges are then analysed to search for specific frame sizes which would make
 * up the video for example in a conference call.
 */
class FrameSizeEstimator
    : public util::ObjectReceiver<const mat::Mat2D<uint8_t> &> {
 public:
  /**
   * @brief Construct a new FrameSizeEstimator object
   *
   * @param export_images a boolean flag indicating whether to export images
   * @param export_path the path to where the images will be exported
   * @param confidence_level the confidence level over which the frame size will
   *                         be accepted to confidently be correct
   */
  explicit FrameSizeEstimator(bool export_images,
                              const std::string &export_path,
                              int confidence_level);

  /**
   * @brief The Accept method expects a grayscale image
   *
   * @param mat this is a 2D single channel unsigned char matrix
   */
  void Accept(const mat::Mat2D<uint8_t> &mat) override;

  /**
   * @brief Get the Best Estimate Frame Size for the input video
   *
   * @return std::pair<int, int> the best estimate frame size as
   *                             a pair [width, height]
   */
  std::pair<int, int> GetBestEstimateFrameSize();

/**
 * @brief Check if a best estimate has been found
 * 
 * @return true if a best estimate has been found
 * @return false if a best estimate has not been found
 */
  bool HasBestEstimate() const {
      return best_estimate_found_;
  }

 private:
  const bool export_images_;
  const std::string export_path_;
  const int confidence_level_;
  std::map<int, int> rows_;
  std::map<int, int> cols_;
  std::pair<int, int> frame_size_;
  std::atomic<bool> best_estimate_found_;

  typedef const mat::Mat2D<uint8_t> ConstMatU8;
  typedef mat::Mat2D<uint8_t> MatU8;

  void ExportImage(ConstMatU8 &mat,                // NOLINT(runtime/references)
                   const std::string &name_base);  // NOLINT(runtime/references)
  MatU8 ApplyGaussianFilter(ConstMatU8 &mat);      // NOLINT(runtime/references)
  MatU8 ApplyThresholdFilter(ConstMatU8 &mat);     // NOLINT(runtime/references)
  MatU8 ApplyEdgeDetectionFilter(
      ConstMatU8 &mat);                       // NOLINT(runtime/references)
  MatU8 ApplyContourFinder(ConstMatU8 &mat);  // NOLINT(runtime/references)
  MatU8 ApplyLinearFeatureFinder(
      ConstMatU8 &mat);  // NOLINT(runtime/references)
  std::map<int, int> ApplyCornerFinder(
      ConstMatU8 &mat);  // NOLINT(runtime/references)

  void UpdateFrameSizes(std::map<int, int> corners, int width, int height);
  void UpdateBestEstimateFrameSizes(int rows, int cols, int boundary);
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FRAME_SIZE_ESTIMATOR_H_
