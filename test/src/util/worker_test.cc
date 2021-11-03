#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "video-detect/util/mock_object_receiver.h"
#include "video-detect/util/worker.h"

namespace cppeng {
namespace video_detect {
namespace util {

TEST(UtilTests, WorkerTestExecution) {

  // Setup mock receiver and expect call
  MockObjectReceiver<std::string> mock_object_receiver;
  EXPECT_CALL(mock_object_receiver, Accept("Hello World!"))
      .Times(testing::Exactly(1));

  // Create worker
  Worker worker;

  // Provide the worker with a job
  worker.Accept([&mock_object_receiver]() {
    mock_object_receiver.Accept("Hello World!");
  });
}

} // namespace util
} // namespace video_detect
} // namespace cppeng