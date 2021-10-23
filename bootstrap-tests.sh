#!/usr/bin/env bash 

# Install dependencies
vcpkg install gtest

# Setup cmake to use vcpkg dependency manager
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/usr/vcpkg/scripts/buildsystems/vcpkg.cmake

# Build
cd build
cmake -DBUILD_TESTS=ON ..
make
make test
