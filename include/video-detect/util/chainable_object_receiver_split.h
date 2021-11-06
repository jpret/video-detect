/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_SPLIT_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_SPLIT_H_

#include "video-detect/util/chainable_object_receiver.h"

namespace video_detect {
namespace util {

template <typename T>
class ChainableObjectReceiverSplit : public util::ChainableObjectReceiver<T> {
 public:
  explicit ChainableObjectReceiverSplit(
      util::ChainableObjectReceiver<T>
          &split_to_chain)  // NOLINT(runtime/references)
      : split_to_chain_(split_to_chain) {}

  void Accept(T t) override {
    // Split the chain: Leg 1
    ChainableObjectReceiver<T>::Accept(t);
    // Split the chain: Leg 2
    split_to_chain_.Accept(t);
  }

 private:
  util::ChainableObjectReceiver<T> &split_to_chain_;
};

}  // namespace util
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_SPLIT_H_
