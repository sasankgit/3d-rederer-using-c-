#ifndef CL_MANAGER_H
#define CL_MANAGER_H

#include <CL/cl.h>
#include <vector>

class CLManager {
public:
    CLManager();
    ~CLManager();

    void initialize();
    void createBuffers();
    void executeKernel(float angle);

private:
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;

    std::vector<float> vertexData;
    size_t bufferSize;
};

#endif // CL_MANAGER_H