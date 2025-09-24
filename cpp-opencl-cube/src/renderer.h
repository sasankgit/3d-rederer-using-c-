#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>
#include <OpenCL/cl.h>
#include <vector>
#include "math_utils.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void initialize(int width, int height);
    void render();
    void update(float deltaTime);
    void cleanup();

private:
    GLFWwindow* window;
    std::vector<float> vertexData;
    float rotationAngleX;
    float rotationAngleY;

    void setupVertexData();
    void handleInput();
};

#endif // RENDERER_H