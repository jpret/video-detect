/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/hv_edge_detector.h"

#include <utility>

#include "video-detect/mat/filter.h"
#include "video-detect/mat/kernel_defs.h"
#include "video-detect/opencv2/export_u8_mat_2d.h"
#include "video-detect/util/chainable_object_receiver_split.h"

namespace video_detect {

HVEdgeDetector::HVEdgeDetector(bool export_images,
                               const std::string& export_path) {
  // Setup the conversion chain strategy

  // 1. A Gaussian filter to create a blur
  auto gaussian_filter =
      std::make_unique<mat::Filter<uint8_t, float>>(mat::kKernelGaussian3x3);

  // If the export images flag is set the first export the input + output image
  std::unique_ptr<opencv2::ExportU8Mat2D> hv_detector_input_export;
  std::unique_ptr<opencv2::ExportU8Mat2D> gaussian_filter_output_export;
  if (export_images) {
    hv_detector_input_export = std::make_unique<opencv2::ExportU8Mat2D>(
        "HVEdgeDetectorInput", export_path);
    gaussian_filter_output_export = std::make_unique<opencv2::ExportU8Mat2D>(
        "GaussianFilterOutput", export_path);
    // Add elements to the chain
    hv_detector_input_export->AppendToChain(*gaussian_filter);
    gaussian_filter->AppendToChain(*gaussian_filter_output_export);
  }

  // 2. Horizontal + Vertical line detection filter
  auto hline_filter =
      std::make_unique<mat::Filter<uint8_t, int8_t>>(mat::kKernelHLine3x3);
  auto vline_filter =
      std::make_unique<mat::Filter<uint8_t, int8_t>>(mat::kKernelVLine3x3);

  // 3. Split the chain, thus the H and V filters get a copy from the gaussian
  // filter
  auto chain_split = std::make_unique<
      util::ChainableObjectReceiverSplit<const mat::Mat2D<uint8_t>&>>(
      *vline_filter);

  // 3.1 The VLine filter will split off of the main chain via the chain
  // splitter
  gaussian_filter->AppendToChain(*chain_split);

  // 3.2 The HLine will continue on the current chain
  gaussian_filter->AppendToChain(*hline_filter);

  // If the export images flag is set then export the hline + vline output
  // images
  std::unique_ptr<opencv2::ExportU8Mat2D> h_line_filter_output_export;
  std::unique_ptr<opencv2::ExportU8Mat2D> v_line_filter_output_export;
  if (export_images) {
    h_line_filter_output_export = std::make_unique<opencv2::ExportU8Mat2D>(
        "HLineFilterOutput", export_path);
    v_line_filter_output_export = std::make_unique<opencv2::ExportU8Mat2D>(
        "VLineFilterOutput", export_path);
    // Add elements to the chain - hline on original chain and vline on the
    // split
    gaussian_filter->AppendToChain(*h_line_filter_output_export);
    vline_filter->AppendToChain(*v_line_filter_output_export);
  }

  // 5. Combine the chain
  // TODO(jangabriel): CONTINUE HERE!

  // If export images enabled push back the image export links to the vector
  // owning chain the instances
  if (export_images) {
    handler_chain.push_back(std::move(hv_detector_input_export));
    handler_chain.push_back(std::move(gaussian_filter_output_export));
    handler_chain.push_back(std::move(h_line_filter_output_export));
    handler_chain.push_back(std::move(v_line_filter_output_export));
  }

  // Push the rest of the items to the vector owning the chain instances
  handler_chain.push_back(std::move(gaussian_filter));
  handler_chain.push_back(std::move(hline_filter));
  handler_chain.push_back(std::move(vline_filter));
  handler_chain.push_back(std::move(chain_split));
}

void HVEdgeDetector::Accept(const mat::Mat2D<uint8_t>& img) {
  if (!handler_chain.empty()) {
    handler_chain.front()->Accept(img);
  }
}

}  // namespace video_detect
