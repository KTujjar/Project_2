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

    // Raw GLFW handle, for input polling (mouse buttons / cursor) in main.
    GLFWwindow* native() const;

    // Current width/height ratio for the camera's projection. Kept fresh by
    // the resize callback.
    float aspect() const;

    // Scroll wheel movement accumulated since the last call; calling it
    // resets the accumulator to zero ("take", not "peek").
    float take_scroll();

private:
    // GLFW callbacks are plain C function pointers, so they can't be regular
    // member functions — static ones + glfwSetWindowUserPointer bridge back
    // to `this`.
    static void on_resize(GLFWwindow* win, int w, int h);
    static void on_scroll(GLFWwindow* win, double dx, double dy);

    GLFWwindow* handle;   // the underlying GLFW window/context (owned)
    int width;
    int height;
    double scroll = 0.0;  // accumulated wheel movement since take_scroll()
};
