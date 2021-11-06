/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_SOBEL_XY_FILTER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_SOBEL_XY_FILTER_H_

#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include "video-detect/mat/conv.h"
#include "video-detect/mat/kernel.h"
#include "video-detect/util/chainable_object_receiver.h"

namespace video_detect {
namespace mat {

class SobelXYFilter : public util::ChainableObjectReceiver<const cv::Mat &> {
 public:
  /**
   * The SobelXYFilter constructor sets the flag to export images of the
   * conversion or not
   */
  explicit SobelXYFilter(bool export_images)
      : export_images_(export_images), conversion_counter_(0) {}

  void Accept(const cv::Mat &img) override {
    // Create a new Mat class from the edge detected image, first in the
    // X-direction
    cv::Mat img_x = ConvCvMatKernel(img, sobel_x_3x3_);
    cv::Mat img_y = ConvCvMatKernel(img, sobel_y_3x3_);

    cv::Mat img_x_f, img_y_f;
    img_x.convertTo(img_x_f, CV_64FC1);
    img_y.convertTo(img_y_f, CV_64FC1);

    // TODO(jangabriel): Refactor
    cv::Mat img_xy_f, img_xy, img_xx_f, img_yy_f, img_xxyy_f, img_mag_f,
        img_mag;
    cv::multiply(img_x_f, img_x_f, img_xx_f);
    cv::multiply(img_y_f, img_y_f, img_yy_f);
    cv::add(img_xx_f, img_yy_f, img_xxyy_f);
    cv::sqrt(img_xxyy_f, img_mag_f);
    img_mag_f.convertTo(img_mag, CV_8UC1);

    // Save the images
    if (export_images_) {
      cv::imwrite("SobelFilterXY_input_image_" +
                      std::to_string(conversion_counter_) + ".png",
                  img);
      cv::imwrite("SobelFilterXY_output_image_x_" +
                      std::to_string(conversion_counter_) + ".png",
                  img_x);
      cv::imwrite("SobelFilterXY_output_image_y_" +
                      std::to_string(conversion_counter_) + ".png",
                  img_y);
      cv::imwrite("SobelFilterXY_output_image_xy_" +
                      std::to_string(conversion_counter_) + ".png",
                  img_mag);
    }

    // Increase the counter
    ++conversion_counter_;

    // Continue the chain with the edge detected image here
    ChainableObjectReceiver::Accept(img_xy);
  }

 private:
  int conversion_counter_;
  const bool export_images_;

  // Gaussian kernel 3x3
  const Kernel<int> sobel_x_3x3_{{{1, 0, -1}, {2, 0, -2}, {1, 0, -1}}};
  const Kernel<int> sobel_y_3x3_{{{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}}};
};

}  // namespace mat
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_MAT_SOBEL_XY_FILTER_H_
