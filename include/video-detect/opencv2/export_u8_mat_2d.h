/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_EXPORT_U8_MAT_2D_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_EXPORT_U8_MAT_2D_H_

#include <string>

#include "video-detect/mat/mat_2d.h"
#include "video-detect/util/object_receiver.h"

namespace video_detect {
namespace opencv2 {

class ExportU8Mat2D : public util::ObjectReceiver<const mat::Mat2D<uint8_t> &> {
 public:
  explicit ExportU8Mat2D(std::string name, std::string path);

  void Accept(const mat::Mat2D<uint8_t> &mat) override;

 private:
  static int counter_;
  const std::string name_;
  const std::string path_;
};

}  // namespace opencv2
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_EXPORT_U8_MAT_2D_H_
