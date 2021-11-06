/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/opencv2/export_u8_mat_2d.h"

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "video-detect/util/chainable_object_receiver.h"

namespace video_detect {
namespace opencv2 {

ExportU8Mat2D::ExportU8Mat2D(std::string name, std::string path)
    : counter_(0), name_(name), path_(path) {}

void ExportU8Mat2D::Accept(const mat::Mat2D<uint8_t> &mat) {
  // Create the cv::Mat matrix
  cv::Mat cv_mat(mat.GetRowCount(), mat.GetColCount(), CV_8UC1, cv::Scalar(0));

  // Set the values for the cv matrix
  for (int row = 0; row < mat.GetRowCount(); row++) {
    for (int col = 0; col < mat.GetColCount(); col++) {
      cv_mat.at<uint8_t>(row, col) = mat.GetValue(row, col);
    }
  }

  // Write the cv::Mat matrix
  const std::string output_file =
      path_ + "/" + name_ + "_" + std::to_string(counter_++) + ".png";
      std::cout << "Writine file: " << output_file << std::endl;
  cv::imwrite(output_file, cv_mat);

  // Continue the chain
  util::ChainableObjectReceiver<const mat::Mat2D<uint8_t> &>::Accept(mat);
}

}  // namespace opencv2
}  // namespace video_detect
