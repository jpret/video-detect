/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/hv_edge_detector.h"

#include <utility>

#include "video-detect/mat/Threshold.h"
#include "video-detect/mat/filter.h"
#include "video-detect/mat/kernel_defs.h"
#include "video-detect/opencv2/detect.h"
#include "video-detect/opencv2/export_u8_mat_2d.h"
#include "video-detect/opencv2/util.h"
#include "video-detect/util/chainable_object_receiver_split.h"
#include "video-detect/vline.h"

namespace video_detect {

HVEdgeDetector::HVEdgeDetector(bool export_images,
                               const std::string& export_path)
    : export_images_(export_images), export_path_(export_path) {
  // Setup the conversion chain strategy start
  auto chain_start = std::make_unique<Chain>();

  // 1. Add a gaussian filter to smooth image
  AddGaussianFilterToChain(*chain_start);

  // 2. Add a threshold filter to remove out of bounds values
  AddThresholdFilterToChain(*chain_start);

  // 3. Add Sobel edge detection filter
  AddEdgeDetectionFilterToChain(*chain_start);

  // 4. Add Contour finder
  //

  // 5. Approximate contours with linear features
  //

  // 6. Find rectangles with "frame-like" attributes

  // Finally, push the front of the chain to the chain handler
  handler_chain.push_back(std::move(chain_start));
}

void HVEdgeDetector::Accept(const mat::Mat2D<uint8_t>& img) {
  // Temporary: use the OpenCV way
  opencv2::Detect(export_path_, opencv2::ConvertMat2DToCvMat(img));

  if (!handler_chain.empty()) {
    // During the time building the chain, the chain start
    // was added last
    handler_chain.back()->Accept(img);
  }
}

void HVEdgeDetector::AddExportImage(Chain& c, const std::string& name_base) {
  // If the export images flag is set, export the image
  if (export_images_) {
    // Create the image exporter
    std::unique_ptr<opencv2::ExportU8Mat2D> exporter;
    exporter =
        std::make_unique<opencv2::ExportU8Mat2D>(name_base, export_path_);

    // Add exporter to the chain
    c.AppendToChain(*exporter);

    // Add to chain handler owner
    handler_chain.push_back(std::move(exporter));
  }
}

void HVEdgeDetector::AddGaussianFilterToChain(Chain& c) {
  // Create filter
  auto filter =
      std::make_unique<mat::Filter<uint8_t, float>>(mat::kKernelGaussian3x3);

  // Add filter to chain + exporters (export_image check done by
  // AddExportImage())
  AddExportImage(c, "GaussianFilterInput");
  c.AppendToChain(*filter);
  AddExportImage(c, "GaussianFilterOutput");

  // Add to chain handler owner
  handler_chain.push_back(std::move(filter));
}

void HVEdgeDetector::AddThresholdFilterToChain(Chain& c) {
  // Create filter
  auto filter = std::make_unique<mat::Threshold<uint8_t>>(100, 200);

  // Add filter to chain + exporters (export_image check done by
  // AddExportImage())
  AddExportImage(c, "ThresholdFilterInput");
  c.AppendToChain(*filter);
  AddExportImage(c, "ThresholdFilterOutput");

  // Add to chain handler owner
  handler_chain.push_back(std::move(filter));
}

void HVEdgeDetector::AddEdgeDetectionFilterToChain(Chain& c) {
  // Create filters
  auto x_filter =
      std::make_unique<mat::Filter<uint8_t, int8_t>>(mat::kSobelX3x3);
  auto y_filter =
      std::make_unique<mat::Filter<uint8_t, int8_t>>(mat::kSobelY3x3);

  // Split the chain, thus the H and V filters get a copy
  auto chain_split = std::make_unique<
      util::ChainableObjectReceiverSplit<const mat::Mat2D<uint8_t>&>>(
      *y_filter);

  // Add input image export
  AddExportImage(c, "EdgeDetectionFilterInput");

  // The chain splitter will forward it to the y_filter
  c.AppendToChain(*chain_split);
  c.AppendToChain(*x_filter);

  // Add output image export
  AddExportImage(c, "EdgeDetectionFilterOutput_X");
  AddExportImage(*y_filter, "EdgeDetectionFilterOutput_Y");

  // Add to chain handler owner
  handler_chain.push_back(std::move(x_filter));
  handler_chain.push_back(std::move(chain_split));
  handler_chain.push_back(std::move(y_filter));
}

}  // namespace video_detect
