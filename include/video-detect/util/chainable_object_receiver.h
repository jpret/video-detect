/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_H_

#include "video-detect/util/object_receiver.h"

namespace video_detect {
namespace util {

/**
 * The ChainableObjectReceiver class implements the chain of responsibility
 * design pattern using the ObjectReceiver. This means that the different object
 * receivers can be chained together. Each link in the chain can decide itself
 * to continue walking the chain or to exit the chain.
 */
template <typename T, typename ReturnType = void>
class ChainableObjectReceiver : public ObjectReceiver<T, ReturnType> {
 public:
  /**
   * Append a ChainableObjectReceiver implementation to the current chain
   */
  virtual void AppendToChain(
      ChainableObjectReceiver<T, ReturnType>
          &chainable_object_receiver) {  // NOLINT(runtime/references)
    if (next_ == nullptr) {
      next_ = &chainable_object_receiver;
    } else {
      next_->AppendToChain(chainable_object_receiver);
    }
  }

  /**
   * Implement the Accept method to set the default chain behaviour
   */
  virtual ReturnType Accept(T t) {
    if (next_ != nullptr) {
      next_->Accept(t);
    }
  }

  virtual ~ChainableObjectReceiver() = default;

 private:
  ChainableObjectReceiver<T, ReturnType> *next_{nullptr};
};

}  // namespace util
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_H_
