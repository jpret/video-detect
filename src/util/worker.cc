/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/util/worker.h"

#include <algorithm>
#include <utility>

namespace video_detect {
namespace util {

void Worker::Accept(std::function<void()> job) {
  {
    // Obtain the queue access
    std::lock_guard<std::mutex> lock_guard(queue_access_);

    // Push the job into the queue
    jobs_.push(std::move(job));
  }

  // Execute work
  DoWork();
}

Worker::~Worker() {
  // Join the thread if it exists
  if (thread_ != nullptr) {
    thread_->join();
  }
}

bool Worker::IsBusy() { return busy_; }

void Worker::DoWork() {
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

}  // namespace util
}  // namespace video_detect
