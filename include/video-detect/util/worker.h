/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_WORKER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_WORKER_H_

#include "video-detect/util/object_receiver.h"

#include <algorithm>
#include <atomic>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

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
  void Accept(std::function<void()> job) override {
    {
      // Obtain the queue access
      std::lock_guard<std::mutex> lock_guard(queue_access_);

      // Push the job into the queue
      jobs_.push(std::move(job));
    }

    // Execute work
    DoWork();
  }

  /**
   * Cleanup the thread
   */
  ~Worker() {
    // Join the thread if it exists
    if (thread_ != nullptr) {
      thread_->join();
    }
  }

  bool IsBusy() { return busy_; }

private:
  std::queue<std::function<void()>> jobs_; // queue to hold the jobs
  std::unique_ptr<std::thread> thread_{nullptr};
  std::mutex queue_access_;
  std::atomic<bool> busy_{false};

  /**
   * The DoWork method is where all the work in the queue gets executed by the
   * executor
   */
  void DoWork() {

    // Only start the working thread when it is not yet busy
    if (!busy_) {
      // Set the working flag
      busy_ = true;

      // Join the thread if it exists
      if (thread_ != nullptr) {
        thread_->join();
      }

      // Start the thread and go do the work
      thread_ = std::make_unique<std::thread>([this] {
        // Do all the work until empty
        while (!jobs_.empty()) {
          {
            // Obtain the queue access
            std::lock_guard<std::mutex> lock_guard(queue_access_);

            // Execute the job and pop it from the queue
            jobs_.front()();
            jobs_.pop();
          }
        }
        // Reset the working flag
        busy_ = false;
      });
    }
  }
};

} // namespace util
} // namespace video_detect

#endif // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_EXECUTOR_H_
