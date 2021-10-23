# Set CMake requirements
cmake_minimum_required(VERSION 3.12.0)

# List sources
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cc")

# Create the executable
add_executable(${PROJECT_NAME} ${sources})