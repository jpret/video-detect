/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_WORKER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_WORKER_H_

#include <algorithm>
#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

#include "video-detect/util/object_receiver.h"

namespace video_detect {
namespace util {

/**
 * The Worker class handles the execution of work / jobs in the program.
 * It is a single threaded worker.
 */
class Worker : public ObjectReceiver<std::function<void()>> {
 public:
  /**
   * The Accept a lambda-type std::function to perform the work
   */
  void Accept(std::function<void()> job) override;

  /**
   * Cleanup the thread
   */
  ~Worker();

  bool IsBusy();

  void CancelWork();

 private:
  std::queue<std::function<void()>> jobs_;  // queue to hold the jobs
  std::unique_ptr<std::thread> thread_{nullptr};
  std::mutex queue_access_;
  std::atomic<bool> busy_{false};
  std::atomic<bool> cancel_work_{false};

  /**
   * The DoWork method is where all the work in the queue gets executed by the
   * executor
   */
  void DoWork();
};

}  // namespace util
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_WORKER_H_
