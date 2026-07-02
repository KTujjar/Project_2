#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

// Owns a GLFW window plus its OpenGL 3.3 core context. Because it owns a
// resource (the GLFWwindow* handle), this is a class with an invariant to
// protect — unlike the plain-data Particle struct.
class Window {
public:
    // Create the window and a current GL 3.3 core context, then load glad.
    // Does the full init sequence in order: glfwInit -> window hints ->
    // glfwCreateWindow -> glfwMakeContextCurrent -> gladLoadGL -> glViewport.
    // Should report/handle failure if init or window creation fails.
    Window(int width, int height, const char* title);

    // Destroy the window and shut GLFW down (glfwDestroyWindow + glfwTerminate).
    ~Window();

    // True once the user has asked to close the window (clicked X, etc.).
    // The render loop runs while this is false.
    bool should_close() const;

    // End-of-frame step: present the rendered image (glfwSwapBuffers) and
    // process pending input/OS events (glfwPollEvents).
    void swap_and_poll();

private:
    GLFWwindow* handle;   // the underlying GLFW window/context (owned)
    int width;
    int height;
};
