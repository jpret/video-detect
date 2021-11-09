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
 * @tparam MatType the type of the 2D matrix
 * @tparam KernelType the type of Kernel (defaulted to the same as the matrix)
 */
template <typename MatType, typename KernelType = MatType>
class Filter : public util::ChainableObjectReceiver<const Mat2D<MatType> &> {
 public:
  /**
   * @brief Construct a new Filter object
   *
   * @param kernel a 2D matrix with the Kernel to use on matrices during
   *               filtering
   */
  explicit Filter(const mat::Mat2D<KernelType> &kernel) : kernel_(kernel) {}

  /**
   * @brief This version of the filter is used in combination with a chainable
   * object receiver. This means you can setup a filter chain of responsibility.
   *
   * @param mat the target 2D matrix to filter
   */
  void Accept(const Mat2D<MatType> &mat) override {
    // Continue the chain with the filtered image
    util::ChainableObjectReceiver<const Mat2D<MatType> &>::Accept(Apply(mat));
  }

  /**
   * @brief Apply the filter as setup in the constructor
   *
   * @param mat the target 2D matrix to filter
   * @return Mat2D<MatType> the filtered 2D matrix
   */
  Mat2D<MatType> Apply(const Mat2D<MatType> &mat) {
    return ConvMat2D(mat, kernel_);
  }

 private:
  const mat::Mat2D<KernelType> &kernel_;
};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_FILTER_H_
