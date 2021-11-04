
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_CONV_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_CONV_H_

#include <iostream>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include "video-detect/img/kernel.h"

namespace video_detect {
namespace img {

/**
 * This function uses convulution between the provided Matrix and the Kernel
 * @param mat       a 2D matrix with 3 channels depth e.g. a RGB image
 * @param kernel    an integer Kernel to use in the Convolution
 * @return          the resulting 2D matrix
 */
static cv::Mat ConvCvMat3bKernel(const cv::Mat &mat,
                                 const Kernel<int> &kernel) {
  cv::Mat result = mat.clone();

  // Two D - traverse the matrix
  for (int row = 0; row < mat.rows; row++) {
    for (int col = 0; col < mat.cols; col++) {

      // Now travers the perform the matrix multiplication
      uint8_t r{},g{},b{};

      for (int y = -kernel.GetRowCount() / 2; y < kernel.GetRowCount() / 2;
           y++) {
        for (int x = -kernel.GetColCount() / 2; x < kernel.GetColCount() / 2;
             x++) {
          // Multiply the matrix value with the corresponding kernel value       
          r += (uint8_t)result.at<cv::Vec3b>(row + y, col + x)[0];
          g += (uint8_t)result.at<cv::Vec3b>(row + y, col + x)[1];
          b += (uint8_t)result.at<cv::Vec3b>(row + y, col + x)[2];
        }
      }
      // Set the new pixel value  
      result.at<cv::Vec3b>(row, col, 0) = r / kernel.GetSumOfContents();
      result.at<cv::Vec3b>(row, col, 1) = g / kernel.GetSumOfContents();
      result.at<cv::Vec3b>(row, col, 2) = b / kernel.GetSumOfContents();
    }
  }

  return result;
}

} // namespace img
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_CONV_H_