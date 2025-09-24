cmake_minimum_required(VERSION 3.10)

project(cpp-opencl-cube)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)
include_directories(src)

# Find OpenCL
find_package(OpenCL REQUIRED)

# Find GLFW
find_package(GLFW REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/renderer.cpp
    src/cl_manager.cpp
)

# Add executable
add_executable(cpp-opencl-cube ${SOURCES})

# Link libraries
target_link_libraries(cpp-opencl-cube ${OPENCL_LIBRARIES} ${GLFW_LIBRARIES})