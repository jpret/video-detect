/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_OBJECT_RECEIVER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_OBJECT_RECEIVER_H_

namespace video_detect {
namespace util {

/**
 * The ObjectReceiver class is a templated interface class to implement
 * for passing on values to a class
 */
template <typename T, typename ReturnType = void> class ObjectReceiver {
public:
  /**
   * The Accept method must be implemented for the specified template T value
   */
  virtual ReturnType Accept(T) = 0;

  virtual ~ObjectReceiver() = default;
};

} // namespace util
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_OBJECT_RECEIVER_H_
