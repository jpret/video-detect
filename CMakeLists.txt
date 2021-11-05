# Set CMake requirements
cmake_minimum_required(VERSION 3.12.0)

# Set project name & version
project(video-detect VERSION 1.0)

# Specify the c++ standard version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set target compile options
add_compile_options("-Wno-deprecated-declarations")

# Set options
option(CHECK_STYLES "Style Checks" OFF)
option(BUILD_TESTS "Build tests" OFF)

# Add the required sub-directories
add_subdirectory(src)

# Only build tests if instructed to do so
if (BUILD_TESTS) 

    # Enable testing
    enable_testing()

    # Add testing subdirectory
    add_subdirectory(test)

endif()