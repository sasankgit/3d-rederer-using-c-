# External Libraries Used in the Project

This project utilizes several external libraries to facilitate the rendering of a rotating cube using OpenCL for GPU acceleration. Below is a list of the key libraries and their purposes:

## GLFW
- **Description**: GLFW is an open-source library for creating windows with OpenGL contexts and managing input.
- **Usage**: It is used to create the window for rendering the cube and handle user input events.

## OpenCL
- **Description**: OpenCL (Open Computing Language) is a framework for writing programs that execute across heterogeneous platforms, including CPUs and GPUs.
- **Usage**: OpenCL is used to accelerate the rendering process by offloading computations to the GPU, allowing for efficient processing of vertex data.

## CMake
- **Description**: CMake is a cross-platform build system generator.
- **Usage**: It is used to manage the build process of the project, specifying the necessary libraries and include directories.

## Additional Notes
- Ensure that you have the necessary development packages for GLFW and OpenCL installed on your system.
- Refer to the project's `CMakeLists.txt` for instructions on how to build the project and link the required libraries.