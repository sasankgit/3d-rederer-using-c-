#include <iostream>
#include <GLFW/glfw3.h>
#include <CL/cl.hpp>
#include "renderer.h"
#include "cl_manager.h"

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenCL Rotating Cube", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize OpenCL
    CLManager clManager;
    if (!clManager.initialize()) {
        std::cerr << "Failed to initialize OpenCL" << std::endl;
        return -1;
    }

    // Initialize Renderer
    Renderer renderer;
    if (!renderer.initialize(window, &clManager)) {
        std::cerr << "Failed to initialize Renderer" << std::endl;
        return -1;
    }

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        renderer.update();
        renderer.render();

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup
    renderer.cleanup();
    clManager.cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}