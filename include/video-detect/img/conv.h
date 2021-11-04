
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_CONV_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_CONV_H_

#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include "video-detect/img/kernel.h"

namespace video_detect {
namespace img {

/**
 * This function uses convulution between the provided Matrix and the Kernel
 * @param mat       a 2D matrix
 * @param kernel    a Kernel to use in the Convolution
 * @return          the resulting 2D matrix
 */ 
static cv::Mat ConvCvMatKernel(const cv::Mat &mat, const Kernel &kernel) {
    cv::Mat result = mat.clone();
    return result;
}

} // namespace img
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_CONV_H_