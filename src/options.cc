/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#include "video-detect/options.h"

#include <iostream>
#include <algorithm>

namespace video_detect {

Options::Options()
    : options_{
          {{"--help"}, {"\tDisplay the program options"}},
          {{"--version"}, {"Print the program version"}},
          {{"--fmod"},
           {"\t[Optional] Set the frame modulo filter (integer). "
           "E.g. if set to 20 only every 20th frame is processed. "
           "The default is 20."}},
          {{"--infile"}, {"Set the input file full path + name"}},
          {{"--outpath"},
           {"[Optional] Set the output path. If set, the program "
           "will export images of the analyzed frames to this path."}},
          {{"--clevel"},
           {"[Optional] Set a confidence level (not percentage) for frame size "
            "detected(integer). The default is 10."}},
      }, confidence_level_(10), frame_modulo_(20) {
  // Register the option handlers
  option_handlers_.insert(std::make_pair(
      "--help", std::bind(&Options::HandleHelp, this, std::placeholders::_1)));
  option_handlers_.insert(std::make_pair(
      "--version",
      std::bind(&Options::HandleVersion, this, std::placeholders::_1)));
  option_handlers_.insert(std::make_pair(
      "--fmod",
      std::bind(&Options::HandleFrameModulo, this, std::placeholders::_1)));
  option_handlers_.insert(std::make_pair(
      "--infile",
      std::bind(&Options::HandleFileInput, this, std::placeholders::_1)));
  option_handlers_.insert(std::make_pair(
      "--outpath",
      std::bind(&Options::HandleOutputPath, this, std::placeholders::_1)));
  option_handlers_.insert(std::make_pair(
      "--clevel",
      std::bind(&Options::HandleConfidenceLevel, this, std::placeholders::_1)));
}

void Options::PrintHelp() {
  std::cout << "*******************************************" << std::endl;
  std::cout << "  CppEngineer: Video Detect, v. " << VIDEO_DETECT_VERSION
            << " HELP" << std::endl;
  std::cout << "*******************************************" << std::endl;
  for (auto &option : options_) {
    std::cout << option.first << "\t" << option.second << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Example usage: " << std::endl;
  std::cout << "video-detect";
  std::cout << " --infile /share/sample-4x4.mp4";
  std::cout << " --fmod 20";
  std::cout << " --outpath /share";
  std::cout << " --clevel 10\n" << std::endl;
  std::cout << "*******************************************" << std::endl;
}

bool Options::Parse(int argc, const char *argv[]) {
  bool result = false;

  // Go through each option and parse it
  for (int i = 1; i < argc; i++) {
    const std::string arg = argv[i];
    auto it = options_.find(arg);

    // See if the option is available and if there is another argument following
    // the option
    if (it != options_.end()) {
      // Save the argument
      std::string value;
      if (i + 1 < argc) {
        value = argv[i + 1];
      }

      // Get the option handler and call it
      auto func = std::find_if(
          option_handlers_.begin(), option_handlers_.end(),
          [arg](const std::pair<const char *,
                                std::function<void(const std::string &)>>
                    &option) { return arg == option.first; });
      // Call the option handler
      if (func != option_handlers_.end()) {
        func->second(value);
      } else {
        std::cout << "Invalid option: " << argv[i]
                  << ", See \'video-detect "
                     "--help\' for more information"
                  << std::endl;
        exit(EXIT_FAILURE);
      }

      // Increase the loop counter (thus, reading two args in one-loop)
      ++i;
    }
  }

  // Ensure we have sufficient information to continue with the program
  if (file_input_.empty() || frame_modulo_ <= 0 || confidence_level_ <= 0) {
    std::cout << "Not all arguments have been provided. See \'video-detect "
                 "--help\' for more information"
              << std::endl;
    exit(EXIT_FAILURE);
  } else {
    result = true;
  }

  return result;
}

void Options::HandleFileInput(const std::string &value) { file_input_ = value; }

void Options::HandleOutputPath(const std::string &value) {
  output_path_ = value;
}

void Options::HandleFrameModulo(const std::string &value) {
  try {
    frame_modulo_ = std::stoi(value);
  } catch (std::exception &e) {
    std::cerr << "Invalid integer conversion: " << value
              << ", error: " << e.what() << std::endl;
  }
}

void Options::HandleConfidenceLevel(const std::string &value) {
  try {
    confidence_level_ = std::stoi(value);
  } catch (std::exception &e) {
    std::cerr << "Invalid integer conversion: " << value
              << ", error: " << e.what() << std::endl;
  }
  if (confidence_level_ == 0) {
    std::cout << "Invalid confidence level: " << value << std::endl;
    std::cout << "Choose an integer value larger than zero" << std::endl;
  }
}

void Options::HandleHelp(const std::string &value) {
  // Print the help section and exit
  PrintHelp();
  exit(EXIT_SUCCESS);
}

void Options::HandleVersion(const std::string &value) {
  // Print the version and exit
  std::cout << "CppEngineer: Video Detect, v. " << VIDEO_DETECT_VERSION;
  exit(EXIT_SUCCESS);
}

const std::string &Options::GetFileInput() const { return file_input_; }
const std::string &Options::GetOutputPath() const { return output_path_; }
bool Options::IsExportImages() const { return !output_path_.empty(); }
const int Options::GetFrameModulo() const { return frame_modulo_; }
const int Options::GetConfidenceLevel() const { return confidence_level_; }

}  // namespace video_detect
