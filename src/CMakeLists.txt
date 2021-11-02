# Set CMake requirements
cmake_minimum_required(VERSION 3.12.0)

# Find FMPEG libraries
find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec)

find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
find_library(AVFORMAT_LIBRARY avformat)

find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h)
find_library(AVUTIL_LIBRARY avutil)

find_path(AVDEVICE_INCLUDE_DIR libavdevice/avdevice.h)
find_library(AVDEVICE_LIBRARY avdevice)

# List sources
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cc")

# Create the executable
add_executable(${PROJECT_NAME} ${sources})

# Add include directories
target_include_directories(${PROJECT_NAME} 
                            PRIVATE 
                            ${AVCODEC_INCLUDE_DIR} 
                            ${AVFORMAT_INCLUDE_DIR} 
                            ${AVUTIL_INCLUDE_DIR} 
                            ${AVDEVICE_INCLUDE_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} 
                        PRIVATE 
                        ${AVCODEC_LIBRARY} 
                        ${AVFORMAT_LIBRARY} 
                        ${AVUTIL_LIBRARY} 
                        ${AVDEVICE_LIBRARY})

# Set output directories
set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)