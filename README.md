# video-detect
#### A C++ program analyzing video frames
This program uses image detection to identify the video size frames in a video grid such as in a video call.

[![Docker Image CI](https://github.com/cppengineer/video-detect/actions/workflows/docker-image.yml/badge.svg)](https://github.com/cppengineer/video-detect/actions/workflows/docker-image.yml)

## Quick Started
The quickest way to get started is to use the readily available docker image on docker hub as follows:
```sh
#
# video-detect quick start with docker
#
docker run \   # Initiate the docker container run command
       --rm \  # Cleanup the container afterwards
       -it \   # Run docker interactively in your CLI
       -v '/local/share/':'/container/share' \ # Create a volume to 
                                # share the specified folder with the
                                # target one in the container
       -t cppengineer/video-detect:latest \ # Docker will pull 
                                            # the latest image from docker hub
       --help # Add video-detect arguments here
```

# System Requirements

## C++ Standard
The C++ standard used for this project is:
+ C++14

## Operating Systems
This project has been tested on the following operating system(s):
+ Linux (Ubuntu)

## Compilers
The compiler(s) supported and tested include:
+ GNU GCC 11.2.0

## Build System(s)
The following build system(s) is used:
+ CMake 3.18.4 & GNU Make 4.3

## Debugger
The following debugger was tested:
+ GNU GDB 10.1.90

## Unit Tests
The following test framework was used for the unit tests:
+ Google Test Framework release-1.10.0

# Build
A build from sources are done as follows:
```sh
# From the source root directory
cmake -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
cmake --build build -t test
cmake --build build -t install
```
The available cmake options are:
+ Build unit tests: `BUILD_TESTING=[ON|OFF]`. Default is **OFF**
+ Check styles *(only if BUILD_TESTING=ON)*: `CHECK_STYLES=[ON|OFF]`. Default is **ON**
+ Build type: `CMAKE_BUILD_TYPE=[Release|Debug]`. Default is **Debug**

# Build Pipeline
This project uses a github workflow for building and deploying the docker image to docker hub. The latest build status is shown in the tag above.


# Contact
You can contact me through the contact page at [Cpp::Engineer](https://cppengineer.com)
