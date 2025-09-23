cmake_minimum_required(VERSION 3.14)
project(SimpleRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell user to provide packages if not found
find_package(OpenGL REQUIRED)
find_package(PkgConfig QUIET)

# Try find glfw3 via find_package or pkg-config
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
  pkg_check_modules(GLFW REQUIRED glfw3)
endif()

# Find GLM
find_package(glm QUIET)
if(NOT glm_FOUND)
  message(STATUS "glm not found via find_package; you can install glm or add it manually.")
endif()

# If GLAD not found, use a local header fallback (user can add glad)
# We'll expect the user to have GLAD headers installed or use package manager.

add_executable(SimpleRenderer main.cpp)

# Link libraries (adjust if your platform uses different names)
target_include_directories(SimpleRenderer PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(SimpleRenderer PRIVATE glfw OpenGL::GL)

# On some systems, link math libs
if(UNIX)
  target_link_libraries(SimpleRenderer PRIVATE dl)
endif()

# If GLM installed, add include dir
if(glm_FOUND)
  target_include_directories(SimpleRenderer PRIVATE ${GLM_INCLUDE_DIRS})
endif()
