/**
 * MIT License Copyright (c) 2021 CppEngineer
 */

#ifndef VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPTIONS_H_
#define VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPTIONS_H_

#include <functional>
#include <map>
#include <string>

namespace video_detect {

/**
 * @brief The Options class is responsible for parsing the command line
 * arguments into the necessary program options
 *
 */
class Options {
 public:
  /**
   * @brief Construct a new Options object
   *
   */
  Options();

  /**
   * @brief Parse the command line arguments
   *
   * @param argc the commandline argument count as provided by main()
   * @param argv the commandline arguments as provided by main()
   * @return true if parsing was successful
   * @return false if parsing was unsuccessful
   */
  bool Parse(int argc, const char *argv[]);

  // Normal option getters
  const std::string &GetFileInput() const;
  const std::string &GetOutputPath() const;
  bool IsExportImages() const;
  const int GetFrameModulo() const;
  const int GetConfidenceLevel() const;

 private:
  std::string file_input_;
  std::string output_path_;
  int frame_modulo_;
  int confidence_level_;
  const std::map<std::string, std::string> options_;
  std::map<const char *, std::function<void(const std::string &)>>
      option_handlers_;

  /**
   * @brief Print the application help documentation
   *
   */
  void PrintHelp();

  void HandleFileInput(const std::string &value);
  void HandleOutputPath(const std::string &value);
  void HandleFrameModulo(const std::string &value);
  void HandleConfidenceLevel(const std::string &value);
  [[noreturn]] void HandleHelp(const std::string &value);
  [[noreturn]] void HandleVersion(const std::string &value);
};

}  // namespace video_detect

#endif  // VIDEO_DETECT_INCLUDE_VIDEO_DETECT_OPTIONS_H_
