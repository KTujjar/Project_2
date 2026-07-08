cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to an optimized build: the O(n^2) force loop is ~20x slower at -O0.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

project(Project2)

add_executable(MyProgram)

target_include_directories(MyProgram PRIVATE src)
find_package(glm REQUIRED)
# --- glad: compile the generated loader as a static lib ---
add_library(glad STATIC third_party/glad/src/gl.c)
target_include_directories(glad PUBLIC third_party/glad/include)

# --- glfw: found via its CMake config, like glm ---
find_package(glfw3 REQUIRED)

# --- link everything into the app ---
target_link_libraries(MyProgram PRIVATE glm::glm glfw glad)

# Bake the absolute path to the shader sources into the binary so it runs
# from any working directory (dev convenience; a shipping app would copy
# shaders next to the executable instead).
target_compile_definitions(MyProgram PRIVATE SHADER_DIR="${CMAKE_SOURCE_DIR}/shaders")

target_sources(MyProgram
    PRIVATE
        src/app/main.cpp
        src/physics/nbody.cpp
        src/renderer/window.cpp
        src/renderer/shader.cpp
        src/renderer/camera.cpp
        src/renderer/particle_renderer.cpp
)