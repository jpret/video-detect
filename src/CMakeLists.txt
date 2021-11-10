# Set CMake requirements
cmake_minimum_required(VERSION 3.12.0)

# Find FMPEG libraries
find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec REQUIRED)

find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
find_library(AVFORMAT_LIBRARY avformat REQUIRED)

find_path(SWSCALE_INCLUDE_DIR libswscale/swscale.h)
find_library(SWSCALE_LIBRARY swscale REQUIRED)

# Find package(s)
find_package( OpenCV REQUIRED )

# List sources
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cc")

# Set the include directories
set(include_directories 
        ${AVCODEC_INCLUDE_DIR} 
        ${AVFORMAT_INCLUDE_DIR} 
        ${SWSCALE_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS})

# Set the link libraries
set(link_libraries 
        ${AVCODEC_LIBRARY} 
        ${AVFORMAT_LIBRARY} 
        -lavutil
        ${SWSCALE_LIBRARY}
        ${OpenCV_LIBS})

# Create the executable
add_executable(${PROJECT_NAME} ${sources})

# Add Threads
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(${PROJECT_NAME} PUBLIC "-pthread")
endif()

# Add include directories
target_include_directories(${PROJECT_NAME} 
                            PRIVATE ${include_directories} ${PROJECT_SOURCE_DIR}/include)

# Make version available for the program
target_compile_definitions(${PROJECT_NAME} PRIVATE VIDEO_DETECT_VERSION=${PROJECT_VERSION})

# Link libraries
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(${PROJECT_NAME}  
                          PUBLIC "${CMAKE_THREAD_LIBS_INIT}"
                          PRIVATE ${link_libraries})
else()
    target_link_libraries(${PROJECT_NAME}
                          PRIVATE ${link_libraries})
endif()


# Set output directories
set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Install rules for the executable
install(TARGETS ${PROJECT_NAME})

# If building tests, create a lib to link to
if (BUILD_TESTING) 

    # Create a library
    add_library(${PROJECT_NAME}_lib SHARED ${sources})

    # Add threads
    if(THREADS_HAVE_PTHREAD_ARG)
        target_compile_options(${PROJECT_NAME}_lib PUBLIC "-pthread")
    endif()

    # Add include directories
    target_include_directories(${PROJECT_NAME}_lib 
                            PRIVATE ${include_directories}
                            PUBLIC ${PROJECT_SOURCE_DIR}/include)

    # Make version available for the library
    target_compile_definitions(${PROJECT_NAME}_lib PRIVATE VIDEO_DETECT_VERSION=${PROJECT_VERSION})

    # Link libraries
    if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(${PROJECT_NAME}_lib  
                        PUBLIC "${CMAKE_THREAD_LIBS_INIT}"
                        PRIVATE ${link_libraries})
    else()
    target_link_libraries(${PROJECT_NAME}_lib
                        PRIVATE ${link_libraries})
    endif()

    # Set output directories
    set_target_properties( ${PROJECT_NAME}_lib
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )

endif()