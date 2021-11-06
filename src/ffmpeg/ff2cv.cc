/*
 * Read video frame with FFmpeg and convert to OpenCV image
 *
 * Copyright (c) 2016 yohhoy
 *
 * Source: https://gist.github.com/yohhoy/f0444d3fc47f2bb2d0e2
 */

#include <iostream>
#include <vector>

// FFmpeg
#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/pixdesc.h>
#include <libswscale/swscale.h>

#ifdef __cplusplus
}
#endif

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "video-detect/ffmpeg/ff2cv.h"

namespace video_detect {
namespace ffmpeg {

int ff2cv(const char *video_file, int modulo_frame_count,
          video_detect::util::ObjectReceiver<cv::Mat> *receiver) {
  // initialize FFmpeg library
  av_register_all();
  //  av_log_set_level(AV_LOG_DEBUG);
  int ret;

  // open input file context
  AVFormatContext *inctx = nullptr;
  ret = avformat_open_input(&inctx, video_file, nullptr, nullptr);
  if (ret < 0) {
    std::cerr << "fail to avforamt_open_input(\"" << video_file
              << "\"): ret=" << ret;
    return 2;
  }
  // retrive input stream information
  ret = avformat_find_stream_info(inctx, nullptr);
  if (ret < 0) {
    std::cerr << "fail to avformat_find_stream_info: ret=" << ret;
    return 2;
  }

  // find primary video stream
  AVCodec *vcodec = nullptr;
  ret = av_find_best_stream(inctx, AVMEDIA_TYPE_VIDEO, -1, -1, &vcodec, 0);
  if (ret < 0) {
    std::cerr << "fail to av_find_best_stream: ret=" << ret;
    return 2;
  }
  const int vstrm_idx = ret;
  AVStream *vstrm = inctx->streams[vstrm_idx];

  // open video decoder context
  ret = avcodec_open2(vstrm->codec, vcodec, nullptr);
  if (ret < 0) {
    std::cerr << "fail to avcodec_open2: ret=" << ret;
    return 2;
  }

  // print input video stream informataion
  std::cout << "video_file: " << video_file << "\n"
            << "format: " << inctx->iformat->name << "\n"
            << "vcodec: " << vcodec->name << "\n"
            << "size:   " << vstrm->codec->width << 'x' << vstrm->codec->height
            << "\n"
            << "fps:    " << av_q2d(vstrm->codec->framerate) << " [fps]\n"
            << "length: "
            << av_rescale_q(vstrm->duration, vstrm->time_base, {1, 1000}) /
                   1000.
            << " [sec]\n"
            << "pixfmt: " << av_get_pix_fmt_name(vstrm->codec->pix_fmt) << "\n"
            << "frame:  " << vstrm->nb_frames << "\n"
            << std::flush;

  // initialize sample scaler
  const int dst_width = vstrm->codec->width;
  const int dst_height = vstrm->codec->height;
  const AVPixelFormat dst_pix_fmt = AV_PIX_FMT_BGR24;
  SwsContext *swsctx =
      sws_getCachedContext(nullptr, vstrm->codec->width, vstrm->codec->height,
                           vstrm->codec->pix_fmt, dst_width, dst_height,
                           dst_pix_fmt, SWS_BICUBIC, nullptr, nullptr, nullptr);
  if (!swsctx) {
    std::cerr << "fail to sws_getCachedContext";
    return 2;
  }
  std::cout << "output: " << dst_width << 'x' << dst_height << ','
            << av_get_pix_fmt_name(dst_pix_fmt) << std::endl;

  // allocate frame buffer for output
  AVFrame *frame = av_frame_alloc();
  std::vector<uint8_t> framebuf(
      avpicture_get_size(dst_pix_fmt, dst_width, dst_height));
  avpicture_fill(reinterpret_cast<AVPicture *>(frame), framebuf.data(),
                 dst_pix_fmt, dst_width, dst_height);

  // decoding loop
  AVFrame *decframe = av_frame_alloc();
  unsigned nb_frames = 0;
  bool end_of_stream = false;
  int got_pic = 0;
  AVPacket pkt;
  do {
    if (!end_of_stream) {
      // read packet from input file
      ret = av_read_frame(inctx, &pkt);
      if (ret < 0 && ret != AVERROR_EOF) {
        std::cerr << "fail to av_read_frame: ret=" << ret;
        return 2;
      }
      if (ret == 0 && pkt.stream_index != vstrm_idx) goto next_packet;
      end_of_stream = (ret == AVERROR_EOF);
    }
    if (end_of_stream) {
      // null packet for bumping process
      av_init_packet(&pkt);
      pkt.data = nullptr;
      pkt.size = 0;
    }
    // decode video frame
    avcodec_decode_video2(vstrm->codec, decframe, &got_pic, &pkt);
    if (!got_pic) goto next_packet;
    // convert frame to OpenCV matrix
    sws_scale(swsctx, decframe->data, decframe->linesize, 0, decframe->height,
              frame->data, frame->linesize);
    {
      cv::Mat image(dst_height, dst_width, CV_8UC3, framebuf.data(),
                    frame->linesize[0]);

      //////////////////////////////////////////////////////////////////
      // START - Custom code

      // Grab only modulo_frame_count'th frame (customizable later)
      if (nb_frames % modulo_frame_count == 0) {
        // Send the image to the receiver
        receiver->Accept(image);
      }
      // END - Custom Code
      //////////////////////////////////////////////////////////////////

      if (cv::waitKey(1) == 0x1b) break;
    }
    std::cout << nb_frames << '\r' << std::flush;  // dump progress
    ++nb_frames;
  next_packet:
    av_free_packet(&pkt);
  } while (!end_of_stream || got_pic);
  std::cout << nb_frames << " frames decoded" << std::endl;

  av_frame_free(&decframe);
  av_frame_free(&frame);
  avcodec_close(vstrm->codec);
  avformat_close_input(&inctx);
  return 0;
}

}  // namespace ffmpeg
}  // namespace video_detect
