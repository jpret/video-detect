/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include <functional>
#include <iostream>

#include "video-detect/ffmpeg/ff2cv.h"
#include "video-detect/hv_edge_detector.h"
#include "video-detect/util/worker.h"

int main(int argc, const char *argv[]) {
  std::cout << "CppEngineer: Video Detect!" << std::endl;

  // Create a worker for executing work in the program
  video_detect::util::Worker worker;

  // Create a Horizontal Vertical Edge Detector
  video_detect::HVEdgeDetector hv_edge_detector(worker, true);

  // Read the video and analyse the frames, send the frames to the
  // hv_edge_detector
  video_detect::ffmpeg::ff2cv(
      "/workspaces/video-detect/test/data/mosaic-sample-big.mp4", 500,
      &hv_edge_detector);

  // Wait for worker to finish its work
  while (worker.IsBusy()) {
    // waiting...
  }

  // Exit the application
  return EXIT_SUCCESS;
}
