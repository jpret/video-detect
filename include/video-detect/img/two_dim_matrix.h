
#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_TWO_DIM_MATRIX_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_TWO_DIM_MATRIX_H_

#include <initializer_list>
#include <vector>

namespace video_detect {
namespace img {

/**
 * The TwoDimMatrix aliases a 2D vector
 */
template <typename T> using TwoDimMatrix = std::vector<std::vector<T>>;

} // namespace img
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_IMG_TWO_DIM_MATRIX_H_