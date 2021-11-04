
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GRAYSCALE_ADAPTOR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GRAYSCALE_ADAPTOR_H_

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "video-detect/util/chainable_object_receiver.h"

namespace video_detect {
namespace img {

class GrayscaleAdaptor : public util::ChainableObjectReceiver<const cv::Mat &> {
public:
  /**
   * The GrayscaleAdaptor constructor sets the flag to export images of the
   * conversion or not
   */
  explicit GrayscaleAdaptor(bool export_images)
      : export_images_(export_images), conversion_counter_(0) {}

  void Accept(const cv::Mat & img) override {

    // Create a new Mat class for the grayscale image
    cv::Mat img_gray;

    // Utilize open cv to convert the image
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    // Save the images
    if (export_images_) {
      cv::imwrite("GrayscaleAdaptor_input_image_" +
                      std::to_string(conversion_counter_) + ".png",
                  img);
      cv::imwrite("GrayscaleAdaptor_output_image_" +
                      std::to_string(conversion_counter_) + ".png",
                  img_gray);
    }

    // Increase the counter
    ++conversion_counter_;

    // Continue the chain with the grayscale image
    ChainableObjectReceiver::Accept(img_gray);
  }

private:
  int conversion_counter_;
  const bool export_images_;
};

} // namespace img
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GRAYSCALE_ADAPTOR_H_