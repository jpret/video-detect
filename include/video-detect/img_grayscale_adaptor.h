
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GRAYSCALE_ADAPTOR_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GRAYSCALE_ADAPTOR_H_

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "video-detect/util/object_receiver.h"

namespace cppeng {
namespace video_detect {

class ImgGrayScaleAdaptor : public util::ObjectReceiver<cv::Mat> {
public:
  /**
   * The ImgGrayScaleAdaptor constructor sets the flag to export images of the
   * conversion or not
   */
  explicit ImgGrayScaleAdaptor(bool export_images)
      : export_images_(export_images), conversion_counter_(0) {}

  void Accept(cv::Mat img) override {
    
    // Create a new Mat class for the grayscale image
    cv::Mat img_gray;

    // Utilize open cv to convert the image
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    // Save the images
    if (export_images_) {
      cv::imwrite(
          "normal_image_" + std::to_string(conversion_counter_) + ".png", img);
      cv::imwrite("gray_image_" + std::to_string(conversion_counter_) + ".png",
                  img_gray);
    }

    // Increase the counter
    ++conversion_counter_;
  }

private:
  int conversion_counter_;
  const bool export_images_;
};

} // namespace video_detect
} // namespace cppeng

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_GRAYSCALE_ADAPTOR_H_