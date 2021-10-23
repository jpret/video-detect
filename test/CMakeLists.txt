# Set CMake requirements
cmake_minimum_required(VERSION 3.12.0)

# List sources
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cc")

# Create the executable
add_executable(${PROJECT_NAME}_test ${sources})

# Set output directories
set_target_properties( ${PROJECT_NAME}_test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link GTest
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)