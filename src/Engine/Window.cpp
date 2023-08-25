#include "Window.h"

#include <iostream>

using namespace std;

namespace MyEngine {

    Window::Window(int width, int height, const char* title)
    {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    }

    Window::~Window()
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    void Window::makeContext(Engine* engine) const
    {
        glfwMakeContextCurrent(window);
        // Initializing GLEW
        engine->initGlew();
    }

    void Window::setVsyncEnabled(bool set) {
        glfwSwapInterval(set);
    }

    GLFWwindow* Window::getWindow() const
    {
        return window;
    }

    int Window::getWindowWidth() const 
    {
        int windowWidth;
        glfwGetWindowSize(window, &windowWidth, nullptr);
        return windowWidth;
    }

    int Window::getWindowHeight() const 
    {
        int windowHeight;
        glfwGetWindowSize(window, nullptr, &windowHeight);
        return windowHeight;
    }

    float Window::getNormalizedX(int x) 
    {
        int windowWidth = getWindowWidth();
        return (2.0f * x) / windowWidth - 1.0f;
    }

    float Window::getNormalizedY(int y) 
    {
        int windowHeight = getWindowHeight();
        return (2.0f * y) / windowHeight - 1.0f;
    }
}
