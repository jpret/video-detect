#include "video-detect/ff2cv.h"
#include <functional>
#include <iostream>


int main(int argc, const char *argv[]) {
  std::cout << "Hello World!" << std::endl;

  const char test_vid[] =
      "/workspaces/video-detect/test/data/mosaic-sample-big.mp4";
  const char *args_v[] = {argv[0], &test_vid[0], nullptr};
  int args_c = sizeof(args_v) / sizeof(char *) - 1;

  cppeng::video_detect::ff2cv(args_c, args_v);

  return EXIT_SUCCESS;
}