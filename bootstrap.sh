#!/usr/bin/env bash 

# Setup cmake to use vcpkg dependency manager
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake

# Build
cd build
cmake -DBUILD_TESTS=ON ..
make

# Run tests
make test
