#include "renderer/window.h"
#include <stdexcept>
Window::Window(int width, int height, const char* title){
    this->width = width;
    this->height = height;
    if(!glfwInit()){
        throw std::runtime_error("glfwInit failed");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
    GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   // macOS requires this for core
    #endif
    handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if(handle == NULL){
        glfwTerminate();
        throw std::runtime_error("Window Creation Error");
    }
    glfwMakeContextCurrent(handle);
    if(!gladLoadGL(glfwGetProcAddress)){
        glfwTerminate();
        throw std::runtime_error("gladLoadGL failed");
    }
    // The viewport is in framebuffer PIXELS, not window points — on Retina
    // displays the framebuffer is 2x the window size, so query it rather
    // than assuming it matches width/height.
    int fb_width, fb_height;
    glfwGetFramebufferSize(handle, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    // Register `this` with GLFW so the static callbacks can find the object,
    // then hook resize (keeps viewport + aspect correct) and scroll (zoom).
    glfwSetWindowUserPointer(handle, this);
    glfwSetFramebufferSizeCallback(handle, on_resize);
    glfwSetScrollCallback(handle, on_scroll);
}

// Destroy the window and shut GLFW down (glfwDestroyWindow + glfwTerminate).
Window::~Window(){
    glfwDestroyWindow(handle);
    glfwTerminate();
}

// True once the user has asked to close the window (clicked X, etc.).
// The render loop runs while this is false.
bool Window::should_close() const{
    return glfwWindowShouldClose(handle);
}

// End-of-frame step: present the rendered image (glfwSwapBuffers) and
// process pending input/OS events (glfwPollEvents).
void Window::swap_and_poll(){
    glfwSwapBuffers(handle);
    glfwPollEvents();
}

GLFWwindow* Window::native() const{
    return handle;
}

float Window::aspect() const{
    return (float)width / (float)height;
}

float Window::take_scroll(){
    float s = (float)scroll;
    scroll = 0.0;
    return s;
}

void Window::on_resize(GLFWwindow* win, int w, int h){
    Window* self = (Window*)glfwGetWindowUserPointer(win);
    self->width = w;
    self->height = h;
    glViewport(0, 0, w, h);
}

void Window::on_scroll(GLFWwindow* win, double /*dx*/, double dy){
    Window* self = (Window*)glfwGetWindowUserPointer(win);
    self->scroll += dy;
}