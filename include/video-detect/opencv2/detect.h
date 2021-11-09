/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_DETECT_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_DETECT_H_

#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace video_detect {
namespace opencv2 {

static void SaveImage(const std::string &name, const std::string &path,
                      const cv::Mat &mat) {
  // Write the cv::Mat matrix
  static int counter = 0;

  const std::string output_file =
      path + "/cv_" + name + "_" + std::to_string(counter++) + ".png";

  std::cout << "Writine file: " << output_file << std::endl;

  cv::imwrite(output_file, mat);
}

static cv::Mat FindContoursMatrix(const cv::Mat &mat) {
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(mat, contours, hierarchy, cv::RETR_TREE,
                   cv::CHAIN_APPROX_NONE);

  cv::Mat mat_contour(mat.rows, mat.cols, CV_8UC1, cv::Scalar(0));
  drawContours(mat_contour, contours, -1, cv::Scalar(255), 1);
  // SaveImage("findContours", "/workspaces/video-detect/build/test",
  //          mat_contour);
  return mat_contour;
}

}  // namespace opencv2
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_DETECT_H_
