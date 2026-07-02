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
    glViewport(0,0,width,height);

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