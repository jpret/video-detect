/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_VLINE_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_VLINE_H_

#include <cmath>
#include <deque>
#include <iostream>
#include <utility>

#include "video-detect/mat/mat_2d.h"
#include "video-detect/opencv2/export_u8_mat_2d.h"
#include "video-detect/util/chainable_object_receiver.h"

namespace video_detect {

class VLine
    : public util::ChainableObjectReceiver<const mat::Mat2D<uint8_t> &> {
 public:
  void Accept(const mat::Mat2D<uint8_t> &mat) override {
    if (mat1_.GetRowCount() == 0) {
      mat1_ = mat;
    } else if (mat2_.GetRowCount() == 0) {
      mat2_ = mat;

      std::cout << "Rx both!\n";

      mat::Mat2D<uint8_t> mat_mag(mat.GetRowCount(), mat.GetColCount());
      mat::Mat2D<uint8_t> mat_deg(mat.GetRowCount(), mat.GetColCount());

      for (int row = 0; row < mat.GetRowCount(); row++) {
        for (int col = 0; col < mat.GetColCount(); col++) {
          float gx = mat1_.GetValue(row, col);
          gx *= gx;
          float gy = mat2_.GetValue(row, col);
          gy *= gy;
          float g = sqrt(gx + gy);
          mat_mag.SetValue(row, col, (uint8_t)g);

          float theta = atan(gy / gx);
          theta *= 180 / M_PI;
          int w = 1;
          theta = abs(theta);
          if (((theta >= 90 - w && theta <= 90 + w) ||
               (theta >= 180 - w && theta <= 180 + w)) &&
              g > 200) {
            mat_deg.SetValue(row, col, 0);
          } else {
            mat_deg.SetValue(row, col, 255);
          }
        }
      }
      opencv2::ExportU8Mat2D exporter("TestOutput.png",
                                      "/workspaces/video-detect/build/test");
      exporter.Accept(mat_mag);
      exporter.Accept(mat_deg);
    }

    // Continue the chain with the filtered image
    util::ChainableObjectReceiver<const mat::Mat2D<uint8_t> &>::Accept(mat);
  }

 private:
  mat::Mat2D<uint8_t> mat1_{0, 0};
  mat::Mat2D<uint8_t> mat2_{0, 0};
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_VLINE_H_
