/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_DETECT_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_DETECT_H_

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

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

static cv::Mat SmoothMatrix(const cv::Mat &mat) {
  cv::Mat result;
  cv::boxFilter(mat, result, -1, cv::Size(3, 3));
  return result;
}

static cv::Mat ThresholdMatrix(const cv::Mat &mat) {
  cv::Mat result;
  cv::threshold(mat, result, 200, 255, cv::THRESH_BINARY);
  return result;
}

static cv::Mat DetectEdgesMatrix(const cv::Mat &mat) {
  cv::Mat result(mat.rows, mat.cols, CV_16SC1, cv::Scalar(0));
  cv::Mat dx(mat.rows, mat.cols, CV_16SC1, cv::Scalar(0));
  cv::Mat dy(mat.rows, mat.cols, CV_16SC1, cv::Scalar(0));

  for (int row = 0; row < mat.rows; row++) {
    for (int col = 0; col < mat.cols; col++) {
      dx.at<int16_t>(row, col) = (int16_t)mat.at<uint8_t>(row, col);
      dy.at<int16_t>(row, col) = (int16_t)mat.at<uint8_t>(row, col);
    }
  }

  cv::Canny(dx, dy, result, 20, 40, true);

  Sobel(mat, dx, CV_8UC1, 1, 0, 3);
  Sobel(mat, dy, CV_8UC1, 0, 1, 3);

  SaveImage("DetectEdgesOutputX", "/workspaces/video-detect/build/test", dx);
  SaveImage("DetectEdgesOutputY", "/workspaces/video-detect/build/test", dy);
  return result;
}

static cv::Mat FindContoursMatrix(const cv::Mat &mat) {
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(mat, contours, hierarchy, cv::RETR_TREE,
                   cv::CHAIN_APPROX_NONE);

  cv::Mat mat_contour(mat.rows, mat.cols, CV_8UC1, cv::Scalar(0));
  drawContours(mat_contour, contours, -1, cv::Scalar(255), 1);
  SaveImage("findContours", "/workspaces/video-detect/build/test",
            mat_contour);
  return mat_contour;
}

static cv::Mat ApproxContoursMatrix(const cv::Mat &mat) { return mat; }

static void Detect(const std::string &path, const cv::Mat &mat) {
  SaveImage("DetectInput", "/workspaces/video-detect/build/test", mat);

  cv::Mat result = SmoothMatrix(mat);
  SaveImage("SmoothOutput", "/workspaces/video-detect/build/test", result);

  result = ThresholdMatrix(result);
  SaveImage("ThresholdOutput", "/workspaces/video-detect/build/test", result);

  result = DetectEdgesMatrix(result);
  SaveImage("DetectEdgesOutput", "/workspaces/video-detect/build/test", result);

  // result = FindContoursMatrix(result);
  // SaveImage("FindContoursOutput", "/workspaces/video-detect/build/test",
  // result);

  // result = ApproxContoursMatrix(result);
  // SaveImage("ApproxContoursOutput", "/workspaces/video-detect/build/test",
  // result);
}

}  // namespace opencv2
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPENCV2_DETECT_H_
