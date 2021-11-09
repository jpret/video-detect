/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_MERGE_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_MERGE_H_

#include <utility>

#include "video-detect/util/chainable_object_receiver.h"
#include "video-detect/util/object_receiver.h"


namespace video_detect {
namespace util {

template <typename T>
class ChainableObjectReceiverSplit : public util::ChainableObjectReceiver<T> {
 public:
  explicit ChainableObjectReceiverSplit(
      util::ObjectReceiver<std::pair<T, T>>
          &merge_to_receiver)  // NOLINT(runtime/references)
      : merge_to_receiver_(merge_to_receiver), link_rx_(false) {}

  void Accept(T t) override {
    // Merge the chain, store link 1
    if (!link_rx_) {
      link1_ = t;
      link_rx_ = true;
    } else {
      // Both links have arrived, forward it to the merge to receiver
      merge_to_receiver_.Accept(std::pair<T, T>(link1_, t));
    }

    // The normal chain is not continued here
  }

 private:
  util::ObjectReceiver<T> &merge_to_receiver_;
  bool link_rx_;
  T link1_;
};

}  // namespace util
}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_UTIL_CHAINABLE_OBJECT_RECEIVER_MERGE_H_
