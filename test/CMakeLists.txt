# Set CMake requirements
cmake_minimum_required(VERSION 3.12.0)

# Find packages
find_package(GTest CONFIG REQUIRED)
find_package( OpenCV REQUIRED )

# List sources
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cc")

# Create the executable
add_executable(${PROJECT_NAME}_test ${sources})

# Add tests include folder
target_include_directories(${PROJECT_NAME}_test PRIVATE ${PROJECT_SOURCE_DIR}/test/include)

# Set output directories
set_target_properties( ${PROJECT_NAME}_test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link libraries
target_link_libraries(${PROJECT_NAME}_test PRIVATE 
                    GTest::gmock 
                    GTest::gtest 
                    GTest::gmock_main 
                    GTest::gtest_main
                    ${OpenCV_LIBS}
                    ${PROJECT_NAME}_lib)

# add test to enable use of make test for unit tests
add_test(${PROJECT_NAME}_test ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}_test)

# Only check styles if option is set
if (CHECK_STYLES)
    add_custom_command(
        TARGET ${PROJECT_NAME}_test
        POST_BUILD
        COMMAND cpplint --root=.. --linelength=80 --filter=-build/c++11 --exclude=build/* --recursive ./*
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Running style checks...")
endif()