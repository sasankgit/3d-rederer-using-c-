# cpp-opencl-cube

This project is a simple OpenCL-based application that renders a rotating cube using GPU acceleration. It utilizes a graphics library for window management and OpenCL for parallel computation of vertex positions.

## Project Structure

- **src/**: Contains the source code files.
  - **main.cpp**: Entry point of the application, initializes OpenCL and manages the rendering loop.
  - **renderer.cpp**: Implements the `Renderer` class for drawing the cube.
  - **renderer.h**: Header file for the `Renderer` class.
  - **cl_manager.cpp**: Implements the `CLManager` class for OpenCL setup and memory management.
  - **cl_manager.h**: Header file for the `CLManager` class.

- **kernels/**: Contains OpenCL kernel files.
  - **cube_kernel.cl**: OpenCL kernel code for rendering the cube.

- **include/**: Contains header files for utility functions.
  - **math_utils.h**: Provides mathematical operations for rendering calculations.

- **extern/**: Contains documentation for external libraries used in the project.
  - **README.md**: Information about libraries like GLFW or SDL.

- **CMakeLists.txt**: Configuration file for building the project with CMake.

- **.gitignore**: Specifies files to be ignored by Git.

- **LICENSE**: Licensing information for the project.

## Setup Instructions

1. **Clone the repository**:
   ```
   git clone <repository-url>
   cd cpp-opencl-cube
   ```

2. **Install dependencies**:
   Ensure you have the necessary libraries installed, such as OpenCL and a graphics library (GLFW or SDL).

3. **Build the project**:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the application**:
   ```
   ./cpp-opencl-cube
   ```

## Usage

Once the application is running, you will see a window displaying a rotating cube. You can interact with the cube using keyboard inputs (if implemented in the renderer).

## License

This project is licensed under the MIT License. See the LICENSE file for more details.