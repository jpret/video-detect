/*
 * Read video frame with FFmpeg and convert to OpenCV image
 *
 * Copyright (c) 2016 yohhoy
 *
 * Source: https://gist.github.com/yohhoy/f0444d3fc47f2bb2d0e2
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FFMPEG_FF2CV_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FFMPEG_FF2CV_H_

#include <opencv2/core/mat.hpp>

#include "video-detect/util/object_receiver.h"

namespace video_detect {
namespace ffmpeg {

/**
 * This code is adapted from the referenced GIST to load each frame from a video
 * using FFMPEG into a OpenCV image.
 *
 * Each frame is passed on to the video_detect ObjectReceiver
 *
 * @param video_path            is the full path to the video file
 * @param modulo_frame_count    the frame count is modulo'd by this to prevent
 *                              limit the amount of frames to process by the
 * receiver
 * @param receiver              each non-limited frame is passed on to the
 * receiver
 */
int ff2cv(const char *video_file, int modulo_frame_count,
          video_detect::util::ObjectReceiver<cv::Mat> *receiver);

}  // namespace ffmpeg
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_FFMPEG_FF2CV_H_
