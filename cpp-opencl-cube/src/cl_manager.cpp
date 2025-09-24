#include "cl_manager.h"
#include <CL/cl.h>
#include <iostream>
#include <vector>

CLManager::CLManager() : context(nullptr), commandQueue(nullptr), program(nullptr), device(nullptr) {}

CLManager::~CLManager() {
    cleanup();
}

bool CLManager::initialize() {
    cl_uint numPlatforms;
    cl_platform_id platform;

    // Get the number of OpenCL platforms
    clGetPlatformIDs(1, &platform, &numPlatforms);
    if (numPlatforms == 0) {
        std::cerr << "No OpenCL platforms found." << std::endl;
        return false;
    }

    // Get the first available device
    cl_uint numDevices;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &numDevices);
    if (numDevices == 0) {
        std::cerr << "No GPU devices found." << std::endl;
        return false;
    }

    // Create an OpenCL context
    context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, nullptr);
    if (!context) {
        std::cerr << "Failed to create OpenCL context." << std::endl;
        return false;
    }

    // Create a command queue
    commandQueue = clCreateCommandQueue(context, device, 0, nullptr);
    if (!commandQueue) {
        std::cerr << "Failed to create command queue." << std::endl;
        return false;
    }

    return true;
}

void CLManager::cleanup() {
    if (commandQueue) {
        clReleaseCommandQueue(commandQueue);
        commandQueue = nullptr;
    }
    if (program) {
        clReleaseProgram(program);
        program = nullptr;
    }
    if (context) {
        clReleaseContext(context);
        context = nullptr;
    }
}

bool CLManager::createBuffers(std::vector<float>& vertexData) {
    // Create buffer for vertex data
    cl_int err;
    cl_mem vertexBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                                         vertexData.size() * sizeof(float), vertexData.data(), &err);
    if (err != CL_SUCCESS) {
        std::cerr << "Failed to create vertex buffer." << std::endl;
        return false;
    }
    return true;
}

bool CLManager::executeKernel(const std::string& kernelSource) {
    cl_int err;

    // Create program from kernel source
    const char* source = kernelSource.c_str();
    program = clCreateProgramWithSource(context, 1, &source, nullptr, &err);
    if (err != CL_SUCCESS) {
        std::cerr << "Failed to create program." << std::endl;
        return false;
    }

    // Build the program
    err = clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
    if (err != CL_SUCCESS) {
        std::cerr << "Failed to build program." << std::endl;
        return false;
    }

    // Create kernel
    cl_kernel kernel = clCreateKernel(program, "cubeKernel", &err);
    if (err != CL_SUCCESS) {
        std::cerr << "Failed to create kernel." << std::endl;
        return false;
    }

    // Execute kernel (add appropriate arguments and dimensions)
    // clEnqueueNDRangeKernel(commandQueue, kernel, 1, nullptr, &globalWorkSize, &localWorkSize, 0, nullptr, nullptr);

    // Cleanup
    clReleaseKernel(kernel);
    return true;
}