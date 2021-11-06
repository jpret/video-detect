/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_FILTER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_FILTER_H_

#include <utility>

#include "video-detect/mat/conv.h"
#include "video-detect/mat/mat_2d.h"
#include "video-detect/util/chainable_object_receiver.h"

namespace video_detect {
namespace mat {

/**
 * @brief The Filter class uses a predefined filter Kernel and convolutes it
 * with a received matrix. The resultant matrix is passed on to the next
 * handler.
 *
 * @tparam T the type of 2D matrix of the Kernel
 */
template <typename T>
class Filter : public util::ChainableObjectReceiver<const Mat2D<T> &> {
 public:
  /**
   * @brief Construct a new Filter object
   *
   * @param kernel a 2D matrix with the Kernel to use on matrices during
   *               filtering
   */
  explicit Filter(const mat::Mat2D<T> &&kernel) : kernel_(std::move(kernel)) {}

  void Accept(const cv::Mat &mat) override {
    // Create a new Mat class from the filtered matrix
    Mat2D<T> mat_filtered = ConvMat2D(mat, kernel_);

    // Continue the chain with the filtered image
    util::ChainableObjectReceiver<const Mat2D<T>&>::Accept(mat_filtered);
  }

 private:
  const mat::Mat2D<T> &&kernel_;
};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_FILTER_H_
