#include "renderer.h"
#include "cl_manager.h"
#include <GLFW/glfw3.h>
#include <iostream>

Renderer::Renderer(CLManager& clManager) : clManager(clManager), angleX(0.0f), angleY(0.0f) {}

void Renderer::initialize(int width, int height) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window = glfwCreateWindow(width, height, "OpenCL Cube", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    clManager.executeKernel(angleX, angleY);

    // Here you would typically bind the vertex buffer and draw the cube
    // For simplicity, we will just draw a wireframe cube
    glBegin(GL_LINES);
    for (const auto& edge : cubeEdges) {
        for (int i = 0; i < 2; ++i) {
            glVertex3f(cubeVertices[edge[i]].x, cubeVertices[edge[i]].y, cubeVertices[edge[i]].z);
        }
    }
    glEnd();

    glfwSwapBuffers(window);
}

void Renderer::update(float deltaTime) {
    angleX += 50.0f * deltaTime; // Rotate at 50 degrees per second
    angleY += 30.0f * deltaTime; // Rotate at 30 degrees per second
}

bool Renderer::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Renderer::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}