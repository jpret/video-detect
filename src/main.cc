/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include <iostream>

#include "video-detect/ffmpeg/ff2cv.h"
#include "video-detect/frame_size_estimator.h"
#include "video-detect/mat_bridge.h"
#include "video-detect/options.h"
#include "video-detect/util/worker.h"

/**
 * @brief Application main entry point.
 *
 * @param argc Amount of arguments passed to the program
 * @param argv Arguments to parse
 * @return int the exit result of the program
 */
int main(int argc, const char *argv[]) {
  std::cout << "CppEngineer: Video Detect, v. " << VIDEO_DETECT_VERSION
            << std::endl;

  // Parse the arguments, if the Parse() method returns, then the arguments were
  // parsed successfully
  video_detect::Options options;
  options.Parse(argc, argv);

  // Create a single threaded worker for executing work in the program
  video_detect::util::Worker worker;

  // Create a FrameSizeEstimator
  video_detect::FrameSizeEstimator frame_size_estimator(
      options.IsExportImages(), options.GetOutputPath(),
      options.GetConfidenceLevel());

  // Create a matrix bridge between the external code for reading in the video
  // files and our program
  video_detect::MatBridge mat_bridge(worker, frame_size_estimator);

  // Read the video and analyse the frames, send the frames to the
  // matrix bridge
  if (video_detect::ffmpeg::ff2cv(options.GetFileInput().c_str(),
                                  options.GetFrameModulo(), &mat_bridge) != 0) {
    std::cout << "Error in loading video!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Wait for worker to finish its work
  while (worker.IsBusy()) {
    // If a best estimate has been found then cancel the remaining work
    if (frame_size_estimator.HasBestEstimate()) {
      worker.CancelWork();
    }
  }

  // Print the best estimate frame size
  bool result = frame_size_estimator.HasBestEstimate();
  auto frame_size = frame_size_estimator.GetBestEstimateFrameSize();
  if (result) {
    std::cout << "Found individual frame size: " << frame_size.first << ", "
              << frame_size.second << std::endl;
  } else {
    std::cout << "No best estimate found, if you suspect a false negative, "
                 "lower the --fmod and --clevel values.\n"
              << std::endl;
    std::cout << "Frame size equal to window size: " << frame_size.first << ", "
              << frame_size.second << std::endl;
  }

  // Exit the application
  return frame_size_estimator.HasBestEstimate();
}
