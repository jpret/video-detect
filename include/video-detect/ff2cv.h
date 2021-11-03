

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FRAME_ANALYZER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FF2CV_H_

#include "video-detect/util/object_receiver.h"
#include <opencv2/core/mat.hpp>

namespace cppeng {
namespace video_detect {

int ff2cv(int argc, const char *argv[], util::ObjectReceiver<cv::Mat> &receiver);

} // namespace video_detect
} // namespace cppeng

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FF2CV_H_
