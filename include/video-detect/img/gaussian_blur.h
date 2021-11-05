/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GAUSSIAN_BLUR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GAUSSIAN_BLUR_H_

#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include "video-detect/img/conv.h"
#include "video-detect/img/kernel.h"
#include "video-detect/util/chainable_object_receiver.h"

namespace video_detect {
namespace img {

class GaussianBlur : public util::ChainableObjectReceiver<const cv::Mat &> {
public:
  /**
   * The GaussianBlur constructor sets the flag to export images of the
   * conversion or not
   */
  explicit GaussianBlur(bool export_images)
      : export_images_(export_images), conversion_counter_(0) {}

  void Accept(const cv::Mat & img) override {

    // Create a new Mat class from the blurred image
    cv::Mat img_blur = ConvCvMatKernel(img, kernel_3x3_);

    // Save the images
    if (export_images_) {
      cv::imwrite("GaussianBlur_input_image_" +
                      std::to_string(conversion_counter_) + ".png",
                  img);
      cv::imwrite("GaussianBlur_output_image_" +
                      std::to_string(conversion_counter_) + ".png",
                  img_blur);
    }

    // Increase the counter
    ++conversion_counter_;

    // Continue the chain with the blurred image
    ChainableObjectReceiver::Accept(img_blur);
  }

private:
  int conversion_counter_;
  const bool export_images_;

  // Gaussian kernel 3x3
  const Kernel<float> kernel_3x3_{{{1.f / 24, 2.f / 24, 1.f / 24},
                                   {2.f / 24, 4.f / 24, 2.f / 24},
                                   {1.f / 24, 2.f / 24, 1.f / 24}}};
};

} // namespace img
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GRAYSCALE_ADAPTOR_H_