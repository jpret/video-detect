# Set CMake requirements
cmake_minimum_required(VERSION 3.12.0)

# Set project name & version
project(video-detect VERSION 1.0)

# Specify the c++ standard version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directories
include_directories(include)

# Add the required sub-directories
add_subdirectory(src)

# Set testing option
option(BUILD_TESTS "Build tests" OFF)

# Only build tests if instructed to do so
if (BUILD_TESTS) 
    # Find packages
    find_package(GTest CONFIG REQUIRED)

    # add testing subdirectory
    add_subdirectory(test)

    # Enable testing
    enable_testing()

    # add test to enable use of make test
    add_test(${PROJECT_NAME}_test ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}_test)
endif()