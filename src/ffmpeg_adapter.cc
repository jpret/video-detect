
#include <iostream>

// FFmpeg
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/pixdesc.h>
#include <libswscale/swscale.h>
}

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int adapt() { std::cout << "Adapting..." << std::endl; }