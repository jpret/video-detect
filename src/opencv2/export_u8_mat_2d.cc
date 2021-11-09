/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/opencv2/export_u8_mat_2d.h"

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "video-detect/opencv2/util.h"


namespace video_detect {
namespace opencv2 {

int ExportU8Mat2D::counter_ = 0;

ExportU8Mat2D::ExportU8Mat2D(std::string name, std::string path)
    : name_(name), path_(path) {}

void ExportU8Mat2D::Accept(const mat::Mat2D<uint8_t> &mat) {
  // Create the cv::Mat matrix
  cv::Mat cv_mat = ConvertMat2DToCvMat(mat);

  // Write the cv::Mat matrix
  const std::string output_file =
      path_ + "/" + name_ + "_" + std::to_string(counter_++) + ".png";
  std::cout << "Writine file: " << output_file << std::endl;
  cv::imwrite(output_file, cv_mat);
}

}  // namespace opencv2
}  // namespace video_detect
